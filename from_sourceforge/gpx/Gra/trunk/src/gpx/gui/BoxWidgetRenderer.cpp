/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/BoxWidgetRenderer.hpp"

#include "../../../include/gpx/gui/BoxWidget.hpp"

namespace gpx {
namespace gui {

const gra::Color BoxWidgetRenderer::INITIAL_BORDER_COLOR(0.7, 0.7, 0.7, 1.0);

BoxWidgetRenderer::BoxWidgetRenderer(BoxWidget * widget):
		Parent(widget),
		m_widget(widget),
		m_borderColor(INITIAL_BORDER_COLOR)
{
	setBorderStyle(INITIAL_BORDER_STYLE);
}

BoxWidgetRenderer::~BoxWidgetRenderer()
{
}


const gra::Color & BoxWidgetRenderer::borderColor() const
{
	return m_borderColor;
}

gra::Color & BoxWidgetRenderer::borderColor()
{
	return m_borderColor;
}

BoxWidgetRenderer::borderStyle_t BoxWidgetRenderer::borderStyle() const
{
	return m_borderStyle;
}

void BoxWidgetRenderer::setBorderStyle(borderStyle_t borderStyle)
{
	m_borderStyle = borderStyle;
	switch (borderStyle) {
		case BORDER_SOLID:
			m_borderPainter = & M_SolidBorderPainter;
			break;
		case BORDER_NONE:
			m_borderPainter = & M_NoneBorderPainter;
			break;
		default:
			m_borderPainter = & M_SolidBorderPainter;
			GPX_WARN("unrecognized border style parameter: " << borderStyle);
	}
}

void BoxWidgetRenderer::render(gra2d::RenderContext * context)
{
	Parent::render(context);
	m_borderColor.glSetRgb();
	m_borderPainter->render(m_widget, context);
	if (workareaStyle() == WORKAREA_OPAQUE) {
		workareaColor().glSetRgb();
		gpx::glVertexPointer(Rect::DIM, 0, m_widget->rect().vdata().data());
		glDrawArrays(GL_QUADS, 0, m_widget->rect().vdata().num());
	}
}



void BoxWidgetRenderer::NoneBorderPainter::render(BoxWidget * , gra2d::RenderContext * )
{
}

void BoxWidgetRenderer::SolidBorderPainter::render(BoxWidget * widget, gra2d::RenderContext * context)
{
	context->pushMatrix();
		gpx::glVertexPointer(Rect::DIM, 0, m_box.vdata().data());
		//left
		m_box.setHeight(widget->height() + widget->offset().vertical());
		m_box.setWidth(widget->border().left());
//		m_box.setX(-widget->offset().left());
//		m_box.setY(-widget->offset().top());
//		glTranslate(-widget->offset().left(), widget->border().bottom(), 0.0);
		glDrawArrays(GL_QUADS, 0, m_box.vdata().num());
//		//right
//		m_box.setWidth(widget->border().right());
//		glTranslate(widget->width() + widget->offset().left(), 0.0, 0.0);
//		glDrawArrays(GL_QUADS, 0, m_box.vdata().num());
//		//top
//		m_box.setWidth(widget->width() + widget->padding().horizontal());
//		m_box.setHeight(widget->border().top());
//		glTranslate(-widget->width() - widget->offset().left(), -widget->padding().top(), 0.0);
//		glDrawArrays(GL_QUADS, 0, m_box.vdata().num());
//		//bottom
//		m_box.setHeight(widget->border().bottom());
//		glTranslate(0.0, widget->height() + widget->offset().top(), 0.0);
//		glDrawArrays(GL_QUADS, 0, m_box.vdata().num());
	context->popMatrix();
}


BoxWidgetRenderer::SolidBorderPainter BoxWidgetRenderer::M_SolidBorderPainter;
BoxWidgetRenderer::NoneBorderPainter BoxWidgetRenderer::M_NoneBorderPainter;


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
