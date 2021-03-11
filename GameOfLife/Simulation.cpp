#include "Simulation.h"

#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

Simulation::Simulation() :
	m_automata()
{
	for (int i = 0; i < sim_constants::amountY; ++i)
	{
		for (int j = 0; j < sim_constants::amountX; j++)
		{
			if (rand() % 100 < 80)
			{
				m_automata[i][j] = false;
			} else
			{
				m_automata[i][j] = true;
			}
		}
	}
}

void Simulation::Update()
{
	
}

void Simulation::Render(sf::RenderWindow& window)
{
	sf::RectangleShape automaton{{8, 8}};
	automaton.setFillColor(sf::Color::Blue);
	for (int i = 0; i < sim_constants::amountY; ++i)
	{
		for (int j = 0; j < sim_constants::amountX; j++)
		{
			if(m_automata[i][j])
			{
				automaton.setPosition(i * 8, j * 8);
				window.draw(automaton);
			}
		}
	}
}
