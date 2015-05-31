#ifndef CONG_PHYSICS_HPP
#define CONG_PHYSICS_HPP

#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace Cong {

class Physics {

public:
//	static bool intersectionLineCircle(const sf::Vector2f &lineStart, const sf::Vector2f &lineEnd, const sf::Vector2f &circleCenter, int circleRadius);
	static bool intersectionWithX(const sf::Vector2f &lineStart, const sf::Vector2f &lineEnd, float x, float &delta, sf::Vector2f &intersection);
	static bool intersectionWithY(const sf::Vector2f &lineStart, const sf::Vector2f &lineEnd, float y, float &delta, sf::Vector2f &intersection);

private:
    static const int sgn(float x);
};

}

#endif
