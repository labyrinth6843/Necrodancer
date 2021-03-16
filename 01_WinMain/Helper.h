#pragma once
#include <stack>
#include <queue>
template<typename T >inline void StackClear(stack< T >& Stacks)
{
	while (false == Stacks.empty())
	{
		Stacks.pop();
	}
};

template<typename T >inline void QueueClear(queue< T >& Queue)
{
	while (false == Queue.empty())
	{
		Queue.pop();
	}
};

inline string to_string(wstring wst)
{
	string st;
	st.assign(wst.begin(), wst.end());
	return st;
}

inline wstring to_string(string st)
{
	wstring wst;
	wst.assign(st.begin(), st.end());
	return wst;
}