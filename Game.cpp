#include <chrono>
#include <thread>
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
	static const int PADDLE_SPEED = 150;
    static const int BALL_RADIUS = 10;
	static const int BALL_SPEED = 200;

	Game::Game(const std::string &title, int width, int height) : title(title), width(width), height(height) {
        window = new sf::RenderWindow(sf::VideoMode(width, height), title);
        
        ball = new Cong::Ball(BALL_RADIUS, 0);
        paddle1 = new Cong::Paddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT), PADDLE_SPEED);
        paddle2 = new Cong::Paddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT), PADDLE_SPEED);
        
        ball->setPosition(width * 0.5, height * 0.5); // The Ball's origin is at its center!
        paddle1->setPosition(PADDING, height * 0.5 - (PADDLE_HEIGHT * 0.5));
        paddle2->setPosition(width - (PADDLE_WIDTH + PADDING), height * 0.5 - (PADDLE_HEIGHT * 0.5));
        
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

	void Game::update() {
        
		float ballSpeed = ball->getSpeed() * SECONDS_PER_FRAME;

        sf::Vector2f ballPositionNext((ball->getPosition().x + ball->getDirection().x * ballSpeed), (ball->getPosition().y + ball->getDirection().x * ballSpeed));
        
		if (ballPositionNext.x - BALL_RADIUS <= paddle1->getPosition().x + PADDLE_WIDTH) {
			std::cout << "karambi!\n";
			if (ballPositionNext.y >= paddle1->getPosition().y
				 && ballPositionNext.y <= paddle1->getPosition().y + PADDLE_HEIGHT) {
				std::cout << "korombishi!!!\n";
				ball->reverseDirectionHorizontal();
			}
		}
		

        if (ballPositionNext.x <= 0 + BALL_RADIUS) {
            ballPositionNext.x = 0 + BALL_RADIUS;
			ball->reverseDirectionHorizontal();
        }
        
        if (ballPositionNext.x >= width - BALL_RADIUS) {
            ballPositionNext.x = width - BALL_RADIUS;
			ball->reverseDirectionHorizontal();
        }
    
        if (ballPositionNext.y <= 0 + BALL_RADIUS) {
            ballPositionNext.y = 0 + BALL_RADIUS;
            ball->reverseDirectionVertical();
        }
        
        if (ballPositionNext.y >= height - BALL_RADIUS) {
            ballPositionNext.y = height - BALL_RADIUS;
            ball->reverseDirectionVertical();
        }
        
        ball->move(ball->getDirection().x * ballSpeed, ball->getDirection().y * ballSpeed);
        
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
            int paddle1Y = paddle1Pos.y - PADDLE_SPEED * SECONDS_PER_FRAME;
            paddle1Y = paddle1Y < 0 ? 0 : paddle1Y;
            
            paddle1->setPosition(sf::Vector2f(paddle1Pos.x, paddle1Y));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sf::Vector2f paddle1Pos = paddle1->getPosition();
            int paddle1Y = paddle1Pos.y + PADDLE_SPEED * SECONDS_PER_FRAME;
            paddle1Y = paddle1Y + paddle1->getSize().y > height ? height - paddle1->getSize().y : paddle1Y;
            
            paddle1->setPosition(sf::Vector2f(paddle1Pos.x, paddle1Y));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sf::Vector2f paddle2Pos = paddle2->getPosition();
            int paddle2Y = paddle2Pos.y - PADDLE_SPEED * SECONDS_PER_FRAME;
            paddle2Y = paddle2Y < 0 ? 0 : paddle2Y;
            
            paddle2->setPosition(sf::Vector2f(paddle2Pos.x, paddle2Y));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sf::Vector2f paddle2Pos = paddle2->getPosition();
            int paddle2Y = paddle2Pos.y + PADDLE_SPEED * SECONDS_PER_FRAME;
            paddle2Y = paddle2Y + paddle2->getSize().y > height ? height - paddle2->getSize().y  : paddle2Y;
            
            paddle2->setPosition(sf::Vector2f(paddle2Pos.x, paddle2Y));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            ball->setDirection(sf::Vector2f(1, 0));
            ball->setSpeed(BALL_SPEED);
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
            ball->setDirection(sf::Vector2f(0, 1));
            ball->setSpeed(BALL_SPEED);
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            ball->setDirection(sf::Vector2f(1, 1));
            ball->setSpeed(BALL_SPEED);
        }
	}

}
