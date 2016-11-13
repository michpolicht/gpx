/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/WidgetRenderer.hpp"
#include "../../../include/gpx/gui/Widget.hpp"
#include <gpx/log/Log.hpp>

namespace gpx {
namespace gui {

const gra::Color WidgetRenderer::Properties::INITIAL_WORKAREA_COLOR(0.8, 0.8, 0.8, 1.0);

WidgetRenderer::Properties::Properties():
			workareaStyle(INITIAL_WORKAREA_STYLE),
			workareaColor(INITIAL_WORKAREA_COLOR)
{
}




WidgetRenderer::WidgetRenderer(const Widget * widget, const Properties & defaults):
	Parent(widget),
	m_widget(widget),
	m_props(defaults)
{
}

WidgetRenderer::~WidgetRenderer()
{
}

WidgetRenderer::Properties & WidgetRenderer::Defaults()
{
	static Properties Defaults;
	return Defaults;
}


const Widget * WidgetRenderer::widget() const
{
	return m_widget;
}

WidgetRenderer::workareaStyle_t WidgetRenderer::workareaStyle() const
{
	return m_props.workareaStyle;
}

void WidgetRenderer::setWorkareaStyle(workareaStyle_t workareaStyle)
{
	m_props.workareaStyle = workareaStyle;
}

const gra::Color & WidgetRenderer::workareaColor() const
{
	return m_props.workareaColor;
}

gra::Color & WidgetRenderer::workareaColor()
{
	return m_props.workareaColor;
}

void WidgetRenderer::render(gra2d::RenderContext * context)
{
	Parent::render(context);
	if (workareaStyle() == WORKAREA_OPAQUE) {
		workareaColor().glSetRgb();
		gpx::glVertexPointer(Rect::DIM, 0, widget()->rect().vdata().data());
		glDrawArrays(GL_QUADS, 0, widget()->rect().vdata().num());
	} else if (workareaStyle() == WORKAREA_FRAME) {
		workareaColor().glSetRgb();
		gpx::glVertexPointer(Rect::DIM, 0, widget()->rect().vdata().data());
		glDrawArrays(GL_LINE_LOOP, 0, widget()->rect().vdata().num());
	}
}


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
