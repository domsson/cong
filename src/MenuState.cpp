#include "Game.hpp"
#include "GameState.hpp"
#include "CharMap.hpp"
#include "MenuState.hpp"

namespace Cong
{

	const int MenuState::DEFAULT_MENU_OFFSET = 64;
	const int MenuState::DEFAULT_TITLE_SCALE = 8;
	const int MenuState::DEFAULT_TITLE_MARGIN = 64;
	const int MenuState::DEFAULT_ITEM_SCALE = 4;
	const int MenuState::DEFAULT_ITEM_MARGIN = 32;

	const sf::Color MenuState::DEFAULT_TITLE_COLOR = sf::Color(10, 140, 75);
	const sf::Color MenuState::DEFAULT_ITEM_COLOR = sf::Color::White;
	const sf::Color MenuState::DEFAULT_SELECT_COLOR = sf::Color(200, 170, 60);
	const sf::Color MenuState::DEFAULT_INACTIVE_COLOR = sf::Color(175, 175, 175);

	MenuState::MenuState(const Game &game)
	: GameState(game), charMap(nullptr), currentMenuItem(-1), titleIsSet(false)
	{
		setValuesToDefaults();
		initCharMap();
		initTitle();
	}

	MenuState::~MenuState()
	{
		// Do nothing
	}

	void MenuState::setValuesToDefaults()
	{
		menuOffset = DEFAULT_MENU_OFFSET;
		titleScale = DEFAULT_TITLE_SCALE;
		titleMargin = DEFAULT_TITLE_MARGIN;
		itemScale = DEFAULT_ITEM_SCALE;
		itemMargin = DEFAULT_ITEM_MARGIN;

		titleColor = DEFAULT_TITLE_COLOR;
		itemColor = DEFAULT_ITEM_COLOR;
		selectColor = DEFAULT_SELECT_COLOR;
		inactiveColor = DEFAULT_INACTIVE_COLOR;
	}

	void MenuState::initCharMap()
	{
		if (game != nullptr)
		{
			charMap = game->getDefaultCharMap();
		}
	}

	void MenuState::initTitle()
	{
		title.setCharMap(*charMap);
		title.setScale(sf::Vector2f(titleScale, titleScale));
		title.setAnchor(SpriteTextAnchor::TOP_CENTER);
		title.setPosition(game->getViewportWidth() * 0.5, menuOffset);
		title.setColor(titleColor);
	}

	void MenuState::setTitle(const std::string &label)
	{
		if (label.length() > 0)
		{
			title.setText(label);
			titleIsSet = true;
		}
	}

	int MenuState::addMenuItem(const std::string &label, int itemScale)
	{
		// Create and tweak the new menu item
		MenuItem newItem(*charMap);
		newItem.setScale(sf::Vector2f(itemScale, itemScale));
		newItem.setAnchor(SpriteTextAnchor::TOP_CENTER);
		newItem.setLabel(label);

		addMenuItem(newItem);
	}

	int MenuState::addMenuItem(const std::string &label, const std::string options[], int numOptions)
	{
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

	int MenuState::addMenuItem(const MenuItem &item)
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

	void MenuState::positionTitleAndItems()
	{
		positionTitle();

		for (int i=0; i<menuItems.size(); ++i)
		{
			positionItem(i);
		}
	}

	void MenuState::positionTitle()
	{
		title.setPosition(game->getViewportWidth() * 0.5, menuOffset);
	}

	void MenuState::positionItem(int i)
	{
		float x = game->getViewportWidth() * 0.5;
		float y = 0;

		// First item
		if (i == 0)
		{
			y = (titleIsSet) ? title.getPosition().y + title.getHeight() + titleMargin : menuOffset;
			menuItems.at(0).setPosition(x, y);
		}
		// Remaining items
		else if (i > 0 && i < menuItems.size())
		{
			y = menuItems.at(i-1).getPosition().y + menuItems.at(i-1).getHeight() + itemMargin;
			menuItems.at(i).setPosition(x, y);
		}
	}

	void MenuState::scaleTitle()
	{
		title.setScale(titleScale, titleScale);
	}

	void MenuState::scaleItems()
	{
		for (int i=0; i<menuItems.size(); ++i)
		{
			menuItems.at(i).setScale(itemScale, itemScale);
		}
	}

	void MenuState::styleTitle()
	{
		title.setColor(titleColor);
	}

	void MenuState::styleItems()
	{
		for (int i=0; i<menuItems.size(); ++i)
		{
			menuItems.at(i).setColor(itemColor);
		}
	}

	void MenuState::setMenuOffset(int offset)
	{
		menuOffset = offset;
		positionTitleAndItems();
	}

	void MenuState::setItemScale(int scale)
	{
		itemScale = scale;
		scaleItems();
		positionTitleAndItems();
	}

	void MenuState::setItemMargin(int margin)
	{
		itemMargin = margin;
		positionTitleAndItems();
	}

	void MenuState::setTitleScale(int scale)
	{
		titleScale = scale;
		scaleTitle();
		positionTitleAndItems();
	}

	void MenuState::setTitleMargin(int margin)
	{
		titleMargin = margin;
		positionTitleAndItems();
	}

	void MenuState::setTitleColor(const sf::Color &color)
	{
		titleColor = color;
	}

	void MenuState::setItemColor(const sf::Color &color)
	{
		itemColor = color;
	}

	void MenuState::setSelectColor(const sf::Color &color)
	{
		selectColor = color;
	}

	void MenuState::setInactiveColor(const sf::Color &color)
	{
		inactiveColor = color;
	}

	/**
	 * Modifies the appearance of the given menu item in order to indicate
	 * that it is the currently selected item. Override in child classes to
	 * define a custom 'selected' style for menu items.
	 */
	void MenuState::selectMenuItem(int i)
	{
		menuItems.at(i).setColor(selectColor);
	}

	/**
	 * Modifies the appearance of the given menu item in order to indicate
	 * that it is not currently selected. Override in child classes to define
	 * a custom 'unselected' style for the menu items.
	 */
	void MenuState::deselectMenuItem(int i)
	{
		menuItems.at(i).setColor(itemColor);
	}

	/**
	 * Deselects the currently selected menu item and selects the given item.
	 */
	void MenuState::setCurrentItem(int i)
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


	void MenuState::enableItem(int i)
	{
		if (itemExists(i))
		{
			menuItems.at(i).setEnabled(true);
			menuItems.at(i).setColor(itemColor);
		}
	}

	void MenuState::disableItem(int i)
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

	bool MenuState::itemExists(int i)
	{
		return (i >= 0 && i < menuItems.size());
	}
	
	void MenuState::selectNextMenuItem()
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
	
	int MenuState::findNextMenuItem(int current, int checked)
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

	void MenuState::selectPrevMenuItem()
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

	int MenuState::findPrevMenuItem(int current, int checked)
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

	void MenuState::renderTitle() const
	{
		if (titleIsSet)
		{
			game->getWindow()->draw(title);
		}
	}

	void MenuState::renderItems() const
	{
		for (int i=0; i < menuItems.size(); ++i)
		{
			game->getWindow()->draw(menuItems.at(i));
		}
	}
}
