#include "Game.h"
#include <time.h>

int main()
{	
	// Seed for a random number
	srand(static_cast<unsigned int>(time(0)));

	Game game;

	game.Run();

	// End of application
	return 0;
}