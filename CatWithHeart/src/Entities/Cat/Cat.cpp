#include "Cat.h"

#include <fstream>
#include <string>
#include <exception>


Cat::Cat(const sf::Vector2f& spawnPos)
	: Entity(spawnPos)
	, currentAnim(-1)
	, animationTextures()
{
	LoadTextures();
	Animate();
}

void Cat::Animate()
{
	++currentAnim;
	if (currentAnim == animationTextures.size())
	{
		currentAnim = 0;
	}

	sprite.setTexture(*animationTextures[currentAnim].get());
}

sf::Vector2u Cat::GetOriginSize() const
{
	return animationTextures[0]->getSize();
}

void Cat::Update(sf::Time deltaTime)
{
	static sf::Time animTime = sf::Time::Zero;

	animTime += deltaTime;
	if (animTime >= ANIM_TIME)
	{
		Animate();
		animTime = sf::Time::Zero;
	}
}

void Cat::LoadTextures()
{
	std::string rootPath = "data/textures/cat/";
	for (int i = 1; true; i++)
	{
		std::string fullPathToItem = rootPath + std::to_string(i) + ".png";

		std::ifstream file(fullPathToItem);
		if (!file.is_open()) // The file does not exist.
		{
			break;
		}

		file.close();

		std::unique_ptr<sf::Texture> animation(new sf::Texture());

		if (!animation->loadFromFile(fullPathToItem))
		{
			throw std::runtime_error("Opening file: '" + fullPathToItem + "' failed.");
		}

		animationTextures.push_back(std::move(animation));
	}
}
