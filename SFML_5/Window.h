#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class Window
{
public:
	Window();
	Window(const std::string& i_title, const sf::Vector2u& i_size);
	~Window();

	void BeginDraw();
	void EndDraw();
	void Update();

	bool IsDone();
	bool IsFullScreen();
	sf::Vector2u GetWindowSize();

	void ToggleFullScreen();
	void Draw(sf::Drawable& i_drawable);
	sf::RenderWindow& GetRenderWindow();
private:
	void Setup(const std::string& i_title, const sf::Vector2u& i_size);
	void Destroy();
	void Create();
	
	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone = false;
	bool m_isFullScreen;
};

