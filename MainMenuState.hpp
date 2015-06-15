#ifndef CONG_MAINMENUSTATE_HPP
#define CONG_MAINMENUSTATE_HPP

#include <string>
#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Game.hpp"
#include "GameState.hpp"
#include "CharMap.hpp"
#include "SpriteText.hpp"

namespace Cong {

class MainMenuState: public GameState {

private:

	const CharMap *charMap;

	SpriteText headline;
	SpriteText intro;

	std::vector<SpriteText> menuItems;
	unsigned int currentMenuItem;

	void initCharMap();
	void initText();

	void addMenuItem(const std::string &label);
	void selectNextMenuItem();
	void selectPrevMenuItem();

public:

	MainMenuState(Game &game);
	~MainMenuState();

	void enter();
	void exit();

	void processEvents();
	void processInputs();
    void update();
	void render();

};

}

#endif
