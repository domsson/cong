#ifndef CONG_GAME_HPP
#define CONG_GAME_HPP

#include <string>
#include <chrono>
#include <thread>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "SpriteText.hpp"
#include "StateManager.hpp"
#include "GameState.hpp"
#include "GameStates.hpp"
#include "MainMenuState.hpp"
#include "OptionsMenuState.hpp"
#include "PlayState.hpp"
#include "Options.hpp"

namespace Cong {

class GameState;

class Game: public StateManager {

private:

	sf::RenderWindow *window;

	int width;
	int height;
	std::string title;

	Options options;

	GameState *activeState;
	//mutable bool stateChangeRequested;

	sf::Texture charMapTexture;
	const CharMap *charMap;

	void processEvents();
	void processInputs();
	void update();
	void render();

	void changeState(GameStates newState);
	void tryStateChange();

public:
    
	Game(const std::string &title, int width, int height);
	~Game();

	void run();
	void setState(GameState *newState);
	//void requestStateChange() const;
	sf::RenderWindow* getWindow() const;
	float getDeltaTime() const;
	unsigned int getViewportWidth() const;
	unsigned int getViewportHeight() const;
	std::string getTitle() const;
	const CharMap* getDefaultCharMap() const;
	Options* getOptions();

	static bool loadSound(const std::string &soundFile, sf::SoundBuffer &buffer, sf::Sound &sound);
	static bool loadTexture(const std::string &textureFile, sf::Texture &texture);

};

}

#endif

