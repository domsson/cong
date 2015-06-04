#ifndef CONG_SPRITETEXTURE_HPP
#define CONG_SPRITETEXTURE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "CharMap.hpp"
#include "SpriteTextAnchor.hpp"

namespace Cong {

class SpriteText : public sf::Transformable, public sf::Drawable {

private:
	const CharMap *charMap;

	std::string text;
	sf::Sprite *charSprites;

	SpriteTextAnchor anchor;
	sf::Color color;

protected:

	int getUnscaledWidth() const;
	int getUnscaledHeight() const;

	void setCharacter(int i, const char &c);
	void updateSpritePosition(unsigned int i);
	void updateSpritePositions();
	void updateOrigin();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:

	SpriteText(const CharMap &charMap);
	~SpriteText();

	void setText(const std::string &text);
	void setCharMap(const CharMap &charMapTexture);
	void setAnchor(SpriteTextAnchor anchor);
	void setColor(const sf::Color &color);

	float getWidth() const;
	float getHeight() const;
	SpriteTextAnchor getAnchor() const;

};

}

#endif
