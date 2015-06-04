#include "CharMap.hpp"

namespace Cong
{

	CharMap::CharMap(const sf::Texture &texture, const std::string &chars, int charWidth, int charHeight, int charPadding, int charsPerLine)
		: texture(&texture), chars(chars), charWidth(charWidth), charHeight(charHeight), charPadding(charPadding), charsPerLine(charsPerLine)
	{
		// Do nothing
	}

	void CharMap::setTexture(const sf::Texture &texture)
	{
		this->texture = &texture;
	}

	const sf::Texture* CharMap::getTexture() const
	{
		return texture;
	}

	unsigned int CharMap::getCharPosX(char c) const
	{
		std::size_t pos = chars.find(c);
		if (pos == std::string::npos) { return -1; }
		unsigned int charColumn = pos % charsPerLine;
		return (charColumn * (charWidth + charPadding));
	}

	unsigned int CharMap::getCharPosY(char c) const
	{
		std::size_t pos = chars.find(c);
		if (pos == std::string::npos) { return -1; }
		unsigned int charRow = pos / charsPerLine;
		return (charRow * (charHeight + charPadding));		
	}
}
