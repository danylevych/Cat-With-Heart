#pragma once


#include "../Entity/Entity.h"

#include <memory>
#include <vector>
#include <SFML/Graphics/Texture.hpp>

///////////////////////////////////////////
// \brief
//		Class represent the cat object
//		in our project.
// 
///////////////////////////////////////////
class Cat : public Entity
{
private:
	uint32_t currentAnim; // Store curent state of the animation.
	std::vector<std::unique_ptr<sf::Texture>> animationTextures; // Store all textures for animation.

	const sf::Time ANIM_TIME = sf::seconds(0.15f);

public:
	/////////////////////////////////////////////
	// \brief
	//		Constructor that thakes a spawn
	//		position for our entity.
	//  
	/////////////////////////////////////////////
	Cat(const sf::Vector2f& spawnPos);

	/////////////////////////////////////////////
	// \brief
	//		Virtual destructor, becsuse it
	//		probably will be that we will
	//		inherit from this class.
	// 
	/////////////////////////////////////////////
	virtual ~Cat() = default;

public:
	//////////////////////////////////////////////////
	// \brief
	//		Overloaded method that returns the 
	//      origin size of the entity.
	// 
	//////////////////////////////////////////////////
	virtual sf::Vector2u GetOriginSize() const override;
	
	//////////////////////////////////////////////////
	// \brief
	//		Overloaded Update method, that change
	//		states of the entity.
	// 
	//////////////////////////////////////////////////
	virtual void Update(sf::Time deltaTime) override;

private:
	/////////////////////////////////////////////
	// \brief
	//		This method change the animation
	//		state for our game.
	// 
	/////////////////////////////////////////////
	void Animate();

	/////////////////////////////////////////////
	// \brief
	//		This method fill our array of
	//		animations.
	// 
	/////////////////////////////////////////////
	void LoadTextures();
};

