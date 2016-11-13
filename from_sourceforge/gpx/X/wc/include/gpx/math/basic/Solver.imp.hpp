/**
 * @file
 * @brief .
 */

#include <algorithm>

namespace gpx {
namespace math {
namespace basic {

template <int EQ_FLAGS, std::size_t N, typename T>
inline
Solver<EQ_FLAGS, N, T>::Solver(gpx::math::Matrix<N, N, T> & a):
	m_a(a)
{
}

template <int EQ_FLAGS, std::size_t N, typename T>
gpx::math::Vector<N, T> Solver<EQ_FLAGS, N, T>::solve(gpx::math::VectorRef<N, T> b)
{
	gpx::math::Vector<N, T> result(T(), b.size());
	gpx::math::Matrix<N, N, T> a(m_a);

	std::size_t i = 0;
	//considering column j
	for (std::size_t j = 0; j < a.cols(); j++) {
	//		GPX_INFO("considering column: " << j << " row: " << i);
		//find max pivot
		std::size_t iPivot = i;
		for (std::size_t ii = i + 1; ii < a.rows(); ii++)
			if (std::abs(a(ii, j)) > std::abs(a(iPivot, j)))
				iPivot = ii;
		if (iPivot != i) {
			a.swapRows(i, iPivot);
			b.swap(i, iPivot);
		}
	//		GPX_INFO("m_a: " << std::endl << a);
	//		GPX_INFO("m_b: " << std::endl << b);
		T divisor = a(i, j);
	//		GPX_INFO("divisor(" << i << ", " << j << "): " << divisor);
		if (!gpx::math::ape(divisor, T())) {
			for (std::size_t jj = j; jj < a.cols(); jj++)
				a(i, jj) /= divisor;
			b(i) /= divisor;
	//			GPX_INFO("m_a: " << std::endl << a);
	//			GPX_INFO("m_b: " << std::endl << b);
			for (std::size_t ii = i + 1; ii < a.rows(); ii++) {
	//				GPX_INFO("multiplier: " << a(ii, j));
	//				T multiplier = a(ii, j);
				for (std::size_t jj = j + 1; jj < a.cols(); jj++)
					a(ii, jj) -= a(ii, j) * a(i, jj);
				b(ii) -= a(ii, j) * b(i);
			}
			GPX_INFO("m_a: " << std::endl << a);
			GPX_INFO("m_b: " << std::endl << b);
		}
		i++;
	}
	//get solution from triangular matrix
	i = a.rows();
	do {
		i--;
		if (gpx::math::ape(a(i, i), T()))
			result(i) = T();
		else {
			result(i) = b(i);
			for (std::size_t j = i + 1; j < a.cols(); j++)
				result(i) -= result(j) * a(i, j);
		}
	} while (i > 0);
	return result;
}

/*
template <int EQ_FLAGS, std::size_t N, typename T>
gpx::math::Vector<N, T> Solver<EQ_FLAGS, N, T>::solve(gpx::math::VectorRef<N, T> b)
{

	//Rough, fast written piece of code... although it solves systems of dependent equations.

	gpx::math::Vector<N, T> result(b.size());
	gpx::math::Matrix<N, N, T> a(m_a);

	std::size_t i = 0;
	//considering column j
	for (std::size_t j = 0; j < a.cols(); j++) {
//		GPX_INFO("considering column: " << j << " row: " << i);
		//find max pivot
		std::size_t iPivot = i;
		for (std::size_t ii = i + 1; ii < a.rows(); ii++)
			if (std::abs(a(ii, j)) > std::abs(a(iPivot, j)))
				iPivot = ii;
		a.swapRows(i, iPivot);
		b.swap(i, iPivot);
//		GPX_INFO("m_a: " << std::endl << a);
//		GPX_INFO("m_b: " << std::endl << b);
		T divisor = a(i, j);
//		GPX_INFO("divisor(" << i << ", " << j << "): " << divisor);
		if (!gpx::math::ape(divisor, T())) {
			for (std::size_t jj = j; jj < a.cols(); jj++)
				a(i, jj) /= divisor;
			b(i) /= divisor;
//			GPX_INFO("m_a: " << std::endl << a);
//			GPX_INFO("m_b: " << std::endl << b);
			for (std::size_t ii = 0; ii < a.rows(); ii++)
				if (ii != i) {
					T multiplier = a(ii, j);
					for (std::size_t jj = j; jj < a.cols(); jj++)
						a(ii, jj) -= multiplier * a(i, jj);
					b(ii) -= multiplier * b(i);
				}
//			GPX_INFO("m_a: " << std::endl << a);
//			GPX_INFO("m_b: " << std::endl << b);
			i++;
		}
	}
	for (std::size_t i = 0; i < a.rows(); i++) {
		std::size_t numCoefs = 0;
		for (std::size_t j = 0; j < a.cols(); j++)
			if (result(j) != T()) {
				b(i) -= a(i, j) * result(j);
				a(i, j) = T();
			} else if (!gpx::math::ape(a(i, j), T()))
				numCoefs++;
		if (numCoefs) {
			b(i) /= static_cast<T>(numCoefs);
			for (std::size_t j = 0; j < a.cols(); j++)
				if (!gpx::math::ape(a(i, j), T()))
					result(j) = b(i) / a(i, j);
		}
	}
//	GPX_DEBUG("result: " << result);

//	for (std::size_t i = 0; i < a.rows(); i++) {
//		T sumCoefs = T();
//		for (std::size_t j = 0; j < a.cols(); j++)
//			sumCoefs += a(i, j);
//		b(i) /= sumCoefs;
//	}
//	GPX_INFO("m_b: " << std::endl << b);
//	for (std::size_t j = 0; j < a.cols(); j++) {
//		std::size_t selRow = 0;
//		for (std::size_t i = 0; i < a.rows(); i++)
//			if (std::abs(a(i, j)) > std::abs(a(selRow, j)))
//				selRow = i;
//		result(j) = a(selRow, j) * b(selRow);
//	}
	return result;
}
*/

}
}
}
