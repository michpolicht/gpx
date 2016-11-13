/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_CNEWTON_PMEPP2_S_ICFIXED_HPP_
#define GPX_Phy2d_CNEWTON_PMEPP2_S_ICFIXED_HPP_

#include "Cluster.hpp"
#include "ACoefsMapper.hpp"
#include "BCoefsMapper.hpp"
#include "../../ILocalFrame.hpp"
#include "../../../phy/material.hpp"

namespace gpx {
namespace phy2d {
namespace cnewton {
namespace pmepp2_s {

/**
 * Basic Newton colliding interface.
 */
class ICFixed : public virtual ILocalFrame,
				public virtual cdetect::interseg::ICPolyGroup
{
	public:
		/**
		 * Get "a" coefficients. These are coefficients in form aFdt=b, where Fdt is an impulse.
		 * They have to be given in global coordinates. Separate paper shall explain how to
		 * calculate them.
		 */
		virtual void aCoefs(const DetectionData & dData, math::Matrix<> & a) const = 0;

		/**
		 * Get "b" coefficients. These are coefficients in form aFdt=b, where Fdt is an impulse.
		 * They have to be given in global coordinates. Separate paper shall explain how to
		 * calculate them.
		 */
		virtual void bCoefs(const DetectionData & dData, math::Vector<> & b) const = 0;

		/**
		 * Get material id.
		 * @param element element index.
		 */
//		virtual phy::material_t material(element_t element) const = 0;

	protected:
		~ICFixed() {}
};

}
}
}
}

#endif /* GPX_Phy2d_CNEWTON_PMEPP2_S_ICFIXED_HPP_ */

//(c)MP: Copyright © 2013, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
