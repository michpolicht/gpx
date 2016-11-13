/**
 * @file
 * @brief .
 */

#include "_Poly_warning.hpp"


#ifndef GPX_X_MODEL__BASE_INDEXEDPOLY_HPP_
#define GPX_X_MODEL__BASE_INDEXEDPOLY_HPP_

//#note: "_base_IndexedPoly_Index.hpp" included near eof
//#note: "_base_IndexedPoly_Iterator.hpp" included near eof


namespace gpx {
namespace model {


/**
 * Indexed polygon.
 */
template <std::size_t DIM, typename I, typename T>
class base_IndexedPoly
{
	protected:
		template <typename IT_I, typename IT_T>
		class Iterator;

	public:
		class Index;
		typedef Iterator<I, T> iterator;
		typedef Iterator<I, const T> const_iterator;

	protected:
		Index m_index;
		VertexData<DIM, T> m_vdata;

	public:
		/**
		 * Constructor.
		 * @param index index of vertices.
		 * @param vdata vertex data.
		 */
		base_IndexedPoly(const Index & index, const VertexData<DIM, T> & vData);

		/**
		 * Constructor.
		 * @param indices indices.
		 * @param size indices size (number of indices).
		 * @param vdata vertex data.
		 */
		base_IndexedPoly(I * indices, std::size_t size, const VertexData<DIM, T> & vdata);

	public:
		Index & index();

		const Index & index() const;

		VertexData<DIM, T> & vdata();

		const VertexData<DIM, T> & vdata() const;

		/**
		 * Iterator begin.
		 * @return iterator begin.
		 */
		iterator begin();

		/**
		 * Const iterator begin.
		 * @return const iterator begin.
		 */
		const_iterator begin() const;

		/**
		 * Iterator end.
		 * @return iterator end.
		 */
		iterator end();

		/**
		 * Const iterator end.
		 * @return const iterator end.
		 */
		const_iterator end() const;
};



template <std::size_t DIM, typename I, typename T>
inline
base_IndexedPoly<DIM, I, T>::base_IndexedPoly(const Index & index, const VertexData<DIM, T> & vData):
	m_index(index),
	m_vdata(vData)
{
}

template <std::size_t DIM, typename I, typename T>
inline
base_IndexedPoly<DIM, I, T>::base_IndexedPoly(I * indices, std::size_t size, const VertexData<DIM, T> & vData):
	m_index(indices, size),
	m_vdata(vData)
{
}

template <std::size_t DIM, typename I, typename T>
inline
typename base_IndexedPoly<DIM, I, T>::Index & base_IndexedPoly<DIM, I, T>::index()
{
	return m_index;
}

template <std::size_t DIM, typename I, typename T>
inline
const typename base_IndexedPoly<DIM, I, T>::Index & base_IndexedPoly<DIM, I, T>::index() const
{
	return m_index;
}

template <std::size_t DIM, typename I, typename T>
inline
VertexData<DIM, T> & base_IndexedPoly<DIM, I, T>::vdata()
{
	return m_vdata;
}

template <std::size_t DIM, typename I, typename T>
inline
const VertexData<DIM, T> & base_IndexedPoly<DIM, I, T>::vdata() const
{
	return m_vdata;
}

template <std::size_t DIM, typename I, typename T>
inline
typename base_IndexedPoly<DIM, I, T>::iterator base_IndexedPoly<DIM, I, T>::begin()
{
	return iterator(m_index.ptr, m_vdata.data());
}

template <std::size_t DIM, typename I, typename T>
inline
typename base_IndexedPoly<DIM, I, T>::const_iterator base_IndexedPoly<DIM, I, T>::begin() const
{
	return const_iterator(m_index.ptr, m_vdata.data());
}

template <std::size_t DIM, typename I, typename T>
inline
typename base_IndexedPoly<DIM, I, T>::iterator base_IndexedPoly<DIM, I, T>::end()
{
	return iterator(m_index.ptrEnd);
}

template <std::size_t DIM, typename I, typename T>
inline
typename base_IndexedPoly<DIM, I, T>::const_iterator base_IndexedPoly<DIM, I, T>::end() const
{
	return const_iterator(m_index.ptrEnd);
}

}
}

#include "_base_IndexedPoly_Index.hpp"
#include "_base_IndexedPoly_Iterator.hpp"


#endif /* GPX_X_MODEL__BASE_INDEXEDPOLY_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
