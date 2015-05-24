#include "Ball.hpp"
#include "Physics.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Cong {
    
    Ball::Ball(int radius, int speed) : sf::RectangleShape(sf::Vector2f(radius*2, radius*2)), speed(speed) {
        direction = new sf::Vector2f(0, 0);
		setOrigin(radius, radius);
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
    
    bool Ball::contains(const sf::Vector2f &point) const {
        return (point.x - getPosition().x) * (point.x - getPosition().x) + (point.y - getPosition().y) * (point.y - getPosition().y) == getRadius() * getRadius();
    }
    
    bool Ball::intersects(const sf::FloatRect &rectangle) const {
        // http://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
        // http://stackoverflow.com/questions/18704999/how-to-fix-circle-and-rectangle-overlap-in-collision-response/18790389#18790389
        
        // The ball's center is within the rectangle, so they definitely intersect.
        if (rectangle.contains(getPosition().x, getPosition().y)) {
            return true;
        }
        
        // The ball's center is not within the rectangle, but it might still intersect with one of the four sides.
		float rectLeft = rectangle.left;
		float rectRight = rectangle.left + rectangle.width;
		float rectTop = rectangle.top;
		float rectBottom = rectangle.top + rectangle.height;

		float ballLeft = getPosition().x - getRadius();
		float ballRight = getPosition().x + getRadius();
		float ballTop = getPosition().y - getRadius();
		float ballBottom = getPosition().y + getRadius();

        // Collision with rect's right edge?
        if (isMovingLeft()) {
            float radicand = - (rectRight * rectRight) - (getPosition().x * getPosition().x)
            				 + (2 * getPosition().x * rectRight) + (getRadius() * getRadius());
            
            if (radicand >= 0) {
                float y1 = getPosition().y + std::sqrt(radicand);
                float y2 = getPosition().y - std::sqrt(radicand);
                
                if (y1 >= rectTop && y2 <= rectBottom) {
					return true;
                }
            }
		}
        // Collision with rect's left edge?
        else if (isMovingRight()) {
            float radicand = - (rectLeft * rectLeft) - (getPosition().x * getPosition().x)
            				 + (2 * getPosition().x * rectLeft) + (getRadius() * getRadius());
            
            if (radicand >= 0) {
                float y1 = getPosition().y + std::sqrt(radicand);
                float y2 = getPosition().y - std::sqrt(radicand);
                
                if (y1 >= rectTop && y2 <= rectBottom) {
					return true;
                }
            }
        }
        
        // Collision with rect's bottom edge?
        if (isMovingUp()) {
            float radicand = - (rectBottom * rectBottom) - (getPosition().y * getPosition().y)
            				 + (2 * rectBottom * getPosition().y) + (getRadius() * getRadius());

            if (radicand >= 0) {
                float x1 = getPosition().x - std::sqrt(radicand);
                float x2 = getPosition().x + std::sqrt(radicand);
                
                if (x1 >= rectLeft && x1 <= rectRight) {
					return true;
                }
            }
        }
        
        // Collision with rect's top edge?
        else if (isMovingDown()) {
            float radicand = - (rectTop * rectTop) - (getPosition().y * getPosition().y)
            				 + (2 * rectTop * getPosition().y) + (getRadius() * getRadius());

            if (radicand >= 0) {
                float x1 = getPosition().x - std::sqrt(radicand);
                float x2 = getPosition().x + std::sqrt(radicand);
                
                if (x1 >= rectLeft && x1 <= rectRight) {
					return true;
                }
            }
        }
        
        return false;
    }
    
    bool Ball::intersects(const sf::FloatRect &rectangle, int &edges) const {
        bool intersects = false;
        edges = 0;

		sf::Vector2f rectTopLeft(rectangle.left, rectangle.top);
		sf::Vector2f rectTopRight(rectangle.left + rectangle.width, rectangle.top);
		sf::Vector2f rectBottomLeft(rectangle.left, rectangle.top + rectangle.height);
		sf::Vector2f rectBottomRight(rectangle.left + rectangle.width, rectangle.top + rectangle.height);
        
        // The ball's center is within the rectangle, so they definitely intersect.
        if (rectangle.contains(getPosition().x, getPosition().y)) {
            intersects = true;
            std::cout << "Inside" << std::endl;
        }
        
        // The ball's center is not within the rectangle, but it might still intersect with one of the four sides.
        if (isMovingLeft()) {
			if (Physics::intersectionLineCircle(rectTopRight, rectBottomRight, getPosition(), getRadius())) {
                intersects = true;
                edges = edges | 2;
                std::cout << "Right Edge: " << edges << std::endl;
            }
		}
        // Collision with rect's left edge?
        else if (isMovingRight()) {
            if (Physics::intersectionLineCircle(rectTopLeft, rectBottomLeft, getPosition(), getRadius())) {
                intersects = true;
                edges = edges | 8;
                std::cout << "Left Edge: " << edges << std::endl;
            }
        }
        
        // Collision with rect's bottom edge?
        if (isMovingUp()) {
            if (Physics::intersectionLineCircle(rectBottomLeft, rectBottomRight, getPosition(), getRadius())) {
                intersects = true;
                edges = edges | 4;
                std::cout << "Bottom Edge: " << edges << std::endl;
            }
        }
        
        // Collision with rect's top edge?
        else if (isMovingDown()) {
            if (Physics::intersectionLineCircle(rectTopLeft, rectTopRight, getPosition(), getRadius())) {
                intersects = true;
                edges = edges | 1;
                std::cout << "Top Edge: " << edges << std::endl;
            }
        }
        
        return intersects;
    }

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
