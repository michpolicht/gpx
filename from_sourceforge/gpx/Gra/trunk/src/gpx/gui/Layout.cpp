/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/Layout.hpp"

namespace gpx {
namespace gui {

Layout::Properties::Layout::Layout():
		spacing(INITIAL_SPACING),
		padding(INITIAL_PADDING),
		halign(INITIAL_HALIGN),
		valign(INITIAL_VALIGN)
{
}

Layout::Properties::Properties(const Parent::Properties & prop):
		Parent::Properties(prop)
{
	widthPolicy = INITIAL_WIDTH_POLICY;
	heightPolicy = INITIAL_HEIGHT_POLICY;
}




Layout::Layout(WidgetRenderer * renderer, const Properties & defaults):
		Parent(renderer, defaults),
		m_props(defaults.layout),
		m_repacking(false)
{
}

Layout::~Layout()
{
}

Layout::Properties & Layout::Defaults()
{
	static Properties Defaults(Parent::Defaults());
	return Defaults;
}

BoxOffset & Layout::spacing()
{
	return m_props.spacing;
}

const BoxOffset & Layout::spacing() const
{
	return m_props.spacing;
}

BoxOffset & Layout::padding()
{
	return m_props.padding;
}

const BoxOffset & Layout::padding() const
{
	return m_props.padding;
}

Layout::halign_t Layout::halign() const
{
	return m_props.halign;
}

void Layout::setHalign(halign_t halign)
{
	m_props.halign = halign;
}

Layout::valign_t Layout::valign() const
{
	return m_props.valign;
}

void Layout::setValign(valign_t valign)
{
	m_props.valign = valign;
}


void Layout::add(Widget * widget)
{
	Parent::add(widget);
	m_repacking = true;
	GPX_DEBUG(this << ": calling repack on add widget");
	repack();
	m_repacking = false;
}

void Layout::remove(Widget * widget)
{
	Parent::remove(widget);
	m_repacking = true;
	repack();
	m_repacking = false;
}

void Layout::event(const utils::Observable<BoxOffset>::Event & )
{
	m_repacking = true;
	repack();
	m_repacking = false;
}

void Layout::event(const Widget::Event<StateEvent> & e)
{
	Parent::event(e);
	if (!m_repacking)
		if (e.state() == StateEvent::TOTAL_SIZE_CHANGED) {
			m_repacking = true;
			GPX_DEBUG(this << ": calling repack on resize event");
			repack();
			m_repacking = false;
		}
}

void Layout::event(const Widget::Event<ChildEvent> & e)
{
	Parent::event(e);
	if (!m_repacking)
		if (e.state() == StateEvent::TOTAL_SIZE_CHANGED) {
			m_repacking = true;
			GPX_DEBUG(this << ": calling repack on child resize event");
			repack();
			m_repacking = false;
		}
}


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
