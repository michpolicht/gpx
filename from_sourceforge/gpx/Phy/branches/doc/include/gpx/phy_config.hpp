/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy_PHY_CONFIG_HPP_
#define GPX_Phy_PHY_CONFIG_HPP_

#include "phy_version.hpp"

/* Macros affecting gpx::ext::UnorderedSet */

/* Define STL unordered map header (e.g., <unordered_map>). */
#define GPX_UNORDERED_MAP_HEADER <ext/hash_map>

/* Define STL unordered map class name (e.g., std::unordered_map). */
#define GPX_EXT_UNORDERED_MAP __gnu_cxx::hash_map

/* Macros affecting gpx::ext::UnorderedMap */

/* Define STL unordered set header (e.g., <unordered_set>). */
#define GPX_UNORDERED_SET_HEADER <ext/hash_set>

/* Define STL unordered set class name (e.g., std::unordered_set). */
#define GPX_EXT_UNORDERED_SET __gnu_cxx::hash_set


/* Macros affecting gpx::ext::UnorderedMap and gpx::ext::UnorderedSet */

/* Define STL hash function name (e.g., std::hash). */
#define GPX_EXT_HASH_FUNC __gnu_cxx::hash


/* Assertions. */

#ifdef GPX_X_EXT_UNORDEREDSET_HPP_
#error "gpx/ext/UnorderedSet.hpp included before phy_config.hpp"
#endif /* GPX_X_EXT_UNORDEREDSET_HPP_ */

#ifdef GPX_X_EXT_UNORDEREDMAP_HPP_
#error "gpx/ext/UnorderedMap.hpp included before phy_config.hpp"
#endif /* GPX_X_EXT_UNORDEREDMAP_HPP_ */

#endif /* GPX_Phy_PHY_CONFIG_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
