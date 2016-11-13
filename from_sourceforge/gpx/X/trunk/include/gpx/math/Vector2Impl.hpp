/**
 * @file
 * @brief Vector<2> inline functions implementation.
 */

#include "_structures_warning.hpp"


namespace gpx {
namespace math {


template<typename T>
inline
Vector<2, T>::Vector():
	VectorPtr<2, T>(m_coords)
{
	//do not use mem* functions cause float/double/whatever 0.0 representation is
	//not necessarily 0 binary. Compiler will hopefully unroll this loop.
	for (std::size_t i = 0; i < Parent::SIZE; i++)
		m_coords[i] = T();
};

template<typename T>
inline
Vector<2, T>::Vector(const Vector<2, T> & other):
	VectorPtr<2, T>(m_coords)
{
	memcpy(m_coords, other.m_coords, sizeof(m_coords));
};

template<typename T>
inline
Vector<2, T>::Vector(const const_VectorPtr<2, T> & other):
	VectorPtr<2, T>(m_coords)
{
	memcpy(m_coords, other.m_ptr, sizeof(m_coords));
};

template<typename T>
inline
Vector<2, T>::Vector(const T coords[2]):
	VectorPtr<2, T>(m_coords)
{
	memcpy(m_coords, coords, sizeof(m_coords));
};

template<typename T>
inline
Vector<2, T>::Vector(T x, T y):
	VectorPtr<2, T>(m_coords)
{
	m_coords[0] = x;
	m_coords[1] = y;
};

template<typename T>
inline
const Vector<2, T> & Vector<2, T>::operator=(const real_t other[2])
{
	//self assignment branch not required here
	memcpy(m_coords, other, 2 * sizeof(T));
	return *this;
};

template<typename T>
inline
const Vector<2, T> & Vector<2, T>::operator=(const const_VectorPtr<2, T> & other)
{
	//self assignment branch not required here
	memcpy(m_coords, other.m_ptr, 2 * sizeof(T));
	return *this;
};

template<typename T>
inline
const Vector<2, T> & Vector<2, T>::operator=(const VectorPtr<2, T> & other)
{
	//self assignment branch not required here
	memcpy(m_coords, other.m_ptr, 2 * sizeof(T));
	return *this;
};

template<typename T>
inline
const Vector<2, T> & Vector<2, T>::operator=(const Vector<2, T> & other)
{
	//self assignment branch not required here
	memcpy(m_coords, other.m_ptr, 2 * sizeof(T));
	return *this;
};


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
