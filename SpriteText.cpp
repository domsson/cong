#include "SpriteText.hpp"
#include <iostream>

namespace Cong {

	SpriteText::SpriteText(sf::Texture *charMap, CharMapProperties *charMapProperties)
		: charMap(charMap), charMapProperties(charMapProperties)	
	{
		scale = 1;
		anchor = LEFT;
		position.x = 0;
		position.y = 0;
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
		for (int i=0; i<text.length(); ++i) {		
			target.draw(charSprites[i], states);
		}
	}

	void SpriteText::setPosition(float x, float y) {
		position.x = x;
		position.y = y;
		updateSpritePositions();
	}

	void SpriteText::setPosition(const sf::Vector2f &position) {
		this->position.x = position.x;
		this->position.y = position.y;
		updateSpritePositions();
	}

	void SpriteText::setAnchor(SpriteTextAnchor anchor) {
		this->anchor = anchor;
		updateSpritePositions();
	}

	void SpriteText::setScale(unsigned int scale) {
		this->scale = scale;
		updateSpritePositions();
	}

	unsigned int SpriteText::getWidth() const {
		return text.length() * charMapProperties->getCharWidth() * scale;
	}

	unsigned int SpriteText::getHeight() const {
		return charMapProperties->getCharHeight() * scale;
	}

	unsigned int SpriteText::getScale() const {
		return scale;
	}

	SpriteTextAnchor SpriteText::getAnchor() const {
		return anchor;
	}

	const sf::Vector2f& SpriteText::getPosition() const {
		return position;
	}

	void SpriteText::updateSpritePosition(unsigned int i, float offsetX) {
		charSprites[i].setPosition(offsetX + position.x + charMapProperties->getCharWidth() * scale * i, position.y);
		charSprites[i].setScale(sf::Vector2f(scale, scale));
	}

	void SpriteText::updateSpritePositions() {
		float offsetX;
		switch (anchor) {
			case LEFT:
				offsetX = 0;
				break;
			case CENTER:
				offsetX = -getWidth() * 0.5;
				break;
			case RIGHT:
				std::cout << "Anchor: right" << std::endl;
				std::cout << "getWidth(): " << getWidth() << std::endl;
				offsetX = -getWidth();
				break;
		}
		std::cout << "SpriteText offsetX: " << offsetX << std::endl;
		for (int i=0; i < text.length(); ++i) {
			updateSpritePosition(i);
		}
	}

}
