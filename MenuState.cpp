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
			return;
		}

		// Deselect the currently selected item, if any
		if (currentMenuItem != -1)
		{
			deselectMenuItem(currentMenuItem);
			currentMenuItem = -1;
		}

		// If <i> refers to an existing menu item, select it
		if (i >= 0 && i < menuItems.size())
		{
			selectMenuItem(i);
			currentMenuItem = i;
		}		
	}

	
	void MenuState::selectNextMenuItem()
	{
		setCurrentItem((currentMenuItem + 1 >= menuItems.size()) ? 0 : currentMenuItem + 1);		
	}

	void MenuState::selectPrevMenuItem()
	{
		setCurrentItem((currentMenuItem - 1 < 0) ? menuItems.size() - 1 : currentMenuItem - 1);
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
