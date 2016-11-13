/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gra2d/Clip.hpp"


#include <algorithm>


namespace gpx {
namespace gra2d {

Clip::Clip(real_t width, real_t height)
{
	m_planes[LEFT] = 0.0;
	m_planes[RIGHT] = width;
	m_planes[BOTTOM] = 0.0;
	m_planes[TOP] = height;
}

Clip::Clip(real_t left, real_t right, real_t bottom, real_t top)
{
	m_planes[LEFT] = left;
	m_planes[RIGHT] = right;
	m_planes[BOTTOM] = bottom;
	m_planes[TOP] = top;
}

Clip::~Clip()
{
}

real_t Clip::operator[](plane_t plane) const
{
	return m_planes[plane];
}

real_t Clip::plane(plane_t plane) const
{
	return m_planes[plane];
	return m_planes[plane];
}

void Clip::setPlane(plane_t plane, real_t val)
{
	m_planes[plane] = val;
	notifyObservers();
}

const real_t * Clip::planes() const
{
	return m_planes;
}

void Clip::setPlanes(const real_t planes[4])
{
	std::copy(planes, planes + 4, this->m_planes);
	notifyObservers();
}

void Clip::setPlanes(real_t left, real_t right, real_t bottom, real_t top)
{
	m_planes[LEFT] = left;
	m_planes[RIGHT] = right;
	m_planes[BOTTOM] = bottom;
	m_planes[TOP] = top;
	notifyObservers();
}

void Clip::setSize(real_t width, real_t height)
{
	m_planes[RIGHT] = m_planes[LEFT] + width;
	m_planes[TOP] = m_planes[BOTTOM] + height;
	notifyObservers();
}

void Clip::setPos(real_t x, real_t y)
{
	//planes[RIGHT] = x + width = x + (planes[RIGHT] - planes[LEFT])
	m_planes[RIGHT] -= m_planes[LEFT];
	m_planes[RIGHT] += x;
	m_planes[LEFT] = x;
	//planes[TOP] = y + height = y + (planes[TOP] - planes[BOTTOM])
	m_planes[TOP] -= m_planes[BOTTOM];
	m_planes[TOP] += y;
	m_planes[BOTTOM] = y;
	notifyObservers();
}

real_t Clip::left() const
{
	return m_planes[LEFT];
}

void Clip::setLeft(real_t left)
{
	m_planes[LEFT] = left;
	notifyObservers();
}

real_t Clip::right() const
{
	return m_planes[RIGHT];
}

void Clip::setRight(real_t right)
{
	m_planes[RIGHT] = right;
	notifyObservers();
}

real_t Clip::bottom() const
{
	return m_planes[BOTTOM];
}

void Clip::setBottom(real_t bottom)
{
	m_planes[BOTTOM] = bottom;
	notifyObservers();
}

real_t Clip::top() const
{
	return m_planes[TOP];
}

void Clip::setTop(real_t top)
{
	m_planes[TOP] = top;
	notifyObservers();
}

real_t Clip::width() const
{
	return m_planes[RIGHT] - m_planes[LEFT];
}

real_t Clip::height() const
{
	return m_planes[TOP] - m_planes[BOTTOM];
}


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
