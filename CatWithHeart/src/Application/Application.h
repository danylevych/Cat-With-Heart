#pragma once

#include "../Entities/Cat/Cat.h"
#include "../Entities/Heart/Heart.h"
#include "../Tools/FileReader/FileReader.h"
#include "../Tools/EventManager/EventManager.h"
#include "../Entities/TextParticleSystem/TextParticleSystem.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>


/////////////////////////////////////////////////
// \brief
//		Class represents the appliction,
//		that conteins all data we need 
//		to start the program.
// 
/////////////////////////////////////////////////
class Application
{
private:
	//==========   Window  ============
	sf::Image icon;
	sf::RenderWindow window;
	sf::Music backgroundMusic;
	EventManager* eventManager;

	//==========    Text   ============
	TextParticleSystem textParticleSystem;
	FileReader reader;
	sf::Font font;

	//==========  Objects  ============
	sf::CircleShape heartTraectory;
	Cat cat;
	Heart heart;

	//========== Constantes ===========
	const sf::Time FRAME_PER_SECOND = sf::seconds(1.f / 60.f);

public:
	/////////////////////////////////////////////////////
	// \brief
	//		Constructor for creating the instsnce
	//		of the program.
	// 
	/////////////////////////////////////////////////////
	Application();

public:
	/////////////////////////////////////////////////////
	// \brief
	//			The method starts the program.
	// 
	/////////////////////////////////////////////////////
	void Run();

private:
	/////////////////////////////////////////////////////
	// \brief
	//		 Ask the events that was happened.
	// 
	/////////////////////////////////////////////////////
	void Process();

	/////////////////////////////////////////////////////
	// \brief
	//		Update the states of objects in the app.
	// 
	/////////////////////////////////////////////////////
	void Update(sf::Time delta);

	/////////////////////////////////////////////////////
	// \brief
	//       Draw all objects in the app window.
	// 
	/////////////////////////////////////////////////////
	void Render();

private: // Init section.
	/////////////////////////////////////////////////////
	// \brief
	//		Sets the position of each object.
	// 
	/////////////////////////////////////////////////////
	void InitSpawnPos();

	/////////////////////////////////////////////////////
	// \brief
	//		Load the resources for the appliction.
	// 
	/////////////////////////////////////////////////////
	void InitResources();

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
