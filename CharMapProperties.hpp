#ifndef CONG_CHARMAPPROPERTIES_HPP
#define CONG_CHARMAPPROPERTIES_HPP

#include <string>

namespace Cong {

class CharMapProperties {

private:

	std::string chars;		
	unsigned int charWidth;
	unsigned int charHeight;
	unsigned int charPadding;
	unsigned int charsPerLine;

public:

	CharMapProperties(std::string chars, int charWidth, int charHeight, int charPadding, int charsPerLine);
	~CharMapProperties();

	unsigned int getCharWidth() const;
	unsigned int getCharHeight() const;
	unsigned int getCharPadding() const;
	unsigned int getCharsPerLine() const;

};



}

#endif
