#include "Application.h"

#include "States/GameState/GameState.h"
#include "States/LoadState/LoadState.h"

#include <iostream>
#include <SFML/Graphics/Color.hpp>


Application::Application()
	: backgroundMusic()
	, window(nullptr)
	, stateStack(Context::GetInstance())
{
	window = &Context::GetInstance().window;
	InitResources();
	InitStateStack();
	InitBindedKeys();
}

void Application::InitResources()
{
	if (backgroundMusic.openFromFile("data/audio/background.ogg"))
	{
		backgroundMusic.setLoop(true);
		backgroundMusic.play();
	}
}

void Application::InitBindedKeys()
{
	// Bind the static events.
	eventManager.BindKey(sf::Event::EventType::Closed, [this]() { 
		window->close(); 
	});
}

void Application::InitStateStack()
{
	stateStack.RegistrState<GameState>(StateID::Game);
	stateStack.RegistrState<LoadState>(StateID::Loading);
}

void Application::Run()
{
	sf::Time timeFromLastUpdate = sf::Time::Zero;
	sf::Clock clock;

	stateStack.Push(StateID::Loading);

	while (window->isOpen())
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
	while (window->pollEvent(event))
	{
		eventManager.HandleInput(event);

		stateStack.HandleEvent(event);
	}
	eventManager.HandleRealTimeInput();
}

void Application::Update(sf::Time delta)
{
	stateStack.Update(delta);
}

void Application::Render()
{
	window->clear(sf::Color::Color(255, 192, 203));
	
	stateStack.Draw();

	window->display();
}