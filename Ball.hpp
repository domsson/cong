#ifndef CONG_BALL_HPP
#define CONG_BALL_HPP

#include <SFML/Graphics.hpp>

namespace Cong {

class Ball: public sf::CircleShape {
    
private:
    int speed;
    sf::Vector2f *direction;

public:
	Ball(int radius, int speed);
	~Ball();
    
    void setSpeed(int speed);
    int getSpeed();
    void setDirection(const sf::Vector2f &direction);
    const sf::Vector2f &getDirection();
	int getDiameter();

	void reverseDirectionHorizontal();
	void reverseDirectionVertical();

};

}

#endif
