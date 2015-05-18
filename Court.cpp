#include "Court.hpp"

namespace Cong {
    
    static const float SEGMENT_WHITESPACE_RATIO = 0.65;
    
    Court::Court(int width, int height, int segmentWidth, int numSegments) : width(width), height(height), segmentWidth(segmentWidth), numSegments(numSegments) {
        // Pointer to pointer... confusing
        // http://stackoverflow.com/questions/20303820/creation-of-dynamic-array-of-dynamic-objects-in-c
        // http://stackoverflow.com/questions/8462895/how-to-dynamically-declare-an-array-of-objects-with-a-constructor-in-c
        // TODO: Why does the asterisk have to be between type and square brackets, not before the type?
        
        lineSegments = new sf::RectangleShape *[numSegments];
        initSegments();
    }
    
    Court::~Court() {
        for (int i=0; i < numSegments; ++i) {
            delete lineSegments[i];
        }
        delete[] lineSegments;
    }
    
    void Court::initSegments() {
        int totalSegmentHeight = (int) (SEGMENT_WHITESPACE_RATIO * height);
        int totalWhitespaceHeight = height - totalSegmentHeight;
        int whitespaceHeight = totalWhitespaceHeight / (numSegments - 1);
        int segmentHeight = totalSegmentHeight / numSegments;
        int segmentXPos = width * 0.5 - segmentWidth * 0.5;
        
        for (int i=0; i < numSegments; ++i) {
            lineSegments[i] = new sf::RectangleShape(sf::Vector2f(segmentWidth, segmentHeight));
            lineSegments[i]->setPosition(segmentXPos, whitespaceHeight * 0.5 + i * (segmentHeight + whitespaceHeight));
        }
    }
    
    void Court::draw(sf::RenderWindow &window) {
        
        for (int i=0; i < numSegments; ++i) {
            window.draw(*lineSegments[i]);
        }
    }
    
}
