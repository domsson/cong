#ifndef CONG_MATH_HPP
#define CONG_MATH_HPP

#include <cmath>
#include <SFML/System.hpp>

namespace Cong {

class Math {

public:  
	static const int sgn(float x);
	static const bool rangesIntersect(const sf::Vector2f &range1, const sf::Vector2f &range2);

};

}

#endif
