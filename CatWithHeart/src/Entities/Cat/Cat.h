#pragma once


#include "../AnimatedEntity/AnimatedEntity.h"

#include <SFML/Graphics/Texture.hpp>

///////////////////////////////////////////
// \brief
//		Class represent the cat object
//		in our project.
// 
///////////////////////////////////////////
class Cat : public AnimatedEntity
{
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
};

