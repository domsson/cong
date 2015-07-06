#include "Game.hpp"
#include "GameState.hpp"
#include "CharMap.hpp"
#include "MenuState.hpp"

namespace Cong
{

	const int MenuState::DEFAULT_MENU_OFFSET = 64;
	const int MenuState::DEFAULT_TITLE_SCALE = 8;
	const int MenuState::DEFAULT_TITLE_MARGIN = 64;

	const sf::Color MenuState::DEFAULT_TITLE_COLOR = sf::Color(10, 140, 75);

	MenuState::MenuState(const Game &game)
	: GameState(game), charMap(nullptr), titleIsSet(false)
	{
		setValuesToDefaults();
		initCharMap();
		initTitle();
		initMenu();
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

		titleColor = DEFAULT_TITLE_COLOR;
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
		title.setAnchor(Anchor::TOP_CENTER);
		title.setPosition(game->getViewportWidth() * 0.5, menuOffset);
		title.setColor(titleColor);
	}

	void MenuState::initMenu()
	{
		menu.setCharMap(*charMap);
		positionMenu();
	}

	void MenuState::setTitle(const std::string &label)
	{
		if (label.length() > 0)
		{
			title.setText(label);
			titleIsSet = true;
		}
		else
		{
			title.setText("");
			titleIsSet = false;
		}

		positionTitleAndMenu();
	}

	void MenuState::positionTitleAndMenu()
	{
		positionTitle();
		positionMenu();
	}

	void MenuState::positionTitle()
	{
		title.setPosition(game->getViewportWidth() * 0.5, menuOffset);
	}

	void MenuState::positionMenu()
	{
		if (titleIsSet)
		{
			menu.setPosition(game->getViewportWidth() * 0.5, title.getPosition().y + title.getHeight() + titleMargin);
		}
		else
		{
			menu.setPosition(game->getViewportWidth() * 0.5, menuOffset);
		}
	}

	void MenuState::scaleTitle()
	{
		title.setScale(titleScale, titleScale);
	}

	void MenuState::styleTitle()
	{
		title.setColor(titleColor);
	}

	void MenuState::setMenuOffset(int offset)
	{
		menuOffset = offset;
		positionTitleAndMenu();
	}

	void MenuState::setTitleScale(int scale)
	{
		titleScale = scale;
		scaleTitle();
		positionTitleAndMenu();
	}

	void MenuState::setTitleMargin(int margin)
	{
		titleMargin = margin;
		positionTitleAndMenu();
	}

	void MenuState::setTitleColor(const sf::Color &color)
	{
		titleColor = color;
	}

	void MenuState::renderTitle() const
	{
		if (titleIsSet)
		{
			game->getWindow()->draw(title);
		}
	}

	void MenuState::renderMenu() const
	{
		game->getWindow()->draw(menu);
	}
}
