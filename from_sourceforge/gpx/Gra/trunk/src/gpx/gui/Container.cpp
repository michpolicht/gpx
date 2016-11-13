/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/Container.hpp"

namespace gpx {
namespace gui {

Container::Container(WidgetRenderer * renderer, const Properties & defaults):
		Parent(renderer, defaults)
{
}

Container::~Container()
{
	for (Container::WidgetsContainer::iterator wi = widgets().begin(); wi != widgets().end(); ++wi)
		(*wi)->setParent(0);
}

Container::Properties & Container::Defaults()
{
	static Properties Defaults(Parent::Defaults());
	return Defaults;
}

const Container::WidgetsContainer & Container::widgets() const
{
	return m_widgets;
}

void Container::add(Widget * widget)
{
	m_widgets.push_back(widget);
	widget->setParent(this);
}

void Container::remove(Widget * widget)
{
	m_widgets.remove(widget);
	widget->setParent(0);
}

Container::WidgetsContainer & Container::widgets()
{
	return m_widgets;
}

void Container::event(const Widget::Event<CursorEvent> & e)
{
	Parent::event(e);
	math::Point<2> pos(mapToLocal(math::Point<2>(e.x(), e.y())));
	for (Container::WidgetsContainer::iterator wi = widgets().begin(); wi != widgets().end(); ++wi)
		(*wi)->event(CursorEvent(e.action(), pos));
}

void Container::event(const Widget::Event<TriggerEvent> & e)
{
	Parent::event(e);
	math::Point<2> pos(mapToLocal(math::Point<2>(e.x(), e.y())));
	for (Container::WidgetsContainer::iterator wi = widgets().begin(); wi != widgets().end(); ++wi)
		(*wi)->event(TriggerEvent(e.action(), e.type(), pos));
}

void Container::event(const Widget::Event<ScrollEvent> & e)
{
	Parent::event(e);
	for (Container::WidgetsContainer::iterator wi = widgets().begin(); wi != widgets().end(); ++wi)
		(*wi)->event(static_cast<ScrollEvent>(e));
}

void Container::event(const Widget::Event<StateEvent> & e)
{
	Parent::event(e);
	switch (e.state()) {
		case StateEvent::FOCUS_LOST:
			for (Container::WidgetsContainer::iterator wi = widgets().begin(); wi != widgets().end(); ++wi)
				(*wi)->setFocus(false);
			break;
		case StateEvent::PARENT_CHANGED:
			for (Container::WidgetsContainer::iterator wi = widgets().begin(); wi != widgets().end(); ++wi)
				(*wi)->inheritPolicies(this);	//opportunity to inherit new properties by childs
			break;
		case StateEvent::SIZE_POLICY_CHANGED:
			for (Container::WidgetsContainer::iterator wi = widgets().begin(); wi != widgets().end(); ++wi)
				(*wi)->inheritPolicies(this);	//opportunity to inherit new properties by childs
			break;
		case StateEvent::FOCUS_POLICY_CHANGED:
			for (Container::WidgetsContainer::iterator wi = widgets().begin(); wi != widgets().end(); ++wi)
				(*wi)->inheritPolicies(this);	//opportunity to inherit new properties by childs
			break;
		default:
			break;
	}
}

void Container::event(const Widget::Event<ChildEvent> & )
{
}


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
