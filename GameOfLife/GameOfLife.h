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

struct Automaton
{
	bool m_alive = false;
	int m_generation = 0;
};

class GameOfLife
{
public:
	GameOfLife();
	void Tick();
	void Render(sf::RenderWindow& window);
private:
	std::array<std::array<Automaton, sim_constants::amountX>, sim_constants::amountY> m_automata;

	int GetNeighbourCount(int col, int row) const;
};

