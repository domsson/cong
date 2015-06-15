#include "SpriteText.hpp"
#include <iostream>

namespace Cong {

	SpriteText::SpriteText()
	: charMap(nullptr), charSprites(nullptr), anchor(TOP_LEFT), color(sf::Color::White)
	{
		// Do nothing
	}

	SpriteText::SpriteText(const CharMap &charMap)
	: charMap(&charMap), charSprites(nullptr), anchor(TOP_LEFT), color(sf::Color::White)
	{
		// Do nothing
	}
	
	SpriteText::~SpriteText()
	{
		delete[] charSprites;
	}

	void SpriteText::setCharMap(const CharMap &charMap)
	{
		this->charMap = &charMap; // Update the reference
		if (text.length() > 0)
		{
			setText(text); // Setting the text will do all the required sprite adjustments
		}
	}
	
	void SpriteText::setText(const std::string &text)
	{
		this->text = text;
		allocateCharSprites();
		adjustCharSpritesToText();
	}

	void SpriteText::allocateCharSprites()
	{
		delete[] charSprites;
		if (text.length() > 0)
		{
			charSprites = new sf::Sprite[text.length()];
		}
	}

	void SpriteText::adjustCharSpritesToText()
	{
		for (int i=0; i < text.length(); ++i)
		{
			charSprites[i].setTexture(*charMap->getTexture());
			charSprites[i].setColor(color);
			updateSpritePosition(i);
			setCharacter(i, text[i]);
		}
		updateOrigin();
	}

	void SpriteText::updateSpritePosition(unsigned int i)
	{
		charSprites[i].setPosition(charMap->charWidth * i, 0.0);
	}

	void SpriteText::updateSpritePositions()
	{
		for (int i=0; i < text.length(); ++i)
		{
			updateSpritePosition(i);
		}
	}

	void SpriteText::setCharacter(int i, const char &c)
	{
		int charPosX = charMap->getCharPosX(c);
		int charPosY = charMap->getCharPosY(c);

		// If one of the above returned -1, the character c is not defined in the char map properties
		if (charPosX < 0)
		{
			std::cerr << "Warning: Trying to set a SpriteText character that is not known for the used CharMap." << std::endl;
			return;		
		}

		charSprites[i].setTextureRect(sf::IntRect(charPosX, charPosY, charMap->charWidth, charMap->charHeight));
	}

	void SpriteText::setAnchor(SpriteTextAnchor anchor)
	{
		this->anchor = anchor;
		updateOrigin();
	}

	void SpriteText::setColor(const sf::Color &color)
	{
		this->color.r = color.r;
		this->color.g = color.g;
		this->color.b = color.b;
		this->color.a = color.a;

		for (int i=0; i<text.length(); ++i)
		{		
			charSprites[i].setColor(this->color);
		}
	}

	void SpriteText::updateOrigin()
	{
		switch (anchor)
		{
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

	float SpriteText::getWidth() const
	{
		return (charMap == nullptr) ? -1 : getUnscaledWidth() * getScale().x;
	}

	float SpriteText::getHeight() const
	{
		return (charMap == nullptr) ? -1 : getUnscaledHeight() * getScale().y;
	}

	int SpriteText::getUnscaledWidth() const
	{
		return (charMap == nullptr) ? -1 : text.length() * charMap->charWidth;
	}

	int SpriteText::getUnscaledHeight() const
	{
		return (charMap == nullptr) ? -1 : charMap->charHeight;
	}

	std::string SpriteText::getText() const
	{
		return text;
	}

	SpriteTextAnchor SpriteText::getAnchor() const
	{
		return anchor;
	}

	void SpriteText::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		if (charMap == nullptr)
		{
			std::cerr << "Warning: Trying to draw a SpriteText when no CharMap has been set." << std::endl;
			return;		
		}

		states.transform *= getTransform();
		for (int i=0; i<text.length(); ++i)
		{		
			target.draw(charSprites[i], states);
		}
	}

}
