#include "GameOfLife.h"

#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

GameOfLife::GameOfLife(const sf::Vector2i& startPosition, const sf::Vector2i& windowSize) :
	m_startPosition(startPosition),
	m_windowSize(windowSize),
	m_numRows(100),
	m_numCols(100)
{
	for (int i = 0; i < m_numCols; ++i)
	{
		std::vector<Automaton> aVector;
		for (int j = 0; j < m_numRows; j++)
		{
			Automaton a{ false };
			if (rand() % 100 < 25)
			{
				a.m_alive = true;
			}
			aVector.push_back(a);
		}
		m_automata.push_back(aVector);
	}
}

void GameOfLife::Tick()
{
	// Loop through the cells
	for (int i = 0; i < static_cast<int>(m_automata.size()); ++i)
	{
		for (int j = 0; j < static_cast<int>(m_automata[i].size()); j++)
		{
			const int neighbourCount = GetNeighbourCount(i, j);

			auto& automaton = m_automata[i][j];

			// 1. Any live cell with two or three live neighbours survives.
			if (neighbourCount != 2 && neighbourCount != 3)
			{
				automaton.m_alive = false;
			}

			// 3. All other live cells die in the next generation. Similarly, all other dead cells stay dead.
			automaton.m_generation++;

			if (automaton.m_generation > 1)
			{
				automaton.m_alive = false;
			}

			// 2. Any dead cell with three live neighbours becomes a live cell.
			if (neighbourCount == 3 && !automaton.m_alive)
			{
				automaton.m_alive = true;
				automaton.m_generation = 0;
			}
		}
	}
}

void GameOfLife::Render(sf::RenderWindow& window)
{
	const int sizeX = m_windowSize.x / m_numCols;
	const int sizeY = m_windowSize.y / m_numRows;
	sf::RectangleShape automaton{ {static_cast<float>(sizeX), static_cast<float>(sizeY)} };
	automaton.setFillColor(sf::Color::Blue);

	for (int i = 0; i < static_cast<int>(m_automata.size()); ++i)
	{
		for (int j = 0; j < static_cast<int>(m_automata[i].size()); ++j)
		{
			if (m_automata[i][j].m_alive)
			{
				automaton.setPosition(m_startPosition.x + i * sizeX, m_startPosition.y + j * sizeY);
				window.draw(automaton);
			}
		}
	}
}

int GameOfLife::GetNeighbourCount(const int col, const int row) const
{
	int neighbourCount = 0;

	// TL
	if (col != 0 && row != 0 && m_automata[col - 1][row - 1].m_alive)
	{
		neighbourCount++;
	}

	// Top
	if (row != 0 && m_automata[col][row - 1].m_alive)
	{
		neighbourCount++;
	}

	// TR
	if (col != m_automata.size() - 1 && row != 0 && m_automata[col + 1][row - 1].m_alive)
	{
		neighbourCount++;
	}

	// Left 
	if (col != 0 && m_automata[col - 1][row].m_alive)
	{
		neighbourCount++;
	}

	// Right
	if (col < m_automata.size() - 1 && m_automata[col + 1][row].m_alive)
	{
		neighbourCount++;
	}

	// BL
	if (col != 0 && row < m_automata[0].size() - 1 && m_automata[col - 1][row + 1].m_alive)
	{
		neighbourCount++;
	}

	// BR
	if (col != m_automata.size() - 1 && row < m_automata[0].size() - 1 && m_automata[col + 1][row + 1].m_alive)
	{
		neighbourCount++;
	}

	// Bottom
	if (row < m_automata[0].size() - 1 && m_automata[col][row + 1].m_alive)
	{
		neighbourCount++;
	}

	return neighbourCount;
}

