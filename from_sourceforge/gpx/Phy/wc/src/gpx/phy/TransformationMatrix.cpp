/**
 * @file
 * @brief .
 */


#include "../../../include/gpx/phy/TransformationMatrix.hpp"

namespace gpx {
namespace phy {

TransformationMatrix::TransformationMatrix():
	math::Matrix<4,4>(static_cast<real_t>(1.0))
{
}

math::Vector<2> TransformationMatrix::prod(math::const_VectorRef<2> vec) const
{
	math::Vector<2> result;
	for (std::size_t c = 0; c < 2; c++) {
		math::const_VectorRef<2> col = column(c).ptr();
		for (std::size_t r = 0; r < 2; r++)
			result(r) += col(r) * vec(c);
	}
	return result;
}

math::Vector<2> TransformationMatrix::operator *(math::const_VectorRef<2> vec) const
{
	return prod(vec);
}

math::Point<2> TransformationMatrix::prod(math::const_PointRef<2> point) const
{
	math::Point<2> result(column(3).ptr());	//add 3rd column
	for (std::size_t c = 0; c < 2; c++) {
		math::const_VectorRef<2> col = column(c).ptr();
		for (std::size_t r = 0; r < 2; r++)
			result(r) += col(r) * point(c);
	}
	return result;
}

math::Point<2> TransformationMatrix::operator *(math::const_PointRef<2> point) const
{
	return prod(point);
}

}
}
