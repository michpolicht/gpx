/**
 * @file
 * @brief Platform-specific options and basic setup.
 */

//note: phycfg.hpp relies on current include guards names
#ifndef GPX_X_PLATFORM_HPP_
#define GPX_X_PLATFORM_HPP_

#include <cstddef>
#include <cassert>
#include <limits>

#define GPX_VERSION_ "milestone13"

#ifndef NDEBUG
	#define GPX_VERSION GPX_VERSION_"-debug"
#else
	#define GPX_VERSION GPX_VERSION_

	#ifndef GPX_INTROSPECT
		#define GPX_NO_INTROSPECT
	#endif

	#ifndef GPX_LOG
		#define GPX_NO_LOG
	#endif
#endif


#ifdef GPX_DYNAMIC
	#ifdef _WIN32
		#ifdef GPX_BUILD
			//export symbols to dll
			#define GPX_API __declspec(dllexport)
		#else
			//using functions from dll
			#define GPX_API __declspec(dllimport)
		#endif
	#else
		#define GPX_API
	#endif
#else
	#define GPX_API
#endif

//math library back-end (basic) @todo: tnt_jama, eigen, armadillo...
#ifndef GPX_X_MATH_BACKEND_HEADER
	#define GPX_X_MATH_BACKEND_HEADER "basic/backend.hpp"
#endif

namespace gpx {

//define real type's desired precision
#ifdef GPX_REAL
	typedef GPX_REAL real_t;
#else
	typedef double real_t;
#endif

//machine epsilon multiplier
#ifndef GPX_EPS_MULT
	#define GPX_EPS_MULT static_cast<real_t>(2048.0)
#endif

//machine epsilon * 0.5 is the smallest possible epsilon for which GPX approximation functions make sense
const real_t EPS = std::numeric_limits<real_t>::epsilon() * static_cast<real_t>(0.5) * GPX_EPS_MULT;

}

//macro to stop bitching about unused parameter
#define GPX_UNUSED(x) (void)(x)

#endif

//(c)MP: Copyright © 2014, Michal Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
