#ifndef CONG_STATEMANAGER_HPP
#define CONG_STATEMANAGER_HPP

namespace Cong
{

class StateManager
{

protected:

	StateManager();

	mutable bool stateChangeRequested;

public:

	void requestStateChange() const;

};

}

#endif
