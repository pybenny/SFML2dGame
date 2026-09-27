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


/*
(0,0)
  +--------------------------→ +x
  |
  |
  |
  ↓
 +y

+x = right
-x = left
+y = down
-y = up

RIGHT = +X
LEFT  = -X

DOWN  = +Y
UP    = -Y
*/

int main()
{
	// Create window 1280 x 720.
	sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "2D Sandbox Game");

	// ----------------
	// -- GAME SETUP --
	// ----------------

	constexpr float TILE_SIZE = 32.0f; // 32x32 world tile size

	// player is the variable
	sf::RectangleShape player({ 32.0f, 64.0f }); // TEMP PLAYER SIZE HITBOX
	player.setPosition({ 400.0f, 536.0f }); // TEMP set player position in window

	sf::Clock clock; // clock time variable

	constexpr float PLAYER_SPEED = 400.0f; // TEMP 400.0f player speed

	constexpr float JUMP_VELOCITY = 450.0f; // TEMP 125.0f player jump velocity (Subject to change, const for now)

	//float move = JUMP_VELOCITY; // PLAYER_SPEED of 200.0f

	constexpr int GROUND_Y = 600; // Ground height Y 600 (will change based on block level)

	constexpr float GRAVITY = 1000.0f; // Player gravity +Y

	sf::Vector2f velocity{ 0.0f, 0.0f };

	bool isGrounded = true;

	// !player variable needs bounds, I need to check those bounds for collision




	// -----------------
	// --- GAME LOOP ---
	// -----------------

	// Main game event loop
	while (window.isOpen()) {
		/*
		Time since the previous frame.

		Example:
		if game runs at ~100 FPS,
		deltaTime might be around 0.01 seconds.
		*/
		float deltaTime = clock.restart().asSeconds(); // restarts clock and returns how many seconds pass since previous frame

		// ----------
		// - EVENTS -
		// ----------
		// Checking if user closes
		// Does user press G?
		// Does user resize window?

		// checking if an event happens, and using optional as a box meaning it optionally can contain "something" or "not something"
		while (const optional event = window.pollEvent()) 
		{
			// Close window
			if (event->is<sf::Event::Closed>()) { // if the action is "close(x)" then close the game
				// if optional event variable inside event is of type closed event then close window
				window.close();
			}

			// !need to save game progress

			if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
				// Player can only jump if currently standing on ground
				if (keyReleased->code == sf::Keyboard::Key::Space && isGrounded) {
					// -Y Upward
					velocity.y = -JUMP_VELOCITY;

					// Player is in air
					isGrounded = false;
				}
			}
		}


		// -UPDATE-
		// Player movement will go here
		// Player movement won't be using W and S key (up & down) | Implementation of W and S is subject to change
		// * player speed (pixels per second * time since last clock restart)
		
		/*
		Notes:
		velocity.x = PLAYER_SPEED
		velocity.y = -JUMP_VELOCITY
		*/


		// ---------------------------
		// --- Horizontal Movement ---
		// ---------------------------

		velocity.x = 0.0f; // no horizontal movement unless A or D is held.

		// Player moves right +x
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			velocity.x = PLAYER_SPEED;
			
		}
		
		// Player moves left -x
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			velocity.x = -PLAYER_SPEED;
			
		}

		// -------------------------
		// --- Vertical Movement ---
		// -------------------------

		/*
		GRAVITY is constantly adding positive Y velocity
		Once player -JUMP_VELOCITY is reached gravity adds y
		*/
		velocity.y += GRAVITY * deltaTime;

		// Player moves upward -y
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		//	velocity.y = -JUMP_VELOCITY;
		//	isJumping = true;
		//}

		// Convert current velocity (pixels/sec) into movement for this frame, then move player
		player.move(velocity * deltaTime);

		// -----------------
		// --- COLLISION ---
		// -----------------

		// RectangleShape position refers to the TOP LEFT of the rectangle.
		// player's bottom = player's Y position + player's height.
		float playerBottom = player.getPosition().y + player.getSize().y;

		// If the player's feet go below the temporary ground level, correct their position.
		if (playerBottom >= GROUND_Y) // player bottom >= ground level
		{
			// put the player's bottom exactly on the ground
			// ground - player height = players top left Y 

			player.getPosition({ player.getPosition().x, GROUND_Y - player.getSize().y });
			
			// stop downward movement
			velocity.y = 0.0f;

			// player can jump again
			isGrounded = true;
		}


		// ------------
		// --- DRAW ---
		// ------------

		window.clear(); // erase old frame

		window.draw(player);

		window.display(); // show completed frame
	}


	return 0;
}