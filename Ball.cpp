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
    
    bool Ball::contains (const sf::Vector2f &point) const {
        // TODO
        return (point.x - getPosition().x) * (point.x - getPosition().x) + (point.y - getPosition().y) * (point.y - getPosition().y) == getRadius() * getRadius();
    }
    
    bool Ball::intersects (const sf::FloatRect &rectangle) const {
        // TODO: We don't actually need to check intersection with the rect's edges.
        // We need a different math that 'simply' checks if any point within the circle intersects with
        // any point within the rectangle.
        
        // http://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
        // http://stackoverflow.com/questions/18704999/how-to-fix-circle-and-rectangle-overlap-in-collision-response/18790389#18790389
        
        // The ball's center is within the rectangle, so they definitely intersect.
        if (rectangle.contains(getPosition().x, getPosition().y)) {
            return true;
        }
        
        // The ball's center is not within the rectangle, but it might still intersect with one of the four sides.
        
        /*
        // Collision with rect's right edge?
        if (isMovingLeft()) {
            
			if (getPosition().x - BALL_RADIUS <= paddleLeft->getPosition().x) {
                // Let's have some cool circle line intersection math here!
                sf::Vector2f paddleLeftY(paddleLeft->getPosition().y - PADDLE_HEIGHT * 0.5, paddleLeft->getPosition().y + PADDLE_HEIGHT * 0.5);
                float radicand = - (paddleLeft->getPosition().x * paddleLeft->getPosition().x) - (getPosition().x * getPosition().x)
                + (2 * getPosition().x * paddleLeft->getPosition().x) + (BALL_RADIUS * BALL_RADIUS);
                
                if (radicand >= 0) {
                    float y1 = getPosition().y + std::sqrt(radicand);
                    float y2 = getPosition().y - std::sqrt(radicand);
                    
                    if (y1 >= paddleLeftY.x && y2 <= paddleLeftY.y) {
                        float yDiff = (getPosition().y - paddleLeft->getPosition().y) / (PADDLE_HEIGHT * 0.5);
                        getPosition().x = paddleLeft->getPosition().x + BALL_RADIUS;
                        ball->reverseDirectionHorizontal();
                        ball->slope(yDiff);
                    }
                }
			}
		}
        // Collision with rect's left edge?
        else if (isMovingRight()) {
            
        }
        
        // Collision with rect's bottom edge?
        if (isMovingUp()) {
            float paddleLeftBottomY = paddleLeft->getPosition().y + PADDLE_HEIGHT * 0.5;
            if (getPosition().y - BALL_RADIUS <= paddleLeftBottomY) {
                sf::Vector2f paddleLeftX(paddleLeft->getPosition().x - PADDLE_WIDTH, paddleLeft->getPosition().x);
                float radicand = - (paddleLeftBottomY * paddleLeftBottomY) - (getPosition().y * getPosition().y)
                + (2 * paddleLeftBottomY * getPosition().y) + (BALL_RADIUS * BALL_RADIUS);
                if (radicand >= 0) {
                    float x1 = getPosition().x - std::sqrt(radicand);
                    float x2 = getPosition().x + std::sqrt(radicand);
                    
                    if (x1 >= paddleLeft->getPosition().x - PADDLE_WIDTH && x1 <= paddleLeft->getPosition().x) {
                        getPosition().y = paddleLeftBottomY + BALL_RADIUS;
                        ball->reverseDirectionVertical();
                    }
                }
                
            }
        }
        
        // Collision with rect's top edge?
        else if (isMovingDown()) {
            float paddleLeftTopY = paddleLeft->getPosition().y - PADDLE_HEIGHT * 0.5;
            if (getPosition().y + BALL_RADIUS >= paddleLeftTopY) {
                sf::Vector2f paddleLeftX(paddleLeft->getPosition().x - PADDLE_WIDTH, paddleLeft->getPosition().x);
                float radicand = - (paddleLeftTopY * paddleLeftTopY) - (getPosition().y * getPosition().y)
                + (2 * paddleLeftTopY * getPosition().y) + (BALL_RADIUS * BALL_RADIUS);
                if (radicand >= 0) {
                    float x1 = getPosition().x - std::sqrt(radicand);
                    float x2 = getPosition().x + std::sqrt(radicand);
                    
                    if (x1 >= paddleLeft->getPosition().x - PADDLE_WIDTH && x1 <= paddleLeft->getPosition().x) {
                        getPosition().y = paddleLeftTopY - BALL_RADIUS;
                        ball->reverseDirectionVertical();
                    }
                }
                
            }
        }
         */
        return false;
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
