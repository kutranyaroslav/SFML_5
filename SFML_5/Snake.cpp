#include "Snake.h"

Snake::Snake(int i_size) :
	m_Size(i_size)
{
	m_BodyRect.setSize(sf::Vector2f(m_Size - 1, m_Size - 1));
	Reset();
}
Snake::~Snake(){}

void Snake::Reset() {
	m_SnakeBody.clear();

	m_SnakeBody.push_back(SnakeSegment(5, 7));
	m_SnakeBody.push_back(SnakeSegment(5, 8));
	m_SnakeBody.push_back(SnakeSegment(5, 9));

	SetDirection(Direction::NONE);
	m_Speed = 5;
	m_Lives = 3;
	m_Score = 0;
	m_Lost = false;
}
void Snake::SetDirection(Direction i_dir) {
	m_Dir = i_dir;
}
Direction Snake::GetDirection() { return m_Dir; }
int Snake::GetSpeed() { return m_Speed; }
sf::Vector2i Snake::GetPosition() {
	return (m_SnakeBody.empty() ? sf::Vector2i(1, 1) : m_SnakeBody.front().position);
}

int Snake::GetLives() { return m_Lives; }
int Snake::GetScore() { return m_Score; }
void Snake::IncreaseScore() { m_Score += 10; }
bool Snake::HasLost() { return m_Lost; }
void Snake::Lose() { m_Lost = true; }
void Snake::ToggleLose() { m_Lost = !m_Lost;}

void Snake::Extend() {
	if (m_SnakeBody.empty()) { return; }
	SnakeSegment& tail_head = m_SnakeBody[m_SnakeBody.size() - 1];
	if (m_SnakeBody.size() > 1) {
		SnakeSegment& tail_bone = m_SnakeBody[m_SnakeBody.size() - 2];
		if (tail_head.position.x == tail_bone.position.x) {
			if (tail_head.position.y >  tail_bone.position.y) {
				m_SnakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
			}
			else {
				m_SnakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
			}
		}else if (tail_head.position.y == tail_bone.position.y) {
			if (tail_head.position.x > tail_bone.position.x) {
				m_SnakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
			}
			else {
				m_SnakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
			}
		}
	} else {
		if (m_Dir == Direction::UP) {
			m_SnakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
		}
		else if (m_Dir == Direction::DOWN) {
			m_SnakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
		}
		else if (m_Dir == Direction::RIGHT) {
			m_SnakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
		}
		else if (m_Dir == Direction::LEFT) {
			m_SnakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
		}

	}
	
}
void Snake::Tick() {
	if (m_SnakeBody.empty()) { return; }
	if (m_Dir == Direction::NONE) { return; }
	Move();
	CheckCollisions();
}
void Snake::Move() {
	for (int i = m_SnakeBody.size() - 1; i > 0; --i) {
		m_SnakeBody[i].position = m_SnakeBody[i - 1].position;
	}
	if (m_Dir == Direction::LEFT) {
		--m_SnakeBody[0].position.x;
	}
	else if (m_Dir == Direction::RIGHT) {
		++m_SnakeBody[0].position.x;
	}
	else if (m_Dir == Direction::UP) {
		--m_SnakeBody[0].position.y;
	}
	else if (m_Dir == Direction::DOWN) {
		++m_SnakeBody[0].position.y;
	}
}

void Snake::CheckCollisions() {
	if (m_SnakeBody.size() < 5) { return; }
	SnakeSegment& head = m_SnakeBody.front();
	for (auto itr = m_SnakeBody.begin() + 1; itr != m_SnakeBody.end(); ++itr) {
		if (itr->position == head.position) {
			int segments = std::distance(itr, m_SnakeBody.end());
			Cut(segments);
			break;
		}

	}
}

void Snake::Cut(int i_segments) {
	for (int i = 0; i < i_segments; ++i) {
		m_SnakeBody.pop_back();
	}
	--m_Lives;
	if (m_Lives <= 0) { Lose(); return; }
}

void Snake::Render(sf::RenderWindow& i_window) {
	if (m_SnakeBody.empty()) { return; }
	auto head = m_SnakeBody.begin();
	m_BodyRect.setFillColor(sf::Color::Yellow);
	m_BodyRect.setPosition(head->position.x * m_Size, head->position.y * m_Size);
	i_window.draw(m_BodyRect);
	m_BodyRect.setFillColor(sf::Color::Green);
	for (auto itr = m_SnakeBody.begin() + 1; itr != m_SnakeBody.end(); ++itr) {
		m_BodyRect.setPosition(itr->position.x * m_Size, itr->position.y * m_Size);
		i_window.draw(m_BodyRect);
	}
}
