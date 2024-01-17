#pragma once

#include "../State/State.h"
#include <map>
#include <stack>
#include <functional>


class StateStack
{
public:
	using Ptr = std::unique_ptr<StateStack>;

private:
	Context* context;
	std::stack<State::Ptr> stack;
	std::map<StateID, std::function<State::Ptr()>> factories;

public:
	StateStack(Context& context);

public:
	void Draw();
	void Update(sf::Time deltaTime);
	void HandleEvent(const sf::Event& event);

public:
	bool IsEmpty() const;

	void Push(StateID stateId);
	void Pop();
	void Clear();

	template<typename StateType>
	void RegistrState(StateID stateId)
	{
		factories[stateId] = [this]() -> State::Ptr {
			return State::Ptr(new StateType(*this, *context));
		};
	}
};

