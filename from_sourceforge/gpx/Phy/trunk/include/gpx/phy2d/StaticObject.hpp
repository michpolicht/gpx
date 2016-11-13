/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_STATICOBJECT_HPP_
#define GPX_Phy2d_STATICOBJECT_HPP_

#include "../phy/TransformationMatrix.hpp"

#include <gpx/platform.hpp>

namespace gpx {
namespace phy2d {

class GPX_API StaticObject
{
	public:
		/**
		 * Constructor.
		 */
		StaticObject();

		/**
		 * Destructor.
		 */
		virtual ~StaticObject();

		/**
		 * Returns current position vector.
		 * @return current position vector.
		 */
		const math::Vector<2> & pos() const;

		/**
		 * Set position.
		 * @param pos position vector.
		 */
		void setPos(const math::const_VectorPtr<2> & pos);

		/**
		 * Set position. Provided for convenience.
		 * @param x x coordinate of position vector.
		 * @param y y coordinate of position vector.
		 */
		void setPos(real_t x, real_t y);

		/**
		 * Get x position coordinate.
		 * @return x.
		 */
		real_t x() const;

		/**
		 * Set x position coordinate.
		 * @param x x position coordinate.
		 */
		void setX(real_t x);

		/**
		 * Get y position coordinate.
		 * @return y.
		 */
		real_t y() const;

		/**
		 * Set y position coordinate.
		 * @param y y coordinate.
		 */
		void setY(real_t y);

		/**
		 * Get transformation matrix;
		 */
		const phy::TransformationMatrix & tMatrix() const;

		/**
		 * Map point from global to local coordinates.
		 * @param point point to be mapped.
		 */
		math::Vector<2> mapToLocal(const real_t point[2]) const;

		/**
		 * Map point from local to global coordinates.
		 * @param point point to be mapped.
		 */
		math::Vector<2> mapToGlobal(const real_t point[2]) const;

	protected:
		/**
		 * Construct transformation matrix. This virtual function can be re-implemented.
		 * @param tMatrix transformation matrix.
		 * @param invTMatrix inverted transformation matrix.
		 */
		virtual void constructTMatrix(phy::TransformationMatrix & tMatrix, phy::TransformationMatrix & tMatrixInv);

	private:
		math::Vector<2> m_pos; //position
		phy::TransformationMatrix m_tMatrix;
		phy::TransformationMatrix m_tMatrixInv;
};

}
}

#endif /* GPX_Phy2d_STATICOBJECT_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
