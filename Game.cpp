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

	Game::Game(const std::string &title, int width, int height) :
			window(0), court(0), ball(0), paddleLeft(0), paddleRight(0),
			scoreDisplayLeft(0), scoreDisplayRight(0), charMapTexture(0),
			charMapProps(0), courtTexture(0), ballTexture(0), paddleTexture(0),
			title(title), width(width), height(height)
	{
        window = new sf::RenderWindow(sf::VideoMode(width, height), title);
        
		resetScores();
		initCourt();
		initPaddles();
		initBall();
		initScoreDisplays();
	}

	void Game::resetScores() {
		scoreLeft = 0;
		scoreRight = 0;
	}

	void Game::initCourt() {
		if (!COURT_TEXTURE.empty()) {
			courtTexture = new sf::Texture();
			courtTexture->loadFromFile(TEXTURE_DIR + COURT_TEXTURE);
		}

		court = new sf::RectangleShape(sf::Vector2f(width, height));
		court->setFillColor(sf::Color(COURT_COLOR[0], COURT_COLOR[1], COURT_COLOR[2]));
		court->setTexture(courtTexture);
	}

	void Game::initPaddles() {
		if (!PADDLE_TEXTURE.empty()) {
			paddleTexture = new sf::Texture();
			paddleTexture->loadFromFile(TEXTURE_DIR + PADDLE_TEXTURE);
		}

        paddleLeft = new Cong::Paddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT), PADDLE_SPEED);
		paddleLeft->setOrigin(PADDLE_WIDTH, (PADDLE_HEIGHT * 0.5) - 0.5);
        paddleLeft->setPosition(PADDING + PADDLE_WIDTH, (height-1) * 0.5); // Origin at right edge, vertically centered
        paddleLeft->setFillColor(sf::Color(PADDLE_COLOR[0], PADDLE_COLOR[1], PADDLE_COLOR[2]));
		paddleLeft->setTexture(paddleTexture);
        
        paddleRight = new Cong::Paddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT), PADDLE_SPEED);
		paddleRight->setOrigin(0, (PADDLE_HEIGHT * 0.5) - 0.5);
        paddleRight->setPosition(width - (PADDLE_WIDTH + PADDING), (height-1) * 0.5); // Origin at left edge, vertically centered
        paddleRight->setFillColor(sf::Color(PADDLE_COLOR[0], PADDLE_COLOR[1], PADDLE_COLOR[2]));
		paddleRight->setTexture(paddleTexture);
	}

	void Game::initBall() {
		if (!BALL_TEXTURE.empty()) {
			ballTexture = new sf::Texture();
			ballTexture->loadFromFile(TEXTURE_DIR + BALL_TEXTURE);
		}

        ball = new Cong::Ball(BALL_RADIUS, 0);
        ball->setPosition((width-1) * 0.5, (height-1) * 0.5); // The Ball's origin is at its center!
        ball->setFillColor(sf::Color(BALL_COLOR[0], BALL_COLOR[1], BALL_COLOR[2]));
		ball->setTexture(ballTexture);
	}

	void Game::initScoreDisplays() {
		charMapTexture = new sf::Texture();
		charMapTexture->loadFromFile(TEXTURE_DIR + FONT_TEXTURE);

		charMapProps = new CharMapProperties(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~", 7, 9, 0, 18);

		scoreDisplayLeft = new SpriteText(charMapTexture, charMapProps);
		scoreDisplayLeft->setScale(sf::Vector2f(8, 8));
		scoreDisplayLeft->setAnchor(SpriteTextAnchor::TOP_CENTER);
		scoreDisplayLeft->setPosition(width * 0.35, PADDING);
		scoreDisplayLeft->setText(std::to_string(scoreLeft));

		scoreDisplayRight = new SpriteText(charMapTexture, charMapProps);
		scoreDisplayRight->setScale(sf::Vector2f(8, 8));
		scoreDisplayRight->setAnchor(SpriteTextAnchor::TOP_CENTER);
		scoreDisplayRight->setPosition(width * 0.65, PADDING);
		scoreDisplayRight->setText(std::to_string(scoreRight));
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
		delete courtTexture;
		delete ballTexture;
		delete paddleTexture;
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
        sf::Vector2f ballPositionNext((ball->getPosition().x + ball->getDirection().x * ballSpeed), (ball->getPosition().y + ball->getDirection().y * ballSpeed));
        
		// We check for collisions with the left paddle only if the ball is close to it.
		if (ballPositionNext.x - BALL_RADIUS <= paddleLeft->getPosition().x) {
			sf::FloatRect paddleLeftBounds = paddleLeft->getGlobalBounds();

			float deltaX = 0.0;
			float deltaY = 0.0;
			sf::Vector2f intersectionX(0,0);
			sf::Vector2f intersectionY(0,0);
			bool collisionX = false;
			bool collisionY = false;

			if (ball->isMovingLeft()) {
				sf::Vector2f ballStart(ball->getPosition().x - ball->getRadius(), ball->getPosition().y);
				sf::Vector2f ballEnd(ballPositionNext.x - ball->getRadius(), ballPositionNext.y);
				
				collisionX = Physics::intersectionWithX(ballStart, ballEnd, paddleLeft->getPosition().x, deltaX, intersectionX);			
				sf::Vector2f ballRange(intersectionX.y - ball->getRadius(), intersectionX.y + ball->getRadius());
				sf::Vector2f paddleRange(paddleLeftBounds.top, paddleLeftBounds.top + paddleLeftBounds.height);

				if (collisionX && Math::rangesIntersect(ballRange, paddleRange)) {
					float yDiff = (ballPositionNext.y - paddleLeft->getPosition().y) / (PADDLE_HEIGHT * 0.5);
					ball->reverseDirectionHorizontal();
					ball->setSpeed(ball->getSpeed() * (1.0 + BALL_SPEED_INCREASE));
					ball->slope(yDiff);
				}
			}

			if (ball->isMovingDown()) {
				sf::Vector2f ballStart(ball->getPosition().x, ball->getPosition().y + ball->getRadius());
				sf::Vector2f ballEnd(ballPositionNext.x, ballPositionNext.y + ball->getRadius());

				collisionY = Physics::intersectionWithY(ballStart, ballEnd, paddleLeftBounds.top, deltaY, intersectionY);
				sf::Vector2f ballRange(intersectionY.x - ball->getRadius(), intersectionY.x + ball->getRadius());
				sf::Vector2f paddleRange(paddleLeftBounds.left, paddleLeftBounds.left + paddleLeftBounds.width);

				if (collisionY && Math::rangesIntersect(ballRange, paddleRange)) {
					ball->reverseDirectionVertical();
				}
			}

			else if (ball->isMovingUp()) {
				sf::Vector2f ballStart(ball->getPosition().x, ball->getPosition().y - ball->getRadius());
				sf::Vector2f ballEnd(ballPositionNext.x, ballPositionNext.y - ball->getRadius());				

				collisionY = Physics::intersectionWithY(ballStart, ballEnd, paddleLeftBounds.top + paddleLeftBounds.height, deltaY, intersectionY);
				sf::Vector2f ballRange(intersectionY.x - ball->getRadius(), intersectionY.x + ball->getRadius());
				sf::Vector2f paddleRange(paddleLeftBounds.left, paddleLeftBounds.left + paddleLeftBounds.width);				

				if (collisionY && Math::rangesIntersect(ballRange, paddleRange)) {
					ball->reverseDirectionVertical();
				}
			}
		}

		// We check for collisions with the right paddle only if the ball is close to it.
		if (ballPositionNext.x + BALL_RADIUS >= paddleRight->getPosition().x) {
			sf::FloatRect paddleRightBounds = paddleRight->getGlobalBounds();

			float deltaX = 0.0;
			float deltaY = 0.0;
			sf::Vector2f intersectionX(0,0);
			sf::Vector2f intersectionY(0,0);
			bool collisionX = false;
			bool collisionY = false;

			if (ball->isMovingRight()) {
				sf::Vector2f ballStart(ball->getPosition().x + ball->getRadius(), ball->getPosition().y);
				sf::Vector2f ballEnd(ballPositionNext.x + ball->getRadius(), ballPositionNext.y);
				
				collisionX = Physics::intersectionWithX(ballStart, ballEnd, paddleRight->getPosition().x, deltaX, intersectionX);			
				sf::Vector2f ballRange(intersectionX.y - ball->getRadius(), intersectionX.y + ball->getRadius());
				sf::Vector2f paddleRange(paddleRightBounds.top, paddleRightBounds.top + paddleRightBounds.height);

				if (collisionX && Math::rangesIntersect(ballRange, paddleRange)) {
					float yDiff = (ballPositionNext.y - paddleRight->getPosition().y) / (PADDLE_HEIGHT * 0.5);
					ball->reverseDirectionHorizontal();
					ball->setSpeed(ball->getSpeed() * (1.0 + BALL_SPEED_INCREASE));
					ball->slope(yDiff);
				}
			}

			if (ball->isMovingDown()) {
				sf::Vector2f ballStart(ball->getPosition().x, ball->getPosition().y + ball->getRadius());
				sf::Vector2f ballEnd(ballPositionNext.x, ballPositionNext.y + ball->getRadius());

				collisionY = Physics::intersectionWithY(ballStart, ballEnd, paddleRightBounds.top, deltaY, intersectionY);
				sf::Vector2f ballRange(intersectionY.x - ball->getRadius(), intersectionY.x + ball->getRadius());
				sf::Vector2f paddleRange(paddleRightBounds.left, paddleRightBounds.left + paddleRightBounds.width);

				if (collisionY && Math::rangesIntersect(ballRange, paddleRange)) {
					ball->reverseDirectionVertical();
				}
			}

			else if (ball->isMovingUp()) {
				sf::Vector2f ballStart(ball->getPosition().x, ball->getPosition().y - ball->getRadius());
				sf::Vector2f ballEnd(ballPositionNext.x, ballPositionNext.y - ball->getRadius());				

				collisionY = Physics::intersectionWithY(ballStart, ballEnd, paddleRightBounds.top + paddleRightBounds.height, deltaY, intersectionY);
				sf::Vector2f ballRange(intersectionY.x - ball->getRadius(), intersectionY.x + ball->getRadius());
				sf::Vector2f paddleRange(paddleRightBounds.left, paddleRightBounds.left + paddleRightBounds.width);
				
				if (collisionY && Math::rangesIntersect(ballRange, paddleRange)) {
					ball->reverseDirectionVertical();
				}
			}
		}
		

        if (ballPositionNext.x + BALL_RADIUS <= 0) {
			scoreForLeft();            
			serve();
			return;
        }
        
        if (ballPositionNext.x - BALL_RADIUS >= width) {
			scoreForRight();
            serve();
			return;
        }
    
        if (ballPositionNext.y <= 0 + BALL_RADIUS) {
            ballPositionNext.y = 0 + BALL_RADIUS;
            ball->reverseDirectionVertical();
        }
        
        if (ballPositionNext.y >= height - BALL_RADIUS) {
            ballPositionNext.y = height - BALL_RADIUS;
            ball->reverseDirectionVertical();
        }
        
        // ball->move(ball->getDirection().x * ballSpeed, ball->getDirection().y * ballSpeed);
		ball->setPosition(ballPositionNext);
        
	}

	void Game::scoreForLeft() {
		scoreDisplayLeft->setText(std::to_string(++scoreLeft));
	}

	void Game::scoreForRight() {
		scoreDisplayRight->setText(std::to_string(++scoreRight));
	}

	void Game::render() {
        window->clear();
        window->draw(*court);
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
        ball->setPosition((width-1) * 0.5, (height-1) * 0.5);
    }

}
