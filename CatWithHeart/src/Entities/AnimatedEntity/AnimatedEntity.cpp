#include "AnimatedEntity.h"


AnimatedEntity::AnimatedEntity(const sf::Vector2f& spawnPos, TextureArray& textures, const sf::Time timeBetweenAnimation)
	: Entity(spawnPos)
	, TIME_BETWEEN_ANIMATION(timeBetweenAnimation)
	, animTime(sf::Time::Zero)
	, animationTextures(textures)
	, currentAnim(0)
{	
	// Set the first animation for the entity.
	sprite.setTexture(*animationTextures[currentAnim]);
}

void AnimatedEntity::Animate()
{
	if (++currentAnim == animationTextures.size())
	{
		currentAnim = 0;
	}

	sprite.setTexture(*animationTextures[currentAnim].get());
}

void AnimatedEntity::SetAnimationState(uint32_t flag)
{
	currentAnim = flag;
}

void AnimatedEntity::Update(sf::Time deltaTime)
{
	animTime += deltaTime;
	if (animTime >= TIME_BETWEEN_ANIMATION)
	{
		Animate();
		animTime = sf::Time::Zero;
	}
}