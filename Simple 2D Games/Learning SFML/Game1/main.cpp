//#include <iostream>
//
//#include "SFML\Graphics.hpp"
//#include "SFML\Window.hpp"
//#include "SFML\System.hpp"
//
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(640, 400), "SFML works!");
//	window.setFramerateLimit(60);
//
//	sf::CircleShape triangle(50.f, 3);
//	triangle.setFillColor(sf::Color::Red);
//	triangle.setOutlineThickness(5.f);
//	triangle.setOutlineColor(sf::Color::Blue);
//
//	sf::Vertex line[] = { sf::Vertex(sf::Vector2f(100.f, 400.f)), sf::Vertex(sf::Vector2f(50.f, 100.f)) };
//
//	sf::ConvexShape convex;
//	convex.setPosition(sf::Vector2f(400.f, 50.f));
//
//	convex.setPointCount(5);
//
//	convex.setPoint(0, sf::Vector2f(0, 0));
//	convex.setPoint(1, sf::Vector2f(150, 10));
//	convex.setPoint(2, sf::Vector2f(120, 90));
//	convex.setPoint(3, sf::Vector2f(30, 100));
//	convex.setPoint(4, sf::Vector2f(0, 50));
//	
//
//	while (window.isOpen())
//	{
//		sf::Event e;
//		while (window.pollEvent(e))
//		{
//			if (e.type == sf::Event::Closed)
//				window.close();
//		}
//
//		// Draw
//		window.clear();
//
//		// Draw eveything
//		window.draw(triangle);
//		window.draw(line, 2, sf::Lines);
//		window.draw(convex);
//		// Update
//
//		window.display();
//	}
//
//	// End of application
//	return 0;
//}