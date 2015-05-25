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
    static const int FILL_COLOR[] = {255, 255, 255};

	Game::Game(const std::string &title, int width, int height) : title(title), width(width), height(height) {
        window = new sf::RenderWindow(sf::VideoMode(width, height), title);
        
		scoreLeft = 0;
		scoreRight = 0;

		ballTexture = new sf::Texture();
		ballTexture->loadFromFile("./tex/ball2.png");
		courtTexture = new sf::Texture();
		courtTexture->loadFromFile("./tex/court.png");		
		texturedCourt = new sf::RectangleShape(sf::Vector2f(width, height));
		texturedCourt->setTexture(courtTexture);

        court = new Cong::Court(width, height, 4, 15);
        
        ball = new Cong::Ball(BALL_RADIUS, 0);
        ball->setPosition(width * 0.5, height * 0.5); // The Ball's origin is at its center!
        ball->setFillColor(sf::Color(FILL_COLOR[0], FILL_COLOR[1], FILL_COLOR[2]));
		ball->setTexture(ballTexture);
        
        paddleLeft = new Cong::Paddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT), PADDLE_SPEED);
		paddleLeft->setOrigin(PADDLE_WIDTH, PADDLE_HEIGHT * 0.5);
        paddleLeft->setPosition(PADDING + PADDLE_WIDTH, height * 0.5); // Origin at right edge, vertically centered
        paddleLeft->setFillColor(sf::Color(FILL_COLOR[0], FILL_COLOR[1], FILL_COLOR[2]));
        
        paddleRight = new Cong::Paddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT), PADDLE_SPEED);
		paddleRight->setOrigin(0, PADDLE_HEIGHT * 0.5);
        paddleRight->setPosition(width - (PADDLE_WIDTH + PADDING), height * 0.5); // Origin at left edge, vertically centered
        paddleRight->setFillColor(sf::Color(FILL_COLOR[0], FILL_COLOR[1], FILL_COLOR[2]));
        
		charMapTexture = new sf::Texture();
		charMapTexture->loadFromFile("./tex/charmap-cellphone-white.png");
		charMapProps = new CharMapProperties(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~", 7, 9, 0, 18);

		scoreDisplayLeft = new SpriteText(charMapTexture, charMapProps);
		scoreDisplayLeft->setScale(sf::Vector2f(8, 8));
		scoreDisplayLeft->setAnchor(SpriteTextAnchor::TOP_CENTER);
		scoreDisplayLeft->setPosition(width * 0.35, PADDING);
		scoreDisplayLeft->setText("0");

		scoreDisplayRight = new SpriteText(charMapTexture, charMapProps);
		scoreDisplayRight->setScale(sf::Vector2f(8, 8));
		scoreDisplayRight->setAnchor(SpriteTextAnchor::TOP_CENTER);
		scoreDisplayRight->setPosition(width * 0.65, PADDING);
		scoreDisplayRight->setText("0");
	}

	Game::~Game() {
		window->close();

		delete window;
		delete ball;
		delete court;
		delete paddleLeft;
		delete paddleRight;
		delete scoreDisplayLeft;
		delete scoreDisplayRight;

		delete charMapTexture;
		delete charMapProps;

		delete texturedCourt;
		delete courtTexture;
		delete ballTexture;
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
			scoreForLeft();            
			serve();
        }
        
        if (ballPositionNext.x - BALL_RADIUS >= width) {
			scoreForRight();
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

	void Game::scoreForLeft() {
		scoreDisplayLeft->setText(std::to_string(++scoreLeft));
	}

	void Game::scoreForRight() {
		scoreDisplayRight->setText(std::to_string(++scoreRight));
	}

	void Game::render() {
        window->clear();
        // window->draw(*court);
		window->draw(*texturedCourt);
        window->draw(*scoreDisplayLeft);
        window->draw(*scoreDisplayRight);
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
