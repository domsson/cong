#ifndef CONG_GAME_HPP
#define CONG_GAME_HPP

#include <string>
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

class GameState;

class Game {

private:
	sf::RenderWindow *window;

	int width;
	int height;
	std::string title;

	GameState *state;

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

    void processEvents();
	void processInputs();
    void update();
	void render();
    
    void serve();
	void scoreForLeft();
	void scoreForRight();

	void initCourt();
	void initPaddles();
	void initBall();
	void initScoreDisplays();
	void initSounds();

	void resetScores();

public:
    
	Game(const std::string &title, int width, int height);
	~Game();

	void run();
	void setState(GameState *state);
	sf::RenderWindow* getWindow() const;

	static bool loadSound(const std::string &soundFile, sf::SoundBuffer &buffer, sf::Sound &sound);
	static bool loadTexture(const std::string &textureFile, sf::Texture &texture);

};

}

#endif

