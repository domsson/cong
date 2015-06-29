#ifndef CONG_OPTIONS_HPP
#define CONG_OPTIONS_HPP

#include <string>
#include <iostream>

namespace Cong
{

enum Resolution {
	LOW,
	MEDIUM,
	HIGH
};

enum Theme {
	CLASSIC,
	FANCY
};

enum Sound {
	ON,
	OFF
};

class Options
{

public:
	
	static const Resolution DEFAULT_RESOLUTION = LOW;
	static const Theme DEFAULT_THEME = CLASSIC;
	static const Sound DEFAULT_PLAY_SOUNDS = ON;

	static Resolution resolution;
	static Theme theme;
	static Sound playSounds;

	Options();

};

}

#endif

