#ifndef CONG_GAME_HPP
#define CONG_GAME_HPP

#include <string>
#include "Ball.hpp"
#include "Paddle.hpp"
#include "SpriteText.hpp"
#include "CharMapProperties.hpp"
#include "Physics.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace Cong {

class Game {

private:
	sf::RenderWindow *window;

	sf::RectangleShape *court;
	Ball *ball;
	Paddle *paddleLeft;
	Paddle *paddleRight;
	SpriteText *scoreDisplayLeft;
    SpriteText *scoreDisplayRight;

	sf::Texture *charMapTexture;
	CharMapProperties *charMapProps;
	sf::Texture *courtTexture;
	sf::Texture *ballTexture;
	sf::Texture *paddleTexture;

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

	void initCourt();
	void initPaddles();
	void initBall();
	void initScoreDisplays();

	void resetScores();

	bool rangesIntersect(const sf::Vector2f &range1, const sf::Vector2f &range2) const;

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

