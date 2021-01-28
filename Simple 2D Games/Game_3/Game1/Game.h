#pragma once

#include <map>
#include <string>
#include <sstream>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

// Class that acts as the Game Engine
class Game
{
private:
	// Window
	sf::RenderWindow* window; 

	// Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	// GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;
	
	// World
	sf::Sprite worldBackground;
	sf::Texture worldBackgroundTex;

	// Player
	Player* player;

	// PlayerGUI
	sf::RectangleShape playerHPBar;
	sf::RectangleShape playerHPBarBack;

	// Systems
	unsigned points;

	// Enemies
	std::vector<Enemy*> enemies;
	float spawnTimer;
	float spawnTimerMax;

	// Private function
	void InitWindow();
	void InitTextures();
	void InitGUI();
	void InitWorld();
	void InitSystems();
	void InitPlayer();
	void InitEnemies();

public:
	Game();
	virtual ~Game();

	// Functions
	void Run();

	void UpdatePollEvents();
	void UpdateInput();
	void UpdateGUI();
	void UpdateWorld();
	void UpdateCollision();
	void UpdateBullets();
	void UpdateEnemies();
	void UpdateCombat();
	void Update();

	void RenderGUI();
	void RenderWorld();
	void Render();
};
