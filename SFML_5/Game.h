#pragma once
#include "Window.h"
#include "World.h"
class Game
{
public:
	Game();
	~Game();
	void HandleInput();
	void Update();
	void Render();
	void RestartClock();
	sf::Time GetElapsed();
	Window* GetWindow();
private:
	Window m_window;
	sf::Clock m_Clock;
	sf::Time m_Elapsed;
	

	World m_World;
	Snake m_Snake;

};

