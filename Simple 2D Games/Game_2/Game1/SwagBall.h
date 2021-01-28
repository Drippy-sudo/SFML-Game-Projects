#pragma once

// SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum SwagBallTypes {DEFAULT = 0, DAMAGING, HEALING, NROFTYPES};

class SwagBall
{
private:
	sf::CircleShape shape;

	int type;

	void InitShape(const sf::RenderWindow& window);

public:
	SwagBall(const sf::RenderWindow& window, int type);
	virtual ~SwagBall();

	// Accessors
	const sf::CircleShape getShape() const;
	const int& getType() const;

	// Functions
	void Update();
	void Render(sf::RenderTarget& target);
};

