/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/DFlowLayout.hpp"

namespace gpx {
namespace gui {

DFlowLayout::DFlowLayout(const Properties & defaults):
		Parent(& m_renderer, defaults),
		m_renderer(this),
		m_componentsTotalWidth(0.0),
		m_componentsTotalHeight(0.0),
		m_componentsMaxWidth(0.0),
		m_componentsMaxHeight(0.0)
{
}

DFlowLayout::~DFlowLayout()
{
}

void DFlowLayout::add(Widget * widget)
{
	m_componentsTotalWidth += widget->totalWidth() + spacing().horizontal();
	m_componentsTotalHeight += widget->totalHeight() + spacing().vertical();
	m_componentsMaxWidth = std::max(m_componentsMaxWidth, widget->totalWidth());
	m_componentsMaxHeight = std::max(m_componentsMaxHeight, widget->totalHeight());
	Parent::add(widget);
}

void DFlowLayout::remove(Widget * widget)
{
	m_componentsTotalWidth -= widget->totalWidth() + spacing().horizontal();
	m_componentsTotalHeight -= widget->totalHeight() + spacing().vertical();
	Parent::remove(widget);
	if (m_componentsMaxWidth == widget->totalWidth()) {
		m_componentsMaxWidth = 0.0;
		for (WidgetsContainer::iterator wi = widgets().begin(); wi != widgets().end(); ++wi)
			m_componentsMaxWidth = std::max(m_componentsMaxWidth, (*wi)->totalWidth());
	}
	if (m_componentsMaxHeight == widget->totalHeight()) {
		m_componentsMaxHeight = 0.0;
		for (WidgetsContainer::iterator wi = widgets().begin(); wi != widgets().end(); ++wi)
			m_componentsMaxHeight = std::max(m_componentsMaxHeight, (*wi)->totalHeight());
	}
}

real_t DFlowLayout::componentsTotalWidth() const
{
	return m_componentsTotalWidth;
}

real_t DFlowLayout::componentsTotalHeight() const
{
	return m_componentsTotalHeight;
}

real_t DFlowLayout::componentsMaxWidth() const
{
	return m_componentsMaxWidth;
}

real_t DFlowLayout::componentsMaxHeight() const
{
	return m_componentsMaxHeight;
}

void DFlowLayout::event(const Widget::Event<ChildEvent> & e)
{
	if (e.state() == StateEvent::TOTAL_SIZE_CHANGED)
		componentsParamRecalc();
	Parent::event(e);
}

void DFlowLayout::componentsParamRecalc()
{
	m_componentsMaxWidth = 0.0;
	m_componentsMaxHeight = 0.0;
	m_componentsTotalWidth = 0.0;
	m_componentsTotalHeight = 0.0;
	for (WidgetsContainer::const_iterator wi = widgets().begin(); wi != widgets().end(); ++wi) {
		m_componentsMaxWidth = std::max(m_componentsMaxWidth, (*wi)->totalWidth());
		m_componentsMaxHeight = std::max(m_componentsMaxHeight, (*wi)->totalHeight());
		m_componentsTotalWidth += (*wi)->totalWidth() + spacing().horizontal();
		m_componentsTotalHeight += (*wi)->totalHeight() + spacing().vertical();
	}
}


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
