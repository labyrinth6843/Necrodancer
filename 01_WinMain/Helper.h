#pragma once
#include <stack>

template<typename T >inline void StackClear(stack< T >& Stacks)
{
	while (false == Stacks.empty())
	{
		Stacks.pop();
	}
};