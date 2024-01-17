#include "GameState.h"

#include <iostream>


GameState::GameState(StateStack& stack, Context& context)
	: State(stack, context)
	, textParticleSystem()
	, reader("data/texts/labels.txt")
	, cat(sf::Vector2f())
	, heart(sf::Vector2f())
	, heartTraectory()
{
	InitSpawnPos();
	InitBindedKeys();
	InitTextGenerator();
}

void GameState::Draw()
{
	sf::RenderWindow& window = context->window;

	window.draw(textParticleSystem);
	window.draw(cat);
	window.draw(heart);
}

void GameState::Update(sf::Time deltaTime)
{
	eventManager.HandleRealTimeInput();

	textParticleSystem.Update(deltaTime);
	cat.Update(deltaTime);
	heart.Update(deltaTime);
}

void GameState::HandleInput(const sf::Event& event)
{
	eventManager.HandleInput(event);
}

void GameState::InitSpawnPos()
{
	// Set all elements in position we need.
	float centerX = context->window.getSize().x / 2.f;
	float centerY = context->window.getSize().y / 2.f;

	cat.setOrigin(cat.GetOriginSize().x / 2.f, cat.GetOriginSize().y / 2.f);
	cat.setScale(4.5f, 4.5f);
	cat.setPosition(centerX, centerY);

	heart.setOrigin(heart.GetOriginSize().x / 2.f, heart.GetOriginSize().y / 2.f);
	heart.setScale(3.4f, 3.4f);
	heart.SetStartAnimeScale(3.4f);
	heart.SetZoomedAnimeScale(3.7f);
	heart.setPosition(centerX, centerY + 70);

	// Set the traectory of the heart.
	heartTraectory.setFillColor(sf::Color::White);
	heartTraectory.setRadius(15);
	heartTraectory.setOrigin(heartTraectory.getRadius(), heartTraectory.getRadius());
	heartTraectory.setPosition(centerX, heart.getPosition().y - heartTraectory.getRadius());
}

void GameState::InitBindedKeys()
{
	// Bind the real time events.
	eventManager.BindRealTimeKey(sf::Mouse::Left, [this]() {
		std::cout << "I am work" << std::endl;
		std::string str = reader[Random<size_t>().GetRandomNumber(0, reader.GetCountOfLines())];
		textParticleSystem.GenerateUnit(str);
	});

	eventManager.BindRealTimeKey(EventManager::Actions::EveryFrame, [this]() {
		// Calculate the new position of heart.
		sf::Vector2i pos = EventManager::GetMousePos(context->window);
		sf::Vector2f circlePos = heartTraectory.getPosition();

		float dx = pos.x - circlePos.x;
		float dy = pos.y - circlePos.y;

		float rotationRad = atan2(dy, dx);

		float newPosX = std::cos(rotationRad) * heartTraectory.getRadius();
		float newPosY = std::sin(rotationRad) * heartTraectory.getRadius();

		heart.setPosition(newPosX + heartTraectory.getPosition().x,
			              newPosY + heartTraectory.getPosition().y);
	});
}

void GameState::InitTextGenerator()
{
	textParticleSystem.SetMaxCountOfElemnt(25);

	textParticleSystem.SetFont(*context->fonts.Get(FontID::Main).get());
	textParticleSystem.SetColor(sf::Color::Red);
	textParticleSystem.SetRotationAngles(RangeF{ -45.f, 45.f });
	textParticleSystem.SetFontSizeRange(RangeI{ 25, 60 });
	textParticleSystem.SetColorsOpasities(RangeI{ 25, 200 });

	sf::Vector2f viewSixe = context->window.getDefaultView().getSize();
	textParticleSystem.SetGeneretionBorders(sf::FloatRect(sf::Vector2f(0.f, 0.f), viewSixe));

	textParticleSystem.SetAnimTime(sf::seconds(0.5f));
	textParticleSystem.SetBetweenTime(sf::seconds(0.15f));
	textParticleSystem.SetLifeTime(sf::seconds(12.f));
}
