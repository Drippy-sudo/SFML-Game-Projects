#include "Player.h"

void Player::InitVariables()
{
	this->movementSpeed = 5.f;
	this->maxHP = 10;
	this->hp = maxHP;
}

void Player::InitShape()
{
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);

	this->InitVariables();
	this->InitShape();
}

Player::~Player()
{

}

const sf::RectangleShape& Player::getShape() const
{
	return this->shape;
}

const int& Player::getHP() const
{
	return this->hp;
}

const int& Player::getMaxHP() const
{
	return this->maxHP;
}

void Player::TakeDamage(const int damage)
{
	if (this->hp > 0)
		this->hp -= damage;

	if(this->hp < 0)
		this->hp = 0;
}

void Player::GainHealth(const int health)
{
	if (this->hp < this->maxHP)
		this->hp += health;

	if (this->hp > this->maxHP)
		this->hp = this->maxHP;
}

void Player::UpdateInput()
{
	// Keyboard input
	// Horizontal movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->shape.move(-this->movementSpeed, 0.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->shape.move(this->movementSpeed, 0.f);

	// Vertical movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->shape.move(0.f, -this->movementSpeed);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->shape.move(0.f, this->movementSpeed);
}

void Player::UdpateWindowBoundsCollision(const sf::RenderTarget* target)
{
	// Left 
	if (this->shape.getGlobalBounds().left <= 0.f)
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);

	// Right
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);

	// Top 
	if (this->shape.getGlobalBounds().top <= 0.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);

	// Bottom
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
}

void Player::Update(const sf::RenderTarget* target)
{
	this->UpdateInput();

	// Window bound collision
	this->UdpateWindowBoundsCollision(target);
}

void Player::Render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
