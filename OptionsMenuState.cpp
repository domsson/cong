#include "Game.hpp"
#include "OptionsMenuState.hpp"

namespace Cong
{

	OptionsMenuState::OptionsMenuState(const Game &game)
	: MenuState(game)
	{
	}

	OptionsMenuState::~OptionsMenuState()
	{
		// Do nothing
	}

	void OptionsMenuState::enter()
	{
	}

	void OptionsMenuState::exit()
	{
	}

	void OptionsMenuState::processEvents()
	{
	}

	void OptionsMenuState::processInputs()
	{
	}

    void OptionsMenuState::update()
	{
	}

	void OptionsMenuState::render()
	{
		game->getWindow()->clear();
		renderTitle();
		renderItems();
		game->getWindow()->display();
	}

}
