/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gra2d/GraphicsObject.hpp"

namespace gpx {
namespace gra2d {

GraphicsObject::GraphicsObject():
	m_pos(m_tMatrix.column(3).ptr())
{
}

math::const_PointRef<2> GraphicsObject::pos() const
{
	return m_pos;
}

void GraphicsObject::setPos(math::const_PointRef<2> pos)
{
	m_pos = pos;
	m_tMatrixInv(0, 3) = -m_tMatrix(0, 3);
	m_tMatrixInv(1, 3) = -m_tMatrix(1, 3);
}

void GraphicsObject::setPos(real_t x, real_t y)
{
	setPos(math::Point<2>(x, y));
}

real_t GraphicsObject::x() const
{
	return m_pos[0];
}

void GraphicsObject::setX(real_t x)
{
	setPos(math::Point<2>(x, y()));
}

real_t GraphicsObject::y() const
{
	return m_pos[1];
}

void GraphicsObject::setY(real_t y)
{
	setPos(math::Point<2>(x(), y));
}

const gra::TransformationMatrix & GraphicsObject::tMatrix() const
{
	return m_tMatrix;
}

const gra::TransformationMatrix & GraphicsObject::tMatrixInv() const
{
	return m_tMatrixInv;
}

math::Point<2> GraphicsObject::mapToLocal(math::const_PointRef<2> point) const
{
	return m_tMatrixInv.prod(point);
}

math::Point<2> GraphicsObject::mapToGlobal(math::const_PointRef<2> point) const
{
	return m_tMatrix.prod(point);
}



}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
