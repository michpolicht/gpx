/**
 * @file
 * @brief Algebraic structures header. This file binds (const_)Vector* and Matrix* class definitions
 * from separate headers. Include this file rather than any other (const_)Vector*.h or Matrix*.h.
 */

#ifndef GPX_X_MATH_STRUCTURES_HPP_
#define GPX_X_MATH_STRUCTURES_HPP_

#include <iostream>
#include <cmath>
#include <cstring> //mem* functions

#include "functions.hpp"

#include "Matrix.hpp"				//Matrix definitions
#include "const_VectorPtr.hpp"		//const_VectorPtr definitions
#include "VectorPtr.hpp"			//VectorPtr definitions
#include "Vector.hpp"				//Vector definitions
#include "MatrixImpl.hpp"			//implementation of Matrix
#include "const_VectorPtrImpl.hpp"	//implementation of const_VectorPtr
#include "VectorPtrImpl.hpp"		//implementation of VectorPtr
#include "VectorImpl.hpp"			//implementation of Vector



/**
 * Stream operator for Vector<N>.
 * @param s output stream.
 * @param v VectorPtr object.
 */
template <std::size_t N, typename T>
std::ostream & operator<<(std::ostream & s, const gpx::math::const_VectorPtr<N, T> & v)
{
	s.precision(gpx::math::const_VectorPtr<N, T>::PrintPrecision);
	s << "(";
	for (std::size_t i = 0; i < N-1; i++)
		s << v(i) << ", ";
	s << v(N-1) << ")" << std::endl;
	return s;
};

/**
 * Stream operator for Vector<N>.
 * @param s output stream.
 * @param v Vector2d object.
 */
template <std::size_t N, std::size_t M>
std::ostream & operator<<(std::ostream & s, const gpx::math::Matrix<N, M> & m)
{
	//find max digits num
	int maxBase = 0;
	for (std::size_t i = 0; i < N; i++)
		for (std::size_t j = 0; j < M; j++)
			if (m(i,j) != 0.0)
				maxBase = std::max(maxBase, static_cast<int>(std::log10(std::fabs(m(i,j)))));
	maxBase++;

	s.setf(std::ios::showpoint | std::ios::fixed);
	s.width(gpx::math::Matrix<N, M>::PrintWidth);
	s.precision(gpx::math::Matrix<N, M>::PrintWidth - maxBase - 2); //-2 for sign and point
	for (std::size_t i = 0; i < N; i++) {
		s << "[ ";
		for (std::size_t j = 0; j < M; j++)
			s << m(i,j) << " ";
		s << "]" << std::endl;
	}
    return s;
};

#endif /* GPX_X_MATH_STRUCTURES_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
