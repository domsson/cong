#include "Game.hpp"

namespace Cong {

	static const int TARGET_FPS = 50;
	static const float SECONDS_PER_FRAME = 1.0 / TARGET_FPS;
	
	static const std::string GAME_ICON = "icon.png";

	static const std::string TEXTURE_DIR = "./tex/";
	static const std::string SOUND_DIR = "./sfx/";

	static const std::string CHARMAP_TEXTURE = "charmap-cellphone-white.png";
	static const std::string CHARMAP_CHARS = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

	Game::Game(const std::string &title, int width, int height)
	: window(nullptr), title(title), width(width), height(height), activeState(nullptr), charMap(nullptr), iconLoaded(false)
	{
		iconLoaded = gameIcon.loadFromFile(GAME_ICON);
		initWindow();

		Game::loadTexture(CHARMAP_TEXTURE, charMapTexture);
		charMap = new CharMap(charMapTexture, CHARMAP_CHARS , 7, 9, 0, 18);
	}
	
	void Game::initWindow()
	{
		window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Close);
		window->setMouseCursorVisible(false);
		if (iconLoaded)
		{
			window->setIcon(gameIcon.getSize().x, gameIcon.getSize().y, gameIcon.getPixelsPtr());
		}
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

	void Game::requestResolutionChange() const
	{
		resolutionChangeRequested = true;
	}

	void Game::updateWindow()
	{
		sf::Vector2u newResolution;
		
		switch (Options::resolution)
		{
			case (Resolution::LOW):
				newResolution.x = 640;
				newResolution.y = 480;
				break;
			case (Resolution::MEDIUM):
				newResolution.x = 800;
				newResolution.y = 600;
				break;
			case (Resolution::HIGH):
				newResolution.x = 1024;
				newResolution.y =  768;
				break;
		}

		if (window->getSize().x != newResolution.x || window->getSize().y != newResolution.y)
		{
			// setSize() doesn't work when sf::Style::Resize flag not set - BUG in SFML!
			// See: http://en.sfml-dev.org/forums/index.php?topic=12952.0
			// And: https://github.com/SFML/SFML/issues/466
			//window->setSize(newResolution);
			window->create(sf::VideoMode(newResolution.x, newResolution.y), title, sf::Style::Close);
			updateViewport();
		}

		resolutionChangeRequested = false;
	}

	void Game::updateViewport()
	{
			sf::View view;

			float ratio = (float) height / (float) width; // 0.75 in the case of 800x600
			float newRatio = (float) window->getSize().y / (float) window->getSize().x;
			
			if (newRatio == ratio) { // Fits perfectly
				view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));	
			}
			else if (newRatio < ratio) { // Need black bars at left/right
				float viewWidth = (float) window->getSize().y / ratio;
				float fraction = viewWidth / (float) window->getSize().x;
				view.setViewport(sf::FloatRect((1-fraction) * 0.5, 0.0f, fraction, 1.0f));
			}
			else if (newRatio > ratio) { // Need black bars at top/bottom
				float viewHeight = (float) window->getSize().x * ratio;
				float fraction = viewHeight / (float) window->getSize().y;
				view.setViewport(sf::FloatRect(0.0f, (1-fraction) * 0.5, 1.0f, fraction));
			}

			view.setSize(width, height);
			view.setCenter(width * 0.5, height * 0.5); // Why do I have to define these as center of the VIEW's size?
			window->setView(view);
			std::cout << "window.getSize(): " << window->getSize().x << "x" << window->getSize().y << std::endl;
			std::cout << "window.getView().getSize(): " << window->getView().getSize().x << "x" << window->getView().getSize().y << std::endl;
			std::cout << "view.getCenter(): " << view.getCenter().x << "x" << view.getCenter().y << std::endl;
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
			float elapsedSeconds = clock.restart().asSeconds();
			//std::cout << elapsedSeconds << " ";

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
	            update(elapsedSeconds);
            	render();
			}

			if (resolutionChangeRequested)
			{
				updateWindow();
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

	void Game::update(float deltaTime)
	{
		activeState->update(deltaTime);
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
		//return window->getSize().x;
		return width;
	}

	unsigned int Game::getViewportHeight() const
	{
		//return window->getSize().y;
		return height;
	}

	std::string Game::getTitle() const
	{
		return title;
	}

	const CharMap* Game::getDefaultCharMap() const
	{
		return charMap;
	}

	Options* Game::getOptions()
	{
		return &options;
	}

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
