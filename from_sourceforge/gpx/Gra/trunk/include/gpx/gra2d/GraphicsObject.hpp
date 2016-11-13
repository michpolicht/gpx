/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra2d_GRAPHICSOBJECT_HPP_
#define GPX_Gra2d_GRAPHICSOBJECT_HPP_

#include "../gra/TransformationMatrix.hpp"

namespace gpx {
namespace gra2d {

/**
 * Graphics object.
 *
 * @todo transformations (rotation, translation etc).
 */
class GPX_API GraphicsObject
{
	public:
		GraphicsObject();

	public:
		math::const_PointRef<2> pos() const;

		void setPos(math::const_PointRef<2> pos);

		void setPos(real_t x, real_t y);

		real_t x() const;

		void setX(real_t x);

		real_t y() const;

		void setY(real_t y);

		const gra::TransformationMatrix & tMatrix() const;

		const gra::TransformationMatrix & tMatrixInv() const;

		math::Point<2> mapToGlobal(math::const_PointRef<2> point) const;

		math::Point<2> mapToLocal(math::const_PointRef<2> point) const;

		//test(cvertex)

	private:
		gra::TransformationMatrix m_tMatrix;
		gra::TransformationMatrix m_tMatrixInv;
		math::PointRef<2> m_pos;
};

}
}

#endif /* GPX_Gra2d_GRAPHICSOBJECT_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
