#include "PlayState.hpp"

namespace Cong {

    static const int PADDING = 20;
    static const int PADDLE_WIDTH = 24; // 32;
    static const int PADDLE_HEIGHT = 96; // 128;
	static const int PADDLE_SPEED = 400;
    static const int BALL_RADIUS = 12; // 16;
	static const int BALL_SPEED = 300;
	static const float BALL_SPEED_INCREASE = 0.05;

	static const int COURT_COLOR[] = {255, 255, 255};
    static const int BALL_COLOR[] = {255, 255, 255};
	static const int PADDLE_COLOR[] = {255, 255, 255};

	static const std::string BALL_TEXTURE = "fancy-ball.png";
	static const std::string COURT_TEXTURE = "fancy-court.png";
	static const std::string PADDLE_TEXTURE = "fancy-paddle.png";

	static const std::string HIT_PADDLE_SOUND = "ping_pong_8bit_beeep.ogg";
	static const std::string HIT_WALL_SOUND = "ping_pong_8bit_plop.ogg";
	static const std::string BALL_OUT_SOUND = "ping_pong_8bit_peeeeeep.ogg";

	PlayState::PlayState(Game &game)
	: GameState(game), court(0), ball(0), paddleLeft(0), paddleRight(0), scoreDisplayLeft(0), scoreDisplayRight(0), charMap(0)
	{
		charMap = this->game->getDefaultCharMap();
	}

	PlayState::~PlayState()
	{
		delete ball;
		delete court;
		delete paddleLeft;
		delete paddleRight;
		delete scoreDisplayLeft;
		delete scoreDisplayRight;
	}

	void PlayState::enter()
	{
		resetScores();
		initCourt();
		initPaddles();
		initBall();
		initScoreDisplays();
		initSounds();
	}

	void PlayState::exit()
	{
	}

	void PlayState::resetScores()
	{
		scoreLeft = 0;
		scoreRight = 0;
	}

	void PlayState::initCourt()
	{
		if (!COURT_TEXTURE.empty())
		{
			Game::loadTexture(COURT_TEXTURE, courtTexture);
		}

		court = new sf::RectangleShape(sf::Vector2f(game->getViewportWidth(), game->getViewportHeight()));
		court->setFillColor(sf::Color(COURT_COLOR[0], COURT_COLOR[1], COURT_COLOR[2]));
		court->setTexture(&courtTexture);
	}

	void PlayState::initPaddles()
	{
		if (!PADDLE_TEXTURE.empty())
		{
			Game::loadTexture(PADDLE_TEXTURE, paddleTexture);
		}

        paddleLeft = new Cong::Paddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT), PADDLE_SPEED);
		paddleLeft->setOrigin(PADDLE_WIDTH, (PADDLE_HEIGHT * 0.5) - 0.5);
        paddleLeft->setPosition(PADDING + PADDLE_WIDTH, (game->getViewportHeight()-1) * 0.5); // Origin at right edge, vertically centered
        paddleLeft->setFillColor(sf::Color(PADDLE_COLOR[0], PADDLE_COLOR[1], PADDLE_COLOR[2]));
		paddleLeft->setTexture(&paddleTexture);
        
        paddleRight = new Cong::Paddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT), PADDLE_SPEED);
		paddleRight->setOrigin(0, (PADDLE_HEIGHT * 0.5) - 0.5);
        paddleRight->setPosition(game->getViewportWidth() - (PADDLE_WIDTH + PADDING), (game->getViewportHeight()-1) * 0.5); // Origin at left edge, vertically centered
        paddleRight->setFillColor(sf::Color(PADDLE_COLOR[0], PADDLE_COLOR[1], PADDLE_COLOR[2]));
		paddleRight->setTexture(&paddleTexture);
	}

	void PlayState::initBall()
	{
		if (!BALL_TEXTURE.empty())
		{
			Game::loadTexture(BALL_TEXTURE, ballTexture);
		}

        ball = new Cong::Ball(BALL_RADIUS, 0);
        ball->setPosition((game->getViewportWidth()-1) * 0.5, (game->getViewportHeight()-1) * 0.5); // The Ball's origin is at its center!
        ball->setFillColor(sf::Color(BALL_COLOR[0], BALL_COLOR[1], BALL_COLOR[2]));
		ball->setTexture(&ballTexture);
	}

	void PlayState::initScoreDisplays()
	{
		scoreDisplayLeft = new SpriteText(*charMap);
		scoreDisplayLeft->setScale(sf::Vector2f(8, 8));
		scoreDisplayLeft->setAnchor(SpriteTextAnchor::TOP_CENTER);
		scoreDisplayLeft->setPosition(game->getViewportWidth() * 0.35, PADDING);
		scoreDisplayLeft->setText(std::to_string(scoreLeft));

		scoreDisplayRight = new SpriteText(*charMap);
		scoreDisplayRight->setScale(sf::Vector2f(8, 8));
		scoreDisplayRight->setAnchor(SpriteTextAnchor::TOP_CENTER);
		scoreDisplayRight->setPosition(game->getViewportWidth() * 0.65, PADDING);
		scoreDisplayRight->setText(std::to_string(scoreRight));
	}

	void PlayState::initSounds()
	{
		Game::loadSound(HIT_PADDLE_SOUND, paddleSoundFile, paddleSound);
		Game::loadSound(HIT_WALL_SOUND, wallSoundFile, wallSound);
		Game::loadSound(BALL_OUT_SOUND, outSoundFile, outSound);
	}	

	void PlayState::update()
	{
		float ballSpeed = ball->getSpeed() * game->getDeltaTime();
        sf::Vector2f ballPositionNext((ball->getPosition().x + ball->getDirection().x * ballSpeed), (ball->getPosition().y + ball->getDirection().y * ballSpeed));
        
		// We check for collisions with the left paddle only if the ball is close to it.
		if (ballPositionNext.x - BALL_RADIUS <= paddleLeft->getPosition().x)
		{
			sf::FloatRect paddleLeftBounds = paddleLeft->getGlobalBounds();

			float deltaX = 0.0;
			float deltaY = 0.0;
			sf::Vector2f intersectionX(0,0);
			sf::Vector2f intersectionY(0,0);
			bool collisionX = false;
			bool collisionY = false;

			if (ball->isMovingLeft())
			{
				sf::Vector2f ballStart(ball->getPosition().x - ball->getRadius(), ball->getPosition().y);
				sf::Vector2f ballEnd(ballPositionNext.x - ball->getRadius(), ballPositionNext.y);
				
				collisionX = Physics::intersectionWithX(ballStart, ballEnd, paddleLeft->getPosition().x, deltaX, intersectionX);			
				sf::Vector2f ballRange(intersectionX.y - ball->getRadius(), intersectionX.y + ball->getRadius());
				sf::Vector2f paddleRange(paddleLeftBounds.top, paddleLeftBounds.top + paddleLeftBounds.height);

				if (collisionX && Math::rangesIntersect(ballRange, paddleRange))
				{
					float yDiff = (ballPositionNext.y - paddleLeft->getPosition().y) / (PADDLE_HEIGHT * 0.5);
					ball->reverseDirectionHorizontal();
					ball->setSpeed(ball->getSpeed() * (1.0 + BALL_SPEED_INCREASE));
					ball->slope(yDiff);
					if (Options::playSounds == Sound::ON)
					{
						paddleSound.play();
					}
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
					if (Options::playSounds == Sound::ON)
					{
						paddleSound.play();
					}
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
					if (Options::playSounds == Sound::ON)
					{
						paddleSound.play();
					}
				}
			}
		}

		// We check for collisions with the right paddle only if the ball is close to it.
		if (ballPositionNext.x + BALL_RADIUS >= paddleRight->getPosition().x)
		{
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
					if (Options::playSounds == Sound::ON)
					{
						paddleSound.play();
					}
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
					if (Options::playSounds == Sound::ON)
					{
						paddleSound.play();
					}
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
					if (Options::playSounds == Sound::ON)
					{
						paddleSound.play();
					}
				}
			}
		}

        if (ballPositionNext.x + BALL_RADIUS <= 0) {
			scoreForRight();          
			if (Options::playSounds == Sound::ON) { outSound.play(); }
			serve();
			return;
        }
        
        if (ballPositionNext.x - BALL_RADIUS >= game->getViewportWidth()) {
			scoreForLeft();
			if (Options::playSounds == Sound::ON) { outSound.play(); }
            serve();
			return;
        }
    
        if (ballPositionNext.y <= 0 + BALL_RADIUS) {
            ballPositionNext.y = 0 + BALL_RADIUS;
			if (Options::playSounds == Sound::ON) { wallSound.play(); }
            ball->reverseDirectionVertical();
        }
        
        if (ballPositionNext.y >= game->getViewportHeight() - BALL_RADIUS) {
            ballPositionNext.y = game->getViewportHeight() - BALL_RADIUS;
			if (Options::playSounds == Sound::ON) { wallSound.play(); }
            ball->reverseDirectionVertical();
        }
        
        // ball->move(ball->getDirection().x * ballSpeed, ball->getDirection().y * ballSpeed);
		ball->setPosition(ballPositionNext);
	}

    void PlayState::serve()
	{
        ball->setSpeed(0);
        ball->setDirection(sf::Vector2f(1, 1));
        ball->setPosition((game->getViewportWidth()-1) * 0.5, (game->getViewportHeight()-1) * 0.5);
    }

	void PlayState::scoreForLeft()
	{
		scoreDisplayLeft->setText(std::to_string(++scoreLeft));
	}

	void PlayState::scoreForRight()
	{
		scoreDisplayRight->setText(std::to_string(++scoreRight));
	}

	void PlayState::processEvents()
	{
		sf::Event event;
        while (game->getWindow()->pollEvent(event))
		{
            if (event.type == sf::Event::Closed)
			{
                game->getWindow()->close();
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					changeState(GameStates::MAIN_MENU);
				}
			}
        }
    }

	void PlayState::processInputs()
	{        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            sf::Vector2f paddleLeftPos = paddleLeft->getPosition();
            int paddleLeftY = paddleLeftPos.y - PADDLE_SPEED * game->getDeltaTime();
            paddleLeftY = paddleLeftY - PADDLE_HEIGHT * 0.5 < 0 ? PADDLE_HEIGHT * 0.5  : paddleLeftY;
            
            paddleLeft->setPosition(sf::Vector2f(paddleLeftPos.x, paddleLeftY));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sf::Vector2f paddleLeftPos = paddleLeft->getPosition();
            int paddleLeftY = paddleLeftPos.y + PADDLE_SPEED * game->getDeltaTime();
            paddleLeftY = paddleLeftY + PADDLE_HEIGHT * 0.5 > game->getViewportHeight() ? game->getViewportHeight() - PADDLE_HEIGHT * 0.5  : paddleLeftY;
            
            paddleLeft->setPosition(sf::Vector2f(paddleLeftPos.x, paddleLeftY));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sf::Vector2f paddleRightPos = paddleRight->getPosition();
            int paddleRightY = paddleRightPos.y - PADDLE_SPEED * game->getDeltaTime();
            paddleRightY = paddleRightY - PADDLE_HEIGHT * 0.5 < 0  ? PADDLE_HEIGHT * 0.5  : paddleRightY;
            
            paddleRight->setPosition(sf::Vector2f(paddleRightPos.x, paddleRightY));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sf::Vector2f paddleRightPos = paddleRight->getPosition();
            int paddleRightY = paddleRightPos.y + PADDLE_SPEED * game->getDeltaTime();
            paddleRightY = paddleRightY + PADDLE_HEIGHT * 0.5  > game->getViewportHeight() ? game->getViewportHeight() - PADDLE_HEIGHT * 0.5   : paddleRightY;
            
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
			ball->setPosition(PADDING + BALL_RADIUS, game->getViewportHeight() - BALL_RADIUS * 2 - PADDING);
            ball->setDirection(sf::Vector2f(0, -1));
            ball->setSpeed(BALL_SPEED);
        }
	}

	void PlayState::render()
	{
		game->getWindow()->clear();
        game->getWindow()->draw(*court);
        game->getWindow()->draw(*scoreDisplayLeft);
        game->getWindow()->draw(*scoreDisplayRight);
        game->getWindow()->draw(*ball);
        game->getWindow()->draw(*paddleLeft);
        game->getWindow()->draw(*paddleRight);
        game->getWindow()->display();
	}

}

