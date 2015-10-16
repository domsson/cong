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
    void update(float deltaTime);
	void render();

private:

	void onConfirmPressed();
	void onLeftPressed();
	void onRightPressed();

	void loadResolutionOption();
	void loadThemeOption();
	void loadSoundOption();

	void saveResolutionOption();
	void saveThemeOption();
	void saveSoundOption();

};

}

#endif
