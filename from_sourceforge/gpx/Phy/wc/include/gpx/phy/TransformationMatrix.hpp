/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy_TRANSFORMATIONMATRIX_HPP_
#define GPX_Phy_TRANSFORMATIONMATRIX_HPP_

#include <gpx/platform.hpp>
#include <gpx/math/structures.hpp>
//#include <Eigen/Core>

//USING_PART_OF_NAMESPACE_EIGEN


namespace gpx {
namespace phy {

/**
 * Transformation matrix. Class is a container for 4x4 matrix stored in column-major order.
 * Storage is compatible with OpenGL. Initially matrix is an identity matrix.
 * */
class GPX_API TransformationMatrix : public math::Matrix<4, 4>
{
	typedef math::Matrix<4, 4> Parent;

	public:
		/**
		 * Default constructor.
		 */
		TransformationMatrix();

		using Parent::prod;

		/**
		 * 2D vector product.
		 * @param vec vector multiplier. Vector [x, y] is mapped to homogenous
		 * coordinates [x, y, 0, 0].
		 * @return product of matrix multiplied by vector.
		 */
		math::Vector<2> prod(math::const_VectorRef<2> vec) const;

		using Parent::operator *;

		/**
		 * 2D vector product. Alias of prod().
		 * @param vec vector multiplier. Vector [x, y] is mapped to homogenous
		 * coordinates [x, y, 0, 0].
		 * @return product of matrix multiplied by vector.
		 */
		math::Vector<2> operator *(math::const_VectorRef<2> vector) const;

		/**
		 * 2D point product.
		 * @param point point multiplier. Point [x, y] is mapped to vector
		 * with homogenous coordinates [x, y, 0, 1]. Matrix is then multiplied
		 * by this vector.
		 * @return product of matrix multiplied by vector mapped to a point.
		 */
		math::Point<2> prod(math::const_PointRef<2> point) const;

		/**
		 * 2D point product. Alias of prod().
		 * @param point point multiplier. Point [x, y] is mapped to vector
		 * with homogenous coordinates [x, y, 0, 1]. Matrix is then multiplied
		 * by this vector.
		 * @return product of matrix multiplied by vector mapped to a point.
		 */
		math::Point<2> operator *(math::const_PointRef<2> point) const;
};


}
}

#endif /* GPX_Phy_TRANSFORMATIONMATRIX_HPP_ */
