/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MODEL_FUNCTIONS_HPP_
#define GPX_X_MODEL_FUNCTIONS_HPP_

#include "Segment.hpp"


namespace gpx {
namespace model {

/**
 * Check orientation of triangle ABC. This functions checks orientation of triangle
 * on the plane (considering two first coordinates of given vertices).
 * @param T any type implementing subscript operations T[0], T[1].
 * @param A triangle's first vertex.
 * @param B triangle's second vertex.
 * @param C triangle's third vertex.
 * @return if curve is positively (or counterclockwise) oriented 1, if curve is
 * negatively (or clockwise) oriented -1. When curve is non-orientable
 * (points are collinear) function returns 0.
 */
template <typename T>
inline
int ccw(const T & A, const T & B, const T & C)
{
	real_t ccw = ((C[1] - A[1]) * (B[0] - A[0])) - ((B[1] - A[1]) * (C[0] - A[0]));
	return ccw > 0.0 ? 1 : ccw < 0.0 ? -1 : 0;
}

/**
 *  Check whenever two segments intersect (including endpoints).
 *  @param AB first segment.
 *  @param CD second segment.
 *  @return @p true when two segments intersect, @p false otherwise.
 */
template<typename T>
inline
bool intersect(const const_Segment<2, T> & AB, const const_Segment<2, T> & CD)
{
	return ccw(AB.first(), CD.first() , CD.second()) != ccw(AB.second(), CD.first(), CD.second())
		&& ccw(AB.first(), AB.second(), CD.first()) != ccw(AB.first(), AB.second(), CD.second());
}

/**
 *  Check whenever two segments intersect (excluding endpoints).
 *  @param AB first segment.
 *  @param CD second segment.
 *  @return @p true when two segments intersect, @p false otherwise.
 */
template<typename T>
inline
bool xintersect(const const_Segment<2, T> & AB, const const_Segment<2, T> & CD)
{
	return ccw(AB.first(), CD.first() , CD.second()) == -ccw(AB.second(), CD.first(), CD.second())
		&& ccw(AB.first(), AB.second(), CD.first()) == -ccw(AB.first(), AB.second(), CD.second());
}

/**
 * Calculate intersection point. Calculates intersection point of two lines. Lines are
 * given in form at + b, where @a t is an independent parametric variable, @a a is a slope
 * and b is an initial point.
 * @param a1 slope of the first line.
 * @param b1 initial point of the first line.
 * @param a2 slope of the second line.
 * @param b2 initial point of the second line.
 * @return intersection point. If no intersection point exists result is undefined.
 */
template<typename T>
inline
math::Vector<2, T> intersection(const math::const_VectorPtr<2, T> & a1, const math::const_VectorPtr<2, T> & b1,
							    const math::const_VectorPtr<2, T> & a2, const math::const_VectorPtr<2, T> & b2)
{
	//solving equations:
	//a1(0) s - a2(0) t = b2(0) - b1(0)
	//a1(1) s - a2(1) t = b2(1) - b1(1)
	//this is basic implementation, using Cramer's rules.
	//@todo possibly find better algorithm.

	real_t det = (a1[1] * a2[0]) - (a1[0] * a2[1]);

	//it doesn't matter if s or t is used (this redundancy of information gives a premise that better algorithm may exist)
	real_t detS = ((b2[1] - b1[1]) * a2[0]) - ((b2[0] - b1[0]) * a2[1]);
//	real_t detT = ((b2[1] - b1[1]) * a1[0]) - ((b2[0] - b1[0]) * a1[1]);
	real_t s = detS/det;
//	real_t t = detT/det;
//	std::cout << "intersection() s: (" << a1[0] * s + b1[0] << ", " << a1[1] * s + b1[1] << ")" << std::endl;
//	std::cout << "intersection() t: (" << a2[0] * t + b2[0] << ", " << a2[1] * t + b2[1] << ")" << std::endl;
	return math::Vector<2>(a1[0] * s + b1[0], a1[1] * s + b1[1]);
}


}
}


#endif /* GPX_X_MODEL_FUNCTIONS_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
