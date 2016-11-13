/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/phy2d/MovableObject.hpp"

namespace gpx {
namespace phy2d {


MovableObject::MovableObject():
	m_pos(m_doubleBufferController),
	m_tMatrix(m_doubleBufferController),
	m_tMatrixInv(m_doubleBufferController)
{
	constructTMatrix(m_tMatrix.active(), m_tMatrixInv.active());
}

MovableObject::~MovableObject()
{
}

const utils::DoubleBufferController & MovableObject::doubleBufferController() const
{
	return m_doubleBufferController;
}


void MovableObject::constructTMatrix(phy::TransformationMatrix & tMatrix, phy::TransformationMatrix & tInvMatrix)
{
	tMatrix(0,3) = posB(0);
	tMatrix(1,3) = posB(1);

	tInvMatrix(0,3) = -posB(0);
	tInvMatrix(1,3) = -posB(1);
}

const math::Vector<2> & MovableObject::pos() const
{
	return m_pos.active();
}

void MovableObject::setPos(const math::const_VectorPtr<2> & pos)
{
	m_pos.active() = pos;
	m_pos.background() = pos;

	constructTMatrix(m_tMatrix.active(), m_tMatrixInv.active());
}

void MovableObject::setPos(real_t x, real_t y)
{
	setPos(math::Vector<2>(x, y));
}

real_t MovableObject::x() const
{
	return m_pos.active()[0];
}

void MovableObject::setX(real_t x)
{
	setPos(math::Vector<2>(x, this->m_pos.active()[1]));
}

real_t MovableObject::y() const
{
	return m_pos.active()[1];
}

void MovableObject::setY(real_t y)
{
	setPos(math::Vector<2>(this->m_pos.active()[0], y));
}

const phy::TransformationMatrix & MovableObject::tMatrix() const
{
	return m_tMatrix.active();
}

math::Vector<2> MovableObject::mapToLocal(const math::const_VectorPtr<2> & point) const
{
	math::Vector<2> result(point);
	m_tMatrixInv.active().mult(result);
	return result;
}

math::Vector<2> MovableObject::mapToGlobal(const math::const_VectorPtr<2> & point) const
{
	math::Vector<2> result(point);
	m_tMatrix.active().mult(result);
	return result;
}

void MovableObject::swapBuffers()
{
	m_doubleBufferController.swapBuffers();
}

void MovableObject::update(real_t dt)
{
	updatePos(dt, m_pos.background());
	constructTMatrix(m_tMatrix.background(), m_tMatrixInv.background());
}

const math::Vector<2> & MovableObject::posA() const
{
	return m_pos.active();
}

real_t MovableObject::posA(std::size_t i)
{
	return m_pos.active().coord(i);
}

const math::Vector<2> & MovableObject::posB() const
{
	return m_pos.background();
}

real_t MovableObject::posB(std::size_t i)
{
	return m_pos.background().coord(i);
}

void MovableObject::updateTMatrix()
{
	constructTMatrix(m_tMatrix.active(), m_tMatrixInv.active());
}

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
