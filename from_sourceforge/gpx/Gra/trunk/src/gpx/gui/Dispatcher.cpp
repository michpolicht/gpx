/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/Dispatcher.hpp"

namespace gpx {
namespace gui {

Dispatcher::Dispatcher(gra::RenderWindow & renderWindow):
		m_renderWindow(renderWindow)
{
}

Dispatcher::~Dispatcher()
{
}

gra::RenderWindow & Dispatcher::renderWindow()
{
	return m_renderWindow;
}

const gra::RenderWindow & Dispatcher::renderWindow() const
{
	return m_renderWindow;
}

void Dispatcher::add(IEventListener * listener)
{
#ifndef NDEBUG
	if (std::find(m_eventListeners.begin(), m_eventListeners.end(), listener) != m_eventListeners.end())
		GPX_WARN("adding listener which already exists");
#endif /* NDEBUG */
	m_eventListeners.push_back(listener);
}

void Dispatcher::remove(IEventListener * listener)
{
#ifndef NDEBUG
	if (std::find(m_eventListeners.begin(), m_eventListeners.end(), listener) == m_eventListeners.end())
		GPX_WARN("attempting to remove listener which doesn't exist");
#endif /* NDEBUG */
	m_eventListeners.remove(listener);
}

void Dispatcher::event(const sf::Event & e)
{
	switch (e.Type) {
		case sf::Event::MouseMoved:
			propagateEvent(CursorEvent(CursorEvent::MOVE, e.MouseMove.X, flipY(e.MouseMove.Y)));
			break;
		case sf::Event::MouseButtonPressed:
			propagateEvent(TriggerEvent(TriggerEvent::PRESS, MapSfMouseButton(e.MouseButton.Button), e.MouseButton.X, flipY(e.MouseButton.Y)));
			break;
		case sf::Event::MouseButtonReleased:
			propagateEvent(TriggerEvent(TriggerEvent::RELEASE, MapSfMouseButton(e.MouseButton.Button), e.MouseButton.X, flipY(e.MouseButton.Y)));
			break;
		default:
			break;
	}
}

bool Dispatcher::processEvent()
{
	if (m_renderWindow.fetchEvent(m_event)) {
		event(m_event);
		return true;
	}
	return false;
}

sf::Event & Dispatcher::processedEvent()
{
	return m_event;
}

void Dispatcher::processEvents()
{
	while (processEvent()) {};
}




TriggerEvent::type_t Dispatcher::MapSfMouseButton(const sf::Mouse::Button & button)
{
	switch (button) {
		case sf::Mouse::Left:
			return TriggerEvent::PRIMARY;
		case sf::Mouse::Right:
			return TriggerEvent::SECONDARY;
		case sf::Mouse::Middle:
			return TriggerEvent::TERTIARY;
		case sf::Mouse::XButton1:
			return TriggerEvent::QUATERNARY;
		case sf::Mouse::XButton2:
			return TriggerEvent::QUINARY;
		default:
			return button + TriggerEvent::DENARY;
	}
}

Dispatcher::EventListenersContainer & Dispatcher::eventListeners()
{
	return m_eventListeners;
}

const Dispatcher::EventListenersContainer & Dispatcher::eventListeners() const
{
	return m_eventListeners;
}


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
