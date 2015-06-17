#include "MenuState.hpp"

namespace Cong
{

	const int MenuState::DEFAULT_MENU_OFFSET = 64;
	const int MenuState::DEFAULT_TITLE_SCALE = 8;
	const int MenuState::DEFAULT_TITLE_MARGIN = 32;
	const int MenuState::DEFAULT_ITEM_SCALE = 4;
	const int MenuState::DEFAULT_ITEM_MARGIN = 32;

	const sf::Color MenuState::DEFAULT_TITLE_COLOR = sf::Color::Red;
	const sf::Color MenuState::DEFAULT_ITEM_COLOR = sf::Color::White;
	const sf::Color MenuState::DEFAULT_SELECT_COLOR = sf::Color::Green;

	MenuState::MenuState(Game &game)
	: GameState(game), charMap(nullptr), currentMenuItem(0), titleIsSet(false)
	{
		initCharMap();
		initTitle();
	}

	MenuState::~MenuState()
	{
		// Do nothing
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

	void MenuState::addMenuItem(const std::string &label, int itemScale=DEFAULT_ITEM_SCALE)
	{
		SpriteText newItem;
		newItem.setCharMap(*charMap);
		newItem.setScale(sf::Vector2f(itemScale, itemScale));
		newItem.setAnchor(SpriteTextAnchor::TOP_CENTER);
		int offsetY = menuItems.size() * (newItem.getHeight() + DEFAULT_ITEM_MARGIN);
		newItem.setPosition(game->getViewportWidth() * 0.5, DEFAULT_MENU_OFFSET * 2 + offsetY);
		newItem.setText(label);

		menuItems.push_back(newItem);		
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
