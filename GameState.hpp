#ifndef CONG_GAMESTATE_HPP
#define CONG_GAMESTATE_HPP

#include "Game.hpp"

namespace Cong {

class Game;

class GameState {

public:

	GameState();
	virtual ~GameState();

	virtual void enter() = 0;
	virtual void exit() = 0;

	virtual void processEvents(Game *game) = 0;
	virtual void processInputs(Game *game) = 0;
    virtual void update(Game *game) = 0;
	virtual void render(Game *game) = 0;

protected:

	void changeState(Game *game, GameState *state);

};

}

#endif
