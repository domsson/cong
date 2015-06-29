#include <string>
#include <unistd.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "MainMenuState.hpp"
//#include "PlayState.hpp"
#include "Options.hpp"

using namespace Cong;

Game* game = nullptr;

static const int VIEWPORT_WIDTH = 800;
static const int VIEWPORT_HEIGHT = 600;
static const std::string TITLE = "Cong!";

// Init options (TODO - this is horrible...)
Resolution Options::resolution = Options::DEFAULT_RESOLUTION;
Theme Options::theme = Options::DEFAULT_THEME;
Sound Options::playSounds = Options::DEFAULT_PLAY_SOUNDS;

int main() {
	char* path = getcwd(nullptr, 0);
	std::cout << "CWD: " << path << std::endl;

	game = new Game(TITLE, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
	game->setState(new MainMenuState(*game));
	game->run();

	delete game;
	return 0;
}
