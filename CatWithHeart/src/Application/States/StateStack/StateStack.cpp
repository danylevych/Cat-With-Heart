#include "StateStack.h"

StateStack::StateStack(Context& context)
	: context(&context)
{	}

void StateStack::Draw()
{
	if (!stack.empty())
	{
		stack.top()->Draw();
	}
}

void StateStack::Update(sf::Time deltaTime)
{
	if (!stack.empty())
	{
		stack.top()->Update(deltaTime);
	}

	ApplyChanges();
}

void StateStack::HandleEvent(const sf::Event& event)
{
	if (!stack.empty())
	{
		stack.top()->HandleInput(event);
	}
}

bool StateStack::IsEmpty() const
{
	return stack.empty();
}

void StateStack::Push(StateID stateId)
{
	pendingChanges.push(PendingChanges(Action::Push, stateId));
}

void StateStack::Pop()
{
	pendingChanges.push(Action::Pop);
}

void StateStack::Clear()
{
	pendingChanges.push(Action::Clear);
}

void StateStack::ApplyChanges()
{
	while (!pendingChanges.empty())
	{
		switch (pendingChanges.top().action)
		{
		case Action::Push:
			stack.push(std::move(factories[pendingChanges.top().stateId]()));
			break;

		case Action::Pop:
			stack.pop();
			break;

		case Action::Clear:
			while (!stack.empty())
			{
				stack.pop();
			}
			break;
		}
		pendingChanges.pop();
	}
}

