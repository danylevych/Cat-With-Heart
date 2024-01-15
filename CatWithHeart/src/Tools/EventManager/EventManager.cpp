#include "EventManager.h"

EventManager& EventManager::GetInstance()
{
	static EventManager instance;
	return instance;
}

sf::Vector2i EventManager::GetMousePos(const sf::WindowBase& window)
{
	return sf::Mouse::getPosition(window);
}

void EventManager::HandleInput(const sf::Event& event) const
{
	std::string key;

	if (event.type == sf::Event::KeyPressed)
	{
		key = nameOf(sf::Keyboard::) + std::to_string(event.key.code);
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		key = nameOf(sf::Mouse::) + std::to_string(event.mouseButton.button);
	}
	else if (event.type == sf::Event::Closed)
	{
		key = nameOf(sf::Event::EventType::) + std::to_string(sf::Event::Closed);
	}
	// TODO: make other handeling.

	if (!key.empty())
	{
		auto foundVal = staticActions.find(key);
		if (foundVal != staticActions.end()) // We have the binded action.
		{
			foundVal->second();
		}
	}
}

void EventManager::HandleRealTimeInput() const
{
	auto getCode = [](const std::string& key) -> int32_t {
		return std::stoi(key.substr(key.rfind(':') + 1));
	};

	auto contains = [](const std::string& where, const std::string& what) -> bool {
		return where.find(what) != std::string::npos;
	};

	for (const auto& item : realTimeActions)
	{
		if (contains(item.first, nameOf(EventManager::Actions)))
		{
			Actions action = static_cast<Actions>(getCode(item.first));

			switch (action)
			{
			case EventManager::Actions::Never:
				break;
			case EventManager::Actions::OnlyOnce:

				break;
			case EventManager::Actions::EveryFrame:
				item.second();
				break;
			}
		}
		else if (contains(item.first, nameOf(sf::Keyboard)))
		{
			// Check is the button was pressed.
			if (EventManager::IsKeyPressedRealTime(static_cast<sf::Keyboard::Key>(getCode(item.first))))
			{
				item.second(); // Call binded command.
			}
		}
		else if (contains(item.first, nameOf(sf::Mouse)))
		{
			// Check is the button was pressed.
			if (EventManager::IsKeyPressedRealTime(static_cast<sf::Mouse::Button>(getCode(item.first))))
			{
				item.second(); // Call binded command.
			}
		}
	}
}
