#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

int main()
{
	sf::RenderWindow window(
		sf::VideoMode({ 1280, 720 }), "2D Sandbox Game");

	// while loop when window is open
	while (window.isOpen()) {
		while (const optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}
	}

	window.clear();

	// Game content drawn below

	window.display();

	return 0;
}