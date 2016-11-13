/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GUI_DISPATCHER_HPP_
#define GPX_Gra_GUI_DISPATCHER_HPP_

#include <list>

#include <SFML/Window/Event.hpp>

#include "IEventListener.hpp"
#include "../gra/RenderWindow.hpp"

namespace gpx {
namespace gui {

/**
 * Dispatcher. Dispatcher retrieves SFML-specific events from gra::RenderWindow, translates
 * them into GUI-specific ones and then asks listeners to process them.
 */
class GPX_API Dispatcher
{
	public:
		Dispatcher(gra::RenderWindow & renderWindow);

		virtual ~Dispatcher();

	public:
		/**
		 * Get render window.
		 * @return associated render window.
		 */
		gra::RenderWindow & renderWindow();

		/**
		 * Get render window (const version).
		 * @return associated render window.
		 */
		const gra::RenderWindow & renderWindow() const;

		/**
		 * Add event listener.
		 * @param listener event listener.
		 */
		void add(IEventListener * listener);

		/**
		 * Remove event listener.
		 * @param listener event listener.
		 */
		void remove(IEventListener * listener);

		/**
		 * Process event.
		 * @param e event to process.
		 */
		void event(const sf::Event & e);

		/**
		 * Fetch and process event from render window queue.
		 * @return @p true when event was successfully processed, @p false when there are
		 * no more events in queue.
		 */
		bool processEvent();

		/**
		 * Get processed event.
		 * @return last event being processed.
		 */
		sf::Event & processedEvent();

		/**
		 * Process events. Causes dispatcher to process all events waiting in the queue.
		 * This is fast option, if default behavior is sufficient. The alternate way is
		 * to process events one by one, using processEvent() and processedEvent()
		 * functions.
		 */
		void processEvents();

	protected:
		typedef std::list<IEventListener *> EventListenersContainer;

	protected:
		static TriggerEvent::type_t MapSfMouseButton(const sf::Mouse::Button & button);

	protected:
		EventListenersContainer & eventListeners();

		const EventListenersContainer & eventListeners() const;

	private:
		template<class EVENT>
		void propagateEvent(const EVENT & e);

		int flipY(int y);

	private:
		sf::Event m_event;
		EventListenersContainer m_eventListeners;
		gra::RenderWindow & m_renderWindow;

};



template<class EVENT>
inline
void Dispatcher::propagateEvent(const EVENT & e)
{
	for (EventListenersContainer::iterator listener = m_eventListeners.begin(); listener != m_eventListeners.end(); ++listener)
		(*listener)->event(e);
}

inline
int Dispatcher::flipY(int y)
{
	return m_renderWindow.GetHeight() - y;
}



}
}

#endif /* GPX_Gra_GUI_DISPATCHER_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
