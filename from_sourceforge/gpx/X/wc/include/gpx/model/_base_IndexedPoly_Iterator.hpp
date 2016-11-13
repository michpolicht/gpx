/**
 * @file
 * @brief .
 */

#include "_Poly_warning.hpp"


#ifndef GPX_X_MODEL__BASE_INDEXEDPOLY_ITERATOR_HPP_
#define GPX_X_MODEL__BASE_INDEXEDPOLY_ITERATOR_HPP_


namespace gpx {
namespace model {


/**
 * Indexed polygon iterator. Polygon iterator hops over vertices by index. Thus it mixes Index
 * and VertexData iterators functionality.
 */
template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
class base_IndexedPoly<DIM, I, T>::Iterator
{
	protected:
		IT_I * m_pos;
		IT_T * m_vData;

	public:
		Iterator();
		Iterator(IT_I * pos, IT_T * vData);

		IT_T * operator *() const;
		Iterator & operator++();
		Iterator operator++(int);
		Iterator & operator--();
		Iterator operator--(int);
		Iterator & operator+=(std::size_t n);
		Iterator & operator+=(int n);
		Iterator operator+(std::size_t n) const;
		Iterator operator+(int n) const;
		Iterator & operator-=(std::size_t n);
		Iterator & operator-=(int n);
		Iterator operator-(std::size_t n) const;
		Iterator operator-(int n) const;
		IT_T * operator[](std::size_t i) const;
		IT_T * operator[](int i) const;
	    bool operator==(const Iterator & other) const;
		bool operator!=(const Iterator & other) const;
};



template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::Iterator():
	m_pos(0),
	m_vData(0)
{
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::Iterator(IT_I * pos, IT_T * vData):
	m_pos(pos),
	m_vData(vData)
{
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
IT_T * base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator *() const
{
	return & m_vData[*m_pos * DIM];
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T> & base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator++()
{
	++m_pos;
	return *this;
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T> base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator++(int)
{
	return Iterator(m_pos++, m_vData);
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T> & base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator--()
{
	--m_pos;
	return *this;
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T> base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator--(int)
{
	return Iterator(m_pos--, m_vData);
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T> & base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator+=(std::size_t n)
{
	m_pos += n;
	return *this;
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T> & base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator+=(int n)
{
	m_pos += n;
	return *this;
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T> base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator+(std::size_t n) const
{
	return Iterator(m_pos + n, m_vData);
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T> base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator+(int n) const
{
	return Iterator(m_pos + n, m_vData);
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T> & base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator-=(std::size_t n)
{
	m_pos -= n;
	return *this;
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T> & base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator-=(int n)
{
	m_pos -= n;
	return *this;
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T> base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator-(std::size_t n) const
{
	return Iterator(m_pos - n, m_vData);
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T> base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator-(int n) const
{
	return Iterator(m_pos - n, m_vData);
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
IT_T * base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator[](std::size_t i) const
{
	return & m_vData[*(m_pos + i) * DIM];
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
IT_T * base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator[](int i) const
{
	return & m_vData[*(m_pos + i) * DIM];
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
bool base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator==(const Iterator & other) const
{
	return m_pos == other.m_pos;
}

template <std::size_t DIM, typename I, typename T>
template <typename IT_I, typename IT_T>
inline
bool base_IndexedPoly<DIM, I, T>::Iterator<IT_I, IT_T>::operator!=(const Iterator & other) const
{
	return m_pos != other.m_pos;
}

}
}

#endif /* GPX_X_MODEL__BASE_INDEXEDPOLY_ITERATOR_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
