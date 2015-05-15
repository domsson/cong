#include "Ball.hpp"

namespace Cong {
    
    Ball::Ball(int size, int speed) : sf::CircleShape(size), speed(speed) {
        direction = new sf::Vector2f(0, 0);
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
    
}
