//#include <iostream>
//#include "SFML\Graphics.hpp"
//#include "SFML\Window.hpp"
//#include "SFML\System.hpp"
//
//using namespace sf;
//
//void Update(int &keyTime, RectangleShape &player, RenderWindow& window);
//void Draw(RenderWindow &window, RectangleShape& player);
//
//int main()
//{
//	int keyTime = 8;
//	RenderWindow window(VideoMode(640, 480), "Simple square demo");
//	window.setFramerateLimit(60);
//
//	RectangleShape player(Vector2f(100.0f, 100.0f));
//	player.setFillColor(Color::Green);
//	player.setPosition(window.getSize().x / 2, window.getSize().y / 2);
//
//
//	while (window.isOpen())
//	{
//		Event e;
//		while (window.pollEvent(e))
//		{
//			if (e.type == Event::Closed)
//				window.close();
//
//			if (e.KeyPressed && e.key.code == Keyboard::Escape)
//				window.close();
//		}
//		// Update
//		Update(keyTime, player, window);
//		// Draw
//		Draw(window, player);
//	}
//
//	return 0;
//}
//
//void Update(int &keyTime, RectangleShape &player, RenderWindow& window)
//{
//	if (Keyboard::isKeyPressed(Keyboard::A) && player.getPosition().x > 0) 
//	{
//		player.move(-5.0f, 0.0f);
//		keyTime = 0;
//	}
//	else if (Keyboard::isKeyPressed(Keyboard::D) && player.getPosition().x 
//		+ player.getSize().x < window.getSize().x) 
//	{
//		player.move(5.0f, 0.0f);
//		keyTime = 0;
//	}
//	else if (Keyboard::isKeyPressed(Keyboard::W) && player.getPosition().y > 0) 
//	{
//		player.move(0.0f, -5.0f);
//		keyTime = 0;
//	}
//	else if (Keyboard::isKeyPressed(Keyboard::S) && player.getPosition().y 
//		+ player.getSize().y < window.getSize().y) 
//	{
//		player.move(0.0f, 5.0f);
//		keyTime = 0;
//	}
//
//	if (Mouse::isButtonPressed(Mouse::Left))
//	{
//		player.setFillColor(Color::Blue);
//	}
//	else
//		player.setFillColor(Color::Green);
//}
//
//void Draw(RenderWindow& window, RectangleShape& player)
//{
//	window.clear(Color::White);
//
//	window.draw(player);
//
//	window.display();
//}
