/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/Screen.hpp"
#include "../../../include/gpx/gui/Widget.hpp"

namespace gpx {
namespace gui {

private_ScreenAllocator::private_ScreenAllocator(Dispatcher & dispatcher):
		m_scene(dispatcher.renderWindow().viewport().width(), dispatcher.renderWindow().viewport().height()),
		m_view(dispatcher.renderWindow(), m_scene)
{
}



Screen::Screen(Dispatcher & dispatcher):
		private_ScreenAllocator(dispatcher),
		Parent(dispatcher, private_ScreenAllocator::m_view)
{
	dispatcher.renderWindow().viewport().addObserver(this);
}

Screen::~Screen()
{
	dispatcher().renderWindow().viewport().removeObserver(this);
	for (WidgetsContainer::const_iterator widget = widgets().begin(); widget != widgets().end(); ++widget)
		m_scene.remove((*widget)->renderer());
}

void Screen::add(Widget * widget)
{
	Parent::add(widget);
	widget->setPos(0.0, m_scene.height());
	widget->setSize(m_scene.width(), m_scene.height(), gui::Widget::PARENT_SIZE);
	m_scene.add(widget->renderer());
}

void Screen::remove(Widget * widget)
{
	Parent::remove(widget);
	m_scene.remove(widget->renderer());
}

void Screen::update()
{
	view().update();
}

void Screen::event(const utils::Observable<gra::Viewport>::Event & e)
{
	const gra::Viewport * viewport = e.observable();
	m_scene.clip().setSize(viewport->width(), viewport->height());
	for (WidgetsContainer::const_iterator widget = widgets().begin(); widget != widgets().end(); ++widget) {
		(*widget)->setPos(0.0, m_scene.height());
		(*widget)->setSize(m_scene.width(), m_scene.height(), gui::Widget::PARENT_SIZE);
	}
}

gra2d::View & Screen::view()
{
	return private_ScreenAllocator::m_view;
}

gra2d::Scene & Screen::scene()
{
	return m_scene;
}

const gra2d::Scene & Screen::scene() const
{
	return m_scene;
}


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
