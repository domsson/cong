#include "Game.hpp"

namespace Cong {

	static const int TARGET_FPS = 50;
	static const float SECONDS_PER_FRAME = 1.0 / TARGET_FPS;

	static const std::string TEXTURE_DIR = "./tex/";
	static const std::string SOUND_DIR = "./sfx/";

	static const std::string CHARMAP_TEXTURE = "charmap-cellphone-white.png";
	static const std::string CHARMAP_CHARS = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

	Game::Game(const std::string &title, int width, int height)
	: window(nullptr), title(title), width(width), height(height), activeState(nullptr), charMap(nullptr)
	{
        window = new sf::RenderWindow(sf::VideoMode(width, height), title);

		Game::loadTexture(CHARMAP_TEXTURE, charMapTexture);
		charMap = new CharMap(charMapTexture, CHARMAP_CHARS , 7, 9, 0, 18);
	}


	void Game::setState(GameState *newState)
	{
		if (activeState != nullptr)
		{
			activeState->exit();
			delete activeState;
		}
		activeState = newState;
		newState->enter();
	}


	void Game::changeState(GameStates newState)
	{
		switch (newState)
		{
			case GameStates::NONE:
				
				break;
			case GameStates::MAIN_MENU:
				setState(new MainMenuState(*this));
				break;
			case GameStates::OPTIONS_MENU:
				setState(new OptionsMenuState(*this));
				break;
			case GameStates::GAMEPLAY:
				setState(new PlayState(*this));
				break;
		}
	}

	void Game::tryStateChange()
	{
		if (activeState != nullptr && stateChangeRequested)
		{
			stateChangeRequested = false;
			changeState(activeState->getNextState());
		}
	}

	Game::~Game()
	{
		window->close();

		delete window;
		delete activeState;
		delete charMap;
	}

	void Game::run()
	{
		sf::Clock clock;
		std::cout << "Target SPF: " << SECONDS_PER_FRAME << std::endl;

		while (window->isOpen())
		{
			sf::Time elapsed = clock.restart();
			float elapsedSeconds = elapsed.asSeconds();
			// std::cout << "Elapsed: " << elapsedSeconds << "s\n"; 

			// We're gonna be optimistic and assume no computer will lag behind
			if (elapsedSeconds < SECONDS_PER_FRAME)
			{
				long sleepingTime = (SECONDS_PER_FRAME - elapsedSeconds) * 1000;
				// std::cout << "Sleeping for " << sleepingTime << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(sleepingTime));
			}

			if (activeState != nullptr)
			{
	            processEvents();
	            processInputs();  
	            update();
            	render();
			}
		}
	}

    void Game::processEvents()
	{
		activeState->processEvents();
		tryStateChange();
    }

	void Game::processInputs()
	{
		activeState->processInputs();
		tryStateChange();
	}

	void Game::update()
	{
		activeState->update();
		tryStateChange();
	}

	void Game::render()
	{
    	activeState->render();
		tryStateChange();
	}

	sf::RenderWindow* Game::getWindow() const
	{
		return window;
	}

	float Game::getDeltaTime() const
	{
		return SECONDS_PER_FRAME;
	}

	unsigned int Game::getViewportWidth() const
	{
		return window->getSize().x;	
	}

	unsigned int Game::getViewportHeight() const
	{
		return window->getSize().y;	
	}

	std::string Game::getTitle() const
	{
		return title;
	}

	const CharMap* Game::getDefaultCharMap() const
	{
		return charMap;
	}

	/*
	void Game::requestStateChange() const
	{
		stateChangeRequested = true;
	}
	*/

	bool Game::loadSound(const std::string &soundFile, sf::SoundBuffer &buffer, sf::Sound &sound)
	{
		if (!buffer.loadFromFile(SOUND_DIR + soundFile))
		{
			std::cerr << "Error: Could not load sound file " << soundFile << std::endl;
			return false;
		}
		sound.setBuffer(buffer);
		std::cout << "Loaded " << soundFile << " (Duration: " << buffer.getDuration().asMilliseconds() << " ms)" << std::endl;
		return true;
	}

	bool Game::loadTexture(const std::string &textureFile, sf::Texture &texture)
	{
		if (!texture.loadFromFile(TEXTURE_DIR + textureFile))
		{
			std::cerr << "Error: Could not load image file " << textureFile << std::endl;
			return false;
		}
		std::cout << "Loaded " << textureFile << " (Size: " << texture.getSize().x << " x " << texture.getSize().y << " px)" << std::endl;
		return true;	
	}
    
}
