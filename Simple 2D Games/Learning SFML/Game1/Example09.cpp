#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <vector>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(640, 480), "Gf dodge");
	window.setFramerateLimit(60);

	// Charis
	Texture charisTex;
	Sprite charis;

	if (!charisTex.loadFromFile("images/charis.png"))
		throw "Could not load charis.png";

	charis.setTexture(charisTex);
	charis.setScale(Vector2f(0.3f, 0.3f));
	int charisSpawnTimer = 0;

	std::vector<Sprite> chariss;
	chariss.push_back(Sprite(charis));

	// Ed
	Texture edTex;
	Sprite ed;
	int hp = 10;
	RectangleShape hpBar;
	hpBar.setFillColor(Color::Red);
	hpBar.setSize(Vector2f((float)hp * 20.0f, 20.0f));
	hpBar.setPosition(200.0f, 10.0f);

	if(!edTex.loadFromFile("images/ed.png"))
		throw "Could not load ed.png";

	ed.setTexture(edTex);
	ed.setScale(Vector2f(0.3f, 0.3f));


	// Game loop
	while (window.isOpen() && hp > 0)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}

		// Update
		// Update Ed (Player)
		ed.setPosition(ed.getPosition().x, Mouse::getPosition(window).y);

		// Stops player going out of bounds
		if (ed.getPosition().y > window.getSize().y - ed.getGlobalBounds().height) // bottom
			ed.setPosition(ed.getPosition().x, window.getSize().y - ed.getGlobalBounds().height); 

		if (ed.getPosition().y < 0) // top
			ed.setPosition(ed.getPosition().x, 0);

		// Update charis
		for (size_t i = 0; i < chariss.size(); i++)
		{
			chariss[i].move(-8.0f, 0.0f);

			if (chariss[i].getPosition().x < 0 - charis.getGlobalBounds().width)
			{
				chariss.erase(chariss.begin() + i);
			}
		}

		if (charisSpawnTimer < 50)
			charisSpawnTimer++;

		if (charisSpawnTimer >= 50)
		{
			charis.setPosition(window.getSize().x, rand()%int(window.getSize().y - charis.getGlobalBounds().height));
			chariss.push_back(Sprite(charis));
			charisSpawnTimer = 0;
		}

		// Collision
		for (size_t i = 0; i < chariss.size(); i++)
		{
			if (ed.getGlobalBounds().intersects(chariss[i].getGlobalBounds()))
			{
				hp--;
				chariss.erase(chariss.begin() + i);
			}
		}

		// Update UI
		hpBar.setSize(Vector2f((float)hp * 20.0f, 20.0f));

		// Draw
		window.clear(Color::White);


		for (size_t i = 0; i < chariss.size(); i++)
		{
			window.draw(chariss[i]);
		}

		window.draw(ed);

		// UI
		window.draw(hpBar);

		window.display();
	}

	return 0;
}