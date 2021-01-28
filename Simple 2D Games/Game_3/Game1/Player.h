#pragma once

#include "Bullet.h"

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	int hp;
	int maxHp;

	// Private functions
	void InitVariables();
	void InitTexture();
	void InitSprite();

public:
	Player();
	virtual ~Player();

	// Accessors
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHP() const;
	const int& getHPMax() const;

	// Modifiers
	void setPostion(const sf::Vector2f pos);
	void setPostion(const float x, const float y);
	void setHP(const int hp);
	void loseHP(const int value);

	// Functions
	void Move(const float dirX, const float dirY);
	const bool canAttack();

	void UpdateAttack();
	void Update();
	void Render(sf::RenderTarget& target);
};


