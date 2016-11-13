/**
 * @file
 * @brief Platform-specific options and basic setup.
 */

//note: phycfg.hpp relies on current include guards names
#ifndef GPX_X_PLATFORM_HPP_
#define GPX_X_PLATFORM_HPP_

#include <cstddef>
#include <cassert>

#define GPX_VERSION_ "milestone11"

#ifndef NDEBUG
	#define GPX_VERSION GPX_VERSION_"-debug"
#else
	#define GPX_VERSION GPX_VERSION_
#endif /* NDEBUG */


#ifdef GPX_DYNAMIC
	#ifdef _WIN32
		#ifdef GPX_BUILD
			//export symbols to dll
			#define GPX_API __declspec(dllexport)
		#else
			//using functions from dll
			#define GPX_API __declspec(dllimport)
		#endif /* GPX_BUILD */
	#else
		#define GPX_API
	#endif /* _WIN32 */
#else
	#define GPX_API
#endif /* GPX_DYNAMIC */


namespace gpx {

//define real type's desired precision
#ifdef GPX_REAL
	typedef GPX_REAL real_t;
#else
	typedef double real_t;
#endif /* GPX_REAL */

}

#endif /* GPX_X_PLATFORM_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
