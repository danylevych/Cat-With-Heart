#pragma once

#include "../../../Enums/StateID.h"
#include "../../../Utilities/Context/Context.h"

#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/NonCopyable.hpp>


class StateStack;


class State : private sf::NonCopyable
{
public:
	using Ptr = std::unique_ptr<State>;

protected:
	Context* context;
	StateStack* stateStack;

public:
	State(StateStack& stack, Context& context);
	virtual ~State() = default;

public:
	virtual void Draw() = 0;
	virtual void Update(sf::Time deltaTime) = 0;
	virtual void HandleInput(const sf::Event& event) = 0;

protected:
	void RequestStackPush(StateID stateId);
	void RequestStackPop();
	void RequestStackClear();
};

