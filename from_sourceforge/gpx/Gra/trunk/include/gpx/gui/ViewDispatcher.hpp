/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GUI_VIEWDISPATCHER_HPP_
#define GPX_Gra_GUI_VIEWDISPATCHER_HPP_

#include "Dispatcher.hpp"
#include "../gra2d/View.hpp"

namespace gpx {
namespace gui {

class Widget;

/**
 * View dispatcher. Delivers events to widgets with respect to view in which they are
 * registered.
 */
class GPX_API ViewDispatcher : public virtual IEventListener
{
	public:
		/**
		 * Constructor. During construction instance of this class will be added to the
		 * dispatcher.
		 * @param dispatcher dispatcher.
		 * @param view view.
		 */
		ViewDispatcher(Dispatcher & dispatcher, const gra2d::View & view);

		/**
		 * Destructor. Instance of this class will be removed from the dispatcher during
		 * destruction.
		 */
		virtual ~ViewDispatcher();

	public:
		/**
		 * Add widget.
		 * @param widget widget to be added.
		 */
		void add(Widget * widget);

		/**
		 * Remove widget.
		 * @param widget widget to remove.
		 */
		void remove(Widget * widget);

		virtual void event(const CursorEvent & e);

		virtual void event(const TriggerEvent & e);

		virtual void event(const ScrollEvent & e);

		const Dispatcher & dispatcher() const;

		Dispatcher & dispatcher();

	protected:
		typedef std::list<Widget *> WidgetsContainer;

	protected:
		const WidgetsContainer & widgets() const;

		const gra2d::View & view() const;

	private:
		template<class EVENT>
		void propagateEvent(const EVENT & e);

	private:
		Dispatcher & m_dispatcher;
		const gra2d::View & m_view;
		sf::Event m_event;
		WidgetsContainer m_widgets;
};



}
}

#endif /* GPX_Gra_GUI_VIEWDISPATCHER_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
