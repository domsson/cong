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

	const sf::Color MenuState::DEFAULT_TITLE_COLOR = sf::Color::Red;
	const sf::Color MenuState::DEFAULT_ITEM_COLOR = sf::Color::White;
	const sf::Color MenuState::DEFAULT_SELECT_COLOR = sf::Color::Green;

	MenuState::MenuState(const Game &game)
	: GameState(game), charMap(nullptr), currentMenuItem(0), titleIsSet(false)
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
		title.setScale(sf::Vector2f(DEFAULT_TITLE_SCALE, DEFAULT_TITLE_SCALE));
		title.setAnchor(SpriteTextAnchor::TOP_CENTER);
		title.setPosition(game->getViewportWidth() * 0.5, DEFAULT_MENU_OFFSET);
		title.setColor(DEFAULT_TITLE_COLOR);
	}

	void MenuState::setTitle(const std::string &label)
	{
		if (label.length() > 0)
		{
			title.setText(label);
			titleIsSet = true;
		}
	}

	void MenuState::addMenuItem(const std::string &label, int itemScale)
	{
		// Create and tweak the new menu item
		SpriteText newItem;
		newItem.setCharMap(*charMap);
		newItem.setScale(sf::Vector2f(itemScale, itemScale));
		newItem.setAnchor(SpriteTextAnchor::TOP_CENTER);
		newItem.setText(label);

		// Insert the new item into the collection
		menuItems.push_back(newItem);

		// Calculate the index of the new item within the collection
		int itemNum = menuItems.size() - 1;

		// Position the new item based on the item above it, if any
		positionItem(itemNum);

		// It this is the first item, 'select' (highlight/hover) it
		if (itemNum == 0)
		{
			selectMenuItem(itemNum);
		}
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

	void MenuState::setMenuOffset(int offset)
	{
		menuOffset = offset;
		positionTitleAndItems();
	}

	void MenuState::setItemScale(int scale)
	{
		itemScale = scale;
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
		positionTitleAndItems();
	}

	void MenuState::setTitleMargin(int margin)
	{
		titleMargin = margin;
		positionTitleAndItems();
	}

	void MenuState::selectMenuItem(int i)
	{
		menuItems.at(i).setColor(DEFAULT_SELECT_COLOR);
	}

	void MenuState::deselectMenuItem(int i)
	{
		menuItems.at(i).setColor(DEFAULT_ITEM_COLOR);
	}

	void MenuState::selectNextMenuItem()
	{
		deselectMenuItem(currentMenuItem);

		if (++currentMenuItem >= menuItems.size())
		{
			currentMenuItem = 0;
		}

		selectMenuItem(currentMenuItem);
	}

	void MenuState::selectPrevMenuItem()
	{
		deselectMenuItem(currentMenuItem);
				
		if (--currentMenuItem < 0)
		{
			currentMenuItem = menuItems.size() - 1;
		}

		selectMenuItem(currentMenuItem);
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
