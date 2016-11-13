/**
 * @file
 * @brief .
 */


#include "../../../include/gpx/gra2d/PointRenderer.hpp"


namespace gpx {
namespace gra2d {


real_t PointRenderer::DotSize = INITIAL_DOT_SIZE;
real_t PointRenderer::CrossSize = INITIAL_CROSS_SIZE;
const utils::Array<4> PointRenderer::INITIAL_COLOR = {{0.0, 0.0, 0.0, 0.0}};


PointRenderer::PointRenderer(const real_t point[2], PointRenderer::Style style):
	m_point(point),
	m_style(style),
	m_color(INITIAL_COLOR)
{
}

PointRenderer::~PointRenderer()
{
}

const real_t * PointRenderer::point() const
{
	return m_point;
}

void PointRenderer::setPoint(const real_t point[2])
{
	this->m_point = point;
}

void PointRenderer::setColor(const utils::Array<4> & color)
{
	this->m_color = color;
}

const utils::Array<4> & PointRenderer::color() const
{
	return m_color;
}

PointRenderer::Style PointRenderer::style() const
{
	return m_style;
}

void PointRenderer::setStyle(PointRenderer::Style style)
{
	this->m_style = style;
}

void PointRenderer::render(RenderContext * context)
{
	assert(m_point != 0);

	glColor4v(m_color.ptr());
	switch (m_style) {
		case Dot:
			glPointSize(DotSize * context->currentView()->svHeightRatio());
			glBegin(GL_POINTS);
				glVertex2v(m_point);
			glEnd();
			break;
		case Cross:
			glBegin(GL_LINES); {
				real_t crossSize = CrossSize * context->currentView()->svHeightRatio();
				glVertex2(m_point[0] - crossSize, m_point[1] - crossSize);
				glVertex2(m_point[0] + crossSize, m_point[1] + crossSize);
				glVertex2(m_point[0] - crossSize, m_point[1] + crossSize);
				glVertex2(m_point[0] + crossSize, m_point[1] - crossSize);
			} glEnd();
			break;
		default:
			break;
	}
}

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
