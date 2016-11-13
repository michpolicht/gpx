/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_BASIC_VECTORPTRSTORAGE_HPP_
#define GPX_X_MATH_BASIC_VECTORPTRSTORAGE_HPP_

//#note: "VectorPtrStorage.imp.hpp" included near eof

#include <algorithm>	//std::swap

namespace gpx {
namespace math {
namespace basic {

template <std::size_t N, typename T>
class VectorPtrStorage
{
	protected:
		VectorPtrStorage(T * coords);

		//generated copy ctor OK
		//VectorPtrStorage(const VectorPtrStorage<N, T> & other);

	protected:
		//generated copy assignment OK
		//operator =(const VectorPtrStorage<N, T> & other);

		std::size_t size() const;

		void setSize(std::size_t size);

		const T * ptr() const;

		T * ptr();

		T coord(std::size_t i) const;

		T & coord(std::size_t i);

		void swap(std::size_t c1, std::size_t c2);

	private:
		T * const m_ptr;
};

template <typename T>
class VectorPtrStorage<gpx::math::SIZE_DYNAMIC, T>
{
	protected:
		VectorPtrStorage(T * coords, std::size_t size);

		//generated copy ctor OK
		//VectorPtrStorage(const VectorPtrStorage<N, T> & other);

	protected:
		//generated copy assignment OK
		//operator =(const VectorPtrStorage<N, T> & other);

		std::size_t size() const;

		void setSize(std::size_t size);

		const T * ptr() const;

		T * ptr();

		void setPtr(T * ptr);

		void setPtr(T * ptr, std::size_t size);

		T coord(std::size_t i) const;

		T & coord(std::size_t i);

		void swap(std::size_t c1, std::size_t c2);

	private:
		T * m_ptr;
		std::size_t m_size;
};

}
}
}

#include "VectorPtrStorage.imp.hpp"

#endif /* GPX_X_MATH_BASIC_VECTORPTRSTORAGE_HPP_ */

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
