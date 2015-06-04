#include "SpriteText.hpp"
#include <iostream>

namespace Cong {

	SpriteText::SpriteText(const CharMap &charMap)
		: charMap(&charMap)	
	{
		anchor = TOP_LEFT;
		charSprites = nullptr;

		color.r = 255;
		color.g = 255;
		color.b = 255;
		color.a = 255;
	}
	
	SpriteText::~SpriteText() {
		delete[] charSprites;
	}
	
	void SpriteText::setText(const std::string &text) {
		this->text = text;
		delete[] charSprites;
		charSprites = new sf::Sprite[text.length()];

		for (int i=0; i < text.length(); ++i) {
			charSprites[i].setTexture(*charMap->getTexture());
			charSprites[i].setColor(color);
			updateSpritePosition(i);
			setCharacter(i, text[i]);
		}
		updateOrigin();
	}

	void SpriteText::setCharacter(int i, const char &c) {
		// TODO Handle the case of getCharPos returning -1 (char not in charmap)
		int charPosX = charMap->getCharPosX(c);
		int charPosY = charMap->getCharPosY(c);

		charSprites[i].setTextureRect(sf::IntRect(charPosX, charPosY, charMap->charWidth, charMap->charHeight));
	}

	void SpriteText::setCharMap(const CharMap &charMap) {
		this->charMap = &charMap;
		updateSpritePositions();
		updateOrigin();
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

	void SpriteText::setColor(const sf::Color &color) {
		this->color.r = color.r;
		this->color.g = color.g;
		this->color.b = color.b;
		this->color.a = color.a;

		for (int i=0; i<text.length(); ++i) {		
			charSprites[i].setColor(this->color);
		}
	}

	void SpriteText::updateOrigin() {
		switch (anchor) {
			case TOP_LEFT:
				setOrigin(0.0, 0.0);
				break;
			case TOP_CENTER:
				setOrigin(getUnscaledWidth() * 0.5, 0.0);
				break;
			case TOP_RIGHT:
				setOrigin(getUnscaledWidth(), 0.0);
				break;
			case CENTER_LEFT:
				setOrigin(0.0, getUnscaledHeight() * 0.5);
				break;
			case CENTER_CENTER:
				setOrigin(getUnscaledWidth() * 0.5, getUnscaledHeight() * 0.5);
				break;
			case CENTER_RIGHT:
				setOrigin(getUnscaledWidth(), getUnscaledHeight() * 0.5);
				break;
			case BOTTOM_LEFT:
				setOrigin(0.0, getUnscaledHeight());
				break;
			case BOTTOM_CENTER:
				setOrigin(getUnscaledWidth() * 0.5, getUnscaledHeight());
				break;
			case BOTTOM_RIGHT:
				setOrigin(getUnscaledWidth(), getUnscaledHeight());
				break;			
		}
	}

	float SpriteText::getWidth() const {
		return getUnscaledWidth() * getScale().x;
	}

	int SpriteText::getUnscaledWidth() const {
		return text.length() * charMap->charWidth;
	}

	float SpriteText::getHeight() const {
		return getUnscaledHeight() * getScale().y;
	}

	int SpriteText::getUnscaledHeight() const {
		return charMap->charHeight;
	}

	SpriteTextAnchor SpriteText::getAnchor() const {
		return anchor;
	}

	void SpriteText::updateSpritePosition(unsigned int i) {
		charSprites[i].setPosition(charMap->charWidth * i, 0.0);
	}

	void SpriteText::updateSpritePositions() {
		for (int i=0; i < text.length(); ++i) {
			updateSpritePosition(i);
		}
	}

}
