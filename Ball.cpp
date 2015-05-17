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
		normalizeDirection();
    }

	void Ball::normalizeDirection() {
		float length = std::sqrt((direction->x * direction->x) + (direction->y * direction->y));
		direction->x = direction->x / length;
		direction->y = direction->y / length;
	}
    
    const sf::Vector2f &Ball::getDirection() {
        return *direction;
    }

	int Ball::getDiameter() {
		return getRadius() + getRadius();
	}

	bool Ball::isMovingLeft() {
		return direction->x < 0;
	}

	bool Ball::isMovingRight() {
		return direction->x > 0;
	}

	bool Ball::isMovingUp() {
		return direction->y < 0;
	}

	bool Ball::isMovingDown() {
		return direction->y > 0;
	}

	void Ball::reverseDirectionHorizontal() {
		direction->x = -direction->x;
	}

	void Ball::reverseDirectionVertical() {
		direction->y = -direction->y;
	}
    
}
