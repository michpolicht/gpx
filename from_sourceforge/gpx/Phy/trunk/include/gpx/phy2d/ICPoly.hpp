/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_ICPOLY_HPP_
#define GPX_Phy2d_ICPOLY_HPP_

#include "IPointDetection.hpp"

#include <gpx/model/VertexData.hpp>

namespace gpx {
namespace phy2d {

/**
 * Newton collision points. Structure contains data about points, where collision occurred.
 */
struct CollisionPoints
{
	math::Vector<2> pre;	///< C-vertex position before collision (given in local coordinates).
	math::Vector<2> post;	///< C-vertex position after collision (given in local coordinates).
	math::Vector<2>	eff;	///< Effective collision point (calculated by "bumper", given in local coordinates).
};

/**
 * Colliding polygon.
 */
class ICPoly : public virtual IPointDetection
{
	public:
		/**
		 * Get colliding vertices. C-vertices or colliding vertices are those vertices
		 * that bound object in particular polyg onal shape. C-vertices have to be given
		 * in object's local coordinates.
		 *
		 * @return reference to vertex container with object's c-vertices.
		 *
		 * @warning do not resize c-vertices vector during collision calculations,
		 * it may invalidate iterators.
		 */
		virtual const model::VertexData<2> & cvertices() const = 0;

		/**
		 * Get effective collision point. Based on pre- and post-collision points,
		 * object should determine effective collision point where collision occurred.
		 * In simplest approach just pre-collision point may be returned. Effective
		 * point have to be given in object's local coordinates.
		 * @param pre pre-collision point.
		 * @param post post-collision point.
		 *
		 * @return effective point where collision was expected to occur.
		 */
		virtual math::Vector<2> eff(const math::const_VectorPtr<2> & pre, const math::const_VectorPtr<2> & post) const = 0;

		/**
		 * Get normal. Get normal vector, which defines direction of collision. In most cases
		 * normal vector will be perpendicular to object's shape in the point where edge of
		 * the object and section defined by pre- and post-collision points intersect.
		 * Normal vector has to be given in global coordinates.
		 * @param cPoints structure containing pre-, post- and effective collision points.
		 *
		 * @return normal.
		 */
		virtual math::Vector<2> normal(const CollisionPoints & cPoints) const = 0;
};

}
}

#endif /* GPX_Phy2d_ICPOLY_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
