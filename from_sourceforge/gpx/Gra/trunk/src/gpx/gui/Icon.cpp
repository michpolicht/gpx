/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/Icon.hpp"

namespace gpx {
namespace gui {

Icon::Properties::Properties(const Widget::Properties & widgetProp, const WidgetRenderer::Properties & rendererProp):
		Widget::Properties(widgetProp),
		WidgetRenderer::Properties(rendererProp)
{
	workareaStyle = INITIAL_WORKAREA_STYLE;
}

Icon::Icon(const Image * image, const Properties & defaults):
		Widget(this, defaults),
		WidgetRenderer(this, defaults),
		m_image(image),
		m_tex(1.0, -1.0)
{
	setSize(image->GetWidth(), image->GetHeight()); //initial size of an icon
	//m_image.SetSmooth()?
}

Icon::~Icon()
{
}

const Image * Icon::image() const
{
	return m_image;
}

void Icon::setImage(const Image * image)
{
	m_image = image;
	setSize(image->GetWidth(), image->GetHeight());
}

Icon::Properties & Icon::Defaults()
{
	static Properties Defaults(Widget::Defaults(), WidgetRenderer::Defaults());
	return Defaults;
}

void Icon::render(gra2d::RenderContext * context)
{
	WidgetRenderer::render(context);

	glPushAttrib(GL_TEXTURE_BIT);
	glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
	m_image->Bind();
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glVertexPointer(rect().vdata().dim(), 0, rect().vdata().data());
	glTexCoordPointer(tex().vdata().dim(), 0, tex().vdata().data());
	glDrawArrays(GL_QUADS, 0, rect().vdata().num());

	glPopClientAttrib();
	glPopAttrib();
}

const Rect & Icon::tex() const
{
	return m_tex;
}



}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
