//#include <iostream>
//#include "SFML/Window.hpp"
//#include "SFML/Graphics.hpp"
//#include "SFML/System.hpp"
//
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(640, 480), "Simple game");
//	window.setFramerateLimit(60);
//
//	sf::CircleShape hoop;
//	int dir = 0;
//	hoop.setRadius(50.0f);
//	hoop.setFillColor(sf::Color::Transparent);
//	hoop.setOutlineThickness(5.f);
//	hoop.setOutlineColor(sf::Color::Red);
//	hoop.setPosition(sf::Vector2f(0.0f, 10.0f));
//
//	sf::CircleShape ball;
//	bool isShot = false;
//	ball.setRadius(20.0f);
//	ball.setFillColor(sf::Color::Green);
//	ball.setPosition(sf::Vector2f(0.0f, window.getSize().y - ball.getRadius()*3));
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
//
//		// Hoop logic
//		if (hoop.getPosition().x <= 0)
//			dir = 1;
//		else if (hoop.getPosition().x + hoop.getRadius()*2 >= window.getSize().x)
//			dir = 0;
//
//		if (dir == 0)
//		{
//			hoop.move(-5.0f, 0.0f);
//		}
//		else 
//		{
//			hoop.move(5.0f, 0.0f);
//		}
//
//		// Player logic
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//		{
//			isShot = true;
//		}
//
//		if (!isShot)
//			ball.setPosition(sf::Mouse().getPosition(window).x, ball.getPosition().y);
//		else
//			ball.move(0.0f, -5.0f);
//
//		// Collision
//		if (ball.getPosition().y <= 0 || ball.getGlobalBounds().intersects(hoop.getGlobalBounds()))
//		{
//			// Resets ball
//			isShot = false;
//			ball.setPosition(ball.getPosition().x, window.getSize().y - ball.getRadius() * 3);
//		}
//
//		// Draw
//		window.clear(sf::Color::White);
//		window.draw(hoop);
//		window.draw(ball);
//		window.display();
//	}
//
//	return 0;
//}