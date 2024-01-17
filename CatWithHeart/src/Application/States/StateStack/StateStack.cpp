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
	auto result = factories[stateId]();
	stack.push(std::move(result));
}

void StateStack::Pop()
{
	stack.pop();
}

void StateStack::Clear()
{
	while (!stack.empty())
	{
		stack.pop();
	}
}

