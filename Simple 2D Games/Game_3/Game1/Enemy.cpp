#include "Enemy.h"

void Enemy::InitVariables()
{
	this->pointCount = rand() % 8 + 3; // mini= 3, max = 10
	this->type		= 0;
	this->speed		= static_cast<float>(this->pointCount / 2);
	this->hpMax		= static_cast<int>(this->pointCount);
	this->hp		= this->hpMax;
	this->damage	= this->pointCount;
	this->points	= this->pointCount;
}

void Enemy::InitShape()
{
	this->shape.setRadius(this->pointCount * 5);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->InitVariables();
	this->InitShape();
	this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
	 
}

// Accessors
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

// Functions
void Enemy::Update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::Render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
