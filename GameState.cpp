#include "GameState.hpp"
#include "Game.hpp"

namespace Cong {

	GameState::GameState()
	: game(nullptr), nextState(GameStates::NONE)
	{
		// Do nothing
	}

	GameState::GameState(Game &game)
	: game(nullptr), nextState(GameStates::NONE)
	{
		setGame(game);
	}

	GameState::~GameState()
	{
		// Do nothing
	}

	void GameState::setGame(Game &game)
	{
		this->game = &game;
	}

	GameStates GameState::getNextState() const {
		return nextState;
	}

	void GameState::changeState(GameStates nextState)
	{
		this->nextState = nextState;
		if (game != nullptr)
		{
			game->requestStateChange();
		}
	}

}

