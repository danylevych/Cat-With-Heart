#include "Context.h"


Context Context::instance;

Context& Context::GetInstance()
{
	static bool firstCall = true;

	// Initialize the context if it is first call.
	if (firstCall)
	{
		Initialize();
		firstCall = false;
	}

	return instance;
}

void Context::Initialize()
{
	InitWindow();
	InitFonts();
	InitTextures();
}

void Context::InitWindow()
{
	sf::RenderWindow& window = instance.window;
	window.setKeyRepeatEnabled(false);
	window.create(sf::VideoMode(800, 600), "The most cutiest app", sf::Style::Close);
	
	// Set the icon for the window.
	sf::Image& icon = instance.icon;
	if (icon.loadFromFile("data/icon/heart.png"))
	{
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
}

void Context::InitFonts()
{
	FontsHolder& fonts = instance.fonts;

	// Load the fonts.
	fonts.Load(FontID::Main, "data/fonts/Lemon-Regular.ttf");
}

void Context::InitTextures()
{
	TexturesHolder& textures = instance.textures;

	// Load textures for cat entity.
	textures.Load(TextureID::Cat, "data/textures/cat/1.png");
	textures.Load(TextureID::Cat, "data/textures/cat/2.png");
	textures.Load(TextureID::Cat, "data/textures/cat/3.png");
	textures.Load(TextureID::Cat, "data/textures/cat/4.png");
	textures.Load(TextureID::Cat, "data/textures/cat/5.png");
	textures.Load(TextureID::Cat, "data/textures/cat/6.png");

	// Load textures for heart.
	textures.Load(TextureID::Heart, "data/textures/heart/heart.png");

	// Load textures for progress bar.
	textures.Load(TextureID::ProgressBar, "data/textures/progressBar/1.png");
	textures.Load(TextureID::ProgressBar, "data/textures/progressBar/2.png");
	textures.Load(TextureID::ProgressBar, "data/textures/progressBar/3.png");
	textures.Load(TextureID::ProgressBar, "data/textures/progressBar/4.png");
	textures.Load(TextureID::ProgressBar, "data/textures/progressBar/5.png");
	textures.Load(TextureID::ProgressBar, "data/textures/progressBar/6.png");
	textures.Load(TextureID::ProgressBar, "data/textures/progressBar/7.png");
	textures.Load(TextureID::ProgressBar, "data/textures/progressBar/8.png");
	textures.Load(TextureID::ProgressBar, "data/textures/progressBar/9.png");
	textures.Load(TextureID::ProgressBar, "data/textures/progressBar/10.png");

	// Load textures for particle system.
	textures.Load(TextureID::ClickEffect, "data/textures/clickEffect/1.png");
	textures.Load(TextureID::ClickEffect, "data/textures/clickEffect/2.png");
	textures.Load(TextureID::ClickEffect, "data/textures/clickEffect/3.png");
	textures.Load(TextureID::ClickEffect, "data/textures/clickEffect/4.png");
	textures.Load(TextureID::ClickEffect, "data/textures/clickEffect/5.png");
	textures.Load(TextureID::ClickEffect, "data/textures/clickEffect/6.png");
	textures.Load(TextureID::ClickEffect, "data/textures/clickEffect/7.png");
	textures.Load(TextureID::ClickEffect, "data/textures/clickEffect/8.png");
	textures.Load(TextureID::ClickEffect, "data/textures/clickEffect/9.png");
}

