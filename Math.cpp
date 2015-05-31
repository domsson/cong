#include "Math.hpp"

namespace Cong {

	const int Math::sgn(float x) {
		return (x < 0) ? -1 : 1;
	}

	const bool Math::rangesIntersect(const sf::Vector2f &range1, const sf::Vector2f &range2) {
		return !((range1.x < range2.x && range1.x < range2.y && range1.y < range2.x && range1.y < range2.y) 
		||  (range1.x > range2.x && range1.x > range2.y && range1.y > range2.x && range1.y > range2.y));
	}

}
