#ifndef CONG_GAME_HPP
#define CONG_GAME_HPP

#include <string>
#include "Court.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "ScoreDisplay.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace Cong {

class Game {

private:
	sf::RenderWindow *window;
	Cong::Court *court;
	Cong::Ball *ball;
	Cong::Paddle *paddle1;
	Cong::Paddle *paddle2;
	Cong::ScoreDisplay *scoreDisplay;

	int width;
	int height;
	std::string title;

	void update();
	void processInputs();
	void render(sf::RenderWindow window);
	
public:
	Game(const std::string &title, int width, int height);
	~Game();

	void run();

};

}

#endif

