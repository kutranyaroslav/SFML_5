#pragma once

#include "Snake.h"

class World
{
public:
	World(sf::Vector2u i_windSize);
	~World();
	int GetBlockSize();
	void RespawnApple();
	void Update(Snake& i_player);
	void Render(sf::RenderWindow& i_window);
private:
	sf::Vector2u m_WindowSize;
	sf::Vector2i m_Item;
	int m_BlockSize;

	sf::CircleShape m_AppleShape;
	sf::RectangleShape m_Bounds[4];
};

