#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Game.hpp"

namespace Cong {

	Game::Game(const std::string &title, int width, int height) : title(title), width(width), height(height) {
	}

	Game::~Game() {
		window->close();

		delete window;
		delete ball;
		delete court;
		delete paddle1;
		delete paddle2;
		delete scoreDisplay;
	}

	void Game::run() {
		window = new sf::RenderWindow(sf::VideoMode(width, height), title);
		sf::CircleShape shape(100.f);
		shape.setFillColor(sf::Color::Green);

		while (window->isOpen())
		{
		    sf::Event event;
		    while (window->pollEvent(event))
		    {
		        if (event.type == sf::Event::Closed)
		            window->close();
		    }

		    window->clear();
		    window->draw(shape);
		    window->display();
		}
	}

	void Game::update() {
	}

	void Game::render(sf::RenderWindow window) {
	}

	void Game::processInputs() {
	}

}
