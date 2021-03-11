#pragma once
#include <SFML/System/Clock.hpp>

class FPS
{
public:
    FPS();

    unsigned int GetFPS() const;
    void Update();

private:
    unsigned int m_frame;
    unsigned int m_fps;
    sf::Clock m_clock;
};
