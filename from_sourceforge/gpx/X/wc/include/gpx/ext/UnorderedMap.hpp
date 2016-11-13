/**
 * @file
 * @brief .
 */

#ifndef GPX_X_EXT_UNORDEREDMAP_HPP_
#define GPX_X_EXT_UNORDEREDMAP_HPP_

#ifdef GPX_EXT_UNORDERED_MAP
	#include GPX_UNORDERED_MAP_HEADER
#else
	#include <map>
	#pragma message("warning: unordered_map not supported")
#endif /* GPX_EXT_UNORDERED_MAP */

namespace gpx {
namespace ext {

/**
 * Unordered map type wrapper. In order to use this class following macros must be defined:
 * 	- @p GPX_UNORDERED_MAP_HEADER - STL header providing unordered map class.
 * 	- @p GPX_EXT_UNORDERED_MAP - fully qualified STL unordered map class name.
 * 	- @p GPX_EXT_HASH_FUNC - fully qualified STL hash function name.
 * 	.
 * If @p GPX_EXT_UNORDERED_MAP macro is not defined UnorderedSet falls back to std::map<KEY, VALUE>.
 */
#ifdef GPX_EXT_UNORDERED_MAP
	template<class KEY,
			 class VALUE,
			 class HASH_FUNC = GPX_EXT_HASH_FUNC<KEY>,
			 class PRED = std::equal_to<KEY> >
			//allocator parameter is currently not used since it differs between libraries
	class UnorderedMap : private GPX_EXT_UNORDERED_MAP<KEY, VALUE, HASH_FUNC, PRED>
	{
		public:
			typedef GPX_EXT_UNORDERED_MAP<KEY, VALUE, HASH_FUNC, PRED> Parent;
			typedef	UnorderedMap<KEY, VALUE, HASH_FUNC, PRED> Type;
#else
	//fallback to std::map
	template<class KEY,
			 class VALUE,
			 class HASH_FUNC_IGNORED = KEY,
			 class PRED_IGNORED = KEY>
	class UnorderedMap : private std::map<KEY, VALUE>
	{
		public:
			typedef std::map<KEY, VALUE> Parent;
			typedef	UnorderedMap<KEY, VALUE, HASH_FUNC_IGNORED, PRED_IGNORED> Type;
#endif /* GPX_EXT_UNORDERED_MAP */

			typedef typename Parent::key_type key_type;
			typedef typename Parent::mapped_type mapped_type;
			typedef typename Parent::value_type value_type;
			typedef typename Parent::reference reference;
			typedef typename Parent::const_reference const_reference;
			typedef typename Parent::iterator iterator;
			typedef typename Parent::const_iterator const_iterator;
			typedef typename Parent::size_type size_type;
			typedef typename Parent::difference_type difference_type;
			typedef typename Parent::pointer pointer;
			typedef typename Parent::const_pointer const_pointer;

		public:
			//generated default ctor ok
			//generated copy ctor ok
			//generated operator = ok

			using Parent::empty;
			using Parent::size;
			using Parent::max_size;

			using Parent::insert;
			using Parent::erase;
			using Parent::clear;
			void swap(Type & other)	{ Parent::swap(other); }

			using Parent::find;
			using Parent::count;
			using Parent::equal_range;

			using Parent::begin;
			using Parent::end;

			using Parent::operator [];
	};

}
}

#endif /* GPX_X_EXT_UNORDEREDMAP_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
