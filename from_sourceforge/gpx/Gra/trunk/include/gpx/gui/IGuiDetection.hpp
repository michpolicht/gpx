/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GUI_IGUIDETECTION_HPP_
#define GPX_Gra_GUI_IGUIDETECTION_HPP_

#include "../gra2d/Scene.hpp"

#include <gpx/math/structures.hpp>

namespace gpx {
namespace gui {

class IGuiDetection
{
	public:
		typedef gra2d::Scene::painterPlane_t zHint_t;

	public:
		virtual zHint_t zHint() const = 0;

		/**
		 * Point detection.
		 * @param point collision point.
		 * @return function should return @p true, if point lies inside an object.
		 * Otherwise function shall return @p false.
		 */
		virtual bool test(math::const_PointRef<2> point) const = 0;
};

}
}


#endif /* GPX_Gra_GUI_IGUIDETECTION_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
