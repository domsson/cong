#include "Paddle.hpp"

namespace Cong {
    
    Paddle::Paddle(sf::Vector2f size, int speed) : sf::RectangleShape(size), speed(speed) {
    }
    
    Paddle::~Paddle() {
        
    }

    void Paddle::setSpeed(int speed) {
		this->speed = speed;
	}

    int Paddle::getSpeed() {
		return speed;
	}
    
}

