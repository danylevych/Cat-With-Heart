#pragma once

#include "../Entity/Entity.h"

#include <SFML/Graphics/Texture.hpp>

/////////////////////////////////////////////
// \brief
//		This class represents the heart
//		entity for the ptoject.
// 
/////////////////////////////////////////////
class Heart : public Entity
{
private:
	sf::Texture texture; // Store the texture for the instance.

	//======== Anim settings ==========
	float_t  startScale;
	float_t  zoomedScale;
	sf::Time animeTime;
	
public:
	/////////////////////////////////////////////
	// \brief
	//		Constructor that takes spawn
	//		position for the instance.
	// 
	/////////////////////////////////////////////
	Heart(const sf::Vector2f& spawnPos, float_t staertScale = 1.f, float_t zoomedScale = 3.f,
		  sf::Time animTime = sf::seconds(1.f));
	
	/////////////////////////////////////////////
	// \brief
	//		Virtual destructor, because we 
	//		will probably inherit from the 
	//		class.
	// 
	/////////////////////////////////////////////
	virtual ~Heart() = default;

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

public:
	void SetStartAnimeScale(float_t startScale);
	void SetZoomedAnimeScale(float_t zoomedScale);
};

