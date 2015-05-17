#include "Ball.hpp"
#include <SFML/Graphics.hpp>

namespace Cong {
    
    Ball::Ball(int radius, int speed) : sf::CircleShape(radius), speed(speed) {
        direction = new sf::Vector2f(0, 0);
		setOrigin(radius, radius);
    }
    
    Ball::~Ball() {
        
    }
    
    void Ball::setSpeed(int speed) {
        this->speed = speed;
    }
    
    int Ball::getSpeed() {
        return speed;
    }
    
    void Ball::setDirection(const sf::Vector2f &direction) {
        this->direction = new sf::Vector2f(direction.x, direction.y);
    }
    
    const sf::Vector2f &Ball::getDirection() {
        return *direction;
    }

	int Ball::getDiameter() {
		return getRadius() + getRadius();
	}

	void Ball::reverseDirectionHorizontal() {
		direction->x = -direction->x;
	}

	void Ball::reverseDirectionVertical() {
		direction->y = -direction->y;
	}
    
}
