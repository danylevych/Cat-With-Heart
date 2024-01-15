#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

//////////////////////////////////////////////////
// \brief
//		This class represents the entity
//		in our project.
// 
//////////////////////////////////////////////////
class Entity : private sf::NonCopyable
			 , public  sf::Drawable
			 , public  sf::Transformable
{
protected:
	sf::Vector2f spawnPos;
	sf::Sprite   sprite;

public:
	//////////////////////////////////////////////////
	// \brief
	//		Constructor thakes the spawn position
	//		of the entity.
	// 
	//////////////////////////////////////////////////
	Entity(const sf::Vector2f& spawnPos);

	//////////////////////////////////////////////////
	// \brief
	//		Virtual destructor because we will
	//		inherit form this class.
	// 
	//////////////////////////////////////////////////
	virtual ~Entity() = default;

public:
	//////////////////////////////////////////////////
	// \brief
	//		Method that returns the origin size
	//		of the entity.
	// 
	//////////////////////////////////////////////////
	virtual sf::Vector2u GetOriginSize() const = 0;

	//////////////////////////////////////////////////
	// \brief
	//		Update the state of the entity.
	// 
	//////////////////////////////////////////////////
	virtual void Update(sf::Time deltaTime) = 0;

public:
	//////////////////////////////////////////////////
	// \brief
	//		Overloaded method for drawing the 
	//		entity.
	//
	//////////////////////////////////////////////////
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

