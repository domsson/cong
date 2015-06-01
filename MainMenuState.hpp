#ifndef CONG_MAINMENUSTATE_HPP
#define CONG_MAINMENUSTATE_HPP

#include <string>
#include <iostream>
#include "Game.hpp"
#include "SpriteText.hpp"
#include "CharMapProperties.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Cong {

class MainMenuState: public GameState {

private:

	int width;
	int height;

	SpriteText *headline;
	SpriteText *intro;

	CharMapProperties *charMapProps;
	sf::Texture charMapTexture;


public:

	MainMenuState(int width, int height);
	~MainMenuState();

	void enter();
	void exit();

	void processEvents(Game *game);
	void processInputs(Game *game);
    void update(Game *game);
	void render(Game *game);

};

}

#endif
