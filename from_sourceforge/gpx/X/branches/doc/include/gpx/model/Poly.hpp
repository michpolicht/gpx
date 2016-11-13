/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MODEL_POLY_HPP_
#define GPX_X_MODEL_POLY_HPP_

#include "Segment.hpp"
#include "VertexData.hpp"
#include "_base_UnindexedPoly.hpp"
#include "_base_IndexedPoly.hpp"


namespace gpx {
namespace model {


/**
 * Index type.
 *
 * @todo add support for index types USHORT and UCHAR.
 */
enum index_t {NONE, UCHAR, USHORT, UINT};

/**
 * Polygon.
 */
template <std::size_t DIM, index_t INDEX = NONE, typename T = real_t>
class Poly
{
	private:
		/**
		 * Default constructor.
		 */
		Poly(); // only specializations are allowed.
};


/**
 * Unindexed polygon.
 */
template <std::size_t DIM, typename T>
class Poly<DIM, NONE, T> : public base_UnindexedPoly<DIM, T>
{
	private:
		typedef base_UnindexedPoly<DIM, T> Parent;

	public:
		Poly(const VertexData<DIM, T> & vdata);
};

template <std::size_t DIM, typename T>
inline
Poly<DIM, NONE, T>::Poly(const VertexData<DIM, T> & vdata):
	Parent(vdata)
{
}



/**
 * Polygon with index of type unsigned int.
 */
template <std::size_t DIM, typename T>
class Poly<DIM, UINT, T> : public base_IndexedPoly<DIM, unsigned int, T>
{
	public:
		typedef unsigned int index_t;

	private:
		typedef base_IndexedPoly<DIM, index_t, T> Parent;

	public:
		Poly(index_t * indices, std::size_t size, const VertexData<DIM, T> & vdata);

		Poly(const typename Parent::Index & index, const VertexData<DIM, T> & vdata);
};

template <std::size_t DIM, typename T>
inline
Poly<DIM, UINT, T>::Poly(index_t * indices, std::size_t size, const VertexData<DIM, T> & vdata):
	Parent(indices, size, vdata)
{
}

template <std::size_t DIM, typename T>
inline
Poly<DIM, UINT, T>::Poly(const typename Parent::Index & index, const VertexData<DIM, T> & vdata):
	Parent(index, vdata)
{
}


}
}


#endif /* GPX_X_MODEL_POLY_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
