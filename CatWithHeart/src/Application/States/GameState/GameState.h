#pragma once

#include "../State/State.h"

#include "../../../Entities/Cat/Cat.h"
#include "../../../Entities/Heart/Heart.h"
#include "../../../Tools/FileReader/FileReader.h"
#include "../../../Tools/EventManager/EventManager.h"
#include "../../../Entities/TextParticleSystem/TextParticleSystem.h"

#include <SFML/Graphics/CircleShape.hpp>


class GameState : public State
{
private:
	//==========    Text   ============
	TextParticleSystem textParticleSystem;
	FileReader reader;

	//==========  Objects  ============
	sf::CircleShape heartTraectory;
	Cat cat;
	Heart heart;

	//==========  Manager  ============
	EventManager eventManager;

public:
	GameState(StateStack& stack, Context& context);
	
	virtual ~GameState() = default;

public: // Overriden section.
	virtual void Draw() override;
	virtual void Update(sf::Time deltaTime) override;
	virtual void HandleInput(const sf::Event& event) override;

public:
	/////////////////////////////////////////////////////
	// \brief
	//		Sets the position of each object.
	// 
	/////////////////////////////////////////////////////
	void InitSpawnPos();

	/////////////////////////////////////////////////////
	// \brief
	//		Init binded keys for the appliction.
	// 
	/////////////////////////////////////////////////////
	void InitBindedKeys();

	/////////////////////////////////////////////////////
	// \brief
	//		Init text generetor for the app.
	// 
	/////////////////////////////////////////////////////
	void InitTextGenerator();
};

