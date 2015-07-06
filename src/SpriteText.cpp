#include "CharMap.hpp"
#include "SpriteText.hpp"

namespace Cong {

	SpriteText::SpriteText()
	: charMap(nullptr), charSprites(nullptr), anchor(Anchor::TOP_LEFT), color(sf::Color::White)
	{
		// Do nothing
	}

	SpriteText::SpriteText(const CharMap &charMap)
	: charMap(&charMap), charSprites(nullptr), anchor(Anchor::TOP_LEFT), color(sf::Color::White)
	{
		// Do nothing
	}

	// Copy constructor
	SpriteText::SpriteText(const SpriteText &spriteText)
	: Transformable(spriteText), Drawable(spriteText), charMap(spriteText.charMap),
	  charSprites(nullptr), anchor(spriteText.anchor), color(spriteText.color)
	{
		setText(spriteText.text);
	}

	 // Custom assignment operator
	SpriteText& SpriteText::operator=(const SpriteText &spriteText)
	{
		charMap = spriteText.charMap; // Don't use setCharMap() here, otherwise we'll create overhead
		anchor = spriteText.anchor;
		color = spriteText.color;
		setText(spriteText.text);
	}
	
	SpriteText::~SpriteText()
	{
		delete[] charSprites;
	}

	void SpriteText::setCharMap(const CharMap &charMap)
	{
		this->charMap = &charMap; // Update the reference
		adjustCharSpritesToText(); // Different charMap means the sprites need re-adjustment!
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
			//std::cout << "SpriteText <" << text << "> text adress: " << charSprites << std::endl;
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

	void SpriteText::setAnchor(Anchor anchor)
	{
		this->anchor = anchor;
		updateOrigin();
	}

	void SpriteText::updateOrigin()
	{
		switch (anchor)
		{
			case Anchor::TOP_LEFT:
				setOrigin(0.0, 0.0);
				break;
			case Anchor::TOP_CENTER:
				setOrigin(getUnscaledWidth() * 0.5, 0.0);
				break;
			case Anchor::TOP_RIGHT:
				setOrigin(getUnscaledWidth(), 0.0);
				break;
			case Anchor::CENTER_LEFT:
				setOrigin(0.0, getUnscaledHeight() * 0.5);
				break;
			case Anchor::CENTER_CENTER:
				setOrigin(getUnscaledWidth() * 0.5, getUnscaledHeight() * 0.5);
				break;
			case Anchor::CENTER_RIGHT:
				setOrigin(getUnscaledWidth(), getUnscaledHeight() * 0.5);
				break;
			case Anchor::BOTTOM_LEFT:
				setOrigin(0.0, getUnscaledHeight());
				break;
			case Anchor::BOTTOM_CENTER:
				setOrigin(getUnscaledWidth() * 0.5, getUnscaledHeight());
				break;
			case Anchor::BOTTOM_RIGHT:
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

	Anchor SpriteText::getAnchor() const
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
