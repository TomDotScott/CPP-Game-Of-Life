#include "FPS.h"

FPS::FPS() :
	m_frame(0),
	m_fps(0)
{

}

unsigned FPS::GetFPS() const
{
	return m_fps;
}

void FPS::Update()
{
	if (m_clock.getElapsedTime().asSeconds() >= 1.f)
	{
		m_fps = m_frame;
		m_frame = 0;
		m_clock.restart();
	}

	++m_frame;
}
