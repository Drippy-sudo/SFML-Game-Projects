#include "Game.h"

// Private functions
void Game::InitVariables()
{
	this->window = nullptr;

	// Game logic
	this->endGame = false;
	this->points = 0;
	this->health = 20;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false;
}

void Game::InitWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::InitFonts()
{
	if (this->font.loadFromFile("Fonts/font1.ttf"))
		std::cerr << "FAILED::TO_LOAD::FONT" << std::endl;
}

void Game::InitTexts()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}

void Game::InitEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color::Cyan);
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);
}

Game::Game()
{
	this->InitVariables();
	this->InitWindow();
	this->InitFonts();
	this->InitTexts();
	this->InitEnemies();
}

Game::~Game()
{
	delete this->window;
}

// Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

// Functions
void Game::spawnEnemy()
{
	/*
		@return void

		Spawns enemies and sets their types, colours. Positions set randomly
			- Sets type
			- Sets a random position
			- Sets a color 
			- Adds enemy to the vector
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	// Randomize enemy type
	int type = rand() % 5;

	switch (type)
	{
	case 0:
		this->enemy.setSize(sf::Vector2f(20.f, 20.f));
		this->enemy.setFillColor(sf::Color::Red);
		break;

	case 1:
		this->enemy.setSize(sf::Vector2f(35.f, 35.f));
		this->enemy.setFillColor(sf::Color::Magenta);
		break;

	case 2:
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		this->enemy.setFillColor(sf::Color::Cyan);
		break;

	case 3:
		this->enemy.setSize(sf::Vector2f(70.f, 70.f));
		this->enemy.setFillColor(sf::Color::Blue);
		break;

	case 4:
		this->enemy.setSize(sf::Vector2f(90.f, 90.f));
		this->enemy.setFillColor(sf::Color::Green);
		break;

	default:
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Yellow);
		break;
	}

	// Spawn the enemy
	this->enemies.push_back(this->enemy);

	// TODO Remove enemies at the end of screen

}

void Game::PollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::UpdateMousePositions()
{
	/*
		@ return void

		Updates mouse positions:
			- Mouse positions relative to window (Vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::UpdateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << std::endl 
		<< "Health: " << this->health << std::endl;

	this->uiText.setString(ss.str());
}

void Game::UpdateEnemies()
{
	/*
		@return void

		Updates the enemy spawn timer and spawns enemies
		When the total amount of enemies is smaller than the maximum
		Moves the enemies downwards.
		Removes the enemies at the edge of the screen // TODO
	*/

	// Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			// Spawn enemy and reset timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	// Moveing and Updating enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].move(0.f, 2.5f);

		// Check to see if the position of the enemy is off the screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << std::endl;
		}
	}

	// Check if clicked
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					// Gain points
					if(this->enemies[i].getFillColor() == sf::Color::Red)
						this->points += 20;
					else if(this->enemies[i].getFillColor() == sf::Color::Magenta)
						this->points += 15;
					else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->points += 10;
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points += 5;
					else if (this->enemies[i].getFillColor() == sf::Color::Green)
						this->points += 1;

					std::cout << "Points: " << this->points << std::endl;

					// Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}
	
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::Update()
{
	this->PollEvents();

	if (this->endGame == false)
	{
		this->UpdateMousePositions();

		this->UpdateText();

		this->UpdateEnemies();
	}

	// End game condition
	if (this->health <= 0)
		this->endGame = true;
}

void Game::RenderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::RenderEnemies(sf::RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::Render()
{
	/* 
	Steps:
	- clear old frame
	- render objects
	- display frame in window

	Renders the game objects.
	*/

	this->window->clear();

	// Draw game objects
	this->RenderText(*this->window);

	this->RenderEnemies(*this->window);

	this->window->display();
}
