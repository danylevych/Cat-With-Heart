#pragma once


#include <memory>
#include <vector>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../../Tools/Range.h"
#include "../../Tools/Random.h"
#include "../AnimatedEntity/AnimatedEntity.h"
#include <SFML/Graphics/RenderWindow.hpp>


///////////////////////////////////////////////////////
// \brief
//		Represents the particle text system for
//		this app.
// 
///////////////////////////////////////////////////////
class ParticleSystem : public sf::Drawable
						 , sf::NonCopyable
{
public:
	using Ptr = std::unique_ptr<ParticleSystem>;

	// First parameter of the Properties is life time,
	// second defines if the unit still alive.
	using Properties = std::pair<sf::Time, bool>;

	using Unit = std::pair<AnimatedEntity::Ptr, Properties>;

public:
	enum class GenerationPosition
	{
		InBorders,
		UnderCursor
	};

private:
	std::vector<Unit> units;
	GenerationPosition generationPosition;

	//========= Settings ==========
	uint32_t			maxCountOfElements;
	sf::Time			lifeTime;
	sf::Time			timeBetween;

	RangeF				rotationAngles;
	sf::FloatRect       borders;
	float_t				startScale = 0.01f;

	Random<>			random;

public:
	ParticleSystem(GenerationPosition generationPosition = GenerationPosition::InBorders);

public:
	/////////////////////////////////////////////////////
	// \brief
	//		Generate an instance of the unit.
	// 
	/////////////////////////////////////////////////////
	void GenerateUnit();

	/////////////////////////////////////////////////////
	// \brief
	//			Upade the state of the units.
	// 
	/////////////////////////////////////////////////////
	void Update(sf::Time deltaTime);

	/////////////////////////////////////////////////////
	// \brief
	//			  Draw units into the screen.
	// 
	/////////////////////////////////////////////////////
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	/////////////////////////////////////////////////////
	// \brief
	//     Remove the units, life of which is ended.
	// 
	/////////////////////////////////////////////////////
	void RemoveDeadUnit(Unit& unit);

	/////////////////////////////////////////////////////
	// \brief
	//	  Create a new unit and add it to container.
	// 
	/////////////////////////////////////////////////////
	void CreateNewUnit();

	/////////////////////////////////////////////////////
	// \brief
	//		Find dead unit and resurrect them.
	// 
	/////////////////////////////////////////////////////
	void ResurrectUnit();

	/////////////////////////////////////////////////////
	// \brief
	//		 Set the position of the unit.
	// 
	/////////////////////////////////////////////////////
	void SetUnitPosition(Unit& unit);

public: // Setters
	void SetMaxCountOfElemnt(uint32_t  maxCountOfElements);
	void SetLifeTime(sf::Time lifeTime);
	void SetBetweenTime(sf::Time betweenTime);
	void SetRotationAngles(RangeF rotationAngles);
	void SetGeneretionBorders(const sf::FloatRect& borders);
};

