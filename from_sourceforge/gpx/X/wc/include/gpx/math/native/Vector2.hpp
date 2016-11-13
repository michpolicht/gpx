/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_NATIVE_VECTOR2_HPP_
#define GPX_X_MATH_NATIVE_VECTOR2_HPP_

#include "VectorPtr2.hpp"

namespace gpx {
namespace math {
namespace native {

/**
 * Two dimensional vector specialization. Coords variable may be accessed directly.
 * Coordinates system:
 * @verbatim

   ^ coords[1] (y)
   |
  2|
  1|
   .--------> coords[0] (x)
  0 1 2

 * @endverbatim
 *
 */
template<typename T>
class Vector<2, T> : public VectorPtr<2, T>
{
	private:
		typedef VectorPtr<2, T> Parent;

	protected:
		T m_coords[2];

	public:
		/**
		 * Default constructor. Constructs vector initialized as (0, 0).
		 */
		Vector();

		/**
		 * Copy constructor
		 */
		Vector(const Vector<2, T> & other);

		/**
		 * Constructor. This is not a conversion constructor thus it should be used explicitly.
		 * It copies data from const_VectorPtr<2, T>.
		 * @param other other vector.
		 */
		explicit Vector(const const_VectorPtr<2, T> & other);

		/**
		 * Constructor. This is not a conversion constructor thus it should be used explicitly.
		 * It copies data from coords array.
		 * @param coords array of coordinates. Array must be of length 2.
		 */
		explicit Vector(const T coords[2]);

		/**
		 * Constructor.
		 * @param x x coordinate of vector.
		 * @param y y coordinate of vector.
		 */
		Vector(T x, T y);

		/**
		 * Constructor. Constructs vector for given two points.
		 * @param init initial point
		 * @param end end point.
		 */
		Vector(const T init[2], const T end[2]);

		/**
		 * Assignment operator. Data will be copied from other to ptr.
		 */
		const Vector<2, T> & operator=(const real_t other[2]);

		/**
		 * Assignment operator. Data will be copied from other to ptr.
		 */
		const Vector<2, T> & operator=(const const_VectorPtr<2, T> & other);

		/**
		 * Assignment operator. Data will be copied from other to ptr.
		 */
		const Vector<2, T> & operator=(const VectorPtr<2, T> & other);

		/**
		 * Assignment operator. Data will be copied from other to ptr.
		 */
		const Vector<2, T> & operator=(const Vector<2, T> & other);

};


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
Vector<2, T>::Vector(const T init[2], const T end[2]):
	VectorPtr<2, T>(m_coords)
{
	m_coords[0] = end[0] - init[0];
	m_coords[1] = end[1] - init[1];
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
}

#endif /* GPX_X_MATH_NATIVE_VECTOR2_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
