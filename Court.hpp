#ifndef CONG_COURT_HPP
#define CONG_COURT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace Cong {

    class Court : public sf::Drawable {
    
private:
    int width;
    int height;
    
    sf::RectangleShape **lineSegments;
    int numSegments;
    int segmentWidth;
    
    void initSegments();
        
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Court(int width, int height, int segmentWidth, int numSegments);
	~Court();
    
    //void draw(sf::RenderWindow &window);

};

}

#endif
