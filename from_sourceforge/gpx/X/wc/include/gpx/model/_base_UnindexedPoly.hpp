/**
 * @file
 * @brief .
 */

#include "_Poly_warning.hpp"

#ifndef GPX_X_MODEL__BASE_UNINDEXEDPOLY_HPP_
#define GPX_X_MODEL__BASE_UNINDEXEDPOLY_HPP_


namespace gpx {
namespace model {

/**
 * Unindexed polygon.
 */
template <std::size_t DIM, typename T>
class base_UnindexedPoly
{
//	public:
//		typedef std::pair<T *, T *> Segment;

	protected:
		template <typename IT_T>
		class LineLoop;	//@todo implement?

	public:
		typedef typename VertexData<DIM, T>::iterator iterator;
		typedef typename VertexData<DIM, T>::const_iterator const_iterator;

	protected:
		VertexData<DIM, T> m_vdata;

	public:
		/**
		 * Constructor.
		 * @param vData vertex data.
		 */
		base_UnindexedPoly(const VertexData<DIM, T> & vData);

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



template <std::size_t DIM, typename T>
inline
base_UnindexedPoly<DIM, T>::base_UnindexedPoly(const VertexData<DIM, T> & vData):
	m_vdata(vData)
{
}

template <std::size_t DIM, typename T>
inline
VertexData<DIM, T> & base_UnindexedPoly<DIM, T>::vdata()
{
	return m_vdata;
}

template <std::size_t DIM, typename T>
inline
const VertexData<DIM, T> & base_UnindexedPoly<DIM, T>::vdata() const
{
	return m_vdata;
}

template <std::size_t DIM, typename T>
inline
typename base_UnindexedPoly<DIM, T>::iterator base_UnindexedPoly<DIM, T>::begin()
{
	return m_vdata.begin();
}

template <std::size_t DIM, typename T>
inline
typename base_UnindexedPoly<DIM, T>::const_iterator base_UnindexedPoly<DIM, T>::begin() const
{
	return m_vdata.begin();
}

template <std::size_t DIM, typename T>
inline
typename base_UnindexedPoly<DIM, T>::iterator base_UnindexedPoly<DIM, T>::end()
{
	return m_vdata.end();
}

template <std::size_t DIM, typename T>
inline
typename base_UnindexedPoly<DIM, T>::const_iterator base_UnindexedPoly<DIM, T>::end() const
{
	return m_vdata.end();
}

}
}


#endif /* GPX_X_MODEL__BASE_UNINDEXEDPOLY_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
