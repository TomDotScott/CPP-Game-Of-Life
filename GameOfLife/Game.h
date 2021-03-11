#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameOfLife.h"

class Game
{
public:
	Game();
	void Update(sf::RenderWindow& window);
	void Render(sf::RenderWindow& window);

private:
	GameOfLife m_simulation;
};
