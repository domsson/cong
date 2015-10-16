#include "Game.hpp"
#include "Options.hpp"
#include "OptionsMenuState.hpp"

namespace Cong
{

	const std::string RESOLUTION = "Window";
	const std::string RESOLUTION_LOW    = " 640*480";
	const std::string RESOLUTION_MEDIUM = " 800*600";
	const std::string RESOLUTION_HIGH   = "1024*768";
	const std::string RESOLUTION_HIGHER = "1280*960";

	const std::string FULLSCREEN = "Fullscreen";
	const std::string FULLSCREEN_ON = "Yes";
	const std::string FULLSCREEN_OFF = " No";

	const std::string THEME = "Theme";
	const std::string THEME_CLASSIC = "Classic";
	const std::string THEME_FANCY   = " Fancy ";

	const std::string SOUNDS = "Sounds";
	const std::string SOUNDS_ON  = " On";
	const std::string SOUNDS_OFF = "Off";

	OptionsMenuState::OptionsMenuState(const Game &game)
	: MenuState(game)
	{
		setTitle("Options");
		
		// menuItem 0
		std::string resolutions[] = {RESOLUTION_LOW, RESOLUTION_MEDIUM, RESOLUTION_HIGH};
		menu.addItem(RESOLUTION, resolutions, 3);

		// menuItem 1
		std::string themes[] = {THEME_CLASSIC, THEME_FANCY};
		menu.addItem(THEME, themes, 2);

		// menuItem 2
		std::string sounds[] = {SOUNDS_ON, SOUNDS_OFF};
		menu.addItem(SOUNDS, sounds, 2);

		// menuItem 3
		menu.addItem("Back");

		menu.disableItem(1); // No Theme selection functionality yet.
	}

	OptionsMenuState::~OptionsMenuState()
	{
		// Do nothing
	}

	void OptionsMenuState::enter()
	{
		// TODO this is all rotten to the flesh
		loadResolutionOption();
		loadThemeOption();
		loadSoundOption();
	}

	void OptionsMenuState::exit()
	{
		// TODO this is all fucked to the bones
		saveResolutionOption();
		saveThemeOption();
		saveSoundOption();
		game->requestResolutionChange();
	}

	void OptionsMenuState::loadResolutionOption()
	{
		switch (Options::resolution)
		{
			case Resolution::LOW:
				//menuItems.at(0).showOption(RESOLUTION_LOW);
				menu.getItem(0).showOption(RESOLUTION_LOW);
				break;
			case Resolution::MEDIUM:
				//menuItems.at(0).showOption(RESOLUTION_MEDIUM);
				menu.getItem(0).showOption(RESOLUTION_MEDIUM);
				break;
			case Resolution::HIGH:
				//menuItems.at(0).showOption(RESOLUTION_HIGH);
				menu.getItem(0).showOption(RESOLUTION_HIGH);
				break;
		}
	}

	void OptionsMenuState::loadThemeOption()
	{
		switch (Options::theme)
		{
			case Theme::CLASSIC:
				//menuItems.at(1).showOption(THEME_CLASSIC);
				menu.getItem(1).showOption(THEME_CLASSIC);
				break;
			case Theme::FANCY:
				//menuItems.at(1).showOption(THEME_FANCY);
				menu.getItem(1).showOption(THEME_FANCY);
				break;
		}
	}

	void OptionsMenuState::loadSoundOption()
	{
		switch (Options::playSounds)
		{
			case Sound::ON:
				//menuItems.at(2).showOption(SOUNDS_ON);
				menu.getItem(2).showOption(SOUNDS_ON);
				break;
			case Sound::OFF:
				//menuItems.at(2).showOption(SOUNDS_OFF);
				menu.getItem(2).showOption(SOUNDS_OFF);
				break;
		}
	}

	void OptionsMenuState::saveResolutionOption()
	{
		const std::string resolutionOption = menu.getItem(0).getSelectedOption(); // 0 = resolution...

		if (resolutionOption == RESOLUTION_LOW)
		{
			Options::resolution = Resolution::LOW;
		}
		else if (resolutionOption == RESOLUTION_MEDIUM)
		{
			Options::resolution = Resolution::MEDIUM;
		}
		else if (resolutionOption == RESOLUTION_HIGH)
		{
			Options::resolution = Resolution::HIGH;
		}
	}

	void OptionsMenuState::saveThemeOption()
	{
		std::string themeOption = menu.getItem(1).getSelectedOption(); // 1 = themes...

		if (themeOption == THEME_CLASSIC)
		{
			Options::theme = Theme::CLASSIC;
		}
		else if (themeOption == THEME_FANCY)
		{
			Options::theme = Theme::FANCY;
		}
	}

	void OptionsMenuState::saveSoundOption()
	{
		std::string soundOption = menu.getItem(2).getSelectedOption(); // 2 = sound...

		if (soundOption == SOUNDS_ON)
		{
			Options::playSounds = Sound::ON;
		}
		else if (soundOption == SOUNDS_OFF)
		{
			Options::playSounds = Sound::OFF;
		}
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
						menu.selectPrevItem();
						break;

					case sf::Keyboard::Down:
						menu.selectNextItem();
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
		switch (menu.getCurrentItem())
		{
			case 0:
				onRightPressed();
				break;

			case 1:
				onRightPressed();
				break;

			case 2:
				onRightPressed();
				break;

			case 3:
				changeState(GameStates::MAIN_MENU);
				break;
		}
	}

	void OptionsMenuState::onRightPressed()
	{
		menu.getItem(menu.getCurrentItem()).nextOption();
	}

	void OptionsMenuState::onLeftPressed()
	{
		menu.getItem(menu.getCurrentItem()).prevOption();
	}

	void OptionsMenuState::processInputs()
	{
	}

    void OptionsMenuState::update(float deltaTime)
	{
	}

	void OptionsMenuState::render()
	{
		game->getWindow()->clear();
		renderTitle();
		renderMenu();
		game->getWindow()->display();
	}

}
