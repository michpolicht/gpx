/**
 * @file
 * @brief Implementation of VectorPtr<2, T> inline functions.
 */

#include "_structures_warning.hpp"


namespace gpx {
namespace math {


/*
==============
<CONSTRUCTORS>
==============
*/

template<typename T>
inline
VectorPtr<2, T>::VectorPtr():
	Parent()
{};

template<typename T>
inline
VectorPtr<2, T>::VectorPtr(const VectorPtr<2, T> & other):
	Parent(other)
{};

template<typename T>
inline
VectorPtr<2, T>::VectorPtr(const const_VectorPtr<2, T> & other):
	Parent(other)
{};

template<typename T>
inline
VectorPtr<2, T>::VectorPtr(T * coords):
	Parent(coords)
{
};

template<typename T>
inline
VectorPtr<2, T>::VectorPtr(const Vector<2, T> & other):
	Parent(other)
{
};

/*
==============
<DESTRUCTOR>
==============
*/


/*
==============
<OPERATORS>
==============
*/

template<typename T>
inline
const VectorPtr<2, T> & VectorPtr<2, T>::operator=(const real_t other[2])
{
	//self assignment branch not required here
	memcpy(Parent::m_ptr, other, 2 * sizeof(T));
	return *this;
};

template<typename T>
inline
const VectorPtr<2, T> & VectorPtr<2, T>::operator=(const const_VectorPtr<2, T> & other)
{
	//self assignment branch not required here
	memcpy(Parent::m_ptr, other.m_ptr, 2 * sizeof(T));
	return *this;
};

template<typename T>
inline
const VectorPtr<2, T> & VectorPtr<2, T>::operator=(const VectorPtr<2, T> & other)
{
	//self assignment branch not required here
	memcpy(Parent::m_ptr, other.m_ptr, 2 * sizeof(T));
	return *this;
};

template<typename T>
inline
T & VectorPtr<2, T>::operator[](int i)
{
	return Parent::m_ptr[i];
};

template<typename T>
inline
T & VectorPtr<2, T>::operator()(int i)
{
	return Parent::m_ptr[i];
};

template<typename T>
inline
T & VectorPtr<2, T>::coord(int i)
{
	return Parent::m_ptr[i];
};

template<typename T>
inline
T & VectorPtr<2, T>::x()
{
	return Parent::m_ptr[0];
};

template<typename T>
inline
T & VectorPtr<2, T>::y()
{
	return Parent::m_ptr[1];
};

template<typename T>
inline
T VectorPtr<2, T>::operator[](int i) const
{
	return Parent::m_ptr[i];
};

template<typename T>
inline
T VectorPtr<2, T>::operator()(int i) const
{
	return Parent::m_ptr[i];
};

template<typename T>
inline
T VectorPtr<2, T>::coord(int i) const
{
	return Parent::m_ptr[i];
};

template<typename T>
inline
T VectorPtr<2, T>::x() const
{
	return Parent::m_ptr[0];
};

template<typename T>
inline
T VectorPtr<2, T>::y() const
{
	return Parent::m_ptr[1];
};

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::operator+=(const const_VectorPtr<2, T> & other)
{
	return add(other);
};

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::operator-=(const const_VectorPtr<2, T> & other)
{
	return sub(other);
};

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::operator/=(T scalar)
{
	return div(scalar);
};

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::operator*=(T scalar)
{
	return mult(scalar);
};

template<typename T>
inline
VectorPtr<2, T>::operator T *()
{
	return Parent::m_ptr;
};


/*
==============
<GET-SET>
==============
*/


/*
==============
<METHODS>
==============
*/

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::set(T x, T y)
{
	Parent::m_ptr[0] = x;
	Parent::m_ptr[1] = y;
	return *this;
}

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::zero()
{
	for (std::size_t i = 0; i < Parent::SIZE; i++)
		Parent::m_ptr[i] = T();
	return *this;
};

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::add(const const_VectorPtr<2, T> & other)
{
	Parent::m_ptr[0] += other.m_ptr[0];
	Parent::m_ptr[1] += other.m_ptr[1];
	return *this;
};

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::add(T x, T y)
{
	Parent::m_ptr[0] += x;
	Parent::m_ptr[1] += y;
	return *this;
};

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::sub(const const_VectorPtr<2, T> & other)
{
	Parent::m_ptr[0] -= other.m_ptr[0];
	Parent::m_ptr[1] -= other.m_ptr[1];
	return *this;
};

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::sub(T x, T y)
{
	Parent::m_ptr[0] -= x;
	Parent::m_ptr[1] -= y;
	return *this;
};

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::div(T scalar)
{
	Parent::m_ptr[0] /= scalar;
	Parent::m_ptr[1] /= scalar;
	return *this;
};

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::mult(T scalar)
{
	Parent::m_ptr[0] *= scalar;
	Parent::m_ptr[1] *= scalar;
	return *this;
};

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::mult(const Matrix<2,2> & matrix)
{
	Vector<2, T> copy(*this);
	Parent::m_ptr[0] = (copy.m_ptr[0] * matrix(0,0)) + (copy.m_ptr[1] * matrix(1,0));
	Parent::m_ptr[1] = (copy.m_ptr[0] * matrix(0,1)) + (copy.m_ptr[1] * matrix(1,1));
	return *this;
}

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::mult(const Matrix<4,4> & matrix)
{
	Vector<2, T> copy(*this);
	Parent::m_ptr[0] = (copy.m_ptr[0] * matrix(0,0)) + (copy.m_ptr[1] * matrix(1,0)) + matrix(3,0);
	Parent::m_ptr[1] = (copy.m_ptr[0] * matrix(0,1)) + (copy.m_ptr[1] * matrix(1,1)) + matrix(3,1);
	return *this;
}

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::normalize()
{
	div(Parent::length());
	return *this;
};

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::invert()
{
	Parent::m_ptr[0] = -Parent::m_ptr[0];
	Parent::m_ptr[1] = -Parent::m_ptr[1];
	return *this;
};

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::rotate(T sin, T cos)
{
	T x, y;

	x = Parent::m_ptr[0];
	y = Parent::m_ptr[1];

	Parent::m_ptr[0] = (x * cos) - (y * sin);
	Parent::m_ptr[1] = (y * cos) + (x * sin);

	return *this;
}

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::rotate(T angle)
{
	real_t sin, cos;
	sincos(angle, & sin, & cos);
	return rotate(static_cast<T>(sin), static_cast<T>(cos));
};

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::rotate(T angle, const const_VectorPtr<2, T> & point)
{
	Parent::m_ptr[0] -= point.m_ptr[0];
	Parent::m_ptr[1] -= point.m_ptr[1];
	rotate(angle);
	Parent::m_ptr[0] += point.m_ptr[0];
	Parent::m_ptr[1] += point.m_ptr[1];
	return *this;
};

template<typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T>::minimize(const const_VectorPtr<2, T> & other)
{
	int epsExp;
	int ptrExp[2];
	int dExp;
	T ptrSig[2];
	T epsilon = std::max(eps(other[0]), eps(other[1]));
	std::frexp(epsilon, & epsExp);
	ptrSig[0] = std::frexp(Parent::m_ptr[0], & ptrExp[0]);
	ptrSig[1] = std::frexp(Parent::m_ptr[1], & ptrExp[1]);
	dExp = -epsExp + std::min(ptrExp[0], ptrExp[1]);
	Parent::m_ptr[0] = std::ldexp(ptrSig[0], ptrExp[0] - dExp);
	Parent::m_ptr[1] = std::ldexp(ptrSig[1], ptrExp[1] - dExp);
	return *this;
}


/*
==============
<VIRTUAL>
==============
*/


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
