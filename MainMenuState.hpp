#ifndef CONG_MAINMENUSTATE_HPP
#define CONG_MAINMENUSTATE_HPP

#include <string>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.hpp"
#include "CharMap.hpp"
#include "SpriteText.hpp"

namespace Cong {

class MainMenuState: public GameState {

private:

	int width;
	int height;

	SpriteText *headline; // TODO can we make this object instead of pointer?
	SpriteText *intro;    // TODO can we make this object instead of pointer?

	sf::Texture charMapTexture;
	CharMap *charMap;

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
