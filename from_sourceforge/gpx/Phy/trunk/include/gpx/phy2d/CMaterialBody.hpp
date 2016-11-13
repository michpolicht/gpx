/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_CMATERIALBODY_HPP_
#define GPX_Phy2d_CMATERIALBODY_HPP_

#include "MaterialBody.hpp"
#include "ICNewtonMovable.hpp"
#include "ICDragnDrop.hpp"

#include <gpx/platform.hpp>

namespace gpx {
namespace phy2d {

/**
 * Colliding material body.
 */
class GPX_API CMaterialBody : public MaterialBody,
							  public virtual ICDragnDrop,
							  public virtual ICNewtonMovable
{
	public:
		/**
		 * Constructor.
		 * @param m mass.
		 * @param material material id.
		 */
		CMaterialBody(real_t m, phy::material_t material = 0);

		/**
		 * Destructor.
		 */
		virtual ~CMaterialBody();

	public:
		phy::material_t material() const;

		void setMaterial(phy::material_t material);

	public:
		//ICDragnDrop
		virtual void performDragnDrop(DragnDropCollider * collider);

		//ICNewtonMovable
		void mountImpulse(const Impulse & impulse, const math::const_VectorPtr<2> & point = math::Vector<2>(0.0, 0.0));

		//ICNewtonMovable
		void roundAwayImpulse(Impulse & impulse, const NewtonCollisionData & data, bool normal);

		//ICNewton
		math::Vector<2> aCoef(const NewtonCollisionBase & bData) const;

		//ICNewton
		math::Vector<2> bCoef(real_t p, const NewtonCollisionBase & bData) const;

		//ICNewton
		phy::material_t material(element_t element) const;

	private:
		phy::material_t m_material;
};

}
}

#endif /* GPX_Phy2d_CMATERIALBODY_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
