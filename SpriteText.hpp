#ifndef CONG_SPRITETEXTURE_HPP
#define CONG_SPRITETEXTURE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "CharMapProperties.hpp"
#include "SpriteTextAnchor.hpp"

namespace Cong {

class SpriteText : public sf::Drawable {

private:
	sf::Texture *charMap;
	CharMapProperties *charMapProperties;

	std::string text;
	sf::Sprite *charSprites;

	sf::Vector2f position;

	unsigned int scale;
	SpriteTextAnchor anchor;

protected:

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void setCharacter(int i, const char &c);
	void updateSpritePosition();

public:

	SpriteText(sf::Texture *charMapTexture, CharMapProperties *charMapProperties);
	~SpriteText();

	void setText(const std::string &text);
	void setCharMap(sf::Texture *charMapTexture, CharMapProperties *charMapProperties);
	void setAnchor(SpriteTextAnchor anchor);
	void setScale(unsigned int scale);
	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f &position);

	unsigned int getWidth() const;
	unsigned int getHeight() const;
	unsigned int getScale() const;
	SpriteTextAnchor getAnchor() const;
	const sf::Vector2f& getPosition() const; 

};

}

#endif
