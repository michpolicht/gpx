/**
 * @file
 * @brief Implementation of const_VectorPtr<2, T> functions.
 */


#include "_structures_warning.hpp"


namespace gpx {
namespace math {


template <typename T>
int const_VectorPtr<2, T>::PrintPrecision = std::numeric_limits<T>::digits10 + 2;


/*
==============
<CONSTRUCTORS>
==============
*/

template<typename T>
inline
const_VectorPtr<2, T>::const_VectorPtr():
	m_ptr(0)
{};

template<typename T>
inline
const_VectorPtr<2, T>::const_VectorPtr(const const_VectorPtr<2, T> & other):
	m_ptr(other.m_ptr)
{};

template<typename T>
inline
const_VectorPtr<2, T>::const_VectorPtr(const T * coords):
	m_ptr(const_cast<T * const>(coords))
{
};

template<typename T>
inline
const_VectorPtr<2, T>::const_VectorPtr(const Vector<2, T> & other):
	m_ptr(other.m_ptr)
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
T const_VectorPtr<2, T>::operator[](int i) const
{
	return m_ptr[i];
};

template<typename T>
inline
T const_VectorPtr<2, T>::operator()(int i) const
{
	return m_ptr[i];
};

template<typename T>
inline
T const_VectorPtr<2, T>::coord(int i) const
{
	return m_ptr[i];
};

template<typename T>
inline
T const_VectorPtr<2, T>::x() const
{
	return m_ptr[0];
};

template<typename T>
inline
T const_VectorPtr<2, T>::y() const
{
	return m_ptr[1];
};

template<typename T>
inline
bool const_VectorPtr<2, T>::operator==(const const_VectorPtr<2, T> & other) const
{
	return memcmp(m_ptr, other.m_ptr, sizeof(T)*2) == 0 ? true : false;
};

template<typename T>
inline
bool const_VectorPtr<2, T>::operator!=(const const_VectorPtr<2, T> & other) const
{
	return memcmp(m_ptr, other.m_ptr, sizeof(T)*2) == 0 ? false : true;
};

template<typename T>
inline
Vector<2, T> const_VectorPtr<2, T>::operator+(const const_VectorPtr<2, T> & other) const
{
	Vector<2, T> result(*this);
	result += other;
	return result;
};

template<typename T>
inline
Vector<2, T> const_VectorPtr<2, T>::operator-(const const_VectorPtr<2, T> & other) const
{
	Vector<2, T> result(*this);
	result -= other;
	return result;
};


template<typename T>
inline
Vector<2, T> const_VectorPtr<2, T>::operator-() const
{
	return inverse();
}

template<typename T>
inline
Vector<2, T> const_VectorPtr<2, T>::operator/(T scalar) const
{
	Vector<2, T> result(*this);
	result /= scalar;
	return result;
};

template<typename T>
inline
Vector<2, T> const_VectorPtr<2, T>::operator*(T scalar) const
{
	Vector<2, T> result(*this);
	result *= scalar;
	return result;
};

template<typename T>
inline
const_VectorPtr<2, T>::operator const T *() const
{
	return m_ptr;
};

template<typename T>
inline
const_VectorPtr<2, T>::operator size_t() const
{
	return (size_t)m_ptr;
}

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
T const_VectorPtr<2, T>::dot(const const_VectorPtr<2, T> & other) const
{
	return m_ptr[0] * other.m_ptr[0] + (m_ptr[1] * other.m_ptr[1]);
};

template<typename T>
inline
T const_VectorPtr<2, T>::dot() const
{
	return m_ptr[0] * m_ptr[0] + (m_ptr[1] * m_ptr[1]);
};

template<typename T>
inline
Matrix<2,2> const_VectorPtr<2, T>::out(const const_VectorPtr<2, T> & other) const
{
	Matrix<2,2> result(false);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			result(i,j) = m_ptr[i] * other[j];
	return result;
}

template<typename T>
inline
T const_VectorPtr<2, T>::length() const
{
	return std::sqrt((m_ptr[0] * m_ptr[0]) + (m_ptr[1] * m_ptr[1]));
};

template<typename T>
inline
bool const_VectorPtr<2, T>::isZero() const
{
	return ((m_ptr[0] == T()) && (m_ptr[1] == T()));
}

template<typename T>
inline
Vector<2, T> const_VectorPtr<2, T>::inverse() const
{
	return Vector<2, T>(-m_ptr[0], -m_ptr[1]);
};

template<typename T>
inline
Vector<2, T> const_VectorPtr<2, T>::versor() const
{
	Vector<2, T> result(*this);
	result.div(length());
	return result;
};

template<typename T>
inline
T const_VectorPtr<2, T>::det(const const_VectorPtr<2, T> & other) const
{
	return (m_ptr[0] * other.m_ptr[1]) - (m_ptr[1] * other.m_ptr[0]);
};

template<typename T>
inline
Vector<2, T> const_VectorPtr<2, T>::cross() const
{
	return Vector<2, T>(m_ptr[1], -m_ptr[0]);
}

template<typename T>
inline
Vector<2, T> const_VectorPtr<2, T>::orthoCW() const
{
	return Vector<2, T>(m_ptr[1], -m_ptr[0]);
}

template<typename T>
inline
Vector<2, T> const_VectorPtr<2, T>::orthoCCW() const
{
	return Vector<2, T>(-m_ptr[1], m_ptr[0]);
}

template<typename T>
inline
bool const_VectorPtr<2, T>::ape(const const_VectorPtr<2, T> & other) const
{
	return gpx::math::ape(m_ptr[0], other.m_ptr[0]) && gpx::math::ape(m_ptr[1], other.m_ptr[1]);
}

template<typename T>
inline
bool const_VectorPtr<2, T>::ale(const const_VectorPtr<2, T> & other) const
{
	return gpx::math::ale(m_ptr[0], other.m_ptr[0]) && gpx::math::ale(m_ptr[1], other.m_ptr[1]);
}

template<typename T>
inline
bool const_VectorPtr<2, T>::clt(const const_VectorPtr<2, T> & other) const
{
	return gpx::math::clt(m_ptr[0], other.m_ptr[0]) && gpx::math::clt(m_ptr[1], other.m_ptr[1]);
}

template<typename T>
inline
bool const_VectorPtr<2, T>::cgt(const const_VectorPtr<2, T> & other) const
{
	return gpx::math::cgt(m_ptr[0], other.m_ptr[0]) && gpx::math::cgt(m_ptr[1], other.m_ptr[1]);
}

template<typename T>
inline
Vector<2, T> const_VectorPtr<2, T>::minimal(const const_VectorPtr<2, T> & other) const
{
	int epsExp;
	int ptrExp[2];
	int dExp;
	T ptrSig[2];
	T epsilon = std::max(eps(other[0]), eps(other[1]));
	std::frexp(epsilon, & epsExp);
	ptrSig[0] = std::frexp(m_ptr[0], & ptrExp[0]);
	ptrSig[1] = std::frexp(m_ptr[1], & ptrExp[1]);
	dExp = -epsExp + std::min(ptrExp[0], ptrExp[1]);

	return Vector<2, T>(std::ldexp(ptrSig[0], ptrExp[0] - dExp),
						std::ldexp(ptrSig[1], ptrExp[1] - dExp));
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
