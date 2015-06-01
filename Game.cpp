#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Game.hpp"

namespace Cong {

	static const int TARGET_FPS = 50;
	static const float SECONDS_PER_FRAME = 1.0 / TARGET_FPS;
    
    static const int PADDING = 20;
    static const int PADDLE_WIDTH = 20;
    static const int PADDLE_HEIGHT = 80;
	static const int PADDLE_SPEED = 400;
    static const int BALL_RADIUS = 14;
	static const int BALL_SPEED = 300;
	static const float BALL_SPEED_INCREASE = 0.05;

	static const int COURT_COLOR[] = {255, 255, 255};
    static const int BALL_COLOR[] = {255, 255, 255};
	static const int PADDLE_COLOR[] = {255, 255, 255};

	static const std::string TEXTURE_DIR = "./tex/";
	static const std::string BALL_TEXTURE = "ball4.png";
	static const std::string COURT_TEXTURE = "court.png";
	static const std::string PADDLE_TEXTURE = "";
	static const std::string FONT_TEXTURE = "charmap-cellphone-white.png";

	static const std::string SOUND_DIR = "./sfx/";
	static const std::string BEEP_SOUND = "beep.wav";
	static const std::string HIT_PADDLE_SOUND = "ping_pong_8bit_beeep.ogg";
	static const std::string HIT_WALL_SOUND = "ping_pong_8bit_plop.ogg";
	static const std::string BALL_OUT_SOUND = "ping_pong_8bit_peeeeeep.ogg";

	Game::Game(const std::string &title, int width, int height) :
			window(0), title(title), width(width), height(height), state(0)
	{
        window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	}

	void Game::setState(GameState *state) {
		if (this->state != nullptr) {
			this->state->exit();
			delete this->state;
		}
		this->state = state;
		state->enter();
	}

	Game::~Game() {
		window->close();

		delete state;
		delete window;
	}

	void Game::run() {

		sf::Clock clock;
		std::cout << "Target SPF: " << SECONDS_PER_FRAME << std::endl;

		while (window->isOpen()) {
			sf::Time elapsed = clock.restart();
			float elapsedSeconds = elapsed.asSeconds();
			// std::cout << "Elapsed: " << elapsedSeconds << "s\n"; 

			// We're gonna be optimistic and assume no computer will lage behind
			if (elapsedSeconds < SECONDS_PER_FRAME) {
				long sleepingTime = (SECONDS_PER_FRAME - elapsedSeconds) * 1000;
				// std::cout << "Sleeping for " << sleepingTime << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(sleepingTime));
			}

            processEvents();
            processInputs();  
            update();
            render();
		}
	}

    void Game::processEvents() {

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        state->processEvents(this);
    }

	void Game::processInputs() {
		/*
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window->close();
        }
		*/
		state->processInputs(this);
	}

	void Game::update() {
		state->update(this);
	}

	void Game::render() {
        state->render(this);
	}

	sf::RenderWindow* Game::getWindow() const {
		return window;
	}

	float Game::getDeltaTime() const {
		return SECONDS_PER_FRAME;
	}

	bool Game::loadSound(const std::string &soundFile, sf::SoundBuffer &buffer, sf::Sound &sound) {
		if (!buffer.loadFromFile(soundFile)) {
			std::cerr << "Error: Could not load sound file " << soundFile << std::endl;
			return false;
		}
		sound.setBuffer(buffer);
		std::cout << "Loaded " << soundFile << " (Duration: " << buffer.getDuration().asMilliseconds() << " ms)" << std::endl;
		return true;
	}

	bool Game::loadTexture(const std::string &textureFile, sf::Texture &texture) {
		if (!texture.loadFromFile(textureFile)) {
			std::cerr << "Error: Could not load image file " << textureFile << std::endl;
			return false;
		}
		std::cout << "Loaded " << textureFile << " (Size: " << texture.getSize().x << " x " << texture.getSize().y << " px)" << std::endl;
		return true;	
	}
    
}
