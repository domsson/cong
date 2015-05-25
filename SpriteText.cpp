#include "SpriteText.hpp"
#include <iostream>

namespace Cong {

	SpriteText::SpriteText(sf::Texture *charMap, CharMapProperties *charMapProperties)
		: charMap(charMap), charMapProperties(charMapProperties)	
	{
		anchor = LEFT;
		charSprites = nullptr;
	}
	
	SpriteText::~SpriteText() {
		delete[] charSprites;
	}
	
	void SpriteText::setText(const std::string &text) {
		this->text = text;
		delete[] charSprites;
		charSprites = new sf::Sprite[text.length()];

		for (int i=0; i < text.length(); ++i) {
			charSprites[i].setTexture(*charMap);
			updateSpritePosition(i);
			setCharacter(i, text[i]);
		}
		updateOrigin();
	}

	void SpriteText::setCharacter(int i, const char &c) {
		// TODO Handle the case of getCharPos returning -1 (char not in charmap)
		int charPosX = charMapProperties->getCharPosX(c);
		int charPosY = charMapProperties->getCharPosY(c);
		int charWidth = charMapProperties->getCharWidth();
		int charHeight = charMapProperties->getCharHeight();

		charSprites[i].setTextureRect(sf::IntRect(charPosX, charPosY, charWidth, charHeight));
	}

	void SpriteText::setCharMap(sf::Texture *charMap, CharMapProperties *charMapProperties) {
		this->charMap = charMap;
		this->charMapProperties = charMapProperties;
	}

	void SpriteText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		states.transform *= getTransform();
		for (int i=0; i<text.length(); ++i) {		
			target.draw(charSprites[i], states);
		}
	}

	void SpriteText::setAnchor(SpriteTextAnchor anchor) {
		this->anchor = anchor;
		updateOrigin();
	}

	void SpriteText::updateOrigin() {
		switch (anchor) {
			case LEFT:
				setOrigin(0.0, 0.0);
				break;
			case CENTER:
				setOrigin(getUnscaledWidth() * 0.5, 0.0);
				break;
			case RIGHT:
				setOrigin(getUnscaledWidth(), 0.0);
				break;
		}
	}

	float SpriteText::getWidth() const {
		return getUnscaledWidth() * getScale().x;
	}

	int SpriteText::getUnscaledWidth() const {
		return text.length() * charMapProperties->getCharWidth();
	}

	float SpriteText::getHeight() const {
		return getUnscaledHeight() * getScale().y;
	}

	int SpriteText::getUnscaledHeight() const {
		return charMapProperties->getCharHeight();
	}

	SpriteTextAnchor SpriteText::getAnchor() const {
		return anchor;
	}

	void SpriteText::updateSpritePosition(unsigned int i) {
		charSprites[i].setPosition(charMapProperties->getCharWidth() * i, 0.0);
	}

	void SpriteText::updateSpritePositions() {
		for (int i=0; i < text.length(); ++i) {
			updateSpritePosition(i);
		}
	}

}
