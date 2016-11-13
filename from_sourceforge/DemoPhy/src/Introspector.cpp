#include "Introspector.hpp"

namespace pmepp2_s {

Introspector::Introspector(gpx::gra::RenderWindow & win, gpx::gra2d::View & view):
	m_win(win),
	m_view(view),
	m_skipBreakpoints(false)
{
}

void Introspector::associate(const ICFixed * const fixed, Renderer * const renderer)
{
	m_assoc[fixed] = renderer;
}

void Introspector::toggleSkipBreakpoints()
{
	m_skipBreakpoints = !m_skipBreakpoints;
}

void Introspector::setSkipBreakpoints(bool skip)
{
	m_skipBreakpoints = skip;
}

void Introspector::breakpoint()
{
	if (!m_win.IsOpened())
		return;
	refreshDisplay();
	waitForUser();
}

void Introspector::highlight(const ICFixed & fixed)
{
	if (m_assoc.find(& fixed) == m_assoc.end()) {
		GPX_WARN("given object is not associated with renderer");
		return;
	}
	m_assoc.find(& fixed)->second->highlight();
}

void Introspector::playdown(const ICFixed & fixed)
{
	if (m_assoc.find(& fixed) == m_assoc.end()) {
		GPX_WARN("given object is not associated with renderer");
		return;
	}
	m_assoc.find(& fixed)->second->playdown();
}

void Introspector::off(const ICFixed & fixed)
{
	if (m_assoc.find(& fixed) == m_assoc.end()) {
		GPX_WARN("given object is not associated with renderer");
		return;
	}
	m_assoc.find(& fixed)->second->off();
}

void Introspector::light(const ICFixed & fixed)
{
	if (m_assoc.find(& fixed) == m_assoc.end()) {
		GPX_WARN("given object is not associated with renderer");
		return;
	}
	m_assoc.find(& fixed)->second->light();
}

void Introspector::refreshDisplay()
{
	//clear display
	glClear(GL_COLOR_BUFFER_BIT);
	m_view.update();
	m_win.display();
}

void Introspector::waitForUser()
{
	sf::Event event;
	while (!m_skipBreakpoints) {
		Sleep(0.1);
		m_win.fetchEvent(event);
		if (event.Type == sf::Event::Closed)
			setSkipBreakpoints(true);
		if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
			setSkipBreakpoints(true);
		if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::I))
			setSkipBreakpoints(true);
		if (event.Type == sf::Event::KeyPressed)
			break;
	}
}

}
