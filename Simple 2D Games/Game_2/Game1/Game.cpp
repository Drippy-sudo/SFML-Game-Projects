#include "Game.h"

void Game::InitVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxSwagBalls = 10;
	this->points = 0;
}

void Game::InitWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Game_2", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::InitFonts()
{
	if(!this->font.loadFromFile("Fonts/font1.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::COULD_NOT_LOAD font1.ttf" << "\n";
	}
}

void Game::InitText()
{
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(24);
	this->guiText.setString("test");

	// End game text
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setPosition(sf::Vector2f(20, 300));
	this->endGameText.setString("You Died! Exit the game.");
}

Game::Game()
{
	this->InitVariables();
	this->InitWindow();
	this->InitFonts();
	this->InitText();
}

Game::~Game()
{
	delete this->window;
}

// Accessors

const bool& Game::getEndGame() const
{
	return this->endGame;
}

// Functions

const bool Game::Running() const
{
	return this->window->isOpen(); //&& this->endGame == false;
}

void Game::PollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}


void Game::SpawnSwagBalls()
{
	// Timer
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.f;
	else
	{
		if (this->swagBalls.size() < this->maxSwagBalls)
		{
			this->swagBalls.push_back(SwagBall(*this->window, this->RandBallType()));

			this->spawnTimer = 0.f;
		}
	}
}

const int Game::RandBallType() const
{
	int type = SwagBallTypes::DEFAULT;
	int randValue = rand() % 100 + 1;

	if (randValue > 60 && randValue <= 80)
		type = SwagBallTypes::DAMAGING;
	else if (randValue > 80 && randValue <= 100)
		type = SwagBallTypes::HEALING;

	return type;
}

void Game::UpdatePlayer()
{
	this->player.Update(this->window);

	if (this->player.getHP() <= 0)
		this->endGame = true;
}

void Game::UpdateCollision()
{
	// Check the collision
	for (size_t i = 0; i < swagBalls.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds()))
		{
			switch (this->swagBalls[i].getType())
			{
			case SwagBallTypes::DEFAULT:
				this->points++;
				break;
			case SwagBallTypes::DAMAGING:
				this->player.TakeDamage(10);
				break;
			case SwagBallTypes::HEALING:
				this->player.GainHealth(1);
				break;
			}

			// Add points
			points++;

			// Remove ball
			this->swagBalls.erase(this->swagBalls.begin() + i);
		}
	}
}

void Game::UpdateGUI()
{
	std::stringstream ss;

	ss << " - Points: " << this->points << "\n"
		<< " - Health: " << this->player.getHP() << " / " << this->player.getMaxHP() << "\n";

	this->guiText.setString(ss.str());
}

void Game::Update()
{
	this->PollEvents();

	if (this->endGame == false)
	{
		this->SpawnSwagBalls();
		this->UpdatePlayer();
		this->UpdateCollision();
		this->UpdateGUI();
	}

}

void Game::RenderGUI(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}

void Game::Render()
{
	this->window->clear();

	// Render stuff
	this->player.Render(this->window);

	for (auto i : this->swagBalls)
	{
		i.Render(*this->window);
	}

	// Render gui
	this->RenderGUI(this->window);

	// Render end game
	if (this->endGame == true)
		this->window->draw(this->endGameText);

	this->window->display();
}
