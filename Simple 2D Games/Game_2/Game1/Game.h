#pragma once

// c++ includes
#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "Player.h"
#include "SwagBall.h"

// Class that acts as the Game Engine
class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event ev;

	Player player;

	int points;

	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;

	std::vector<SwagBall> swagBalls;
	float spawnTimerMax;
	float spawnTimer;
	int maxSwagBalls;

	// Private functions
	void InitVariables();
	void InitWindow();
	void InitFonts();
	void InitText();

public:
	Game();
	~Game();

	// Accessors
	const bool& getEndGame() const;

	// Modifiers

	// Functions
	const bool Running() const;
	void PollEvents();

	void SpawnSwagBalls();
	const int RandBallType() const;

	void UpdatePlayer();
	void UpdateCollision();
	void UpdateGUI();
	void Update();

	void RenderGUI(sf::RenderTarget* target);
	void Render();
};
