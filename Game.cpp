#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Game.hpp"

namespace Cong {

	Game::Game(const std::string &title, int width, int height) : title(title), width(width), height(height) {
        window = new sf::RenderWindow(sf::VideoMode(width, height), title);
        
        ball = new Cong::Ball(10, 0);
        paddle1 = new Cong::Paddle(sf::Vector2f(20, 80));
        paddle2 = new Cong::Paddle(sf::Vector2f(20, 80));
        
        ball->setPosition(width * 0.5 - 10, height * 0.5 - 10);
        ball->setDirection(sf::Vector2f(1, 0));
        paddle1->setPosition(20, height * 0.5 - 40);
        paddle2->setPosition(width - 40, height * 0.5 - 40);
        
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

		while (window->isOpen()) {
            processEvents();
            processInputs();
            
            update();
            render();
		}
	}

	void Game::update() {
        
        ball->move(ball->getDirection().x * ball->getSpeed(), ball->getDirection().y * ball->getSpeed());
        
	}

	void Game::render() {
        window->clear();
        window->draw(*ball);
        window->draw(*paddle1);
        window->draw(*paddle2);
        window->display();
	}
    
    void Game::processEvents() {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        
    }

	void Game::processInputs() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window->close();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            sf::Vector2f paddle1Pos = paddle1->getPosition();
            int paddle1Y = paddle1Pos.y - 1;
            paddle1Y = paddle1Y < 0 ? 0 : paddle1Y;
            
            paddle1->setPosition(sf::Vector2f(paddle1Pos.x, paddle1Y));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sf::Vector2f paddle1Pos = paddle1->getPosition();
            int paddle1Y = paddle1Pos.y + 1;
            paddle1Y = paddle1Y + 80 > height ? height - 80 : paddle1Y;
            
            paddle1->setPosition(sf::Vector2f(paddle1Pos.x, paddle1Y));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sf::Vector2f paddle2Pos = paddle2->getPosition();
            int paddle2Y = paddle2Pos.y - 1;
            paddle2Y = paddle2Y < 0 ? 0 : paddle2Y;
            
            paddle2->setPosition(sf::Vector2f(paddle2Pos.x, paddle2Y));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sf::Vector2f paddle2Pos = paddle2->getPosition();
            int paddle2Y = paddle2Pos.y + 1;
            paddle2Y = paddle2Y + 80 > height ? height - 80 : paddle2Y;
            
            paddle2->setPosition(sf::Vector2f(paddle2Pos.x, paddle2Y));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            ball->setSpeed(1);
        }
	}

}
