#ifndef CONG_SPRITETEXTURE_HPP
#define CONG_SPRITETEXTURE_HPP

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Anchor.hpp"

namespace Cong {

class CharMap;

class SpriteText : public sf::Transformable, public sf::Drawable {

private:
	const CharMap *charMap;

	std::string text;
	sf::Sprite *charSprites;

	Anchor anchor;
	sf::Color color;

protected:

	void setCharacter(int i, const char &c);
	void updateSpritePosition(unsigned int i);
	void updateSpritePositions();
	void updateOrigin();

	void allocateCharSprites();
	void adjustCharSpritesToText();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:

	SpriteText();
	SpriteText(const CharMap &charMap);
	SpriteText(const SpriteText &spriteText); // Copy constructor
	SpriteText& operator=(const SpriteText &spriteText); // Custom assignment operator
	virtual ~SpriteText();

	void setText(const std::string &text);
	void setCharMap(const CharMap &charMapTexture);
	void setAnchor(Anchor anchor);
	void setColor(const sf::Color &color);

	float getWidth() const;
	float getHeight() const;

	int getUnscaledWidth() const;
	int getUnscaledHeight() const;

	std::string getText() const;
	Anchor getAnchor() const;

};

}

#endif
