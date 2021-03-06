/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_FUNCTIONS_HPP_
#define GPX_X_MATH_FUNCTIONS_HPP_

#include <algorithm>

#include "constants.hpp"

namespace gpx {
namespace math {

/**
 * Convert radians to degrees.
 * @param rad radians.
 * @return degrees.
 */
inline
real_t radToDeg(real_t rad)
{
	return (180.0 / PI) * rad;
}

/**
 * Convert degrees to radians.
 * @param deg degrees.
 * @return radians.
 */
inline
real_t degToRad(real_t deg)
{
	return (PI / 180.0) * deg;
}

/**
 * Compute sinus and cosinus together. Uses native FPU instructions to optimize performance.
 * @param angle angle in radians.
 * @param sina sinus of the angle. Pointer to real_t variable where sinus shall be stored.
 * @param cosa cosinus of the angle. Pointer to real_t variable where cosinus shall be stored.
 */
inline
void sincos(real_t angle, real_t * sina, real_t * cosa)
{
	#if defined(__GNUC__) && defined(__i386__)
		real_t sinv, cosv;
		asm("fsincos" : "=t" (cosv), "=u" (sinv) : "0" (angle));
		* sina = sinv;
		* cosa = cosv;
	#else
		//TODO add support for other compilers and platforms
		#pragma message("unoptimized code for sincos")
		* sina = std::sin(angle);
		* cosa = std::cos(angle);
	#endif
}



//FP comparison functions, based on Donald E. Knuth "Art of computer programming" [P 4.2.2 Vol2]

/**
 * Approximately equal. Compares real numbers @a r1, @a r2.
 * @param r1 first number to compare.
 * @param r2 second number to compare.
 * @return @p true when @a r1 and @a r2 are approximately equal, @p false otherwise.
 *
 * @see ale().
 */
inline
bool ape(real_t r1, real_t r2)
{
	int exp1, exp2;
	std::frexp(r1, & exp1);
	std::frexp(r2, & exp2);

	return std::abs(r2 - r1) <= std::ldexp(EPS, std::max(exp1, exp2));
}

/**
 * Almost equal. Compares real numbers @a r1, @a r2. Function similar to ape(), however ale()
 * is slightly stronger than ape() (@a r1 and @a r2 must be slightly closer to each other to
 * manifest equality).
 * @param r1 first number to compare.
 * @param r2 second number to compare.
 * @return @p true when @a r1 and @a r2 are almost equal, @p false otherwise.
 *
 * @see ape().
 */
inline
bool ale(real_t r1, real_t r2)
{
	int exp1, exp2;
	std::frexp(r1, & exp1);
	std::frexp(r2, & exp2);

	return std::abs(r2 - r1) <= std::ldexp(EPS, std::min(exp1, exp2));
}

/**
 * Considerably less than.
 * @param r1 first number to compare.
 * @param r2 second number to compare.
 * @return @p true when @a r1 is considerably less than @a r2, @p false otherwise.
 */
inline
bool clt(real_t r1, real_t r2)
{
	int exp1, exp2;
	std::frexp(r1, & exp1);
	std::frexp(r2, & exp2);

	return r1 - r2 < std::ldexp(EPS, std::max(exp1, exp2));
}

/**
 * Considerably greater than.
 * @param r1 first number to compare.
 * @param r2 second number to compare.
 * @return @p true when @a r1 is considerably greater than @a r2, @p false otherwise.
 */
inline
bool cgt(real_t r1, real_t r2)
{
	int exp1, exp2;
	std::frexp(r1, & exp1);
	std::frexp(r2, & exp2);

	return r1 - r2 > std::ldexp(EPS, std::max(exp1, exp2));
}

//additional FP functions

/**
 * Epsilon for number. Get epsilon for real number @a r, that means smallest number which
 * added to @a r changes @a r 's value.
 * @param r real number.
 * @return smallest number which added to @a r changes @a r 's value. If @a r is positive
 * returned number is positive, otherwise it is negative.
 *
 * @see absEps().
 */
inline
real_t eps(real_t r)
{
	int exp;
	std::frexp(r, & exp);
	return std::ldexp(std::signbit(r) ? -EPS : EPS, exp);
}

/**
 * Absolute epsilon for number. Work in similar way to eps() function, except that
 * absolute value is returned instead of signed one.
 * @param r real number.
 * @return smallest number which added to @a r changes @a r 's value. Always non-negative
 * value is returned.
 *
 * @see eps().
 */
inline
real_t absEps(real_t r)
{
	int exp;
	std::frexp(r, & exp);
	return std::ldexp(EPS, exp);
}

}
}

#endif /* GPX_X_MATH_FUNCTIONS_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
