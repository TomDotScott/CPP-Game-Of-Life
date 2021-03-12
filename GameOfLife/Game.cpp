#include "Game.h"


#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

Game::Game() :
	m_simulation({ 0, 0 }, { 800, 800 }),
	m_rows(50),
	m_cols(50),
	m_clickCoolDown(0.f)
{
	m_simulation.SetRows(m_rows);
	m_simulation.SetColumns(m_cols);
	//m_simulation.GenerateRandomAutomata();
}

void Game::Update(sf::RenderWindow& window)
{
	if (m_started)
	{
		// Game tick every 100 ms
		while (m_clock.getElapsedTime() >= sf::milliseconds(300))
		{
			m_clock.restart();
			m_simulation.Tick();
		}
	}
	else
	{
		const float dt = m_clock.getElapsedTime().asSeconds();
		m_clickCoolDown += dt;

		const sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		const int windowX = window.getSize().x;
		const int windowY = window.getSize().y;

		if (m_clickCoolDown > 0.1f)
		{
			if (mousePosition.x > 0 && mousePosition.y > 0 && mousePosition.x < windowX && mousePosition.y < windowY)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					const int mouseX = mousePosition.x / (windowX / m_cols);
					const int mouseY = mousePosition.y / (windowY / m_rows);
					//printf("Mouse Position: %i  %i\n", mouseX / , mouseY / );
					m_simulation.OnClick(mouseY, mouseX);
					m_clickCoolDown = 0.f;
				}
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			m_started = true;
		}
		
		m_clock.restart();
	}
}

void Game::Render(sf::RenderWindow& window)
{
	sf::Vector2u m_windowSize = window.getSize();

	const int sizeX = m_windowSize.x / m_cols;
	const int sizeY = m_windowSize.y / m_rows;

	sf::RectangleShape rectangleShape{ {static_cast<float>(sizeX), static_cast<float>(sizeY)} };
	rectangleShape.setFillColor(sf::Color::Black);
	rectangleShape.setOutlineColor({255, 255, 255, 10});
	rectangleShape.setOutlineThickness(3);

	for (int i = 0; i < m_cols; ++i)
	{
		for (int j = 0; j < m_rows; ++j)
		{
			rectangleShape.setPosition(i * sizeX, j * sizeY);
			window.draw(rectangleShape);
		}
	}
	m_simulation.Render(window);
}
