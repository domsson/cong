#ifndef CONG_GAMESTATE_HPP
#define CONG_GAMESTATE_HPP

// #include "Game.hpp"
#include "Game.fwd.hpp"

namespace Cong {

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
