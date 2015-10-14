#ifndef CONG_MENU_HPP
#define CONG_MENU_HPP

#include <string>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "MenuItem.hpp"

namespace Cong
{

class Menu: public sf::Drawable, public sf::Transformable
{

public:

	static const int DEFAULT_ITEM_SCALE;
	static const int DEFAULT_ITEM_MARGIN;

	static const sf::Color DEFAULT_ITEM_COLOR; // Default color for unselected menu item
	static const sf::Color DEFAULT_SELECT_COLOR; // Default color for selected menu item
	static const sf::Color DEFAULT_INACTIVE_COLOR; // Default color for disabled menu items

	Menu();
	Menu(const CharMap &charMap);

	void setCharMap(const CharMap &charMap);

	int addItem(const std::string &label, int itemScale=DEFAULT_ITEM_SCALE);
	int addItem(const std::string &label, const std::string options[], int numOptions);
	int addItem(const MenuItem &item);

	void selectNextItemOption();
	void selectPrevItemOption();

	void selectNextItem();
	void selectPrevItem();

	MenuItem& getItem(int i);
	int getCurrentItem() const;

	void enableItem(int i);
	void disableItem(int i);

	float getWidth() const;
	float getHeight() const;
	
	void setAnchor(Anchor anchor);
	
protected:

	Anchor anchor;

	int itemScale;
	int itemMargin;

	sf::Color itemColor;
	sf::Color selectColor;
	sf::Color inactiveColor;

	const CharMap *charMap; // CharMap to be used for the items

	std::vector<MenuItem> items; // The menu items
	int currentItem; // What menu item is currently selected?

	void initCharMap();

	void selectItem(int i);
	void deselectItem(int i);

	void setMenuOffset(int offset);
	void setItemScale(int scale);
	void setItemMargin(int margin);

	void setItemColor(const sf::Color &color);
	void setSelectColor(const sf::Color &color);
	void setInactiveColor(const sf::Color &color);

	//void renderItems() const;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	
	void setValuesToDefaults();
	void positionItem(int i);
	void positionItems();
	void scaleItems();
	void styleItems();

	void setCurrentItem(int i);

	bool itemExists(int i) const;
	int findNextItem(int current = -1, int checked = 0) const;
	int findPrevItem(int current = -1, int checked = 0) const;
	int findWidestItem() const;

	void updateOrigin();

};

}

#endif
