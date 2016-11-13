/**
 * @file
 * @brief .
 */

#include "const_VectorPtr.hpp"
#include "../../log.hpp"

namespace gpx {
namespace math {
namespace native {

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
int base_const_VectorPtr<N, VECTOR, MATRIX, T>::PrintPrecision = std::numeric_limits<T>::digits10 + 2;

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
base_const_VectorPtr<N, VECTOR, MATRIX, T>::operator const T *() const
{
	return m_ptr;
};

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
base_const_VectorPtr<N, VECTOR, MATRIX, T>::operator size_t() const
{
	return (size_t)m_ptr;
}

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
T base_const_VectorPtr<N, VECTOR, MATRIX, T>::operator [](int i) const
{
	GPX_ASSERT(sizeof(std::size_t) >= sizeof(int), "int can not be safely converted to std::size_t");
	GPX_ASSERT(static_cast<std::size_t>(i) < N, "index [" << i << "] is out of bounds");
	return m_ptr[i];
};

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
T base_const_VectorPtr<N, VECTOR, MATRIX, T>::operator [](std::size_t i) const
{
	GPX_ASSERT(i < N, "index [" << i << "] is out of bounds");
	return m_ptr[i];
};

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
T base_const_VectorPtr<N, VECTOR, MATRIX, T>::operator ()(std::size_t i) const
{
	GPX_ASSERT(i < N, "index (" << i << ") is out of bounds");
	return m_ptr[i];
};

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
T base_const_VectorPtr<N, VECTOR, MATRIX, T>::coord(std::size_t i) const
{
	GPX_ASSERT(i < N, "coord(" << i << ") is out of bounds");
	return m_ptr[i];
};

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
bool base_const_VectorPtr<N, VECTOR, MATRIX, T>::operator ==(const const_VectorPtr<N, T> & other) const
{
	return memcmp(m_ptr, other.m_ptr, sizeof(T) * N) == 0 ? true : false;
};

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
bool base_const_VectorPtr<N, VECTOR, MATRIX, T>::operator !=(const const_VectorPtr<N, T> & other) const
{
	return memcmp(m_ptr, other.m_ptr, sizeof(T) * N) == 0 ? false : true;
};

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
VECTOR<N, T> base_const_VectorPtr<N, VECTOR, MATRIX, T>::operator +(const const_VectorPtr<N, T> & other) const
{
	VECTOR<N, T> result(* this);
	result += other;
	return result;
};

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
VECTOR<N, T> base_const_VectorPtr<N, VECTOR, MATRIX, T>::operator -(const const_VectorPtr<N, T> & other) const
{
	VECTOR<N, T> result(* this);
	result -= other;
	return result;
};


template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
VECTOR<N, T> base_const_VectorPtr<N, VECTOR, MATRIX, T>::operator -() const
{
	return inverse();
}

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
VECTOR<N, T> base_const_VectorPtr<N, VECTOR, MATRIX, T>::operator /(T scalar) const
{
	VECTOR<N, T> result(* this);
	result /= scalar;
	return result;
};

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
VECTOR<N, T> base_const_VectorPtr<N, VECTOR, MATRIX, T>::operator *(T scalar) const
{
	VECTOR<N, T> result(* this);
	result *= scalar;
	return result;
};

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
T base_const_VectorPtr<N, VECTOR, MATRIX, T>::dot(const const_VectorPtr<N, T> & other) const
{
	T result = T();
	for (std::size_t i = 0; i < N; i++)
		result += coord(i) * other(i);
	return result;
};

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
T base_const_VectorPtr<N, VECTOR, MATRIX, T>::dot() const
{
	return dot(* this);
};

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
MATRIX<N, N, T> base_const_VectorPtr<N, VECTOR, MATRIX, T>::out(const const_VectorPtr<N, T> & other) const
{
	GPX_WARN("matrix initialization methods will be changed!");
	Matrix<N, N> result(false);	//@todo as above
	for (std::size_t i = 0; i < N; i++)
		for (std::size_t j = 0; j < N; j++)
			result(i, j) = coord(i) * other(j);
	return result;
}

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
base_const_VectorPtr<N, VECTOR, MATRIX, T>::base_const_VectorPtr(const T * coords):
	m_ptr(const_cast<T * const>(coords))
{
};

template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
inline
base_const_VectorPtr<N, VECTOR, MATRIX, T>::base_const_VectorPtr(const base_const_VectorPtr<N, VECTOR, MATRIX, T> & other):
	m_ptr(other.m_ptr)
{
};

}
}
}

/**
 * Output stream operator for vector types.
 * @param s output stream.
 * @param v vector object.
 */
template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T>
std::ostream & operator<<(std::ostream & s, const gpx::math::native::base_const_VectorPtr<N, VECTOR, MATRIX, T> & v)
{
	s.precision(gpx::math::native::base_const_VectorPtr<N, VECTOR, MATRIX, T>::PrintPrecision);
	s << "(";
	for (std::size_t i = 0; i < N - 1; i++)
		s << v(i) << ", ";
	s << v(N - 1) << ")" << std::endl;
	return s;
};

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
