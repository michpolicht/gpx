/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_CDETECT_INTERSEG_ICPOLY_HPP_
#define GPX_Phy2d_CDETECT_INTERSEG_ICPOLY_HPP_

#include <gpx/model/VertexData.hpp>
#include <gpx/math/structures.hpp>

namespace gpx {
namespace phy2d {
namespace cdetect {
namespace interseg {

/**
 * Colliding polygon interface. Detection is based on intersecting segments.
 */
class ICPoly
{
	public:
		/**
		 * Get colliding vertices. C-vertices or colliding vertices are those vertices
		 * that bound object in particular polyg onal shape. C-vertices have to be given
		 * in object's local coordinates.
		 * @return reference to vertex container with object's c-vertices.
		 *
		 * @warning do not resize c-vertices vector during collision calculations,
		 * it may invalidate iterators.
		 */
		virtual const model::VertexData<2> & cvertices() const = 0;

		/**
		 * Get normal. Get normal vector, which defines direction of collision. In most cases
		 * normal vector will be perpendicular to object's shape in the point where edge of
		 * the object and section defined by pre- and post-collision points intersect.
		 * @param pre pre-collision point.
		 * @param post post-collision point.
		 * @return normal.
		 *
		 * @note normal vector has to be given in global coordinates!
		 */
		virtual math::Vector<2> normal(math::const_PointRef<2> pre, math::const_PointRef<2> post) const = 0;

		/**
		 * Segment test.
		 * @param pre pre-collision point.
		 * @param post post-collision point.
		 * @return function should return @p true, if segment defined by pre- and
		 * post-collision points intersects an object. Otherwise function shall
		 * return @p false.
		 */
		virtual bool test(math::const_PointRef<2> pre, math::const_PointRef<2> post) const = 0;

	protected:
		~ICPoly() {}
};

}
}
}
}

#endif /* GPX_Phy2d_CDETECT_INTERSEG_ICPOLY_HPP_ */
