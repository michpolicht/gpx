/*
 * constants.h
 *
 *      Author: doc
 */

#ifndef GPX_X_MATH_CONSTANTS_HPP_
#define GPX_X_MATH_CONSTANTS_HPP_

#include <cmath>

#include "../platform.hpp"

namespace gpx {
namespace math {

//	const real_t PI = 3.1415926535897932384626433832795;
	const real_t PI = 4.0l * std::atan(1.0l);

	enum sizeNames_t {
		SIZE_DYNAMIC = 0,
	//	SIZE_MAX = std::numeric_limits<std::size_t>::max()	///< @todo this will work in C++0x.
	};

	enum eqFlagNames_t {
		EQ_GENERAL = 0
	};

}
}

#endif /* GPX_X_MATH_CONSTANTS_HPP_ */
