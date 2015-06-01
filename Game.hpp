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

    void processEvents();
	void processInputs();
    void update();
	void render();

public:
    
	Game(const std::string &title, int width, int height);
	~Game();

	void run();
	void setState(GameState *state);
	sf::RenderWindow* getWindow() const;
	float getDeltaTime() const;

	static bool loadSound(const std::string &soundFile, sf::SoundBuffer &buffer, sf::Sound &sound);
	static bool loadTexture(const std::string &textureFile, sf::Texture &texture);

};

}

#endif

