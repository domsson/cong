#include "Physics.hpp"

namespace Cong {

	bool Physics::intersectionLineCircle(const sf::Vector2f &lineStart, const sf::Vector2f &lineEnd, const sf::Vector2f &circleCenter, int circleRadius) {
		// http://mathworld.wolfram.com/Circle-LineIntersection.html

		float dx = lineEnd.x - lineStart.x;
		float dy = lineEnd.y - lineStart.y;
		float dr = std::sqrt(dx * dx + dy * dy);
		float D = lineStart.x * lineEnd.y - lineEnd.x * lineStart.y;
		float radicand = circleRadius * circleRadius * dr * dr - D * D;
		
		return radicand >= 0; 
	}

}
