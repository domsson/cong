#include "StateManager.hpp"

namespace Cong
{

	StateManager::StateManager()
	: stateChangeRequested(false)
	{
		// Do nothing, this is pretty much an interface
	}

	void StateManager::requestStateChange() const
	{
		stateChangeRequested = true;
	}

}
