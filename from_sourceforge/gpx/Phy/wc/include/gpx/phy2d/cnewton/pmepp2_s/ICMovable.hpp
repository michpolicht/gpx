/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_CNEWTON_PMEPP2_S_ICMOVABLE_HPP_
#define GPX_Phy2d_CNEWTON_PMEPP2_S_ICMOVABLE_HPP_

#include "ICFixed.hpp"
#include "../../Force.hpp"
#include "../../../phy/IMovable.hpp"

namespace gpx {
namespace phy2d {
namespace cnewton {
namespace pmepp2_s {

class ICMovable : public virtual ICFixed,
				  public virtual phy::IMovable
{
	public:
		/**
		 * Apply impulse. Impulse should immediately affect momentum(s).
		 * @param impulse impulse.
		 * @param point point.
		 */
		virtual void applyImpulse(const Impulse & impulse, math::const_PointRef<2> point) = 0;

		virtual void passLimit(const DetectionDataContainer & detections) = 0;

		/**
		 * Dislocate object.
		 * @param dislocation vector given in local coordinates.
		 * @return function should return @p true when dislocation was successful, otherwise
		 * it should return @p false. If @a disloc vector was to small to affect position
		 * of the object, function should set @a disloc value to reflect position of the
		 * object and return @false. Collider may then use @a disloc value as a hint and
		 * repeat dislocation procedure with slightly higher @a disloc value.
		 */
		virtual bool dislocate(math::Vector<2> & disloc) = 0;

		/**
		 * Round away impulses. Just before impulse is applied, object may modify its state
		 * according to prepared collision data. Function may be also used to round away
		 * impulse, fore example from machine epsilon truncation.
		 * @param impulse normal impulse.
		 * @param cData collision data.
		 */
//		virtual void roundAwayImpulses(Impulse & normal, Impulse & parallel, const CollisionData & cData) = 0;

		/**
		 * Round away normal impulse. Just before impulse is mounted, object may modify its state
		 * according to prepared collision data. Function may be also used to round away
		 * impulse from machine epsilon truncation.
		 * @param impulse normal impulse.
		 * @param cData collision data.
		 */
//		virtual void roundAwayNormal(Impulse & impulse, const CollisionData & cData) = 0;

		/**
		 * Round away parallel impulse. Just before impulse is mounted, object may modify its state
		 * according to prepared collision data. Function may be also used to round away
		 * impulse from machine epsilon truncation.
		 * @param impulse normal impulse.
		 * @param cData collision data.
		 */
//		virtual void roundAwayParallel(Impulse & impulse, const CollisionData & cData) = 0;

	protected:
		~ICMovable() {}
};

}
}
}
}

#endif /* GPX_Phy2d_CNEWTON_PMEPP2_S_ICMOVABLE_HPP_ */

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
