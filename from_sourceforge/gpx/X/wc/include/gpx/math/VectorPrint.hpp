#ifndef GPX_X_MATH_STRUCTUREPRINT_HPP
#define GPX_X_MATH_STRUCTUREPRINT_HPP

#include "structures.hpp"

#include <limits>

namespace gpx {
namespace math {

template<std::size_t N = SIZE_DYNAMIC, typename T = real_t>
struct VectorPrint
{
	static int Precision;
};

template<std::size_t N, typename T>
int VectorPrint<N, T>::Precision = std::numeric_limits<T>::digits10 + 2;

}
}

/**
 * Output stream operator for gpx::math::const_VectorRef types.
 * @param s output stream.
 * @param v vector object.
 */
template <std::size_t N, typename T>
std::ostream & operator <<(std::ostream & s, gpx::math::const_VectorRef<N, T> vec)
{
	s.precision(gpx::math::VectorPrint<N, T>::Precision);
	s << "[";
	for (std::size_t i = 0; i < vec.size() - 1; i++)
		s << vec.coord(i) << ", ";
	s << vec.coord(vec.size() - 1) << "]" << std::endl;
	return s;
}

template <std::size_t N, typename T>
std::ostream & operator <<(std::ostream & s, const gpx::math::VectorRef<N, T> & vec)
{
	return operator <<(s, static_cast<gpx::math::const_VectorRef<N, T> >(vec));
}

template <std::size_t N, typename T>
std::ostream & operator <<(std::ostream & s, const gpx::math::Vector<N, T> & vec)
{
	return operator <<(s, static_cast<gpx::math::const_VectorRef<N, T> >(vec));
}

#endif
