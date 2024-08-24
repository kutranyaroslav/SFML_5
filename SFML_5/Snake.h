#pragma once
#include "SFML/Graphics.hpp"
#include <vector>


struct SnakeSegment
{
	SnakeSegment(int x, int y): position(x,y){}
	sf::Vector2i position;

};
using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction {NONE, UP, DOWN, LEFT, RIGHT};

class Snake {
public:
	Snake(int i_BlockSize);
	~Snake();

	void SetDirection(Direction i_dir);
	Direction GetDirection();
	int GetSpeed();
	sf::Vector2i GetPosition();
	int GetLives();
	int GetScore();
	void IncreaseScore();
	bool HasLost();

	void Lose();
	void ToggleLose();

	void Extend();
	void Reset();
	void Move();
	void Tick();
	void Cut(int i_segments);
	void Render(sf::RenderWindow& i_window);
private:
	void CheckCollisions();
	SnakeContainer m_SnakeBody;
	int m_Size;
	int m_Speed;
	int m_Lives;
	Direction m_Dir;
	int m_Score;
	bool m_Lost;
	sf::RectangleShape m_BodyRect;
};