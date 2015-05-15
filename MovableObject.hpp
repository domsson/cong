#ifndef CONG_MOVABLEOBJECT_HPP
#define CONG_MOVABLEOBJECT_HPP

#include <SFML/Graphics.hpp>

namespace Cong {

class MovableObject {
    
private:
    sf::Shape *shape;

public:
	MovableObject();
	~MovableObject();

};

}

#endif
