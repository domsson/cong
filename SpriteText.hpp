#ifndef CONG_SPRITETEXTURE_HPP
#define CONG_SPRITETEXTURE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "CharMapProperties.hpp"
#include "SpriteTextAnchor.hpp"

namespace Cong {

class SpriteText : public sf::Transformable, public sf::Drawable {

private:
	sf::Texture *charMap;
	CharMapProperties *charMapProperties;

	std::string text;
	sf::Sprite *charSprites;

	SpriteTextAnchor anchor;

	int getUnscaledWidth() const;
	int getUnscaledHeight() const;

protected:

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void setCharacter(int i, const char &c);
	void updateSpritePosition(unsigned int i);
	void updateSpritePositions();
	void updateOrigin();

public:

	SpriteText(sf::Texture *charMapTexture, CharMapProperties *charMapProperties);
	~SpriteText();

	void setText(const std::string &text);
	void setCharMap(sf::Texture *charMapTexture, CharMapProperties *charMapProperties);
	void setAnchor(SpriteTextAnchor anchor);

	float getWidth() const;
	float getHeight() const;
	SpriteTextAnchor getAnchor() const;

};

}

#endif
