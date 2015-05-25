#ifndef CONG_GAME_HPP
#define CONG_GAME_HPP

#include <string>
#include "Court.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "ScoreDisplay.hpp"
#include "SpriteText.hpp"
#include "CharMapProperties.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace Cong {

class Game {

private:
	sf::RenderWindow *window;
	Court *court;
	Ball *ball;
	Paddle *paddleLeft;
	Paddle *paddleRight;

	sf::Texture *charMapTexture;
	CharMapProperties *charMapProps;

	SpriteText *scoreDisplayLeft;
    SpriteText *scoreDisplayRight;

	int width;
	int height;
	std::string title;

	int scoreLeft;
	int scoreRight;

    void processEvents();
	void processInputs();
    void update();
	void render();
    
    void serve();
	void scoreForLeft();
	void scoreForRight();
	
public:
    // http://www.codeproject.com/Articles/13740/The-Beginner-s-Guide-to-Using-Enum-Flags
    // TODO Maybe better use Enum for it (Edge::TOP, Edge::LEFT and so on)
    static const int EDGE_TOP;
    static const int EDGE_RIGHT;
    static const int EDGE_BOTTOM;
    static const int EDGE_LEFT;
    
	Game(const std::string &title, int width, int height);
	~Game();

	void run();

};

}

#endif

