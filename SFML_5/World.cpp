#include "World.h"
World::World(sf::Vector2u i_windSize) {
	m_BlockSize = 32;
	m_WindowSize = i_windSize;
	RespawnApple();
	m_AppleShape.setFillColor(sf::Color::Red);
	m_AppleShape.setRadius(m_BlockSize / 2);
	for (int i = 0; i < 4; ++i) {
		m_Bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 1) % 2)) {
			m_Bounds[i].setSize(sf::Vector2f(m_WindowSize.x, m_BlockSize));
		}
		else {
			m_Bounds[i].setSize(sf::Vector2f(m_BlockSize, m_WindowSize.y));
		}
		if (i < 2) {
			m_Bounds[i].setPosition(sf::Vector2f(0, 0));
		}
		else {
			m_Bounds[i].setOrigin(m_Bounds[i].getSize());
			m_Bounds[i].setPosition(sf::Vector2f(m_WindowSize));
		}
	}
}
World::~World(){}

void World::RespawnApple() {
	int maxX = (m_WindowSize.x / m_BlockSize) - 2;
	int maxY = (m_WindowSize.y / m_BlockSize) - 2;
	m_Item = sf::Vector2i(rand() % (maxX - 1) + 1 , rand() % (maxY - 1) + 1);
	m_AppleShape.setPosition(m_Item.x * m_BlockSize, m_Item.y * m_BlockSize);
}


void World::Update(Snake& i_player) {
	if (i_player.GetPosition() == m_Item) {
		i_player.Extend();
		i_player.IncreaseScore();
		RespawnApple();
	}

	int gridSize_x = m_WindowSize.x / m_BlockSize;
	int gridSize_y = m_WindowSize.y / m_BlockSize;

	if (i_player.GetPosition().x < 1 ||
		i_player.GetPosition().y < 1 ||
		i_player.GetPosition().x >= gridSize_x - 1 ||
		i_player.GetPosition().y >= gridSize_y - 1) {
		i_player.Lose();
	}
}

int World::GetBlockSize() { return m_BlockSize; }

void World::Render(sf::RenderWindow& i_window) {
	for (int i = 0; i < 4; ++i) {
		i_window.draw(m_Bounds[i]);
		
	}
	i_window.draw(m_AppleShape);
}