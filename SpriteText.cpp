#include "SpriteText.hpp"

namespace Cong {

	SpriteText::SpriteText(const std::string &charMapTexture, CharMapProperties *charMapProperties)
		: charMapProperties(charMapProperties)	
	{
		setCharMap(charMapTexture);
	}

	SpriteText::SpriteText(sf::Texture *charMap, CharMapProperties *charMapProperties)
		: charMap(charMap), charMapProperties(charMapProperties)	
	{
	}
	
	SpriteText::~SpriteText() {
		delete charMap;
		delete charMapProperties;
		delete[] charSprites;
	}
	
	void SpriteText::setText(const std::string &text) {
	}

	void SpriteText::setCharMap(const std::string &charMapTexture) {
	}

	void SpriteText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		/*		
		for (int i=0; i<numChars; ++i) {		
			target.draw(whatever, states);
		}
		*/
	}

}
