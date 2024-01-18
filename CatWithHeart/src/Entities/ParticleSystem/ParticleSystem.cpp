#include "ParticleSystem.h"

#include <iostream>
#include "../Click/Click.h"

#include "../../Tools/EventManager/EventManager.h"
#include "../../Utilities/Context/Context.h"


ParticleSystem::ParticleSystem(GenerationPosition generationPosition)
	: generationPosition(generationPosition)
{	}

void ParticleSystem::GenerateUnit()
{
	static sf::Clock clock;
	static sf::Time lastGeneration = sf::Time::Zero;
	lastGeneration += clock.restart();

	if (lastGeneration < timeBetween && !units.empty()) // We cann't generate one more unit.
	{
		return;
	}

	if (units.size() == maxCountOfElements) // The vector is full, so we find dead element.
	{
		ResurrectUnit();
	}
	else // Vector is not full, so we create a new unit.
	{
		CreateNewUnit();
	}

	lastGeneration = sf::Time::Zero;
}

void ParticleSystem::CreateNewUnit()
{
	Unit unit(new Click(sf::Vector2f()), Properties(sf::Time::Zero, true));

	unit.first->setScale(1.3f, 1.3f);
	unit.first->setOrigin(unit.first->GetOriginSize().x / 2.f, unit.first->GetOriginSize().y / 2.f);
	unit.first->setRotation(random.GetRandomRealNumber(rotationAngles));

	SetUnitPosition(unit);

	units.push_back(std::move(unit));
}

void ParticleSystem::ResurrectUnit()
{
	auto resurrectUnit = std::find_if(units.begin(), units.end(), [](const Unit& unit) -> bool {
		return unit.second.second == false;
	});

	if (resurrectUnit == units.end()) // We don't have any dead unit.
	{
		return;
	}

	// Reset data for the unit if we found it.
	resurrectUnit->first->SetAnimationState();
	resurrectUnit->second = Properties(sf::Time::Zero, true);
	SetUnitPosition(*resurrectUnit);
}

void ParticleSystem::SetUnitPosition(Unit& unit)
{
	if (generationPosition == GenerationPosition::InBorders)
	{
		unit.first->setPosition(random.GetRandomRealNumber(borders.left, borders.left + borders.width), // Generate x cord.
							    random.GetRandomRealNumber(borders.top, borders.top + borders.height)); // Genarate y cord.
	}
	else if (generationPosition == GenerationPosition::UnderCursor)
	{
		sf::Vector2i cursorPos = EventManager::GetMousePos(Context::GetInstance().window);
		unit.first->setPosition(cursorPos.x * 1.f, cursorPos.y * 1.f);
	}
}

void ParticleSystem::Update(sf::Time deltaTime)
{
	for (auto& unit : units)
	{
		RemoveDeadUnit(unit);
		if (unit.second.second) // If unit alive.
		{
			unit.first->Update(deltaTime);
			unit.second.first += deltaTime;
		}
	}
}

void ParticleSystem::RemoveDeadUnit(Unit& unit)
{
	// Here we chack if unit time is more than life time.
	if (unit.second.first >= lifeTime) // The life of unit ends.
	{
		// Reset vaules for the unit.
		unit.second = std::move(Properties(sf::Time::Zero, false));
	}
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{	
	std::for_each(units.begin(), units.end(), [&target, states](Unit const& unit) {
		if (unit.second.second) // Unit is alive.
		{
			target.draw(*unit.first, states);
		}
	});
}

void ParticleSystem::SetMaxCountOfElemnt(uint32_t maxCountOfElements)
{
	this->maxCountOfElements = maxCountOfElements;
	this->units.reserve(maxCountOfElements);
}

void ParticleSystem::SetLifeTime(sf::Time lifeTime)
{
	this->lifeTime = lifeTime;
}

void ParticleSystem::SetBetweenTime(sf::Time betweenTime)
{
	this->timeBetween = betweenTime;
}

void ParticleSystem::SetRotationAngles(RangeF rotationAngles)
{
	this->rotationAngles = rotationAngles;
}

void ParticleSystem::SetGeneretionBorders(const sf::FloatRect& borders)
{
	this->borders = borders;
}
