#ifndef CONG_PLAYSTATE_HPP
#define CONG_PLAYSTATE_HPP

#include <cmath>
#include <string>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.hpp"
#include "Physics.hpp"
#include "Math.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "CharMap.hpp"
#include "SpriteText.hpp"
#include "GameState.hpp"

namespace Cong {

class PlayState: public GameState {

private:

	int width;
	int height;

	sf::RectangleShape *menuBackground;
	sf::RectangleShape *court;
	Ball *ball;
	Paddle *paddleLeft;
	Paddle *paddleRight;

	sf::Texture courtTexture;
	sf::Texture ballTexture;
	sf::Texture paddleTexture;

	const CharMap *charMap;

	SpriteText *scoreDisplayLeft;
    SpriteText *scoreDisplayRight;
    
    Menu pauseMenu;

	sf::Sound paddleSound;
	sf::Sound wallSound;
	sf::Sound outSound;

	sf::SoundBuffer paddleSoundFile;
	sf::SoundBuffer wallSoundFile;
	sf::SoundBuffer outSoundFile;

	int scoreLeft;
	int scoreRight;
	
	bool isPaused;

	void initCourt();
	void initPaddles();
	void initBall();
	void initScoreDisplays();
	void initSounds();
	void initPauseMenu();
	
	void positionMenu();	
	void onConfirmPressed();

	void serve();
	void scoreForLeft();
	void scoreForRight();
	void resetScores();

public:

	PlayState(Game &game);
	~PlayState();

	void enter();
	void exit();

	void processEvents();
	void processInputs();
    void update();
	void render();
	
	void pause();
	void resume();

};

}

#endif
