#ifndef CONG_CHARMAP_HPP
#define CONG_CHARMAP_HPP

#include <SFML/Graphics.hpp>

namespace Cong {

class CharMap {

private:

	const sf::Texture *texture;

public:

	std::string chars;		
	unsigned int charWidth;
	unsigned int charHeight;
	unsigned int charPadding;
	unsigned int charsPerLine;

	// CTOR
	CharMap(const sf::Texture &texture, const std::string &chars, int charWidth, int charHeight, int charPadding, int charsPerLine);

	// SET
	void setTexture(const sf::Texture &texture);
	
	// GET
	const sf::Texture* getTexture() const;

	// MISC
	unsigned int getCharPosX(char c) const;
	unsigned int getCharPosY(char c) const;

};

}

#endif
