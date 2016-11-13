/**
 * @file
 * @brief Matrix implementations.
 */

#include "_structures_warning.hpp"


namespace gpx {
namespace math {


template<std::size_t N>
int Matrix<N,N>::PrintWidth = 10;


template<std::size_t N>
inline
real_t Matrix<N,N>::_det(const real_t * elements, std::size_t size) const
{
	real_t result = 0.0;
	real_t tmp[--size * size++];

	if (size == 2)
		return elements[0] * elements[3] - (elements[1] * elements[2]);
	for (std::size_t j = 0; j < size; j++) {
		for(std::size_t k = size, ctr = 0; k < size * size; k++)
			if (k % size != j)
				tmp[ctr++] = elements[k];
		result += elements[j] * ((j % 2) ? -1.0 : 1.0) * _det(tmp, size - 1);
	}
	return result;
}


template<std::size_t N>
inline
Matrix<N,N>::Matrix()
{
	for (std::size_t i = 0; i < N*N; i++)
		m_elements[i] = 0.0;
	for (std::size_t i = 0; i < N; i++)
		m_elements[N*i + i] = 1.0;
};

template<std::size_t N>
inline
Matrix<N,N>::Matrix(bool init)
{
	if (init)
		for (std::size_t i = 0; i < N*N; i++)
			m_elements[i] = 0.0;
};

template<std::size_t N>
inline
Matrix<N,N>::Matrix(real_t d)
{
	for(std::size_t i = 0; i < N*N; i++)
		m_elements[i] = d;
};

template<std::size_t N>
inline
Matrix<N,N>::Matrix(real_t * elements)
{
	memcpy(m_elements, elements, sizeof(m_elements));
};

template<std::size_t N>
inline
real_t & Matrix<N,N>::operator()(std::size_t i, std::size_t j)
{
	return m_elements[j*N + i];
};

template<std::size_t N>
inline
real_t Matrix<N,N>::operator()(std::size_t i, std::size_t j) const
{
	return m_elements[j*N + i];
};

template<std::size_t N>
inline
Matrix<N,N>::operator real_t *()
{
	return m_elements;
};

template<std::size_t N>
inline
Matrix<N,N>::operator const real_t *() const
{
	return m_elements;
};

template<std::size_t N>
inline
Matrix<N,N> & Matrix<N,N>::operator+=(const Matrix<N,N> & other)
{
	return add(other);
};

template<std::size_t N>
inline
Matrix<N,N> Matrix<N,N>::operator+(const Matrix<N,N> & other)
{
	Matrix<N,N> result(*this);
	result += other;
	return result;
};

template<std::size_t N>
inline
Matrix<N,N> & Matrix<N,N>::operator-=(const Matrix<N,N> & other)
{
	return sub(other);
};

template<std::size_t N>
inline
Matrix<N,N> Matrix<N,N>::operator-(const Matrix<N,N> & other)
{
	Matrix<N,N> result(*this);
	result -= other;
	return result;
};

template<std::size_t N>
inline
Matrix<N,N> & Matrix<N,N>::operator*=(const Matrix<N,N> & other)
{
	return mult(other);
};

template<std::size_t N>
inline
Matrix<N,N> Matrix<N,N>::operator*(const Matrix<N,N> & other)
{
	Matrix<N,N> result(*this);
	result *= other;
	return result;

};

template<std::size_t N>
inline
real_t * Matrix<N,N>::elements()
{
	return m_elements;
}


template<std::size_t N>
inline
real_t * Matrix<N,N>::elements(std::size_t i, std::size_t j)
{
	return (m_elements + j * N + i);
}

template<std::size_t N>
inline
Matrix<N,N> & Matrix<N,N>::zero()
{
	for (std::size_t i = 0; i < N*N; i++)
		m_elements[i] = 0.0;
	return *this;
};

template<std::size_t N>
inline
Matrix<N,N> & Matrix<N,N>::identity()
{
	for (std::size_t i = 0; i < N*N; i++)
		m_elements[i] = 0.0;
	for (std::size_t i = 0; i < N; i++)
		m_elements[N*i + i] = 1.0;
	return *this;
};

template<std::size_t N>
inline
Matrix<N,N> & Matrix<N,N>::add(const Matrix<N,N> & other)
{
	for (std::size_t i = 0; i < N*N; i++)
		m_elements[i] += other.m_elements[i];
	return *this;
};

template<std::size_t N>
inline
Matrix<N,N> & Matrix<N,N>::sub(const Matrix<N,N> & other)
{
	for (std::size_t i = 0; i < N*N; i++)
		m_elements[i] -= other.m_elements[i];
	return *this;
};


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
