#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

/*
This is my 2d game "Untitled" that will eventually become an engine.
For now this is an open world survival sandbox game similar to Terraria or 
	other 2d sandboxes that might come to mind.
The goal for this project is to develop the game and engine and then eventually
	strip the game part away and build up the engine part and make this an editor.

Potentially use Dear ImGui for engine editor?
Replace constants with serialization?

Made with C++ and SFML 3.0.0 by Benjamin Messenger AKA "PyBenny"
*/


int main()
{
	// Create window 1280 x 720.
	sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "2D Sandbox Game");

	// ----------------
	// -- GAME SETUP --
	// ----------------

	constexpr float TILE_SIZE = 32.f; // 32x32 world tile size

	sf::RectangleShape player({ 32.f, 64.f }); // TEMP PLAYER SIZE HITBOX
	player.setPosition({ 400.f, 300.f }); // TEMP set player position in window

	sf::Clock clock; // clock time variable
	constexpr float PLAYER_SPEED = 200.f; // TEMP defining float player speed of 200.f
	
	// -----------------
	// --- GAME LOOP ---
	// -----------------

	// Main game event loop
	while (window.isOpen()) {
		// -EVENTS-
		// Checking if user closes
		// Does user press G?
		// Does user resize window?
		float deltaTime = clock.restart().asSeconds(); // restarts clock and returns how many seconds pass since previous frame
		
		// checking if an event happens, and using optional as a box meaning it optionally can contain "something" or "not something"
		while (const optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) { // if the action is "closed" then close the window
				// if optional event variable inside event is of type closed event then close window
				window.close();
			}
		}

		// -UPDATE-
		// Player movement will go here

		// player speed (pixels per second * time since last clock restart)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			player.move({ PLAYER_SPEED * deltaTime, 0.f }); // move right
		}
		
		// Is a key held?
		// Move player
		// Apply Gravity
		// Add collision and check for it
		// Update the enemies




		// -DRAW-
		window.clear(); // erase old frame

		window.draw(player);

		window.display(); // show completed frame
	}


	return 0;
}