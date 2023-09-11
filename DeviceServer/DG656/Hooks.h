#ifndef HOOKS_H
#define HOOKS_H

#include <list>
#include <vector>
#include <algorithm>

namespace Hooks_ns
{

typedef void (* HookFunction)(void *arg);
typedef void *HookArgument;

class Hooks
{
protected:
	std::vector<std::list<std::pair<HookFunction, HookArgument> > > hookTable;
	HookFunction hookFunction;

	static void executeHookNode(std::pair<HookFunction, HookArgument> node)
	{
		node.first(node.second);
	}

public:

	Hooks(unsigned int n)
	{
		hookTable.resize(n);
		std::fill(hookTable.begin(), hookTable.end(), std::list<std::pair<HookFunction, HookArgument> >());
	}

	void registerHook(unsigned int hook, HookFunction func, HookArgument arg)
	{
		std::pair<HookFunction, HookArgument> node(func, arg);
		hookTable[hook].push_back(node);
	}

	void unregisterHook(unsigned int hook, HookFunction func)
	{
		for(std::list<std::pair<HookFunction, HookArgument> >::iterator node = hookTable[hook].begin(); node != hookTable[hook].end();)
		{
			if(node->first == func)
				node = hookTable[hook].erase(node);
			else
				node++;
		}
	}

	void executeHook(unsigned int hook)
	{
		std::for_each(hookTable[hook].begin(), hookTable[hook].end(), Hooks::executeHookNode);
	}

}; // Hooks

inline Hooks* getHooks(int n)
{
	static Hooks h(n);
	return &h;
}

} // Hooks_ns

#endif // HOOKS_H
