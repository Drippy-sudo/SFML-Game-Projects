#include "stdafx.h"
#include "Game.h"

void Game::InitWindow()
{
	this->window.create(sf::VideoMode(800, 600), "Game 4", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
}

void Game::InitPlayer()
{
	this->player = new Player();
}

Game::Game()
{
	this->InitWindow();
	this->InitPlayer();
}

Game::~Game()
{
	delete this->player;
}

void Game::UpdatePlayer()
{
	this->player->Update();
}

void Game::UpdateCollision()
{
	// Collision bottom of the screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			this->window.getSize().y - this->player->getGlobalBounds().height
		);
	}
}

void Game::Update()
{
	// Polling window events
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			this->window.close();

		if (this->ev.type == sf::Event::KeyReleased &&
			(
				this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::D ||
				this->ev.key.code == sf::Keyboard::W ||
				this->ev.key.code == sf::Keyboard::S
				)
			)
		{
			this->player->ResetAmimationTimer();
		}
	}

	this->UpdatePlayer();
	this->UpdateCollision();
}

void Game::RenderPlayer()
{
	this->player->Render(this->window);
}

void Game::Render()
{
	this->window.clear();

	// Render game
	this->RenderPlayer();

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}
