#ifndef CONG_CHARMAPPROPERTIES_HPP
#define CONG_CHARMAPPROPERTIES_HPP

#include <string>

namespace Cong {

class CharMapProperties {

private:

	std::string chars;		
	int charWidth;
	int charHeight;
	int charPadding;
	int charsPerLine;

public:

	CharMapProperties(std::string chars, int charWidth, int charHeight, int charPadding, int charsPerLine);
	~CharMapProperties();

};



}

#endif
