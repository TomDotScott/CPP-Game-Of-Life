#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

struct Automaton
{
	explicit Automaton(const bool state) : m_alive(state), m_generation(0) {}
	bool m_alive;
	int m_generation;
};

class GameOfLife
{
public:
	GameOfLife(const sf::Vector2i& startPosition, const sf::Vector2i& windowSize);
	void Tick();
	void Render(sf::RenderWindow& window);

	void SetRows(int amount);
	void SetColumns(int amount);

	void OnClick(int row, int col);
	void GenerateRandomAutomata();

private:
	std::vector<std::vector<Automaton>> m_automata;
	sf::Vector2i m_startPosition;
	sf::Vector2i m_windowSize;
	int m_numRows;
	int m_numCols;


	int GetNeighbourCount(int col, int row) const;
	void ClearBoard();
};

