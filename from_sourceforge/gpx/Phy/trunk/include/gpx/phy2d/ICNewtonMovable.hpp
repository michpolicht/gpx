/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_CNEWTONMOVABLE_HPP_
#define GPX_Phy2d_CNEWTONMOVABLE_HPP_

#include "../phy/IMovable.hpp"
#include "ICNewton.hpp"
#include "Force.hpp"

namespace gpx {
namespace phy2d {

/**
 * Newton-colliding movable.
 */
class ICNewtonMovable: public virtual ICNewton,
					   public virtual phy::IMovable
{
	public:
		/**
		 * Mount impulse.
		 * @param impulse impulse.
		 * @param point point.
		 */
		virtual void mountImpulse(const Impulse & impulse, const math::const_VectorPtr<2> & point) = 0;
		//impulse is const because collider expects that it will be able to use it on another colliding object as well

		/**
		 * Round away impulse. Just before impulse is mounted, object may modify its state
		 * according to prepared collision data. Function may be also used to round away
		 * impulse from machine epsilon truncation.
		 * @param impulse impulse.
		 * @param cData collision data.
		 * @param normal true if impulse is normal, false when parallel.
		 */
		virtual void roundAwayImpulse(Impulse & impulse, const NewtonCollisionData & cData, bool normal) = 0;

		/**
		 * Subsequent collision limit. Invoked when number of subsequent collisions was
		 * exceeded. Object won't be updated in current pass anymore, nor its buffers
		 * will be swapped. Accordingly, function gives object a chance to take special
		 * actions, like cleanup for example.
		 * @param num number of subsequent collisions occurred.
		 */
//		virtual void subsequentLimit(int num) = 0;
};

}
}

#endif /* GPX_Phy2d_CNEWTONMOVABLE_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
