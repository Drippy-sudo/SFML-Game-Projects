#pragma once

// SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player
{
private:
	sf::RectangleShape shape;

	float movementSpeed;
	int hp;
	int maxHP;


	void InitVariables();
	void InitShape();

public:
	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();

	// Accessors
	const sf::RectangleShape& getShape() const;
	const int& getHP() const;
	const int& getMaxHP() const;

	// Functions
	void TakeDamage(const int damage);
	void GainHealth(const int health);

	void UpdateInput();
	void UdpateWindowBoundsCollision(const sf::RenderTarget* target);
	void Update(const sf::RenderTarget* target);
	void Render(sf::RenderTarget* target);
};

