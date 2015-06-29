#ifndef CONG_CHARMAPPROPERTIES_HPP
#define CONG_CHARMAPPROPERTIES_HPP

#include <string>

namespace Cong {

class CharMapProperties {

private:


public:

	static std::string DEFAULT_CHARS;
	static unsigned int DEFAULT_CHAR_WIDTH;
	static unsigned int DEFAULT_CHAR_HEIGHT;
	static unsigned int DEFAULT_CHAR_PADDING;
	static unsigned int DEFAULT_CHARS_PER_LINE;

	std::string chars;		
	unsigned int charWidth;
	unsigned int charHeight;
	unsigned int charPadding;
	unsigned int charsPerLine;

	CharMapProperties();
	CharMapProperties(std::string chars, int charWidth, int charHeight, int charPadding, int charsPerLine);

	unsigned int getCharWidth() const;
	unsigned int getCharHeight() const;
	unsigned int getCharPadding() const;
	unsigned int getCharsPerLine() const;

	int getCharPosX(char c) const;
	int getCharPosY(char c) const;

};



}

#endif
