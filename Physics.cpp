#include "Physics.hpp"
#include <iostream>

namespace Cong {

	bool Physics::intersectionLineCircle(const sf::Vector2f &lineStart, const sf::Vector2f &lineEnd, const sf::Vector2f &circleCenter, int circleRadius) {
		// http://mathworld.wolfram.com/Circle-LineIntersection.html
        // Circle has to be at origin for this to work!!!
        float x1 = lineStart.x - circleCenter.x;
        float y1 = lineStart.y - circleCenter.y;
        float x2 = lineEnd.x - circleCenter.x;
        float y2 = lineEnd.y - circleCenter.y;
        
		float dx = x2 - x1;
		float dy = y2 - y1;
		float dr = std::sqrt(dx * dx + dy * dy);
		float D = x1 * y2 - x2 * y1;
		float radicand = (circleRadius * circleRadius) * (dr * dr) - (D * D);
		      
        if (radicand < 0) {
            return false;
        }
        
        float sqrtTerm = std::sqrt(radicand);
        float sigTerm = Physics::sgn(dy) * dx;
        float absTerm = std::abs(dy);
        float xTerm = D * dy;
        float yTerm = - D * dx;
        
        if (radicand == 0) {
            sf::Vector2f intersection(0, 0);
            intersection.x = (xTerm / (dr * dr));
            intersection.y = (yTerm / (dr * dr));
            // std::cout << "Tangent Intersection @ " << intersection.x << ", " << intersection.y << std::endl;
            
            return ((intersection.x >= x1 && intersection.x <= x2)
                    && (intersection.y >= y1 && intersection.y <= y2));
        }
        
        else if (radicand > 0) {
            sf::Vector2f intersection1(0, 0);
            sf::Vector2f intersection2(0, 0);
            intersection1.x = (xTerm + sigTerm * sqrtTerm) / (dr * dr);
            intersection2.x = (xTerm - sigTerm * sqrtTerm) / (dr * dr);
            intersection1.y = (yTerm + absTerm * sqrtTerm) / (dr * dr);
            intersection1.y = (yTerm - absTerm * sqrtTerm) / (dr * dr);
            // std::cout << "Real Intersection @ " << intersection1.x << ", " << intersection1.y << "; " << intersection2.x << ", " << intersection2.y << std::endl;
            
            return ((intersection1.x >= x1 && intersection1.x <= x2)
                    && (intersection1.y >= y1 && intersection1.y <= y2)
                    && (intersection2.x >= x1 && intersection2.x <= x2)
                    && (intersection2.y >= y1 && intersection2.y <= y2));
        }
        
        // ?
        return false;
	}
    
    const int Physics::sgn(float x) {
        return (x < 0) ? -1 : 1;
    }

}
