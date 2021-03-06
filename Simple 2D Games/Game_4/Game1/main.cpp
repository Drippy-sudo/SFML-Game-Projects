#include "stdafx.h"
#include "Game.h"

int main()
{
	srand(static_cast<unsigned>(time(0)));

	Game game;

	while (game.getWindow().isOpen())
	{
		game.Update();
		game.Render();
	}

	// End of application
	return 0;
}