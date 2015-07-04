#include "Menu.hpp"
#include "CharMap.hpp"

namespace Cong
{

	const int Menu::DEFAULT_ITEM_SCALE = 4;
	const int Menu::DEFAULT_ITEM_MARGIN = 32;

	const sf::Color Menu::DEFAULT_ITEM_COLOR = sf::Color::White;
	const sf::Color Menu::DEFAULT_SELECT_COLOR = sf::Color(200, 170, 60);
	const sf::Color Menu::DEFAULT_INACTIVE_COLOR = sf::Color(175, 175, 175);

	Menu::Menu()
	: charMap(nullptr), currentMenuItem(-1)
	{
		setValuesToDefaults();
	}

	Menu::Menu(const CharMap &charMap)
	: charMap(&charMap), currentMenuItem(-1)
	{
		setValuesToDefaults();
	}

	void Menu::setValuesToDefaults()
	{
		itemScale = DEFAULT_ITEM_SCALE;
		itemMargin = DEFAULT_ITEM_MARGIN;

		itemColor = DEFAULT_ITEM_COLOR;
		selectColor = DEFAULT_SELECT_COLOR;
		inactiveColor = DEFAULT_INACTIVE_COLOR;
	}

	int Menu::addMenuItem(const std::string &label, int itemScale)
	{
		if (charMap == nullptr)
		{
			std::cerr << "Warning: tried to add menu item when no CharMap is set." << std::endl;
			return -1;
		}

		// Create and tweak the new menu item
		MenuItem newItem(*charMap);
		newItem.setScale(sf::Vector2f(itemScale, itemScale));
		newItem.setAnchor(SpriteTextAnchor::TOP_CENTER);
		newItem.setLabel(label);

		addMenuItem(newItem);
	}

	int Menu::addMenuItem(const std::string &label, const std::string options[], int numOptions)
	{
		if (charMap == nullptr)
		{
			std::cerr << "Warning: tried to add menu item when no CharMap is set." << std::endl;
			return -1;
		}

		// Create and tweak the new menu item
		MenuItem newItem(*charMap);
		newItem.setScale(sf::Vector2f(itemScale, itemScale));
		newItem.setAnchor(SpriteTextAnchor::TOP_CENTER);
		newItem.setLabel(label);

		for (int i=0; i<numOptions; ++i)
		{
			newItem.addOption(options[i]);
		}

		addMenuItem(newItem);
	}

	int Menu::addMenuItem(const MenuItem &item)
	{
		// Insert the new item into the collection
		menuItems.push_back(item);

		// Calculate the index of the new item within the collection
		int itemNum = menuItems.size() - 1;

		// Position the new item based on the item above it, if any
		positionItem(itemNum);

		// It this is the first item, 'select' (highlight/hover) it
		if (itemNum == 0)
		{
			setCurrentItem(itemNum);
		}

		// Return the index of the new item so the caller can refer to it later
		return itemNum;
	}

	void Menu::positionItems()
	{
		for (int i=0; i<menuItems.size(); ++i)
		{
			positionItem(i);
		}
	}

	void Menu::positionItem(int i)
	{
		//float x = game->getViewportWidth() * 0.5;
		float x = menuItems.at(findWidestItem()).getWidth() * 0.5;
		float y = 0;

		y = (i == 0) ? 0 : menuItems.at(i-1).getPosition().y + menuItems.at(i-1).getHeight() + itemMargin;
		menuItems.at(i).setPosition(x, y);
	}

	int Menu::findWidestItem() const
	{
		int indexOfWidest = -1;
		int widthOfWidest = 0;
		int currentWidth = 0;

		for (int i=0; i<menuItems.size(); ++i)
		{
			currentWidth = menuItems.at(i).getUnscaledWidth(); // Saves a multiplication in getWidth()
			if (currentWidth > widthOfWidest)
			{
				indexOfWidest = i;
				widthOfWidest = currentWidth;
			}
		}
		return indexOfWidest;
	}

	void Menu::scaleItems()
	{
		for (int i=0; i<menuItems.size(); ++i)
		{
			menuItems.at(i).setScale(itemScale, itemScale);
		}
	}

	void Menu::styleItems()
	{
		for (int i=0; i<menuItems.size(); ++i)
		{
			menuItems.at(i).setColor(itemColor);
		}
	}

	void Menu::setItemScale(int scale)
	{
		itemScale = scale;
		scaleItems();
		positionItems();
	}

	void Menu::setItemMargin(int margin)
	{
		itemMargin = margin;
		positionItems();
	}

	void Menu::setItemColor(const sf::Color &color)
	{
		itemColor = color;
	}

	void Menu::setSelectColor(const sf::Color &color)
	{
		selectColor = color;
	}

	void Menu::setInactiveColor(const sf::Color &color)
	{
		inactiveColor = color;
	}

	/**
	 * Modifies the appearance of the given menu item in order to indicate
	 * that it is the currently selected item. Override in child classes to
	 * define a custom 'selected' style for menu items.
	 */
	void Menu::selectMenuItem(int i)
	{
		menuItems.at(i).setColor(selectColor);
	}

	/**
	 * Modifies the appearance of the given menu item in order to indicate
	 * that it is not currently selected. Override in child classes to define
	 * a custom 'unselected' style for the menu items.
	 */
	void Menu::deselectMenuItem(int i)
	{
		menuItems.at(i).setColor(itemColor);
	}

	/**
	 * Deselects the currently selected menu item and selects the given item.
	 */
	void Menu::setCurrentItem(int i)
	{
		// Do nothing if item <i> is already the currently selected item
		if (i == currentMenuItem)
		{
			std::cerr << "Warning: tried to select the currently selected menu item." << std::endl;
			return;
		}

		// Do nothing it <i> refers to a non-existing menu item
		if (!itemExists(i))
		{
			std::cerr << "Warning: tried to select the non-existing menu item #" << i << "." << std::endl;
			return;
		}

		// Do nothing if the item to be selected is disabled
		if (!menuItems.at(i).isEnabled())
		{
			std::cerr << "Warning: tried to select a deactivated menu item." << std::endl;
			return;
		}

		// Deselect the currently selected item, if any
		if (currentMenuItem != -1)
		{
			deselectMenuItem(currentMenuItem);
			currentMenuItem = -1;
		}

		selectMenuItem(i);
		currentMenuItem = i;
	}


	void Menu::enableItem(int i)
	{
		if (itemExists(i))
		{
			menuItems.at(i).setEnabled(true);
			menuItems.at(i).setColor(itemColor);
		}
	}

	void Menu::disableItem(int i)
	{
		// If we're trying to disable the currently selected item, select the next available item
		if (i == currentMenuItem)
		{
			// Let's find the next available menu item, if any
			int j = findNextMenuItem();

			// If no other is available, then we can't disable the current one, that would be weird
			if (j == -1)
			{
				std::cerr << "Warning: tried to disable the only available menu item." << std::endl;
				return;
			}

			setCurrentItem(j);
		}

		menuItems.at(i).setEnabled(false);
		menuItems.at(i).setColor(inactiveColor);
	}

	bool Menu::itemExists(int i) const
	{
		return (i >= 0 && i < menuItems.size());
	}
	
	void Menu::selectNextMenuItem()
	{
		int i = findNextMenuItem();
		if (i == -1) // There is no next item available
		{
			std::cerr << "Warning: tried to select next menu item when there is none available." << std::endl;
			return;
		}

		setCurrentItem(i);
		//setCurrentItem((currentMenuItem + 1 >= menuItems.size()) ? 0 : currentMenuItem + 1);		
	}
	
	int Menu::findNextMenuItem(int current, int checked) const
	{
		if (current == -1)
		{
			current = currentMenuItem;
		}

		// Did we already make a full circle without success?
		if (checked >= menuItems.size() - 1)
		{
			return -1;
		}

		int next = (current + 1 >= menuItems.size()) ? 0 : current + 1; // Roll over if need be

		if (menuItems.at(next).isEnabled())
		{
			return next;
		}

		return findNextMenuItem(next, ++checked);
	}

	void Menu::selectPrevMenuItem()
	{
		int i = findPrevMenuItem();
		if (i == -1) // There is no previous item available
		{
			std::cerr << "Warning: tried to select previous menu item when there is none available." << std::endl;
			return;
		}

		setCurrentItem(i);
		//setCurrentItem((currentMenuItem - 1 < 0) ? menuItems.size() - 1 : currentMenuItem - 1);
	}

	int Menu::findPrevMenuItem(int current, int checked) const
	{
		if (current == -1)
		{
			current = currentMenuItem;
		}

		// Did we already make a full circle without success?
		if (checked >= menuItems.size() - 1)
		{
			return -1;
		}

		int prev = (current - 1 < 0) ? menuItems.size() - 1 : current - 1; // Roll over if need be

		if (menuItems.at(prev).isEnabled())
		{
			return prev;
		}

		return findPrevMenuItem(prev, ++checked);
	}

/*
	void Menu::renderItems() const
	{
		for (int i=0; i < menuItems.size(); ++i)
		{
			game->getWindow()->draw(menuItems.at(i));
		}
	}
*/

	void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		for (int i=0; i<menuItems.size(); ++i)
		{		
			target.draw(menuItems.at(i), states);
		}
	}

}
