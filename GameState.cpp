#include "GameState.hpp"

namespace Cong {

	GameState::GameState() {
	}

	GameState::~GameState() {
	}

	void GameState::changeState(Game *game, GameState *state) {
		game->setState(state);
	}

}

