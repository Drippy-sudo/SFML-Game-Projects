#pragma once

#include "Enemy.h"

class Bullet
{
private:
	sf::Sprite shape;

	sf::Vector2f direction;
	float movementSpeed;

public:
	Bullet();
	Bullet(sf::Texture* texture, float pos_X, float pos_Y, float dir_X, float dir_Y, float movement_speed);
	virtual ~Bullet();

	// Accessors
	const sf::FloatRect getBounds() const;

	// Functions
	void Update();
	void Render(sf::RenderTarget* target);
};

