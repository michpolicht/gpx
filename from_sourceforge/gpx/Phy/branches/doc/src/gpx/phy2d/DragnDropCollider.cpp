/*
 * DragnDropCollider.cpp
 *
 *      Author: doc
 */

//#include <iostream>

#include "../../../include/gpx/phy2d/ICDragnDrop.hpp"
#include "../../../include/gpx/phy2d/DragnDropCollider.hpp"

namespace gpx {
namespace phy2d {


DragnDropCollider::DragnDropCollider():
	m_dt(0.0)
{
}

DragnDropCollider::~DragnDropCollider()
{
}

void DragnDropCollider::drag(const real_t pos[2])
{
	drag(pos[0], pos[1]);
}

void DragnDropCollider::drag(real_t x, real_t y)
{
	m_pos[0] = x;
	m_pos[1] = y;
	//reset old pos
	m_oldPos[0] = x;
	m_oldPos[1] = y;
	for (ObjectsContainer::iterator i = m_objects.begin(); i != m_objects.end(); ++i)
		if ((*i)->test((*i)->mapToLocal(m_pos)))
			m_dragged.push_back(*i);
}

void DragnDropCollider::drop()
{
	m_dragged.clear();
}

std::size_t DragnDropCollider::draggedNum() const
{
	return m_dragged.size();
}

void DragnDropCollider::setPos(const real_t pos[2])
{
	setX(pos[0]);
	setY(pos[1]);
}

void DragnDropCollider::setPos(real_t x, real_t y)
{
	setX(x);
	setY(y);
}

const real_t * DragnDropCollider::pos() const
{
	return m_pos;
}

void DragnDropCollider::setX(real_t x)
{
	m_oldPos[0] = m_pos[0];
	m_pos[0] = x;
}

real_t DragnDropCollider::x() const
{
	return m_pos[0];
}

real_t DragnDropCollider::dx() const
{
	return m_pos[0] - m_oldPos[0];
}

void DragnDropCollider::setY(real_t y)
{
	m_oldPos[1] = m_pos[1];
	m_pos[1] = y;
}

real_t DragnDropCollider::y() const
{
	return m_pos[1];
}

real_t DragnDropCollider::dy() const
{
	return m_pos[1] - m_oldPos[1];
}

void DragnDropCollider::setDt(real_t dt)
{
	this->m_dt = dt;
}

real_t DragnDropCollider::dt() const
{
	return m_dt;
}

void DragnDropCollider::update(real_t dt)
{
	setDt(dt);
	if (!m_dragged.empty())
		for (DraggedContainer::iterator i = m_dragged.begin(); i != m_dragged.end(); ++i)
			(*i)->performDragnDrop(this);
}

void DragnDropCollider::add(ICDragnDrop * obj)
{
	m_objects.insert(obj);
}

void DragnDropCollider::remove(ICDragnDrop * obj)
{
	for (DraggedContainer::iterator i = m_dragged.begin(); i != m_dragged.end(); ++i)
		if (obj == *i) {
			m_dragged.erase(i);
			break;
		}
	m_objects.erase(obj);
}

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
