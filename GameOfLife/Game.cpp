#include "Game.h"


#include <iostream>
#include <SFML/Window/Mouse.hpp>

Game::Game() :
	m_simulation({ 0, 0 }, { 800, 800 })
{
	m_simulation.SetRows(25);
	m_simulation.SetColumns(25);
}

void Game::Update(sf::RenderWindow& window)
{
	const sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	printf("Mouse Position: %i  %i\n", mousePosition.x, mousePosition.y);
}

void Game::Render(sf::RenderWindow& window) {}
