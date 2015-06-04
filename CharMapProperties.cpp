#include "CharMapProperties.hpp"

namespace Cong {

	std::string CharMapProperties::DEFAULT_CHARS = " !\"#$%&'()*+,-./123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	unsigned int CharMapProperties::DEFAULT_CHAR_WIDTH = 5;
	unsigned int CharMapProperties::DEFAULT_CHAR_HEIGHT = 7;
	unsigned int CharMapProperties::DEFAULT_CHAR_PADDING = 1;
	unsigned int CharMapProperties::DEFAULT_CHARS_PER_LINE = 16;

	CharMapProperties::CharMapProperties() : CharMapProperties(DEFAULT_CHARS, DEFAULT_CHAR_WIDTH, DEFAULT_CHAR_HEIGHT, DEFAULT_CHAR_PADDING, DEFAULT_CHARS_PER_LINE) {
	}

	CharMapProperties::CharMapProperties(std::string chars, int charWidth, int charHeight, int charPadding, int charsPerLine) 
		: chars(chars), charWidth(charWidth), charHeight(charHeight), charPadding(charPadding), charsPerLine(charsPerLine)	
	{
	
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
		unsigned int charColumn = pos % charsPerLine;
		return (charColumn * (charWidth + charPadding));
	}

	int CharMapProperties::getCharPosY(char c) const {
		std::size_t pos = chars.find(c);
		if (pos == std::string::npos) { return -1; }
		unsigned int charRow = pos / charsPerLine;
		return (charRow * (charHeight + charPadding));		
	}

}
