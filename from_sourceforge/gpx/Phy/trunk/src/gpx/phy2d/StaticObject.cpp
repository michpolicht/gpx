/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/phy2d/StaticObject.hpp"

namespace gpx {

namespace phy2d {

StaticObject::StaticObject()
{
	constructTMatrix(m_tMatrix, m_tMatrixInv);
}

StaticObject::~StaticObject()
{
}

void StaticObject::constructTMatrix(phy::TransformationMatrix & tMatrix, phy::TransformationMatrix & tMatrixInv)
{
	tMatrix(0,3) = m_pos(0);
	tMatrix(1,3) = m_pos(1);

	tMatrixInv(0,3) = -m_pos(0);
	tMatrixInv(1,3) = -m_pos(1);
}

const math::Vector<2> & StaticObject::pos() const
{
	return m_pos;
}

void StaticObject::setPos(const math::const_VectorPtr<2> & pos)
{
	this->m_pos = pos;

	constructTMatrix(m_tMatrix, m_tMatrixInv);
}

void StaticObject::setPos(real_t x, real_t y)
{
	setPos(math::Vector<2>(x, y));
}

real_t StaticObject::x() const
{
	return m_pos(0);
}

void StaticObject::setX(real_t x)
{
	setPos(math::Vector<2>(x, this->m_pos(1)));
}

real_t StaticObject::y() const
{
	return m_pos(1);
}

void StaticObject::setY(real_t y)
{
	setPos(math::Vector<2>(this->m_pos(0), y));
}

const phy::TransformationMatrix & StaticObject::tMatrix() const
{
	return m_tMatrix;
}

math::Vector<2> StaticObject::mapToLocal(const real_t point[2]) const
{
	math::Vector<2> result(point);
	m_tMatrixInv.mult(result);
	return result;
}

math::Vector<2> StaticObject::mapToGlobal(const real_t point[2]) const
{
	math::Vector<2> result(point);
	m_tMatrix.mult(result);
	return result;
}



}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
