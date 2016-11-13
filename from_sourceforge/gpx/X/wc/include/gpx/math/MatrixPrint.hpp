#ifndef GPX_X_MATH_MATRIXPRINT_HPP
#define GPX_X_MATH_MATRIXPRINT_HPP

#include "structures.hpp"

#include <iomanip>

namespace gpx {
namespace math {

template<std::size_t M = SIZE_DYNAMIC, std::size_t N = SIZE_DYNAMIC, typename T = real_t>
struct MatrixPrint
{
	static int Precision;
};

template<std::size_t M, std::size_t N, typename T>
int MatrixPrint<M, N, T>::Precision = 10;

}
}

/**
 * Stream operator for Matrix<M, N>.
 * @param s output stream.
 * @param m matrix.
 * @return output stream @a s.
 */
template <std::size_t M, std::size_t N, typename T>
std::ostream & operator <<(std::ostream & s, gpx::math::const_MatrixRef<M, N, T> m)
{
	s.precision(gpx::math::MatrixPrint<M, N, T>::Precision); //7 <- 5 exponent (e[+-]XXX), 1 dot (.), 1 sign (-)
	for (std::size_t i = 0; i < m.rows(); i++) {
		s << "[ ";
		for (std::size_t j = 0; j < m.cols(); j++)
			s << std::setw(gpx::math::MatrixPrint<M, N, T>::Precision + 7) << m(i,j) << " ";
		s << "]\n";
	}
	s << std::flush;
	return s;
}

template <std::size_t M, std::size_t N, typename T>
std::ostream & operator <<(std::ostream & s, const gpx::math::MatrixRef<M, N, T> & m)
{
	return operator <<(s, static_cast<gpx::math::const_MatrixRef<M, N, T> >(m));
}

template <std::size_t M, std::size_t N, typename T>
std::ostream & operator <<(std::ostream & s, const gpx::math::Matrix<M, N, T> & m)
{
	return operator <<(s, static_cast<gpx::math::const_MatrixRef<M, N, T> >(m));
}

#endif // MATRIXPRINT_HPP
