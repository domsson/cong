#include "MainMenuState.hpp"

namespace Cong {

	static const std::string FOO = "Hit <RETURN> to play";
	
	static const int MENU_PADDING = 64;
	static const int MENU_ITEM_SCALE = 4;
	static const int MENU_ITEM_PADDING = 32;
	static const int MENU_START_Y = 128;
	static const char MENU_ITEM_INDICATOR = '>';

	static const std::string MENU_LABEL_PLAY = "Play";
	static const std::string MENU_LABEL_OPTIONS = "Options";
	static const std::string MENU_LABEL_QUIT = "Quit";

	MainMenuState::MainMenuState(Game &game)
	: GameState(game), charMap(nullptr), currentMenuItem(0)
	{
		initCharMap();
		initText();

		addMenuItem("kacke");
		addMenuItem(MENU_LABEL_OPTIONS);
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
		game->getWindow()->draw(intro);
		
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
		headline.setColor(sf::Color::Red);

		intro.setCharMap(*charMap);
		intro.setScale(sf::Vector2f(4, 4));
		intro.setAnchor(SpriteTextAnchor::BOTTOM_CENTER);
		intro.setPosition(game->getViewportWidth() * 0.5, game->getViewportHeight() - MENU_PADDING);
		intro.setText(FOO);		
	}

	void MainMenuState::addMenuItem(const std::string &label)
	{

		SpriteText newItem;
		newItem.setCharMap(*charMap);
		newItem.setScale(sf::Vector2f(MENU_ITEM_SCALE, MENU_ITEM_SCALE));
		newItem.setAnchor(SpriteTextAnchor::TOP_CENTER);
		int offsetY = menuItems.size() * (newItem.getHeight() + MENU_ITEM_PADDING);
		newItem.setPosition(game->getViewportWidth() * 0.5, MENU_START_Y + offsetY);
		newItem.setText("  " + label);
		menuItems.push_back(newItem);


/*
		SpriteText newItem;
		newItem.setCharMap(*charMap);

		unsigned int itemNum = menuItems.size();
		//menuItems.push_back(*(new SpriteText(*charMap)));
		//menuItems.push_back(SpriteText(*charMap));
		menuItems.push_back(newItem);
		menuItems.back().setScale(sf::Vector2f(MENU_ITEM_SCALE, MENU_ITEM_SCALE));
		menuItems.back().setAnchor(SpriteTextAnchor::TOP_CENTER);
		unsigned int offsetY = itemNum * (menuItems.back().getHeight() + MENU_ITEM_PADDING);
		menuItems.back().setPosition(game->getViewportWidth() * 0.5, MENU_START_Y + offsetY);
		menuItems.back().setText("  " + label);
*/
		
	}

	void MainMenuState::selectNextMenuItem()
	{
		std::string prevItemText = menuItems.at(currentMenuItem).getText();
		menuItems.at(currentMenuItem).setText(" " + prevItemText.substr(1, std::string::npos));

		if (++currentMenuItem >= menuItems.size())
		{
			currentMenuItem = 0;
		}
		
		std::string nextItemText = menuItems.at(currentMenuItem).getText();
		menuItems.at(currentMenuItem).setText(MENU_ITEM_INDICATOR + nextItemText.substr(1, std::string::npos));
	}

	void MainMenuState::selectPrevMenuItem()
	{
		std::string prevItemText = menuItems.at(currentMenuItem).getText();
		menuItems.at(currentMenuItem).setText(" " + prevItemText.substr(1, std::string::npos));

		if (--currentMenuItem < 0)
		{
			currentMenuItem = menuItems.size() - 1;
		}
		
		std::string nextItemText = menuItems.at(currentMenuItem).getText();
		menuItems.at(currentMenuItem).setText(MENU_ITEM_INDICATOR + nextItemText.substr(1, std::string::npos));
	}

}
