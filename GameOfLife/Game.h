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
	int m_rows;
	int m_cols;
	bool m_started;
	float m_clickCoolDown;
	sf::Clock m_clock;
};
