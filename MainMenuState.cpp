#include "Game.hpp"
#include "MainMenuState.hpp"

namespace Cong {

	MainMenuState::MainMenuState(const Game &game)
	: MenuState(game)
	{
		setTitle(this->game->getTitle());

		addMenuItem("Play");
		addMenuItem("Options");
		addMenuItem("Quit");
	}

	MainMenuState::~MainMenuState()
	{
		// Do nothing
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
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						game->getWindow()->close();
						break;

					case sf::Keyboard::Return:
						onConfirmPressed();
						break;
					
					case sf::Keyboard::Up:
						selectPrevMenuItem();
						break;

					case sf::Keyboard::Down:
						selectNextMenuItem();
						break;

					case sf::Keyboard::Num1:
						setItemMargin(8);
						break;

					case sf::Keyboard::Num2:
						setItemMargin(16);
						break;

					case sf::Keyboard::Num3:
						setItemMargin(32);
						break;

					case sf::Keyboard::Num4:
						setItemMargin(64);
						break;
				}
			}
        }
	}

	void MainMenuState::onConfirmPressed()
	{
		switch (currentMenuItem)
		{
			case 0:
				changeState(GameStates::GAMEPLAY);
				break;

			case 1:
				break;

			case 2:
				game->getWindow()->close();
				break;
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

		renderTitle();
		renderItems();

		game->getWindow()->display();
	}

}
