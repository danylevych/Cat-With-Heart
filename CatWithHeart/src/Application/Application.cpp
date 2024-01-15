#include "Application.h"

#include <iostream>
#include <SFML/Graphics/Color.hpp>


Application::Application()
	: window(sf::VideoMode(800, 600), "The most cutiest app", sf::Style::Close)
	, eventManager(&EventManager::GetInstance())
	, icon()
	, backgroundMusic()
	, textParticleSystem()
	, reader("data/texts/labels.txt")
	, font()
	, cat(sf::Vector2f())
	, heart(sf::Vector2f())
	, heartTraectory()
{
	InitBindedKeys();
	InitResources();
	InitSpawnPos();
	InitTextGenerator();

	// Set the icon for the window.
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Application::InitSpawnPos()
{
	// Set all elements in position we need.
	float centerX = window.getSize().x / 2.f;
	float centerY = window.getSize().y / 2.f;

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

void Application::InitResources()
{
	if (!icon.loadFromFile("data/icon/heart.png"))
	{
		std::cerr << "Opening the icon file was failed" << std::endl;
	}

	if (!font.loadFromFile("data/fonts/Lemon-Regular.ttf"))
	{
		std::cerr << "Opening the font file was failed" << std::endl;
	}

	if (backgroundMusic.openFromFile("data/audio/background.ogg"))
	{
		backgroundMusic.setLoop(true);
		backgroundMusic.play();
	}
}

void Application::InitBindedKeys()
{
	// Bind the static events.
	eventManager->BindKey(sf::Event::Closed, [this]() { window.close(); });

	// Bind the real time events.
	eventManager->BindRealTimeKey(sf::Mouse::Left, [this]() {
		std::string str = reader[Random<size_t>().GetRandomNumber(0, reader.GetCountOfLines())];
		textParticleSystem.GenerateUnit(str);
	});

	eventManager->BindRealTimeKey(EventManager::Actions::EveryFrame, [this](){
		// Calculate the new position of heart.
		sf::Vector2i pos = EventManager::GetMousePos(window);
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

void Application::InitTextGenerator()
{
	textParticleSystem.SetMaxCountOfElemnt(25);

	textParticleSystem.SetFont(font);
	textParticleSystem.SetColor(sf::Color::Red);
	textParticleSystem.SetRotationAngles(RangeF{ -45.f, 45.f });
	textParticleSystem.SetFontSizeRange(RangeI{ 25, 60 });
	textParticleSystem.SetColorsOpasities(RangeI{ 25, 200 });

	sf::Vector2f viewSixe = window.getDefaultView().getSize();
	textParticleSystem.SetGeneretionBorders(sf::FloatRect(sf::Vector2f(0.f, 0.f), viewSixe));

	textParticleSystem.SetAnimTime(sf::seconds(0.5f));
	textParticleSystem.SetBetweenTime(sf::seconds(0.15f));
	textParticleSystem.SetLifeTime(sf::seconds(12.f));
}


void Application::Run()
{
	sf::Time timeFromLastUpdate = sf::Time::Zero;
	sf::Clock clock;

	while (window.isOpen())
	{
		Process();
		
		timeFromLastUpdate += clock.restart();
		while (timeFromLastUpdate >= FRAME_PER_SECOND)
		{
			Process();
			Update(FRAME_PER_SECOND);
			timeFromLastUpdate -= FRAME_PER_SECOND;
		}

		Render();
	}
}

void Application::Process()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		eventManager->HandleInput(event);
	}
	eventManager->HandleRealTimeInput();
}

void Application::Update(sf::Time delta)
{
	textParticleSystem.Update(delta);
	cat.Update(delta);
	heart.Update(delta);
}

void Application::Render()
{
	window.clear(sf::Color::Color(255, 192, 203));
	
	window.draw(textParticleSystem);
	window.draw(cat);
	window.draw(heart);
	//window.draw(textUi);

	// window.draw(heartTraectory);

	window.display();
}