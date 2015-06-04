#include "MainMenuState.hpp"
#include "PlayState.hpp"

namespace Cong {

	MainMenuState::MainMenuState(int width, int height)
		: width(width), height(height), charMap(0), charMapTexture(), headline(0), intro(0)
	{
	
		Game::loadTexture("./tex/charmap-cellphone-white.png", charMapTexture);
		charMap = new CharMap(charMapTexture, " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~", 7, 9, 0, 18);

		headline = new SpriteText(*charMap);
		headline->setScale(sf::Vector2f(16, 16));
		headline->setAnchor(SpriteTextAnchor::TOP_CENTER);
		headline->setPosition(width * 0.5, 100);
		headline->setText("Cong!");
		headline->setColor(sf::Color::Red);

		intro = new SpriteText(*charMap);
		intro->setScale(sf::Vector2f(4, 4));
		intro->setAnchor(SpriteTextAnchor::BOTTOM_CENTER);
		intro->setPosition(width * 0.5, height - 100);
		intro->setText("Hit <RETURN> to play");	
	}

	MainMenuState::~MainMenuState()
	{
		delete charMap;
		delete headline;
		delete intro;
	}

	void MainMenuState::enter() {
	}

	void MainMenuState::exit() {
	}

	void MainMenuState::processEvents(Game *game) {
	}
	
	void MainMenuState::processInputs(Game *game) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            game->getWindow()->close();
        }
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            game->setState(new PlayState(width, height));
        }
	}

    void MainMenuState::update(Game *game) {
	}
	
	void MainMenuState::render(Game *game) {
		game->getWindow()->clear();
		game->getWindow()->draw(*headline);
		game->getWindow()->draw(*intro);
		game->getWindow()->display();
	}

}
