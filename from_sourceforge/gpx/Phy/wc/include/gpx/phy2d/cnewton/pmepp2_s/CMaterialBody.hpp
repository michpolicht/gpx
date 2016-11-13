/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_CNEWTON_PMEPP2_S_CMATERIALBODY_HPP_
#define GPX_Phy2d_CNEWTON_PMEPP2_S_CMATERIALBODY_HPP_

#include "ICMovable.hpp"
#include "../../MaterialBody.hpp"

#include <gpx/platform.hpp>

namespace gpx {
namespace phy2d {
namespace cnewton {
namespace pmepp2_s {

class GPX_API CMaterialBody : public phy2d::MaterialBody,
							  public virtual ICMovable
{
	typedef phy2d::MaterialBody Parent;

	public:
		CMaterialBody(real_t m, phy::material_t material = 0);

		virtual ~CMaterialBody();

	public:
		//ICFixed
		void aCoefs(const DetectionData & dData, math::Matrix<> & a) const;

		//ICFixed
		void bCoefs(const DetectionData & dData, math::Vector<> & b) const;

//		phy::material_t material() const;
//
//		void setMaterial(phy::material_t material);

		//ICMovable
		void applyImpulse(const Impulse & impulse, math::const_PointRef<2> point);

		//ICMovable
		void passLimit(const DetectionDataContainer & detections);

		//ICMovable
		bool dislocate(math::Vector<2> & disloc);

//		//ICMovable
//		void roundAwayImpulses(Impulse & normal, Impulse & parallel, const CollisionData & cData);
//
//		//ICMovable
//		math::Vector<2> aCoef(const DetectionData & dData) const;
//
//		//ICNewton
//		math::Vector<2> bCoef(const DetectionData & dData) const;
//
//		//ICNewton
//		phy::material_t material(element_t element) const;

	private:
		phy::material_t m_material;
};

}
}
}
}

#endif /* GPX_Phy2d_CNEWTON_PMEPP2_S_CMATERIALBODY_HPP_ */

//(c)MP: Copyright © 2011, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
