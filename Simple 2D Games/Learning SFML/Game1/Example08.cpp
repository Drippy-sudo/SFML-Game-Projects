//#include <iostream>
//#include "SFML/Graphics.hpp"
//#include "SFML/Window.hpp"
//#include "SFML/System.hpp"
//#include <cstdlib>
//
//#include <vector>
//
//int main()
//{
//	srand(time(NULL));
//
//	sf::RenderWindow window(sf::VideoMode(640, 480), "Ball shooter");
//	window.setFramerateLimit(60);
//
//	// Projectile ball
//	sf::CircleShape projectile;
//	projectile.setFillColor(sf::Color::Yellow);
//	projectile.setRadius(5.0f);
//	std::vector <sf::CircleShape> projectiles;
//	projectiles.push_back(sf::CircleShape(projectile)); // Making a copy of projectile
//
//	// Enemy
//	sf::RectangleShape enemy;
//	enemy.setFillColor(sf::Color::Red);
//	enemy.setSize(sf::Vector2f(50.0f, 50.0f));
//	std::vector <sf::RectangleShape> enemies;
//	enemies.push_back(sf::RectangleShape(enemy));
//	int enemySpawnTimer = 0;
//
//	// Player
//	sf::CircleShape player;
//	player.setFillColor(sf::Color::Green);
//	player.setRadius(50.0f);
//	player.setPosition(window.getSize().x / 2 - player.getRadius(), window.getSize().y - player.getRadius() * 2 - 10.0f);
//	sf::Vector2f playerCenter;
//	int shootTimer = 0;
//
//	while (window.isOpen())
//	{
//		sf::Event e;
//		while (window.pollEvent(e))
//		{
//			if (e.type == sf::Event::Closed)
//				window.close();
//			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
//				window.close();
//		}
//
//		// Update
//		// Player
//		playerCenter = sf::Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());
//
//		// Player movement
//		player.setPosition(sf::Mouse::getPosition(window).x, player.getPosition().y);
//
//		// Projectiles
//		if (shootTimer < 5)
//			shootTimer++;
//
//		// Shooting projectiles
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer >= 3) 
//		{
//			projectile.setPosition(playerCenter);
//			projectiles.push_back(sf::CircleShape(projectile));
//
//			shootTimer = 0;
//		}
//
//		// Erasing projectiles
//		for (size_t i = 0; i < projectiles.size(); i++) 
//		{
//			projectiles[i].move(0.0f, -10.0f);
//
//			if (projectiles[i].getPosition().y <= 0)
//				projectiles.erase(projectiles.begin() + i);
//		}
//
//		// Enemies
//		if (enemySpawnTimer < 20)
//			enemySpawnTimer++;
//
//		if (enemySpawnTimer >= 20)
//		{
//			enemy.setPosition((rand() % int(window.getSize().x - enemy.getSize().x)), 0);
//			enemies.push_back(sf::RectangleShape(enemy));
//
//			enemySpawnTimer = 0;
//		}
//
//		for (size_t i = 0; i < enemies.size(); i++)
//		{
//			enemies[i].move(0.0f, 5.0f);
//
//			if (enemies[i].getPosition().y > window.getSize().y - 20)
//				enemies.erase(enemies.begin() + i);
//		}
//
//		// Collision
//		for (size_t i = 0; i < projectiles.size(); i++)
//		{
//			for (size_t k = 0; k < enemies.size(); k++)
//			{
//				if (projectiles[i].getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
//				{
//					projectiles.erase(projectiles.begin() + i);
//					enemies.erase(enemies.begin() + k);
//					break;
//				}
//			}
//		}
//
//		// Draw
//		window.clear(sf::Color::White);
//
//		window.draw(player);
//
//		for (size_t i = 0; i < enemies.size(); i++)
//		{
//			window.draw(enemies[i]);
//		}
//
//		for (size_t i = 0; i < projectiles.size(); i++) // drew last to make sure it's drawn over everything else
//		{
//			window.draw(projectiles[i]);
//		}
//
//		window.display();
//	}
//
//	return 0;
//}