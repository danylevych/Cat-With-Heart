#pragma once


#include "../Entity/Entity.h"
#include <vector>
#include <memory>

///////////////////////////////////////////////////////
// \brief
//	   Represent the antity which has an array of
//     textures for its animation.
// 
///////////////////////////////////////////////////////
class AnimatedEntity : public Entity
{
public:
	using Ptr = std::unique_ptr<AnimatedEntity>;

private:
	using TextureArray = std::vector<std::unique_ptr<sf::Texture>>;

protected:
	uint32_t currentAnim; // Store curent state of the animation.
	TextureArray& animationTextures; // Store all textures for animation.
	sf::Time animTime;

	const sf::Time TIME_BETWEEN_ANIMATION;

public:
	AnimatedEntity(const sf::Vector2f& spawnPos, TextureArray& textures, const sf::Time timeBetweenAnimation);

	virtual ~AnimatedEntity() override = default;

protected:
	/////////////////////////////////////////////////
	// \brief
	//	  Defines how the animation will be. User
	//    can override the beheiver of its work.
	// 
	/////////////////////////////////////////////////
	virtual void Animate();

public: // Override section 
	/////////////////////////////////////////////////
	// \brief
	//  We override the Update method because it 
	//  consists the common code for the animation.
	// 
	/////////////////////////////////////////////////
	virtual void Update(sf::Time deltaTime) override;

public:
	/////////////////////////////////////////////////
	// \brief
	//	   Set the animation state for entity.
	// 
	/////////////////////////////////////////////////
	void SetAnimationState(uint32_t flag = 0);
};

