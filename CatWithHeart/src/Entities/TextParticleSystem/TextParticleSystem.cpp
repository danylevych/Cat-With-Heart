#include "TextParticleSystem.h"

void TextParticleSystem::GenerateUnit(const std::string& text)
{
	static sf::Clock clock;
	static sf::Time lastGeneration = sf::Time::Zero;
	lastGeneration += clock.restart();

	if (lastGeneration < timeBetween && !texts.empty()) // We cann't generate one more unit.
	{
		return;
	}

	if (texts.size() == maxCountOfElements) // The vector is full.
	{
		return;
	}
	
	Unit unit(new sf::Text(), sf::Time::Zero);
	unit.first->setString(text);
	unit.first->setFont(font);
	unit.first->setScale(startScale, startScale);
	unit.first->setFillColor(sf::Color(color.r, color.g, color.b, static_cast<sf::Uint8>(random.GetRandomNumber(opasities))));
	unit.first->setCharacterSize(random.GetRandomNumber(fontSizes));
	unit.first->setRotation(random.GetRandomRealNumber(rotationAngles));
	unit.first->setPosition(random.GetRandomRealNumber(borders.left, borders.left + borders.width), // Generate x cord.
							random.GetRandomRealNumber(borders.top, borders.top + borders.height)); // Genarate y cord.
	texts.push_back(std::move(unit));
	
	lastGeneration = sf::Time::Zero;
}

void TextParticleSystem::Update(sf::Time deltaTime)
{
	//RemoveOldUnit();
	//AnimateUnit();
	//UpdateUnitTime(deltaTime);
}

void TextParticleSystem::AnimateUnit()
{
	const float FINISH_SCALE = 1.f;
	const float SIZE_MULTIPLAYER = FINISH_SCALE / animTime.asSeconds();

	for (auto& unit : texts)
	{
		float progress = unit.second.asSeconds() / animTime.asSeconds();

		if (unit.second <= animTime) // We paly anim.
		{
			// Interpolation of the scale.
			sf::Vector2f scale = unit.first->getScale();
			scale.x = scale.y = FINISH_SCALE + progress * (FINISH_SCALE - scale.x);
			unit.first->setScale(scale);
		}
	}
}

void TextParticleSystem::RemoveOldUnit()
{
	for (size_t i = 0; i < texts.size(); i++)
	{
		if (texts[i].second >= lifeTime) // The life of unit ends.
		{
			texts.erase(texts.begin() + i);
		}
	}
}

void TextParticleSystem::UpdateUnitTime(sf::Time deltaTime)
{
	for (auto& unit : texts)
	{
		unit.second += deltaTime;
	}
}

void TextParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& unit : texts)
	{
		target.draw(*unit.first, states);
	}
}

void TextParticleSystem::SetMaxCountOfElemnt(uint32_t maxCountOfElements)
{
	this->maxCountOfElements = maxCountOfElements;
	this->texts.reserve(maxCountOfElements);
}

void TextParticleSystem::SetLifeTime(sf::Time lifeTime)
{
	this->lifeTime = lifeTime;
}

void TextParticleSystem::SetAnimTime(sf::Time animTime)
{
	this->animTime = animTime;
}

void TextParticleSystem::SetBetweenTime(sf::Time betweenTime)
{
	this->timeBetween = betweenTime;
}

void TextParticleSystem::SetFontSizeRange(RangeI fontSizes)
{
	this->fontSizes = fontSizes;
}

void TextParticleSystem::SetRotationAngles(RangeF rotationAngles)
{
	this->rotationAngles = rotationAngles;
}

void TextParticleSystem::SetGeneretionBorders(const sf::FloatRect& borders)
{
	this->borders = borders;
}

void TextParticleSystem::SetFont(const sf::Font& font)
{
	this->font = font;
}

void TextParticleSystem::SetColor(sf::Color color)
{
	this->color = color;
}

void TextParticleSystem::SetColorsOpasities(RangeI opasities)
{
	this->opasities = opasities;
}
