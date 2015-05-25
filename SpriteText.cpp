#include "SpriteText.hpp"
#include <iostream>

namespace Cong {

	SpriteText::SpriteText(sf::Texture *charMap, CharMapProperties *charMapProperties)
		: charMap(charMap), charMapProperties(charMapProperties)	
	{
		scale = 1;
		anchor = 0;
		charSprites = nullptr;
	}
	
	SpriteText::~SpriteText() {
		// This should be okay.
		delete[] charSprites;
	}
	
	void SpriteText::setText(const std::string &text) {
		this->text = text;
		delete[] charSprites;
		charSprites = new sf::Sprite[text.length()];

		for (int i=0; i < text.length(); ++i) {
			charSprites[i].setTexture(*charMap);
			charSprites[i].setPosition(charMapProperties->getCharWidth() * scale * i, 0);
			charSprites[i].setScale(sf::Vector2f(scale, scale));
			setCharacter(i, text[i]);
		}
	}

	void SpriteText::setCharacter(int i, const char &c) {
		// remove * i after testing
		charSprites[i].setTextureRect(sf::IntRect(0, 0, charMapProperties->getCharWidth() * i, charMapProperties->getCharHeight()));
	}

	void SpriteText::setCharMap(sf::Texture *charMap, CharMapProperties *charMapProperties) {
		this->charMap = charMap;
		this->charMapProperties = charMapProperties;
	}

	void SpriteText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		for (int i=0; i<text.length(); ++i) {		
			target.draw(charSprites[i], states);
		}
	}

	void SpriteText::setAnchor(int anchor) {
		this->anchor = anchor;
	}

	void SpriteText::setScale(int scale) {
		this->scale = scale;
		for (int i=0; i < text.length(); ++i) {
			charSprites[i].setPosition(charMapProperties->getCharWidth() * scale * i, 0);
			charSprites[i].setScale(sf::Vector2f(scale, scale));
		}
	}

	unsigned int SpriteText::getWidth() const {
		return text.length() * charMapProperties->getCharWidth();
	}

	unsigned int SpriteText::getHeight() const {
		return charMapProperties->getCharHeight();
	}

	unsigned int SpriteText::getScale() const {
		return scale;
	}

	unsigned int SpriteText::getAnchor() const {
		return anchor;
	}

}
