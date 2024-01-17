#include "Cat.h"

#include <fstream>
#include <string>
#include <exception>


Cat::Cat(const sf::Vector2f& spawnPos)
	: Entity(spawnPos)
	, currentAnim(-1)
	, animationTextures(Context::GetInstance().textures.Get(TextureID::Cat))
{
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
