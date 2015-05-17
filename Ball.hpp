#ifndef CONG_BALL_HPP
#define CONG_BALL_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

namespace Cong {

class Ball: public sf::CircleShape {
    
private:
    int speed;
    sf::Vector2f *direction;
	void normalizeDirection();

public:
	Ball(int radius, int speed);
	~Ball();
    
    void setSpeed(int speed);
    int getSpeed();
    void setDirection(const sf::Vector2f &direction);
    const sf::Vector2f &getDirection();
	int getDiameter();

	bool isMovingLeft();
	bool isMovingRight();
	bool isMovingUp();
	bool isMovingDown();

	void reverseDirectionHorizontal();
	void reverseDirectionVertical();

	void slope(float amount);

};

}

#endif
