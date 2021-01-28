#include "Player.h"

void Player::InitVariables()
{
	this->movementSpeed = 7.5f;
	this->attackCooldownMax = 5.f;
	this->attackCooldown = this->attackCooldownMax;

	this->maxHp = 100;
	this->hp = this->maxHp;
}

// Private functions
void Player::InitTexture()
{
	// Load texture from file
	if (!this->texture.loadFromFile("Textures/ship.png"))
		std::cout << "ERROR::INITTEXTURE::FAILED::TO::LOAD_SHIP";
}

void Player::InitSprite()
{
	// Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	// Resize sprite
	this->sprite.scale(.1f, .1f);
}

Player::Player()
{
	this->InitVariables();
	this->InitTexture();
	this->InitSprite();
}

Player::~Player()
{

}

// Accessors
const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHP() const
{
	return this->hp;
}

const int& Player::getHPMax() const
{
	return this->maxHp;
}

// Modifiers
void Player::setPostion(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPostion(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHP(const int hp)
{
	this->hp = hp;
}

void Player::loseHP(const int value)
{
	this->hp -= value;

	if (this->hp < 0)
		this->hp = 0;
}

// Functions
void Player::Move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}
	else
		return false;
}

void Player::UpdateAttack()
{
	if(this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

void Player::Update()
{
	this->UpdateAttack();
}

void Player::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
