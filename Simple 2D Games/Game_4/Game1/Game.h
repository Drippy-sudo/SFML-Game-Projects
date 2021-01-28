#pragma once

#include "Player.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	Player* player;

	void InitWindow();
	void InitPlayer();

public:
	Game();
	virtual ~Game();

	// Functions
	void UpdatePlayer();
	void UpdateCollision();
	void Update();
	void RenderPlayer();
	void Render();
	const sf::RenderWindow& getWindow() const;
};
