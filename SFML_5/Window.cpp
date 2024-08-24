#include "Window.h"

Window::Window() {
	Setup("Window",sf::Vector2u(640, 480));
}

Window::Window(const std::string& i_title, const sf::Vector2u& i_size) {
	Setup(i_title, i_size);
}

Window::~Window() { Destroy(); }

void Window::Setup(const std::string& i_title, const sf::Vector2u& i_size) {
	m_windowTitle = i_title;
	m_windowSize = i_size;
	m_isDone = false;
	m_isFullScreen = false;
	Create();
}
void Window::Create() {
	auto style = (m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
}
void Window::Destroy() {
	m_window.close();
}
void Window::Update() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_isDone = true;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
			ToggleFullScreen();
		}
	}
}

sf::RenderWindow& Window::GetRenderWindow() {
	return m_window;
}
void Window::ToggleFullScreen() {
	m_isFullScreen = !m_isFullScreen;
	Destroy();
	Create();
}
void Window::BeginDraw() { m_window.clear(sf::Color::Black); }
void Window::EndDraw() { m_window.display(); }
bool Window::IsDone() { return m_isDone; }
bool Window::IsFullScreen() { return m_isFullScreen; }
sf::Vector2u Window::GetWindowSize() { return m_windowSize; }

void Window::Draw(sf::Drawable& i_drawable) {
	m_window.draw(i_drawable);
}
