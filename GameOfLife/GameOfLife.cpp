#include <iostream>
#include <sstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "FPS.h"
#include "Simulation.h"

int main()
{
	srand(time(nullptr));
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Pac-Man");

	FPS fps;

	sf::Clock clock;

	Simulation sim;
	
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

		window.setTitle("SFML Pac-Man   FPS: " + ss.str());

		// Game tick every 100 ms
		while (clock.getElapsedTime() >= sf::milliseconds(200))
		{
			clock.restart();
			sim.Update();
		}

		window.clear();
		sim.Render(window);
		window.display();
	}
	return EXIT_SUCCESS;
}