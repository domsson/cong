#include "Physics.hpp"
#include <iostream>

namespace Cong {

	/*
	 * Checks if the given line segment intersects with the (infinite) vertical line at position x
	 * and sets delta (distance factor; how far down the line segment?) and the intersection point.
	 * Will only return true if the absolute value of delta is between 0 and 1; otherwise false.
	 * Intersection and delta will still be set if the intersection is not within the segment bounds
	 * and can therefore always be evaluated for further processing outside this function.
	 * A delta value of 0 means that there is no intersection (lines are parallel or identical).
	 */
	bool Physics::intersectionWithX(const sf::Vector2f &lineStart, const sf::Vector2f &lineEnd, float x, float &delta, sf::Vector2f &intersection) {
		delta = (x - lineStart.x) / (lineEnd.x - lineStart.x);
		if (delta == 0) { return false; }
		intersection.x = lineStart.x + delta * (lineEnd.x - lineStart.x);
		intersection.y = lineStart.y + delta * (lineEnd.y - lineStart.y);
		if (std::abs(delta) > 1) { return false; }
		return true;
	}

	/*
	 * Checks if the given line segment intersects with the (infinite) horizontal line at position y
	 * and sets delta (distance factor; how far down the line segment?) and the intersection point.
	 * Will only return true if the absolute value of delta is between 0 and 1; otherwise false.
	 * Intersection and delta will still be set if the intersection is not within the segment bounds
	 * and can therefore always be evaluated for further processing outside this function.
	 * A delta value of 0 means that there is no intersection (lines are parallel or identical).
	 */
	bool Physics::intersectionWithY(const sf::Vector2f &lineStart, const sf::Vector2f &lineEnd, float y, float &delta, sf::Vector2f &intersection) {
		delta = (y - lineStart.y) / (lineEnd.y - lineStart.y);	
		if (delta == 0) { return false; }
		intersection.x = lineStart.x + delta * (lineEnd.x - lineStart.x);
		intersection.y = lineStart.y + delta * (lineEnd.y - lineStart.y);
		if (std::abs(delta) > 1) { return false; }
		return true;
	}
    
    const int Physics::sgn(float x) {
        return (x < 0) ? -1 : 1;
    }

}
