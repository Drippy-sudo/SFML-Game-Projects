#pragma once

// c++ includes
#include <iostream>

// SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Enemy
{
private:
	unsigned pointCount;
	sf::CircleShape shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void InitVariables();
	void InitShape();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	// Accessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	// Functions
	void Update();
	void Render(sf::RenderTarget* target);
};

