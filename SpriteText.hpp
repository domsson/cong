#ifndef CONG_SPRITETEXTURE_HPP
#define CONG_SPRITETEXTURE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "CharMapProperties.hpp"

namespace Cong {

class SpriteText : public sf::Drawable {

private:
	sf::Texture *charMap;
	CharMapProperties *charMapProperties;

	std::string text;
	sf::Sprite *charSprites;

	unsigned int width;
	unsigned int height;
	unsigned int scale;
	unsigned int anchor;

protected:

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void setCharacter(int i, const char &c);

public:

	SpriteText(sf::Texture *charMapTexture, CharMapProperties *charMapProperties);
	~SpriteText();

	void setText(const std::string &text);
	void setCharMap(sf::Texture *charMapTexture, CharMapProperties *charMapProperties);
	void setAnchor(int anchor);
	void setScale(int scale);

	unsigned int getWidth() const;
	unsigned int getHeight() const;
	unsigned int getScale() const;
	unsigned int getAnchor() const;

};

}

#endif
