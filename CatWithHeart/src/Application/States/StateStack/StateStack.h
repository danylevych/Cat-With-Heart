#pragma once

#include "../State/State.h"
#include <map>
#include <stack>
#include <functional>


class StateStack
{
public:
	using Ptr = std::unique_ptr<StateStack>;

private: // Needed functionaly.
	enum class Action
	{
		Pop,
		Push,
		Clear
	};

	/////////////////////////////////////////////////////
	// \brief
	//	Represent the pending change of app stack.
	// 
	/////////////////////////////////////////////////////
	struct PendingChanges 
	{
		StateID stateId;
		Action action;

		PendingChanges(Action action, StateID stateId = StateID::None) 
			: action(action), stateId(stateId) {	}
	};

	std::stack<PendingChanges> pendingChanges;

private:
	Context* context;
	std::stack<State::Ptr> stack;
	std::map<StateID, std::function<State::Ptr()>> factories;

public:
	StateStack(Context& context);

public:
	//////////////////////////////////////////////
	// \brief
	//  Draw the state stack on the game screen.
	// 
	//////////////////////////////////////////////
	void Draw();

	//////////////////////////////////////////////
	// \brief
	//		  Update the stack states.
	// 
	//////////////////////////////////////////////
	void Update(sf::Time deltaTime);

	//////////////////////////////////////////////
	// \brief
	//	   Handle the event for state stack.
	// 
	//////////////////////////////////////////////
	void HandleEvent(const sf::Event& event);

public:
	//////////////////////////////////////////////
	// \brief
	//	Return true if the stack of app states
	//  is empty, otherwise false.
	// 
	//////////////////////////////////////////////
	bool IsEmpty() const;

	//////////////////////////////////////////////
	// \brief
	//   Add the state to the stack of states.
	// 
	//////////////////////////////////////////////
	void Push(StateID stateId);

	//////////////////////////////////////////////
	// \brief
	//      Remove top item from the stack.
	// 
	//////////////////////////////////////////////
	void Pop();

	//////////////////////////////////////////////
	// \brief
	//	        Clear the state stack.
	// 
	//////////////////////////////////////////////
	void Clear();

	//////////////////////////////////////////////
	// \brief
	//      Registr the state for the stack.
	// 
	//////////////////////////////////////////////
	template<typename StateType>
	void RegistrState(StateID stateId)
	{
		factories[stateId] = [this]() -> State::Ptr {
			return State::Ptr(new StateType(*this, *context));
		};
	}

private:
	//////////////////////////////////////////////
	// \brief
	//		   Aplpay peding changes.
	// 
	//////////////////////////////////////////////
	void ApplyChanges();
};

