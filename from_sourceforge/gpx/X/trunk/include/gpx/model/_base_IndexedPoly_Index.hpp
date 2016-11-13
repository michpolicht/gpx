/**
 * @file
 * @brief .
 */

#include "_Poly_warning.hpp"

#ifndef GPX_X_MODEL__BASE_INDEXEDPOLY_INDEX_HPP_
#define GPX_X_MODEL__BASE_INDEXEDPOLY_INDEX_HPP_


namespace gpx {
namespace model {


/**
 * Index of indexed polygon. Binds vertices into faces forming an element.
 */
template <std::size_t DIM, typename I, typename T>
class base_IndexedPoly<DIM, I, T>::Index
{
	friend class base_IndexedPoly<DIM, I, T>;

	public:
		typedef I * iterator;
		typedef const I * const_iterator;

	protected:
		I * m_ptr;
		I * m_ptrEnd;

	public:
		/**
		 * Default constructor.
		 */
		Index();

		/**
		 * Constructor.
		 * @param data data containing indices.
		 * @param size data size (number of indices).
		 */
		Index(I * data, std::size_t size);

		/**
		 * Subscript operator.
		 * @param i subscript value.
		 * @return index specified by @a i.
		 */
		I & operator[](std::size_t i);

		/**
		 * Const version of subscript operator.
		 * @param i subscript value.
		 * @return index specified by @a i.
		 */
		I operator[](std::size_t i) const;

		void setData(I * data, std::size_t size);

		I * data();

		const I * data() const;

		iterator begin();

		const_iterator begin() const;

		iterator end();

		const_iterator end() const;

		std::size_t size() const;

		std::size_t bsize() const;
};


template <std::size_t DIM, typename I, typename T>
inline
base_IndexedPoly<DIM, I, T>::Index::Index():
	m_ptr(0),
	m_ptrEnd(0)
{
}

template <std::size_t DIM, typename I, typename T>
inline
base_IndexedPoly<DIM, I, T>::Index::Index(I * data, std::size_t size):
	m_ptr(data),
	m_ptrEnd(data + size)
{
}

template <std::size_t DIM, typename I, typename T>
inline
I & base_IndexedPoly<DIM, I, T>::Index::operator[](std::size_t i)
{
	assert(m_ptr + i < m_ptrEnd); //out of bounds
	return m_ptr[i];
}

template <std::size_t DIM, typename I, typename T>
inline
I base_IndexedPoly<DIM, I, T>::Index::operator[](std::size_t i) const
{
	assert(m_ptr + i < m_ptrEnd); //out of bounds
	return m_ptr[i];
}

template <std::size_t DIM, typename I, typename T>
inline
void base_IndexedPoly<DIM, I, T>::Index::setData(I * data, std::size_t size)
{
	m_ptr = data;
	m_ptrEnd = data + size;
}

template <std::size_t DIM, typename I, typename T>
inline
I * base_IndexedPoly<DIM, I, T>::Index::data()
{
	return m_ptr;
}

template <std::size_t DIM, typename I, typename T>
inline
const I * base_IndexedPoly<DIM, I, T>::Index::data() const
{
	return m_ptr;
}

template <std::size_t DIM, typename I, typename T>
inline
typename base_IndexedPoly<DIM, I, T>::Index::iterator base_IndexedPoly<DIM, I, T>::Index::begin()
{
	return m_ptr;
}

template <std::size_t DIM, typename I, typename T>
inline
typename base_IndexedPoly<DIM, I, T>::Index::const_iterator base_IndexedPoly<DIM, I, T>::Index::begin() const
{
	return m_ptr;
}

template <std::size_t DIM, typename I, typename T>
inline
typename base_IndexedPoly<DIM, I, T>::Index::iterator base_IndexedPoly<DIM, I, T>::Index::end()
{
	return m_ptrEnd;
}

template <std::size_t DIM, typename I, typename T>
inline
typename base_IndexedPoly<DIM, I, T>::Index::const_iterator base_IndexedPoly<DIM, I, T>::Index::end() const
{
	return m_ptrEnd;
}

template <std::size_t DIM, typename I, typename T>
inline
std::size_t base_IndexedPoly<DIM, I, T>::Index::size() const
{
	return m_ptrEnd - m_ptr;
}

template <std::size_t DIM, typename I, typename T>
inline
std::size_t base_IndexedPoly<DIM, I, T>::Index::bsize() const
{
	return size() * sizeof(I);
}

}
}


#endif /* GPX_X_MODEL__BASE_INDEXEDPOLY_INDEX_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
