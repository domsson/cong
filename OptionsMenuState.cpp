#include "Game.hpp"
#include "OptionsMenuState.hpp"

namespace Cong
{

	OptionsMenuState::OptionsMenuState(const Game &game)
	: MenuState(game)
	{
		setTitle("Options");
		
		std::string fooOptions[] = {"640 x 480", "800 x 600", "1024 x 768"};
		addMenuItem("Resolution", fooOptions, 2);

		std::string barOptions[] = {"Easy", "Medium", "Hard"};
		addMenuItem("Difficulty", barOptions, 3);

		addMenuItem("Back");
		
	}

	OptionsMenuState::~OptionsMenuState()
	{
		// Do nothing
	}

	void OptionsMenuState::enter()
	{
	}

	void OptionsMenuState::exit()
	{
		// TODO This would be a good place to actually save the options set by the user
	}

	void OptionsMenuState::processEvents()
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
						changeState(GameStates::MAIN_MENU);
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

					case sf::Keyboard::Left:
						onLeftPressed();
						break;

					case sf::Keyboard::Right:
						onRightPressed();
						break;
				}
			}
        }
	}

	void OptionsMenuState::onConfirmPressed()
	{
		switch (currentMenuItem)
		{
			case 0:
				onRightPressed();
				break;

			case 1:
				onRightPressed();
				break;

			case 2:
				changeState(GameStates::MAIN_MENU);
				break;
		}
	}

	void OptionsMenuState::onRightPressed()
	{
		menuItems.at(currentMenuItem).nextOption();
	}

	void OptionsMenuState::onLeftPressed()
	{
		menuItems.at(currentMenuItem).prevOption();
	}

	void OptionsMenuState::processInputs()
	{
	}

    void OptionsMenuState::update()
	{
	}

	void OptionsMenuState::render()
	{
		game->getWindow()->clear();
		renderTitle();
		renderItems();
		game->getWindow()->display();
	}

}
