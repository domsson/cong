#ifndef CONG_GAMESTATE_HPP
#define CONG_GAMESTATE_HPP

#include <iostream>
#include "GameStates.hpp"

namespace Cong {

class Game;

class GameState {

public:

	GameState();
	GameState(const Game &game);
	virtual ~GameState(); // TODO Do we need the dtor? Should it be virtual?

	virtual void enter() = 0;
	virtual void exit() = 0;

	virtual void processEvents() = 0;
	virtual void processInputs() = 0;
    virtual void update() = 0;
	virtual void render() = 0;

	void setGame(const Game &game);
	GameStates getNextState() const;

protected:

	const Game *game;
	GameStates nextState;

	void changeState(GameStates nextState);

};

}

#endif
