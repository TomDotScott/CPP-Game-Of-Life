#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <array>
// These rules, which compare the behavior of the automaton to real life, can be condensed into the following :
// 1. Any live cell with two or three live neighbours survives.
// 2. Any dead cell with three live neighbours becomes a live cell.
// 3. All other live cells die in the next generation. Similarly, all other dead cells stay dead.

namespace sim_constants
{
	const int amountX = 100;
	const int amountY = 100;
}

class Simulation
{
public:
	Simulation();
	void Update();
	void Render(sf::RenderWindow& window);
private:
	std::array<std::array<bool, sim_constants::amountX>, sim_constants::amountY> m_automata;
};

