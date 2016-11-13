#ifndef POINTPRINT_HPP
#define POINTPRINT_HPP

#include "structures.hpp"

#include <limits>

namespace gpx {
namespace math {

template<std::size_t N = SIZE_DYNAMIC, typename T = real_t>
struct PointPrint
{
	static int Precision;
};

template<std::size_t N, typename T>
int PointPrint<N, T>::Precision = std::numeric_limits<T>::digits10 + 2;

}
}

/**
 * Output stream operator for gpx::math::const_PointRef types.
 * @param s output stream.
 * @param point point object.
 */
template <std::size_t N, typename T>
std::ostream & operator <<(std::ostream & s, gpx::math::const_PointRef<N, T> point)
{
	s.precision(gpx::math::PointPrint<N, T>::Precision);
	s << "(";
	for (std::size_t i = 0; i < point.size() - 1; i++)
		s << point.coord(i) << ", ";
	s << point.coord(point.size() - 1) << ")" << std::endl;
	return s;
}

template <std::size_t N, typename T>
std::ostream & operator <<(std::ostream & s, const gpx::math::PointRef<N, T> & point)
{
	return operator <<(s, static_cast<gpx::math::const_PointRef<N, T> >(point));
}

template <std::size_t N, typename T>
std::ostream & operator <<(std::ostream & s, const gpx::math::Point<N, T> & point)
{
	return operator <<(s, static_cast<gpx::math::const_PointRef<N, T> >(point));
}

#endif // POINTPRINT_HPP
