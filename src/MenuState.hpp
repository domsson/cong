#ifndef CONG_MENUSTATE_HPP
#define CONG_MENUSTATE_HPP

#include <string>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Menu.hpp"
// #include "MenuItem.hpp"

namespace Cong
{

class Game;
class GameState;
class CharMap;

class MenuState: public GameState
{

public:

	static const int DEFAULT_MENU_OFFSET;
	static const int DEFAULT_TITLE_SCALE;
	static const int DEFAULT_TITLE_MARGIN;

	static const sf::Color DEFAULT_TITLE_COLOR; // Default color for title

protected:

	int menuOffset;
	int titleScale;
	int titleMargin;

	sf::Color titleColor;

	const CharMap *charMap; // CharMap to be used for title and items

	SpriteText title; // Menu title to be displayed atop all menu items
	bool titleIsSet; // Has the menu title been set?

	Menu menu;

	MenuState(const Game &game); // Protected ctor as this is an abstract base class!
	virtual ~MenuState(); // Virtual dtor makes sure child class dtor is called!

	void initCharMap();
	
	void setTitle(const std::string &label);
	void setTitleScale(int scale);
	void setTitleMargin(int margin);

	void setMenuOffset(int offset);

	void setTitleColor(const sf::Color &color);

	void positionTitle();
	void positionMenu();
	void positionTitleAndMenu();

	void scaleTitle();
	void styleTitle();

	void renderTitle() const;
	void renderMenu() const;

private:
	
	void initTitle(); // Prepare the title for later use
	void initMenu();
	void setValuesToDefaults();

};

}

#endif
