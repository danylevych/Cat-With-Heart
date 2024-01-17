#pragma once

#include "../Holders.h"
#include <SFML/Graphics/RenderWindow.hpp>

struct Context
{
public:
	sf::RenderWindow window;
	FontsHolder fonts;
	TexturesHolder textures;

private:
	static Context instance;
	sf::Image icon;

private:
	Context() = default;

public:
	static Context& GetInstance();

private: // Init section.
	static void Initialize();
	static void InitWindow();
	static void InitFonts();
	static void InitTextures();

};

