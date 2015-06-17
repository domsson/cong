#ifndef CONG_MENUSTATE_HPP
#define CONG_MENUSTATE_HPP

#include <string>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "GameState.hpp"
#include "CharMap.hpp"
#include "SpriteText.hpp"

namespace Cong
{

class MenuState: public GameState
{

public:

	static const int DEFAULT_MENU_OFFSET;
	static const int DEFAULT_TITLE_SCALE;
	static const int DEFAULT_TITLE_MARGIN;
	static const int DEFAULT_ITEM_SCALE;
	static const int DEFAULT_ITEM_MARGIN;

	static const sf::Color DEFAULT_TITLE_COLOR; // Default color for title
	static const sf::Color DEFAULT_ITEM_COLOR; // Default color for unselected menu item
	static const sf::Color DEFAULT_SELECT_COLOR; // Default color for selected menu item

protected:

	const CharMap *charMap;

	SpriteText title; // Menu title to be displayed atop all menu items
	bool titleIsSet; // Has the menu title been set?
	std::vector<SpriteText> menuItems; // The menu items
	int currentMenuItem; // What menu item is currently selected?

	MenuState(Game &game); // Protected ctor as this is an abstract base class!
	virtual ~MenuState(); // Virtual dtor makes sure child class dtor is called!

	void initCharMap();

	void setTitle(const std::string &label);
	void addMenuItem(const std::string &label, int itemScale);
	void selectNextMenuItem();
	void selectPrevMenuItem();
	void selectMenuItem(int i);
	void deselectMenuItem(int i);

	void renderTitle() const;
	void renderItems() const;

private:
	
	void initTitle();

};

}

#endif