#include "Game.h"

// Private function
void Game::InitWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600),
		"Game3", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::InitTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::InitGUI()
{
	// Load fonts
	if (!this->font.loadFromFile("Fonts/font1.ttf"))
		std::cout << "ERROR::GAME::Failed_to_load_font" << "\n";

	// Init point text
	this->pointText.setPosition(700.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("TEST");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2 - this->gameOverText.getGlobalBounds().width / 2,
		this->window->getSize().y / 2 - this->gameOverText.getGlobalBounds().height / 2);

	// Init player GUI
	this->playerHPBar.setSize(sf::Vector2f(300.0f, 25.f));
	this->playerHPBar.setFillColor(sf::Color::Red);
	this->playerHPBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHPBarBack = this->playerHPBarBack;
	this->playerHPBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::InitWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/background1.jpg"))
		std::cout << "ERROR::GAME::Failed_to_load_background_texture" << "\n";

	this->worldBackground.setTexture(this->worldBackgroundTex); 
}

void Game::InitSystems()
{
	this->points = 0;
}

void Game::InitPlayer()
{
	this->player = new Player();
}

void Game::InitEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

Game::Game()
{
	this->InitWindow();
	this->InitTextures();
	this->InitGUI();
	this->InitWorld();
	this->InitSystems();
	this->InitPlayer();
	this->InitEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	// Delete textures
	for (auto &i : this->textures)
		delete i.second;

	// Delete bullets
	for (auto *i : this->bullets)
		delete i;

	// Delete enemies
	for (auto* i : this->enemies)
		delete i;
}

// Functions
void Game::Run()
{
	while (this->window->isOpen())
	{
		this->UpdatePollEvents();

		if(this->player->getHP() > 0)
			this->Update();

		this->Render();
	}
}

void Game::UpdatePollEvents()
{
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed)
			this->window->close();

		if (ev.KeyPressed && ev.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::UpdateInput()
{
	// Move player

	// Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->Move(-1.f, 0.f);

	// Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->Move(1.f, 0.f);

	// Up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->Move(0.f, -1.f);

	// Down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->Move(0.f, 1.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
		this->bullets.push_back(new Bullet(this->textures["BULLET"],
			this->player->getPos().x + this->player->getBounds().width / 2.f,
			this->player->getPos().y, 0.f, -1.f, 5.f));
}

void Game::UpdateGUI()
{
	std::stringstream ss;

	ss << "Points: " << this->points;

	this->pointText.setString(ss.str());

	// Update player GUI
	float hpPercent = static_cast<float>(this->player->getHP()) / this->player->getHPMax();
	this->playerHPBar.setSize(sf::Vector2f(300.0f * hpPercent, this->playerHPBar.getSize().y * hpPercent));
}

void Game::UpdateWorld()
{

}

void Game::UpdateCollision()
{
	// Left world collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPostion(0.f, this->player->getBounds().top);
	}
	// Right world collision
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPostion(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	// Top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPostion(this->player->getBounds().left, 0.f);
	}
	// Bottom world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPostion(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::UpdateBullets()
{
	unsigned counter = 0;
	for (auto& bullet : this->bullets)
	{
		bullet->Update();

		// Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			// Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
		}
		++counter;
	}
}

void Game::UpdateEnemies()
{
	// Spawning
	this->spawnTimer += 0.5f;

	// Resets timer
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	// Update
	unsigned counter = 0;
	for (auto& enemy : this->enemies)
	{
		enemy->Update();

		// Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			// Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		}
		// Enemy player collision
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHP(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}

		++counter;
	}
}

void Game::UpdateCombat()
{
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}

void Game::Update()
{
	this->UpdateInput();
	this->player->Update();
	this->UpdateCollision();
	this->UpdateBullets();
	this->UpdateEnemies();
	this->UpdateCombat();
	this->UpdateGUI();
	this->UpdateWorld();
}

void Game::RenderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHPBarBack);
	this->window->draw(this->playerHPBar);
}

void Game::RenderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::Render()
{
	this->window->clear();

	// World
	this->RenderWorld();

	// Draw...
	this->player->Render(*this->window);

	for (auto& bullet : this->bullets)
	{
		bullet->Render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->Render(this->window);
	}

	this->RenderGUI();

	// Game over screen
	if (this->player->getHP() <= 0)
		this->window->draw(this->gameOverText);

	this->window->display();
}
