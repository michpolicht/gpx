/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/Screen.hpp"
#include "../../../include/gpx/gui/Widget.hpp"

namespace gpx {
namespace gui {

ViewDispatcher::ViewDispatcher(Dispatcher & dispatcher, const gra2d::View & view):
		m_dispatcher(dispatcher),
		m_view(view)
{
	m_dispatcher.add(this);
}

ViewDispatcher::~ViewDispatcher()
{
	m_dispatcher.remove(this);
}

void ViewDispatcher::add(Widget * widget)
{
	m_widgets.push_back(widget);
}

void ViewDispatcher::remove(Widget * widget)
{
	m_widgets.remove(widget);
}

void ViewDispatcher::event(const CursorEvent & e)
{
	math::Point<2> pos = view().mapToScene(e.x(), e.y());
	propagateEvent(CursorEvent(e.action(), pos[0], pos[1]));
}

void ViewDispatcher::event(const TriggerEvent & e)
{
	math::Point<2> pos = view().mapToScene(e.x(), e.y());
	propagateEvent(TriggerEvent(e.action(), e.type(), pos[0], pos[1]));
}

void ViewDispatcher::event(const ScrollEvent & e)
{
	propagateEvent(e);
}

const Dispatcher & ViewDispatcher::dispatcher() const
{
	return m_dispatcher;
}

Dispatcher & ViewDispatcher::dispatcher()
{
	return m_dispatcher;
}

const ViewDispatcher::WidgetsContainer & ViewDispatcher::widgets() const
{
	return m_widgets;
}

const gra2d::View & ViewDispatcher::view() const
{
	return m_view;
}

template<class EVENT>
inline
void ViewDispatcher::propagateEvent(const EVENT & e)
{
	for (WidgetsContainer::iterator widget = m_widgets.begin(); widget != m_widgets.end(); ++widget)
		(*widget)->event(e);
}


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
