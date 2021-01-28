#include <iostream>

#include "Game.h"

int main()
{
	// Init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	// Init game object
	Game game;

	// Game loop
	while (game.running() && !game.getEndGame())
	{
		// Update
		game.Update();

		// Render
		game.Render();
	}

	// End of application
	return 0;
}