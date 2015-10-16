#ifndef CONG_MAINMENUSTATE_HPP
#define CONG_MAINMENUSTATE_HPP

#include <string>
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "MenuState.hpp"

namespace Cong {

class Game;

class MainMenuState: public MenuState {

private:

	void onConfirmPressed();

public:

	MainMenuState(const Game &game);
	~MainMenuState();

	void enter();
	void exit();

	void processEvents();
	void processInputs();
    void update(float deltaTime);
	void render();

};

}

#endif
