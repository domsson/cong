#ifndef CONG_PADDLE_HPP
#define CONG_PADDLE_HPP

#include <SFML/Graphics.hpp>

namespace Cong {

class Paddle: public sf::RectangleShape {

private:
	int speed;

public:
    Paddle(sf::Vector2f size, int speed);
	~Paddle();

    void setSpeed(int speed);
    int getSpeed();

};

}

#endif
