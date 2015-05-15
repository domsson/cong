#ifndef CONG_PADDLE_HPP
#define CONG_PADDLE_HPP

#include "MovableObject.hpp"
#include <SFML/Graphics.hpp>

namespace Cong {

    class Paddle: public sf::RectangleShape {

public:
    Paddle(sf::Vector2f size);
	~Paddle();

};

}

#endif
