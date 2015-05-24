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

}
