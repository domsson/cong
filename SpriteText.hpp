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

protected:

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:

	SpriteText(const std::string &charMapTexture, CharMapProperties *charMapProperties);
	SpriteText(sf::Texture *charMapTexture, CharMapProperties *charMapProperties);
	~SpriteText();

	void setText(const std::string &text);
	void setCharMap(const std::string &charMapTexture);

};

}

#endif
