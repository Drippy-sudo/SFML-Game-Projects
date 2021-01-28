#pragma once

// c++ includes
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

// SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

// Class that acts as the Game Engine
class Game
{
private:
	// Variables
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	// Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	sf::Font font;

	// Text
	sf::Text uiText;

	// Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	// Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	// Private functions
	void InitVariables();
	void InitWindow();
	void InitFonts();
	void InitTexts();
	void InitEnemies();

public:
	Game();
	virtual ~Game();

	// Accessors
	const bool running() const;
	const bool getEndGame() const;

	// Functions
	void spawnEnemy();

	// Poll events
	void PollEvents();

	// Update
	void UpdateMousePositions();
	void UpdateText();
	void UpdateEnemies();
	void Update();

	// Render
	void RenderText(sf::RenderTarget& target);
	void RenderEnemies(sf::RenderTarget& target);
	void Render();
};
