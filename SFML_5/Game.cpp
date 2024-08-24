#include "Game.h"
Game::Game():
	m_window("Second window", sf::Vector2u(800,600)),
	m_World(sf::Vector2u(800, 600)),
	m_Snake(m_World.GetBlockSize())
{	
	
}
Game::~Game(){}

void Game::Update() {
	m_window.Update();
	float timestep = 1.0f / m_Snake.GetSpeed();

	while (m_Elapsed.asSeconds() >= timestep) {
		m_Snake.Tick();
		m_World.Update(m_Snake);
		m_Elapsed -= sf::seconds(timestep);

		if (m_Snake.HasLost()) {
			m_Snake.Reset();
			break;
		}
	}
}

void Game::HandleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_Snake.GetDirection() != Direction::DOWN) {
		m_Snake.SetDirection(Direction::UP);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_Snake.GetDirection() != Direction::UP) {
		m_Snake.SetDirection(Direction::DOWN);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_Snake.GetDirection() != Direction::RIGHT) {
		m_Snake.SetDirection(Direction::LEFT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_Snake.GetDirection() != Direction::LEFT) {
		m_Snake.SetDirection(Direction::RIGHT);
	}
	
}
sf::Time Game::GetElapsed() { return m_Elapsed; }

void Game::RestartClock() { 
	m_Elapsed += m_Clock.restart(); 
}



void Game::Render() {
	m_window.BeginDraw();
	m_World.Render(m_window.GetRenderWindow());
	m_Snake.Render(m_window.GetRenderWindow());
	m_window.EndDraw();
}
Window* Game::GetWindow() {
	return &m_window;
}