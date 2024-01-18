#include "LoadState.h"

LoadState::LoadState(StateStack& stack, Context& context)
	: State(stack, context)
{
	InitProgressBar();
	InitLoadingLabel();
}

void LoadState::InitProgressBar()
{
	progressBar.setScale(10.f, 10.f);

	// Set the origin at the center of the sprite.
	sf::Vector2u bounds = progressBar.GetOriginSize();
	progressBar.setOrigin(bounds.x / 2.f, bounds.y / 2.f);

	// Set position in the center of screen.
	progressBar.setPosition(context->window.getDefaultView().getSize() / 2.f);
}

void LoadState::InitLoadingLabel()
{
	// Set font, character size, color and text.
	loadingLabel.setFont(*context->fonts.Get(FontID::Main));
	loadingLabel.setCharacterSize(30);
	loadingLabel.setString("Loading");
	loadingLabel.setFillColor(sf::Color(255, 80, 200));

	// Set origin at the center of label.
	sf::FloatRect bounds = loadingLabel.getLocalBounds();
	loadingLabel.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	// Set the position under progress bar.
	sf::Vector2f progressBarPos = progressBar.getPosition();
	progressBarPos.x -= 10;
	progressBarPos.y += progressBar.GetOriginSize().y / 2.f * progressBar.getScale().x - 10.f;
	loadingLabel.setPosition(progressBarPos);
}

void LoadState::UpdateProgressBar(sf::Time deltaTime)
{
	static sf::Time timeCounter = sf::Time::Zero;

	progressBar.SetProgress(timeCounter.asSeconds() / LOADING_TIME.asSeconds());

	timeCounter += deltaTime;
}

void LoadState::UpdateLoadingLabel(sf::Time deltaTime)
{
	static int countOfDots = 0;
	static sf::Time timeCounter = sf::Time::Zero;
	timeCounter += deltaTime;

	if (timeCounter < FREQUENCY_LABEL_UPDATE) // We can't update the label.
	{
		return;
	}

	if (countOfDots > 3) // Reset dots count.
	{
		countOfDots = 0;
	}

	loadingLabel.setString("Loading" + std::string(countOfDots++, '.'));
	timeCounter = sf::Time::Zero;
}


void LoadState::Draw()
{
	sf::RenderWindow& window = context->window;

	window.draw(progressBar);
	window.draw(loadingLabel);
}

void LoadState::Update(sf::Time deltaTime)
{
	if (progressBar.IsComplete()) // The loading just ends.
	{
		RequestStackPush(StateID::Game);
		RequestStackPop();
		return;
	}

	UpdateProgressBar(deltaTime);
	UpdateLoadingLabel(deltaTime);
}

void LoadState::HandleInput(const sf::Event& event)
{	}