#ifndef CONG_PLAYSTATE_HPP
#define CONG_PLAYSTATE_HPP

#include <string>
#include <iostream>
#include "Ball.hpp"
#include "Paddle.hpp"
#include "SpriteText.hpp"
#include "CharMapProperties.hpp"
#include "Physics.hpp"
#include "Math.hpp"
#include "GameState.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Cong {

class PlayState: public GameState {

private:

	int width;
	int height;

	sf::RectangleShape *court;
	Ball *ball;
	Paddle *paddleLeft;
	Paddle *paddleRight;
	SpriteText *scoreDisplayLeft;
    SpriteText *scoreDisplayRight;

	CharMapProperties *charMapProps;
	sf::Texture charMapTexture;
	sf::Texture courtTexture;
	sf::Texture ballTexture;
	sf::Texture paddleTexture;

	sf::Sound paddleSound;
	sf::Sound wallSound;
	sf::Sound outSound;

	sf::SoundBuffer paddleSoundFile;
	sf::SoundBuffer wallSoundFile;
	sf::SoundBuffer outSoundFile;

	int scoreLeft;
	int scoreRight;

	void initCourt();
	void initPaddles();
	void initBall();
	void initScoreDisplays();
	void initSounds();

	void serve();
	void scoreForLeft();
	void scoreForRight();
	void resetScores();

public:

	PlayState(int width, int height);
	~PlayState();

	void enter();
	void exit();

	void processEvents(Game *game);
	void processInputs(Game *game);
    void update(Game *game);
	void render(Game *game);

};

}

#endif
