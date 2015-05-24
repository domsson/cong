#include "CharMapProperties.hpp"

namespace Cong {

	CharMapProperties::CharMapProperties(std::string chars, int charWidth, int charHeight, int charPadding, int charsPerLine) 
		: chars(chars), charWidth(charWidth), charHeight(charHeight), charPadding(charPadding), charsPerLine(charsPerLine)	
	{
	
	}

	CharMapProperties::~CharMapProperties() {
	}

}
