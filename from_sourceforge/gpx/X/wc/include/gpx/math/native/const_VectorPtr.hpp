/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_NATIVE_CONST_VECTORPTR_HPP_
#define GPX_X_MATH_NATIVE_CONST_VECTORPTR_HPP_

#include "_base_const_VectorPtr.hpp"
//#note: "const_VectorPtr.imp.hpp" included near eof

namespace gpx {
namespace math {
namespace native {

/**
 * N-dimensional vector on top of n-element const pointer.
 */
template <std::size_t N, typename T = real_t>
class const_VectorPtr : public base_const_VectorPtr<N, Vector, Matrix, T>
{
	typedef base_const_VectorPtr<N, Vector, Matrix, T> Parent;

	private:
		/**
		 * Assignment operator disabled.
		 */
//		const const_VectorPtr<N, T> & operator=(const const_VectorPtr<N, T> & other);

//	protected:
		/**
		 * Default constructor forbidden. Must set ptr.
		 */
//		const_VectorPtr();

	public:
		/**
		 * Conversion constructor.
		 * @param coords pointer to N-element array of coordinates.
		 */
		const_VectorPtr(const T * coords);

		/**
		 * Copy constructor. Sets coords pointer to other's pointer. Data is
		 * not copied like when using assignment operator!
		 * @param other other vector.
		 */
		const_VectorPtr(const const_VectorPtr<N, T> & other);

		//x() y() z() w()

};

//template <typename T>
//class const_VectorPtr<2, T> : public base_const_VectorPtr<2, T>
//{
//};

}
}
}

#include "const_VectorPtr.imp.hpp"

#endif /* GPX_X_MATH_NATIVE_CONST_VECTORPTR_HPP_ */

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
