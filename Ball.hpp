#ifndef CONG_BALL_HPP
#define CONG_BALL_HPP

#include <SFML/Graphics.hpp>

namespace Cong {

    class Ball: public sf::CircleShape {

public:
	Ball(int radius);
	~Ball();

};

}

#endif
