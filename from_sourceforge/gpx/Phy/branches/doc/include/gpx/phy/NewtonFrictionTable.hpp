/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy_NEWTONFRICTIONTABLE_HPP_
#define GPX_Phy_NEWTONFRICTIONTABLE_HPP_

#include "../phy_config.hpp"
#include "NewtonFrictionData.hpp"
#include "material.hpp"

#include <gpx/platform.hpp>
#include <gpx/utils/Singleton.hpp>
#include <gpx/ext/UnorderedMap.hpp>

namespace gpx {
namespace phy {

class GPX_API NewtonFrictionTable : public utils::Singleton<NewtonFrictionTable>
{
	public:
		NewtonFrictionTable();

		virtual ~NewtonFrictionTable();

	public:
		NewtonFrictionData & lookup(material_t matA, material_t matB);

	private:
#ifdef GPX_EXT_UNORDERED_MAP
		typedef ext::UnorderedMap<material_t, NewtonFrictionData>::Type RowContainer;
		typedef ext::UnorderedMap<material_t, RowContainer>::Type DataContainer;
#else
		typedef std::map<material_t, NewtonFrictionData> RowContainer;
		typedef std::map<material_t, RowContainer> DataContainer;
#endif /* GPX_HASH_MAP_EXT */

	private:
		DataContainer m_data;
};

}
}

#endif /* GPX_Phy_NEWTONFRICTIONTABLE_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
