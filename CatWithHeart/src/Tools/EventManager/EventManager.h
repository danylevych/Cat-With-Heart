#pragma once

#include "../../Enums/KeyActions.h"

#include <map>
#include <string>
#include <typeinfo>
#include <functional>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>


#define nameOf(value) #value

/////////////////////////////////////////////////////////
// \brief
//		Event manager for our application, it is 
//		singletone.
// 
/////////////////////////////////////////////////////////
class EventManager
{
public:
	using Command = std::function<void()>;

	enum class Actions
	{
		Never,
		OnlyOnce,
		EveryFrame,
	};

private:
	std::map<std::string, Command> staticActions;
	std::map<std::string, Command> realTimeActions;

private:
	EventManager() = default;

public:
	////////////////////////////////////////////////////////
	// \brief
	//		Returns an instance of the manager.
	// 
	////////////////////////////////////////////////////////
	static EventManager& GetInstance();

	////////////////////////////////////////////////////////
	// \brief
	//		Retyrn the position of the cursore on 
	//		the window.
	// 
	////////////////////////////////////////////////////////
	static sf::Vector2i GetMousePos(const sf::WindowBase& window);

	////////////////////////////////////////////////////////
	// \brief
	//		Check if the value has pressed in real time.
	// 
	////////////////////////////////////////////////////////
	static bool IsKeyPressedRealTime(const sf::Mouse::Button& key)
	{
		return sf::Mouse::isButtonPressed(key);
	}

	static bool IsKeyPressedRealTime(const sf::Keyboard::Key& key)
	{
		return sf::Keyboard::isKeyPressed(key);
	}

	////////////////////////////////////////////////////////
	// \brief
	//		Binds the key to some static event in app.
	// 
	////////////////////////////////////////////////////////
	template<typename Type>
	void BindKey(Type bindedKey, Command command)
	{
		staticActions[GetFullNameOf<Type>(bindedKey)] = command;
	}

	////////////////////////////////////////////////////////
	// \brief
	//	  Binds the key to some real time event in app.
	// 
	////////////////////////////////////////////////////////
	template<typename Type>
	void BindRealTimeKey(Type bindedKey, Command command)
	{
		realTimeActions[GetFullNameOf<Type>(bindedKey)] = command;
	}

	////////////////////////////////////////////////////////
	// \brief
	//		  Handles the static input in the app.
	// 
	////////////////////////////////////////////////////////
	void HandleInput(const sf::Event& event) const;

	////////////////////////////////////////////////////////
	// \brief
	//		Handles the real time input in the app.
	// 
	////////////////////////////////////////////////////////
	void HandleRealTimeInput() const;

private:
	template<typename Type>
	std::string GetFullNameOf(Type bindedKey)
	{
		std::string key = typeid(Type).name();

		// Remove all words.
		std::string newKey;
		for (size_t i = key.find(' ') + 1; i < key.size() && i != 0; )
		{
			newKey = key.substr(i);
			i = key.find(' ', i) + 1;
		}
		key = newKey + "::";
		key += std::to_string(static_cast<int32_t>(bindedKey));

		return key;
	}
};
