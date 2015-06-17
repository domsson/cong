#include "MainMenuState.hpp"

namespace Cong {

	static const int MENU_PADDING = 64;
	static const int MENU_ITEM_SCALE = 4;
	static const int MENU_ITEM_PADDING = 32;
	static const int MENU_START_Y = 128;
	static const std::string MENU_ITEM_PREFIX = "[ ";
	static const std::string MENU_ITEM_SUFFIX = " ]";

	static const std::string MENU_LABEL_PLAY = "Play";
	static const std::string MENU_LABEL_OPTIONS = "Options";
	static const std::string MENU_LABEL_QUIT = "Quit";

	static const sf::Color COLOR_TITLE = sf::Color::Red;
	static const sf::Color COLOR_DEFAULT = sf::Color::White;
	static const sf::Color COLOR_SELECTED = sf::Color::Green;

	MainMenuState::MainMenuState(Game &game)
	: GameState(game), charMap(nullptr), currentMenuItem(0)
	{
		initCharMap();
		initText();

		addMenuItem(MENU_LABEL_PLAY);
		addMenuItem(MENU_LABEL_OPTIONS);
		addMenuItem(MENU_LABEL_QUIT);

		selectMenuItem(currentMenuItem);
	}

	MainMenuState::~MainMenuState()
	{
		// delete charMap;
	}

	void MainMenuState::enter()
	{
		// Do nothing
	}

	void MainMenuState::exit()
	{
		// Do nothing
	}

	void MainMenuState::processEvents()
	{
        sf::Event event;
        while (game->getWindow()->pollEvent(event))
		{
            if (event.type == sf::Event::Closed)
			{
                game->getWindow()->close();
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					game->getWindow()->close();
				}
				else if (event.key.code == sf::Keyboard::Return)
				{
					changeState(GameStates::GAMEPLAY);
				}
				else if (event.key.code == sf::Keyboard::Up)
				{
					selectPrevMenuItem();
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					selectNextMenuItem();
				}
			}
        }
	}
	
	void MainMenuState::processInputs()
	{
	}

    void MainMenuState::update()
	{
	}
	
	void MainMenuState::render()
	{
		game->getWindow()->clear();
		game->getWindow()->draw(headline);
		
		for (int i=0; i<menuItems.size(); ++i)
		{
			game->getWindow()->draw(menuItems.at(i));
		}

		game->getWindow()->display();
	}

	void MainMenuState::initCharMap()
	{
		if (game != nullptr)
		{
			charMap = game->getDefaultCharMap();
		}
	}

	void MainMenuState::initText()
	{
		headline.setCharMap(*charMap);
		headline.setScale(sf::Vector2f(8, 8));
		headline.setAnchor(SpriteTextAnchor::TOP_CENTER);
		headline.setPosition(game->getViewportWidth() * 0.5, MENU_PADDING);
		headline.setText(game->getTitle());
		headline.setColor(COLOR_TITLE);	
	}

	void MainMenuState::addMenuItem(const std::string &label)
	{
		SpriteText newItem;
		newItem.setCharMap(*charMap);
		newItem.setScale(sf::Vector2f(MENU_ITEM_SCALE, MENU_ITEM_SCALE));
		newItem.setAnchor(SpriteTextAnchor::TOP_CENTER);
		int offsetY = menuItems.size() * (newItem.getHeight() + MENU_ITEM_PADDING);
		newItem.setPosition(game->getViewportWidth() * 0.5, MENU_START_Y * 2 + offsetY);
		newItem.setText(label);

		menuItems.push_back(newItem);		
	}

	void MainMenuState::selectMenuItem(int i)
	{
		menuItems.at(i).setColor(COLOR_SELECTED);
	}

	void MainMenuState::deselectMenuItem(int i)
	{
		menuItems.at(i).setColor(COLOR_DEFAULT);
	}

	void MainMenuState::selectNextMenuItem()
	{
		deselectMenuItem(currentMenuItem);

		if (++currentMenuItem >= menuItems.size())
		{
			currentMenuItem = 0;
		}

		selectMenuItem(currentMenuItem);
	}

	void MainMenuState::selectPrevMenuItem()
	{
		deselectMenuItem(currentMenuItem);
				
		if (--currentMenuItem < 0)
		{
			currentMenuItem = menuItems.size() - 1;
		}

		selectMenuItem(currentMenuItem);
	}

}
