#ifndef CONG_OPTIONSMENUSTATE_HPP
#define CONG_OPTIONSMENUSTATE_HPP

#include "MenuState.hpp"

namespace Cong
{

class Game;

class OptionsMenuState: public MenuState
{

public:

	OptionsMenuState(const Game &game);
	~OptionsMenuState();

	void enter();
	void exit();

	void processEvents();
	void processInputs();
    void update();
	void render();

};

}

#endif
