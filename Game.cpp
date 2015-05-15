#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Game.hpp"

namespace Cong {
    
    static const int PADDING = 20;
    

	Game::Game(const std::string &title, int width, int height) : title(title), width(width), height(height) {
        window = new sf::RenderWindow(sf::VideoMode(width, height), title);
        
        ball = new Cong::Ball(10, 0);
        paddle1 = new Cong::Paddle(sf::Vector2f(20, 80));
        paddle2 = new Cong::Paddle(sf::Vector2f(20, 80));
        
        ball->setPosition(width * 0.5 - ball->getRadius(), height * 0.5 - ball->getRadius());
        ball->setDirection(sf::Vector2f(1, 0));
        paddle1->setPosition(PADDING, height * 0.5 - (paddle1->getSize().y * 0.5));
        paddle2->setPosition(width - (paddle2->getSize().x + PADDING), height * 0.5 - (paddle2->getSize().y * 0.5));
        
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
        
        sf::Vector2f ballPositionNext((ball->getPosition().x + ball->getDirection().x * ball->getSpeed()), (ball->getPosition().y + ball->getDirection().x * ball->getSpeed()));
        
        if (ballPositionNext.x < 0) {
            ballPositionNext.x = 0;
            ball->setDirection(sf::Vector2f(-ball->getDirection().x, ball->getDirection().y));
        }
        
        if (ballPositionNext.x > width - ball->getRadius()) {
            ballPositionNext.x = width - ball->getRadius();
            ball->setDirection(sf::Vector2f(-ball->getDirection().x, ball->getDirection().y));
        }
    
        if (ballPositionNext.y < 0) {
            ballPositionNext.y = 0;
            ball->setDirection(sf::Vector2f(ball->getDirection().x, -ball->getDirection().y));
        }
        
        if (ballPositionNext.y > height - ball->getRadius()) {
            ballPositionNext.y = height - ball->getRadius();
            ball->setDirection(sf::Vector2f(ball->getDirection().x, -ball->getDirection().y));
        }
        
        
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
            paddle1Y = paddle1Y + paddle1->getSize().y > height ? height - paddle1->getSize().y : paddle1Y;
            
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
            paddle2Y = paddle2Y + paddle2->getSize().y > height ? height - paddle2->getSize().y  : paddle2Y;
            
            paddle2->setPosition(sf::Vector2f(paddle2Pos.x, paddle2Y));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            ball->setSpeed(1);
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
            ball->setDirection(sf::Vector2f(0, 1));
            ball->setSpeed(1);
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            ball->setDirection(sf::Vector2f(1, 1));
            ball->setSpeed(1);
        }
	}

}
