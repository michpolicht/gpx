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
		 * Returns current position vector.
		 * @return current position vector.
		 */
		math::const_PointRef<2> pos() const;

		/**
		 * Set position.
		 * @param pos position vector.
		 */
		void setPos(math::const_PointRef<2> pos);

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
		math::Point<2> mapToLocal(math::const_PointRef<2> point) const;

		/**
		 * Map point from local to global coordinates.
		 * @param point point to be mapped.
		 */
		math::Point<2> mapToGlobal(math::const_PointRef<2> point) const;

	protected:
		/**
		 * Constructor.
		 */
		StaticObject();

		/**
		 * Destructor.
		 */
		virtual ~StaticObject();

	protected:
		/**
		 * Construct transformation matrix. This virtual function can be re-implemented.
		 * @param tMatrix transformation matrix.
		 * @param invTMatrix inverted transformation matrix.
		 */
		virtual void constructTMatrix(phy::TransformationMatrix & tMatrix, phy::TransformationMatrix & tMatrixInv);

	private:
		math::Point<2> m_pos; //position
		phy::TransformationMatrix m_tMatrix;
		phy::TransformationMatrix m_tMatrixInv;
};

}
}

#endif /* GPX_Phy2d_STATICOBJECT_HPP_ */
