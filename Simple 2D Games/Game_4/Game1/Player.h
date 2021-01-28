#pragma once

enum PLAYER_ANIMATION_STATES {IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING};

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;

	// Animation
	short animState;
	sf::IntRect currentFrame;
	bool animSwitch;

	// Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;

	// Core
	void InitVariables();
	void InitTexture();
	void InitSprite();
	void InitAnimations();
	void InitPhysics();

public:
	Player();
	virtual ~Player();

	// Accessors
	const bool& getAnimSwitch();
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	// Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();

	// Functions
	void ResetAmimationTimer();
	void move(const float dir_x, const float dir_y);
	void UpdatePhysics();
	void UpdateMovement();
	void UpdateAnimations();
	void Update();
	void Render(sf::RenderTarget& target);
};

