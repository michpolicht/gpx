/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/BoxOffsetFrame.hpp"

namespace gpx {
namespace gui {

BoxOffsetFrame::BoxOffsetFrame(BoxOffset & offset):
		Parent(gpx::model::VertexData<2>(m_vertices, VERTEX_NUM)),
		m_offset(offset)
{
	for (std::size_t i = 0; i < VERTEX_NUM * DIM; i++)
		m_vertices[i] = 0.0;
	m_offset.addObserver(this);
}

BoxOffsetFrame::BoxOffsetFrame(BoxOffset & offset, real_t width, real_t height):
		Parent(gpx::model::VertexData<2>(m_vertices, VERTEX_NUM)),
		m_offset(offset)
{
	m_vertices[0] = 0.0; m_vertices[1] = 0.0;
	m_vertices[2] = width; m_vertices[3] = 0.0;
	m_vertices[4] = width; m_vertices[5] = height;
	m_vertices[6] = 0.0; m_vertices[7] = height;
	m_offset.addObserver(this);
}

BoxOffsetFrame::~BoxOffsetFrame()
{
	m_offset.removeObserver(this);
}

//BoxFrame::BoxFrame(real_t x, real_t y, real_t width, real_t height):
//		Parent(gpx::model::VertexData<2>(m_vertices, VERTEX_NUM))
//{
//	m_vertices[0] = x; m_vertices[1] = y;
//	m_vertices[2] = width; m_vertices[3] = y;
//	m_vertices[4] = width; m_vertices[5] = height;
//	m_vertices[6] = x; m_vertices[7] = height;
//}
//
//real_t BoxFrame::x() const
//{
//	return m_vertices[0];
//}
//
//void BoxFrame::setX(real_t x)
//{
//	m_vertices[0] = x;
//	m_vertices[6] = x;
//}
//
//real_t BoxFrame::y() const
//{
//	return m_vertices[1];
//}
//
//void BoxFrame::setY(real_t y)
//{
//	m_vertices[1] = y;
//	m_vertices[3] = y;
//}

void BoxOffsetFrame::setSize(real_t width, real_t height)
{
	setWidth(width);
	setHeight(height);
}

real_t BoxOffsetFrame::width() const
{
	return m_vertices[2];
}

void BoxOffsetFrame::setWidth(real_t width)
{
	m_vertices[2] = width;
	m_vertices[4] = width;
}

real_t BoxOffsetFrame::height() const
{
	return m_vertices[5];
}

void BoxOffsetFrame::setHeight(real_t height)
{
	m_vertices[5] = height;
	m_vertices[7] = height;
}

real_t * BoxOffsetFrame::vertices()
{
	return m_vertices;
}


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
