/**
 * @file
 * @brief .
 */

#ifndef GPX_X_EXT_UNORDEREDMAP_HPP_
#define GPX_X_EXT_UNORDEREDMAP_HPP_

#ifdef GPX_EXT_UNORDERED_MAP
	#include GPX_UNORDERED_MAP_HEADER

	namespace gpx {
	namespace ext {

	/**
	 * Unordered map type wrapper. In order to use this class following macros must be defined:
	 * 	- @p GPX_UNORDERED_MAP_HEADER - STL header providing unordered map class.
	 * 	- @p GPX_EXT_UNORDERED_MAP - fully qualified STL unordered map class name.
	 * 	- @p GPX_EXT_HASH_FUNC - fully qualified STL hash function name.
	 */
	template<class KEY,
			 class VALUE,
			 class HASH_FUNC = GPX_EXT_HASH_FUNC<KEY>,
			 class PRED = std::equal_to<KEY> >
			//allocator parameter is currently not used since it differs between libraries
	class UnorderedMap
	{
		public:
			typedef GPX_EXT_UNORDERED_MAP<KEY, VALUE, HASH_FUNC, PRED> Type;
	};

	}
	}
#else
	#include <map>
	#pragma message("warning: unordered_map not supported")
#endif /* GPX_EXT_UNORDERED_MAP */

#endif /* GPX_X_EXT_UNORDEREDMAP_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
