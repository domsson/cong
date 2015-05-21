#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Game.hpp"

namespace Cong {
    
    const int Game::EDGE_TOP = 1;
    const int Game::EDGE_RIGHT = 2;
    const int Game::EDGE_BOTTOM = 4;
    const int Game::EDGE_LEFT = 8;

	static const int TARGET_FPS = 50;
	static const float SECONDS_PER_FRAME = 1.0 / TARGET_FPS;
    
    static const int PADDING = 20;
    static const int PADDLE_WIDTH = 20;
    static const int PADDLE_HEIGHT = 80;
	static const int PADDLE_SPEED = 150;
    static const int BALL_RADIUS = 10;
	static const int BALL_SPEED = 225;
    static const int FILL_COLOR[] = {0, 255, 0};

	Game::Game(const std::string &title, int width, int height) : title(title), width(width), height(height) {
        window = new sf::RenderWindow(sf::VideoMode(width, height), title);
        
        court = new Cong::Court(width, height, 4, 15);
        
        ball = new Cong::Ball(BALL_RADIUS, 0);
        ball->setPosition(width * 0.5, height * 0.5); // The Ball's origin is at its center!
        ball->setFillColor(sf::Color(FILL_COLOR[0], FILL_COLOR[1], FILL_COLOR[2]));
        
        paddleLeft = new Cong::Paddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT), PADDLE_SPEED);
		paddleLeft->setOrigin(PADDLE_WIDTH, PADDLE_HEIGHT * 0.5);
        paddleLeft->setPosition(PADDING + PADDLE_WIDTH, height * 0.5); // Origin at right edge, vertically centered
        paddleLeft->setFillColor(sf::Color(FILL_COLOR[0], FILL_COLOR[1], FILL_COLOR[2]));
        
        paddleRight = new Cong::Paddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT), PADDLE_SPEED);
		paddleRight->setOrigin(0, PADDLE_HEIGHT * 0.5);
        paddleRight->setPosition(width - (PADDLE_WIDTH + PADDING), height * 0.5); // Origin at left edge, vertically centered
        paddleRight->setFillColor(sf::Color(FILL_COLOR[0], FILL_COLOR[1], FILL_COLOR[2]));
	}

	Game::~Game() {
		window->close();

		delete window;
		delete ball;
		delete court;
		delete paddleLeft;
		delete paddleRight;
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
        sf::FloatRect paddleLeftBounds = paddleLeft->getGlobalBounds();
        
		
		if (ballPositionNext.x - BALL_RADIUS <= paddleLeft->getPosition().x) {
            int edge = 0;
			if (ball->intersects(paddleLeft->getGlobalBounds(), edge)) {
                if ((edge & EDGE_RIGHT) == EDGE_RIGHT) {
					float yDiff = (ballPositionNext.y - paddleLeft->getPosition().y) / (PADDLE_HEIGHT * 0.5);                    
					ball->reverseDirectionHorizontal();
					ball->slope(yDiff);
                }
                if (((edge & EDGE_TOP) == EDGE_TOP) || ((edge & EDGE_BOTTOM) == EDGE_BOTTOM)) {
                    ball->reverseDirectionVertical();
                }
			}
		}		


		// Collision with left paddle?
		if (ball->isMovingLeft()) {
			/*
            // Collision with right edge?
			if (ballPositionNext.x - BALL_RADIUS <= paddleLeft->getPosition().x) {
                // Let's have some cool circle line intersection math here!
                sf::Vector2f paddleLeftY(paddleLeft->getPosition().y - PADDLE_HEIGHT * 0.5, paddleLeft->getPosition().y + PADDLE_HEIGHT * 0.5);
                float radicand = - (paddleLeft->getPosition().x * paddleLeft->getPosition().x) - (ballPositionNext.x * ballPositionNext.x)
                                    + (2 * ballPositionNext.x * paddleLeft->getPosition().x) + (BALL_RADIUS * BALL_RADIUS);
                
                if (radicand >= 0) {
                    float y1 = ballPositionNext.y + std::sqrt(radicand);
                    float y2 = ballPositionNext.y - std::sqrt(radicand);
                    
                    if (y1 >= paddleLeftY.x && y2 <= paddleLeftY.y) {
                        float yDiff = (ballPositionNext.y - paddleLeft->getPosition().y) / (PADDLE_HEIGHT * 0.5);
                        ballPositionNext.x = paddleLeft->getPosition().x + BALL_RADIUS;
                        ball->reverseDirectionHorizontal();
                        ball->slope(yDiff);
                    }
                }
			}
            
            // Collision with bottom edge?
            if (ball->isMovingUp()) {
                float paddleLeftBottomY = paddleLeft->getPosition().y + PADDLE_HEIGHT * 0.5;
                if (ballPositionNext.y - BALL_RADIUS <= paddleLeftBottomY) {
                    sf::Vector2f paddleLeftX(paddleLeft->getPosition().x - PADDLE_WIDTH, paddleLeft->getPosition().x);
                    float radicand = - (paddleLeftBottomY * paddleLeftBottomY) - (ballPositionNext.y * ballPositionNext.y)
                                        + (2 * paddleLeftBottomY * ballPositionNext.y) + (BALL_RADIUS * BALL_RADIUS);
                    if (radicand >= 0) {
                        float x1 = ballPositionNext.x - std::sqrt(radicand);
                        float x2 = ballPositionNext.x + std::sqrt(radicand);
                        
                        if (x1 >= paddleLeft->getPosition().x - PADDLE_WIDTH && x1 <= paddleLeft->getPosition().x) {
                            ballPositionNext.y = paddleLeftBottomY + BALL_RADIUS;
                            ball->reverseDirectionVertical();
                        }
                    }
                    
                }
            }
            
            // Collision with top edge?
            else if (ball->isMovingDown()) {
                float paddleLeftTopY = paddleLeft->getPosition().y - PADDLE_HEIGHT * 0.5;
                if (ballPositionNext.y + BALL_RADIUS >= paddleLeftTopY) {
                    sf::Vector2f paddleLeftX(paddleLeft->getPosition().x - PADDLE_WIDTH, paddleLeft->getPosition().x);
                    float radicand = - (paddleLeftTopY * paddleLeftTopY) - (ballPositionNext.y * ballPositionNext.y)
                                        + (2 * paddleLeftTopY * ballPositionNext.y) + (BALL_RADIUS * BALL_RADIUS);
                    if (radicand >= 0) {
                        float x1 = ballPositionNext.x - std::sqrt(radicand);
                        float x2 = ballPositionNext.x + std::sqrt(radicand);
                        
                        if (x1 >= paddleLeft->getPosition().x - PADDLE_WIDTH && x1 <= paddleLeft->getPosition().x) {
                            ballPositionNext.y = paddleLeftTopY - BALL_RADIUS;
                            ball->reverseDirectionVertical();
                        }
                    }
                    
                }
            }
		*/
		}

		// Collision with right paddle?
		if (ball->isMovingRight()) {
			if (ballPositionNext.x + BALL_RADIUS >= paddleRight->getPosition().x) {
				if (ballPositionNext.y >= paddleRight->getPosition().y - PADDLE_HEIGHT * 0.5
					 && ballPositionNext.y <= paddleRight->getPosition().y + PADDLE_HEIGHT * 0.5) {
					float yDiff = (ballPositionNext.y - paddleRight->getPosition().y) / (PADDLE_HEIGHT * 0.5);					
					ballPositionNext.x = paddleRight->getPosition().x - BALL_RADIUS;
					ball->reverseDirectionHorizontal();
					ball->slope(yDiff);
				}
			}
		}
		

        if (ballPositionNext.x + BALL_RADIUS <= 0) {
            // ballPositionNext.x = 0 + BALL_RADIUS;
			// ball->reverseDirectionHorizontal();
            serve();
        }
        
        if (ballPositionNext.x - BALL_RADIUS >= width) {
            // ballPositionNext.x = width - BALL_RADIUS;
			// ball->reverseDirectionHorizontal();
            serve();
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
        window->draw(*court);
        window->draw(*ball);
        window->draw(*paddleLeft);
        window->draw(*paddleRight);
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
            sf::Vector2f paddleLeftPos = paddleLeft->getPosition();
            int paddleLeftY = paddleLeftPos.y - PADDLE_SPEED * SECONDS_PER_FRAME;
            paddleLeftY = paddleLeftY - PADDLE_HEIGHT * 0.5 < 0 ? PADDLE_HEIGHT * 0.5  : paddleLeftY;
            
            paddleLeft->setPosition(sf::Vector2f(paddleLeftPos.x, paddleLeftY));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sf::Vector2f paddleLeftPos = paddleLeft->getPosition();
            int paddleLeftY = paddleLeftPos.y + PADDLE_SPEED * SECONDS_PER_FRAME;
            paddleLeftY = paddleLeftY + PADDLE_HEIGHT * 0.5 > height ? height - PADDLE_HEIGHT * 0.5  : paddleLeftY;
            
            paddleLeft->setPosition(sf::Vector2f(paddleLeftPos.x, paddleLeftY));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sf::Vector2f paddleRightPos = paddleRight->getPosition();
            int paddleRightY = paddleRightPos.y - PADDLE_SPEED * SECONDS_PER_FRAME;
            paddleRightY = paddleRightY - PADDLE_HEIGHT * 0.5 < 0  ? PADDLE_HEIGHT * 0.5  : paddleRightY;
            
            paddleRight->setPosition(sf::Vector2f(paddleRightPos.x, paddleRightY));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sf::Vector2f paddleRightPos = paddleRight->getPosition();
            int paddleRightY = paddleRightPos.y + PADDLE_SPEED * SECONDS_PER_FRAME;
            paddleRightY = paddleRightY + PADDLE_HEIGHT * 0.5  > height ? height - PADDLE_HEIGHT * 0.5   : paddleRightY;
            
            paddleRight->setPosition(sf::Vector2f(paddleRightPos.x, paddleRightY));
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			ball->setPosition(PADDING + BALL_RADIUS, height - BALL_RADIUS * 2 - PADDING);
            ball->setDirection(sf::Vector2f(0, -1));
            ball->setSpeed(BALL_SPEED);
        }
	}
    
    void Game::serve() {
        ball->setSpeed(0);
        ball->setDirection(sf::Vector2f(1, 1));
        ball->setPosition(width * 0.5, height * 0.5);
    }

}
