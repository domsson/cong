#ifndef CONG_MENUSTATE_HPP
#define CONG_MENUSTATE_HPP

#include <string>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "MenuItem.hpp"

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
	static const int DEFAULT_ITEM_SCALE;
	static const int DEFAULT_ITEM_MARGIN;

	static const sf::Color DEFAULT_TITLE_COLOR; // Default color for title
	static const sf::Color DEFAULT_ITEM_COLOR; // Default color for unselected menu item
	static const sf::Color DEFAULT_SELECT_COLOR; // Default color for selected menu item

protected:

	int menuOffset;
	int titleScale;
	int titleMargin;
	int itemScale;
	int itemMargin;

	sf::Color titleColor;
	sf::Color itemColor;
	sf::Color selectColor;

	const CharMap *charMap; // CharMap to be used for title and items

	SpriteText title; // Menu title to be displayed atop all menu items
	bool titleIsSet; // Has the menu title been set?

	std::vector<MenuItem> menuItems; // The menu items
	int currentMenuItem; // What menu item is currently selected?

	MenuState(const Game &game); // Protected ctor as this is an abstract base class!
	virtual ~MenuState(); // Virtual dtor makes sure child class dtor is called!

	void initCharMap();
	
	int addMenuItem(const std::string &label, int itemScale=DEFAULT_ITEM_SCALE);
	int addMenuItem(const std::string &label, const std::string options[], int numOptions);
	int addMenuItem(const MenuItem &item);

	void selectNextMenuItemOption();
	void selectPrevMenuItemOption();

	void selectNextMenuItem();
	void selectPrevMenuItem();
	void selectMenuItem(int i);
	void deselectMenuItem(int i);

	void setTitle(const std::string &label);
	void setMenuOffset(int offset);
	void setItemScale(int scale);
	void setItemMargin(int margin);
	void setTitleScale(int scale);
	void setTitleMargin(int margin);

	void setTitleColor(const sf::Color &color);
	void setItemColor(const sf::Color &color);
	void setSelectColor(const sf::Color &color);

	void renderTitle() const;
	void renderItems() const;

private:
	
	void initTitle(); // Prepare the title for later use
	void setValuesToDefaults();
	void positionTitle();
	void positionItem(int i);
	void positionTitleAndItems();
	void scaleTitle();
	void scaleItems();
	void styleTitle();
	void styleItems();

	void setCurrentItem(int i);

};

}

#endif
