#include <string>
#include <SFML/Graphics.hpp>
#include "Game.hpp"

Cong::Game *game = 0;

static const int VIEWPORT_WIDTH = 800;
static const int VIEWPORT_HEIGHT = 600;
static const std::string TITLE = "Cong!";

int main() {
	game = new Cong::Game(TITLE, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
	game->run();

    return 0;
}
