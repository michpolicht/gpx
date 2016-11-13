/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gra2d/VectorRenderer.hpp"

namespace gpx {
namespace gra2d {

const utils::Array<4> VectorRenderer::INITIAL_COLOR = {0.0, 0.0, 0.0, 0.0};

VectorRenderer::VectorRenderer(const real_t point[2], const real_t vector[2]):
	m_initial(point),
	m_vector(vector),
	m_color(INITIAL_COLOR),
	m_frontArrow(true)
{
}

VectorRenderer::~VectorRenderer()
{
}

const real_t * VectorRenderer::vector() const
{
	return m_vector;
}

void VectorRenderer::setVector(const real_t vector[2])
{
	this->m_vector = vector;
}

const real_t * VectorRenderer::initial() const
{
	return m_initial;
}

void VectorRenderer::setInitial(const real_t initial[2])
{
	this->m_initial = initial;
}

void VectorRenderer::setColor(const utils::Array<4> & color)
{
	this->m_color = color;
}

const utils::Array<4> & VectorRenderer::color() const
{
	return m_color;
}

void VectorRenderer::setFrontArrow(bool enable)
{
	m_frontArrow = enable;
}

bool VectorRenderer::frontArrow() const
{
	return m_frontArrow;
}

void VectorRenderer::render(RenderContext * context)
{
	assert(this->m_initial != 0);
	assert(this->m_vector != 0);

	math::const_VectorRef<2> initial(this->m_initial);
	math::const_VectorRef<2> vector(this->m_vector);

	glColor4v(m_color.ptr());

	glBegin(GL_LINES);
		glVertex2v(initial.ptr());
		glVertex2v((vector + initial).ptr());
	glEnd();

	if (m_frontArrow && !vector.isZero()) {
		math::Vector<2> versor = vector.versor();
		versor.mul(INITIAL_ARROW_SIZE * context->currentView()->svHeightRatio());
		glBegin(GL_TRIANGLES);
			glVertex2v((vector + initial).ptr());
			glVertex2v((vector + initial - versor.rotate(INITIAL_ARROW_ANGLE)).ptr());
			glVertex2v((vector + initial - versor.rotate(-2.0 * INITIAL_ARROW_ANGLE)).ptr());
		glEnd();
	}
}

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
