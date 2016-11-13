/**
 * @file
 * @brief .
 */

#include <algorithm>

#include "../../../include/gpx/gra/Viewport.hpp"

namespace gpx {
namespace gra {

Viewport::Viewport(GLint width, GLint height)
{
	m_params[X] = 0;
	m_params[Y] = 0;
	m_params[WIDTH] = width;
	m_params[HEIGHT] = height;
}

Viewport::Viewport(GLint x, GLint y, GLint width, GLint height)
{
	m_params[X] = x;
	m_params[Y] = y;
	m_params[WIDTH] = width;
	m_params[HEIGHT] = height;
}

Viewport::~Viewport()
{
}

GLint Viewport::operator[](param_t param) const
{
	return m_params[param];
}

GLint Viewport::param(param_t param) const
{
	return m_params[param];
}

void Viewport::setParam(param_t param, GLint val)
{
	m_params[param] = val;
	notifyObservers();
}

const GLint * Viewport::params() const
{
	return m_params;
}

void Viewport::setParams(const GLint params[4])
{
	std::copy(params, params + 4, this->m_params);
	notifyObservers();
}

void Viewport::setParams(GLint x, GLint y, GLint width, GLint height)
{
	m_params[X] = x;
	m_params[Y] = y;
	m_params[WIDTH] = width;
	m_params[HEIGHT] = height;
	notifyObservers();
}

void Viewport::setSize(GLint width, GLint height)
{
	m_params[WIDTH] = width;
	m_params[HEIGHT] = height;
	notifyObservers();
}

void Viewport::setPos(GLint x, GLint y)
{
	m_params[X] = x;
	m_params[Y] = y;
	notifyObservers();
}

GLint Viewport::width() const
{
	return m_params[WIDTH];
}

void Viewport::setWidth(GLint width)
{
	m_params[WIDTH] = width;
	notifyObservers();
}

GLint Viewport::height() const
{
	return m_params[HEIGHT];
}

void Viewport::setHeight(GLint height)
{
	m_params[HEIGHT] = height;
	notifyObservers();
}

GLint Viewport::x() const
{
	return m_params[X];
}

void Viewport::setX(GLint x)
{
	m_params[X] = x;
	notifyObservers();
}

GLint Viewport::y() const
{
	return m_params[Y];
}

void Viewport::setY(GLint y)
{
	m_params[y] = y;
	notifyObservers();
}



}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
