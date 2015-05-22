#ifndef CONG_SCOREDISPLAY_HPP
#define CONG_SCOREDISPLAY_HPP

#include <SFML/Graphics.hpp>

namespace Cong {

    class ScoreDisplay : public sf::Drawable {

private:
    float posX;
    float posY;
        
    sf::RectangleShape *num1;
    sf::RectangleShape *num2;
    
    int charWidth;
    int charHeight;
    int sizeFactor;
        
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	ScoreDisplay(const sf::Texture &texture, const int charWidth, const int charHeight, const int sizeFactor);
	~ScoreDisplay();

    void setPosition(float x, float y);

};

}

#endif
