#include <iostream>
#include "ScoreDisplay.hpp"

namespace Cong {

	const int ScoreDisplay::MAX_VALUE = 99;
    
    ScoreDisplay::ScoreDisplay(const sf::Texture &texture, const int charWidth, const int charHeight, const int sizeFactor)
        : charWidth(charWidth), charHeight(charHeight), sizeFactor(sizeFactor)
    {
		score = 0;
        num1 = new sf::RectangleShape(sf::Vector2f(charWidth * sizeFactor, charHeight * sizeFactor));
        num2 = new sf::RectangleShape(sf::Vector2f(charWidth * sizeFactor, charHeight * sizeFactor));
        num1->setTexture(&texture);
        num2->setTexture(&texture);
        num1->setTextureRect(sf::IntRect(0, 0, charWidth, charHeight));
        num2->setTextureRect(sf::IntRect(0, 0, charWidth, charHeight));
        num1->setPosition(0, 0);
        num2->setPosition(charWidth * sizeFactor, 0);
    }
    
    ScoreDisplay::~ScoreDisplay() {
        
    }
    
    void ScoreDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(*num1, states);
        target.draw(*num2, states);
    }
    
    void ScoreDisplay::setPosition(float x, float y) {
        posX = x;
        posY = y;
        
        num1->setPosition(num1->getPosition().x + posX, num1->getPosition().y + posY);
        num2->setPosition(num2->getPosition().x + posX, num2->getPosition().y + posY);
    }

	void ScoreDisplay::setScore(int score) {
		if (score > MAX_VALUE) {
			std::cerr << "Warning: trying to display too big of a score (" << score << ", max is " << MAX_VALUE << "), truncating." << std::endl;
			this->score = score - MAX_VALUE;		
		}
		else {
			this->score = score;
		}
		updateNumbers();
	}

	void ScoreDisplay::updateNumbers() {
		int leftNum = score / 10;
		int rightNum = score % 10;
		// std::cout << "num1: " << leftNum << ", num2: " << rightNum << std::endl;
		int offsetLeft = charWidth * leftNum;
		int offsetRight = charWidth * rightNum;
		num1->setTextureRect(sf::IntRect(offsetLeft, 0, charWidth, charHeight));
		num2->setTextureRect(sf::IntRect(offsetRight, 0,  charWidth, charHeight));
	}
    
}
