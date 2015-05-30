#ifndef CONG_PHYSICS_HPP
#define CONG_PHYSICS_HPP

#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace Cong {

class Physics {

public:
	static bool intersectionLineCircle(const sf::Vector2f &lineStart, const sf::Vector2f &lineEnd, const sf::Vector2f &circleCenter, int circleRadius);

private:
    static const int sgn(float x);
};

}

#endif
