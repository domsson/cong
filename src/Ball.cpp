#include "Ball.hpp"
#include "Physics.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Cong {
    
    Ball::Ball(int radius, int speed) : sf::RectangleShape(sf::Vector2f(radius*2, radius*2)), speed(speed) {
        direction = new sf::Vector2f(0, 0);
		setOrigin(radius - 0.5, radius - 0.5);
    }
    
    Ball::~Ball() {
        
    }
    
    void Ball::setSpeed(int speed) {
        this->speed = speed;
    }
    
    int Ball::getSpeed() const {
        return speed;
    }
    
    void Ball::setDirection(const sf::Vector2f &direction) {
        this->direction = new sf::Vector2f(direction.x, direction.y);
		normalizeDirection();
    }
    
    void Ball::setDirection(float x, float y) {
        direction->x = x;
        direction->y = y;
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

	int Ball::getRadius() const {
		return getSize().x * 0.5;
	}

	int Ball::getDiameter() const {
		return getRadius() + getRadius();
	}

	bool Ball::isMovingLeft() const {
		return direction->x < 0;
	}

	bool Ball::isMovingRight() const {
		return direction->x > 0;
	}

	bool Ball::isMovingUp() const {
		return direction->y < 0;
	}

	bool Ball::isMovingDown() const {
		return direction->y > 0;
	}
    
	/*
    bool Ball::contains(const sf::Vector2f &point) const {
        return (point.x - getPosition().x) * (point.x - getPosition().x) + (point.y - getPosition().y) * (point.y - getPosition().y) == getRadius() * getRadius();
    }
	*/

	void Ball::reverseDirectionHorizontal() {
		direction->x = -direction->x;
	}

	void Ball::reverseDirectionVertical() {
		direction->y = -direction->y;
	}
    
	void Ball::slope(float amount) {
		direction->y = amount;
		normalizeDirection();
	}
}
