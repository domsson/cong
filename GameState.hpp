#ifndef CONG_GAMESTATE_HPP
#define CONG_GAMESTATE_HPP

#include "Game.hpp"

namespace Cong {

class Game;

class GameState {

public:

	void setGame(Game *game);

	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	virtual void processEvents() = 0;
	virtual void processInputs() = 0;
    virtual void update() = 0;
	virtual void render() = 0;

protected:

	Game *game = 0;

};

}

#endif
