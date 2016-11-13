/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/Button.hpp"

namespace gpx {
namespace gui {


Button::Properties::Button::Button():
		rebound(INITIAL_REBOUND)
{
}

Button::Properties::Properties(const Parent::Properties & prop):
		Parent::Properties(prop)
{
}



Button::Button(WidgetRenderer * renderer, const Properties & defaults):
		Parent(renderer, defaults),
		m_buttonProps(defaults.button),
		m_excited(INITIAL_EXCITED),
		m_pressed(INITIAL_PRESSED),
		m_active(INITIAL_ACTIVE)
{
}

Button::~Button()
{
}

Button::Properties & Button::Defaults()
{
	static Button::Properties Defaults(Parent::Defaults());
	return Defaults;
}

bool Button::excited() const
{
	return m_excited;
}

void Button::setExcited(bool excited)
{
	m_excited = excited;
	if (excited)
		notifyObservers(EXCITED);
	else
		notifyObservers(UNEXCITED);
}

bool Button::active() const
{
	return m_active;
}

void Button::setActive(bool active)
{
	m_active = active;
	if (active)
		notifyObservers(ACTIVATED);
	else
		notifyObservers(DEACTIVATED);
}

bool Button::pressed() const
{
	return m_pressed;
}

void Button::setPressed(bool pressed)
{
	m_pressed = pressed;
	if (pressed)
		notifyObservers(PRESSED);
	else
		notifyObservers(RELEASED);
}

bool Button::rebound() const
{
	return m_buttonProps.rebound;
}

void Button::setRebound(bool rebound)
{
	m_buttonProps.rebound = rebound;
}

void Button::toggle()
{
	setActive(!active());
	if (rebound())
		setActive(!active());
//	else
//		setPressed(!pressed());
}

void Button::event(const Widget::Event<StateEvent> & e)
{
	Parent::event(e);
	switch (e.state()) {
		case StateEvent::ACTIVE_AREA_CHANGED:
			if (e.area() != Widget::OUTER_AREA)
				setExcited(true);
			else
				setExcited(false);
			break;
		default:
			break;
	}
}

void Button::event(const Widget::Event<TriggerEvent> & e)
{
	Parent::event(e);
	if (e.type() == TriggerEvent::PRIMARY) {
		if (e.action() == TriggerEvent::PRESS) {
			//toggle pressed
			setPressed(!pressed());
		}
		if ((e.action() == TriggerEvent::RELEASE) && excited()) {
			toggle();
			if (rebound())
				setPressed(!pressed());
		}
	}
}

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
