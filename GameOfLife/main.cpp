#include <iostream>
#include <sstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "FPS.h"
#include "Game.h"
#include "GameOfLife.h"

int main()
{
	srand(time(nullptr));
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Pac-Man");

	FPS fps;

	sf::Clock clock;

	//GameOfLife sim({0, 0}, {800, 800});
	Game game;
	
	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		fps.Update();
		std::ostringstream ss;
		ss << fps.GetFPS();

		window.setTitle("SFML Game Of Life    |    FPS: " + ss.str());

		game.Update(window);
		
		// Game tick every 100 ms
		while (clock.getElapsedTime() >= sf::milliseconds(300))
		{
			clock.restart();
			//sim.Tick();
		}

		window.clear();
		//sim.Render(window);
		game.Render(window);
		window.display();
	}
	return EXIT_SUCCESS;
}