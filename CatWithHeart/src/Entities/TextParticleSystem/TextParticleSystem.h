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
#include <SFML/Graphics/RenderWindow.hpp>


///////////////////////////////////////////////////////
// \brief
//		Represents the particle text system for
//		this app.
// 
///////////////////////////////////////////////////////
class TextParticleSystem : public sf::Drawable
						 , sf::NonCopyable
{
public:
	using Ptr = std::unique_ptr<TextParticleSystem>;
	using Unit = std::pair<std::unique_ptr<sf::Text>, sf::Time>;

private:
	std::vector<Unit> texts;

	//========= Settings ==========
	uint32_t			maxCountOfElements;
	sf::Time			lifeTime;
	sf::Time			animTime;
	sf::Time			timeBetween;
	sf::Font			font;
	RangeI				fontSizes;
	RangeF				rotationAngles;
	sf::FloatRect       borders;
	float_t				startScale = 0.01f;
	sf::Color			color;
	RangeI				opasities;
	Random<>			random;

public:
	TextParticleSystem() = default;

public:
	/////////////////////////////////////////////////////
	// \brief
	//		Generate an instance of the unit.
	// 
	/////////////////////////////////////////////////////
	void GenerateUnit(const std::string& text = "NONE");

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
	//	   Animate the unit, simply it cahnges the
	//	   scale property for the unit.
	// 
	/////////////////////////////////////////////////////
	void AnimateUnit();

	/////////////////////////////////////////////////////
	// \brief
	//     Remove the units, life of which is ended.
	// 
	/////////////////////////////////////////////////////
	void RemoveOldUnit();

	/////////////////////////////////////////////////////
	// \brief
	//	 Updete time property for each existing unit.
	// 
	/////////////////////////////////////////////////////
	void UpdateUnitTime(sf::Time deltaTime);

public: // Setters
	void SetMaxCountOfElemnt(uint32_t  maxCountOfElements);
	void SetLifeTime(sf::Time lifeTime);
	void SetAnimTime(sf::Time animTime);
	void SetBetweenTime(sf::Time betweenTime);
	void SetFontSizeRange(RangeI fontSizes);
	void SetRotationAngles(RangeF rotationAngles);
	void SetGeneretionBorders(const sf::FloatRect& borders);
	void SetFont(const sf::Font& font);
	void SetColor(sf::Color color);
	void SetColorsOpasities(RangeI opasities);
};

