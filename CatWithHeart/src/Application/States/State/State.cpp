#include "State.h"

#include "../StateStack/StateStack.h"


State::State(StateStack& stack, Context& context)
	: stateStack(&stack)
	, context(&context)
{	}

void State::RequestStackPush(StateID stateId)
{
	stateStack->Push(stateId);
}

void State::RequestStackPop()
{
	stateStack->Pop();
}

void State::RequestStackClear()
{
	stateStack->Clear();
}
