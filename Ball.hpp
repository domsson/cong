#ifndef CONG_BALL_HPP
#define CONG_BALL_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

namespace Cong {

class Ball: public sf::RectangleShape {
    
private:
    int speed;
    sf::Vector2f *direction;
	void normalizeDirection();

public:
	Ball(int radius, int speed);
	~Ball();
    
    void setSpeed(int speed);
    int getSpeed() const;
    void setDirection(const sf::Vector2f &direction);
    void setDirection(float x, float y);
    const sf::Vector2f &getDirection();
	int getRadius() const;
	int getDiameter() const;

	bool isMovingLeft() const;
	bool isMovingRight() const;
	bool isMovingUp() const;
	bool isMovingDown() const;
    
    bool contains(const sf::Vector2f &point) const;
    bool intersects(const sf::FloatRect &rectangle) const;
    bool intersects(const sf::FloatRect &rectangle, int &edges) const;

	void reverseDirectionHorizontal();
	void reverseDirectionVertical();

	void slope(float amount);

};

}

#endif
