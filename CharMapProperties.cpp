#include "CharMapProperties.hpp"

namespace Cong {

	CharMapProperties::CharMapProperties(std::string chars, int charWidth, int charHeight, int charPadding, int charsPerLine) 
		: chars(chars), charWidth(charWidth), charHeight(charHeight), charPadding(charPadding), charsPerLine(charsPerLine)	
	{
	
	}

	CharMapProperties::~CharMapProperties() {
	}

	unsigned int CharMapProperties::getCharWidth() const {
		return charWidth;
	} 

	unsigned int CharMapProperties::getCharHeight() const {
		return charHeight;
	}

	unsigned int CharMapProperties::getCharPadding() const {
		return charPadding;
	}

	unsigned int CharMapProperties::getCharsPerLine() const {
		return charsPerLine;
	}

	int CharMapProperties::getCharPosX(char c) const {
		std::size_t pos = chars.find(c);
		if (pos == std::string::npos) { return -1; }
		unsigned int charColumn = pos % getCharsPerLine();
		return (charColumn * (getCharWidth() + getCharPadding()));
	}

	int CharMapProperties::getCharPosY(char c) const {
		std::size_t pos = chars.find(c);
		if (pos == std::string::npos) { return -1; }
		unsigned int charRow = pos / getCharsPerLine();
		return (charRow * (getCharHeight() + getCharPadding()));		
	}

}
