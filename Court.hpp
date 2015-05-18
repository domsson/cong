#ifndef CONG_COURT_HPP
#define CONG_COURT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace Cong {

class Court {
    
private:
    int width;
    int height;
    
    sf::RectangleShape **lineSegments;
    int numSegments;
    int segmentWidth;
    
    void initSegments();

public:
	Court(int width, int height, int segmentWidth, int numSegments);
	~Court();
    
    void draw(sf::RenderWindow &window);

};

}

#endif
