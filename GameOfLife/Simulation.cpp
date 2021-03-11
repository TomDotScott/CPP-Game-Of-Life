#include "Simulation.h"

#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

Simulation::Simulation() :
	m_automata()
{
	for (int i = 0; i < sim_constants::amountY; ++i)
	{
		for (int j = 0; j < sim_constants::amountX; j++)
		{
			if (rand() % 100 < 80)
			{
				m_automata[i][j].m_alive = false;
			} else
			{
				m_automata[i][j].m_alive = true;
			}
		}
	}
}

void Simulation::Update()
{
	// Loop through the cells
	for (int i = 0; i < sim_constants::amountY; ++i)
	{
		for (int j = 0; j < sim_constants::amountX; j++)
		{
			const int neighbourCount = GetNeighbourCount(i, j);

			auto& automaton = m_automata[i][j];
			
			// 1. Any live cell with two or three live neighbours survives.
			if(neighbourCount != 2 && neighbourCount != 3)
			{
				automaton.m_alive = false;
			}

			// 2. Any dead cell with three live neighbours becomes a live cell.
			if(neighbourCount == 3 && !automaton.m_alive)
			{
				automaton.m_alive = true;
				automaton.m_generation = 0;
			}

			// 3. All other live cells die in the next generation. Similarly, all other dead cells stay dead.
			automaton.m_generation++;
			
			if(m_automata[i][j].m_generation > 1)
			{
				automaton.m_alive = false;
			}
		}
	}
}

void Simulation::Render(sf::RenderWindow& window)
{
	sf::RectangleShape automaton{{8, 8}};
	automaton.setFillColor(sf::Color::Blue);
	automaton.setOutlineThickness(1.f);
	automaton.setOutlineColor(sf::Color::White);
/*	sf::Font font;
	font.loadFromFile("font.ttf");
	sf::Text debugText;
	debugText.setFillColor(sf::Color::White);
	debugText.setCharacterSize(10);
	debugText.setFont(font);*/
	for (int i = 0; i < sim_constants::amountY; ++i)
	{
		for (int j = 0; j < sim_constants::amountX; j++)
		{
			if(m_automata[i][j].m_alive)
			{
				automaton.setPosition(i * 8, j * 8);
				window.draw(automaton);
			}

			/*const std::string text{ std::to_string(i) + ", " + std::to_string(j) };
			debugText.setString(text);
			debugText.setPosition(i * 8, j * 8);
			window.draw(debugText);*/
		}
	}
}

int Simulation::GetNeighbourCount(const int col, const int row) const
{
	int neighbourCount = 0;
	
	if(col != 0 && m_automata[col - 1][row].m_alive)
	{
		neighbourCount++;
	}

	if(col < sim_constants::amountY - 1 && m_automata[col + 1][row].m_alive)
	{
		neighbourCount++;
	}

	if(row < sim_constants::amountX - 1 && m_automata[col][row + 1].m_alive)
	{
		neighbourCount++;
	}

	if(row != 0 && m_automata[col][row - 1].m_alive)
	{
		neighbourCount++;
	}

	return neighbourCount;
}

