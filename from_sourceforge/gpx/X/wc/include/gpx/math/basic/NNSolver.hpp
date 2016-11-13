/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_BASIC_PSOLVER_HPP_
#define GPX_X_MATH_BASIC_PSOLVER_HPP_

#include "../structures.hpp"

#include <algorithm>
#include <numeric>

namespace gpx {
namespace math {
namespace basic {

/**
 * Linear equation solver. Basic implementation, using Gaussian elimination with
 * pivoting.
 * @param EQ_FLAGS flags indicating equation type.
 * @param N linear system size in terms of number of equations.
 * @param T underlying type.
 */
template <int EQ_FLAGS, std::size_t N, typename T>
class NNSolver
{
	protected:
		NNSolver(gpx::math::MatrixRef<N, N, T> a);

		gpx::math::Vector<N, T> solve(gpx::math::VectorRef<N, T> b);

	private:
		gpx::math::MatrixRef<N, N, T> m_a;
};

template <int EQ_FLAGS, std::size_t N, typename T>
NNSolver<EQ_FLAGS, N, T>::NNSolver(gpx::math::MatrixRef<N, N, T> a):
	m_a(a)
{
}


template <int EQ_FLAGS, std::size_t N, typename T>
gpx::math::Vector<N, T> NNSolver<EQ_FLAGS, N, T>::solve(gpx::math::VectorRef<N, T> b)
{
	//Rough, fast written piece of code... although it solves systems of dependent equations.

	gpx::math::Vector<N, T> result(T(), b.size());
#pragma message("temporary code")
	gpx::math::Vector<> bOrg(b);
	gpx::math::Vector<N, T> divisors(T(), b.size());	//tmp
//end pragma
	gpx::math::Matrix<N, N, T> a(m_a);
	std::vector<std::size_t> jWhat(b.size(), 0u);	//what is under column j, e.g., jWhat[1] == 2 indicates that under column 1 lies former column 2
	std::vector<std::size_t> iWhat(b.size(), 0u);
	std::vector<std::size_t> iWhere(b.size(), 0u); //where row i has been moved, e.g., iWhere[1] == 2 indicates that former row 1 has been moved to row 2

	for (std::size_t init = 0; init < b.size(); init++) {
		iWhat[init] = init;
		iWhere[init] = init;
		jWhat[init] = init;
	}
	//C++11
//	std::iota(iInd.begin(), iInd.end(), 0);
//	std::iota(jInd.begin(), jInd.end(), 0);

	std::size_t i = 0;
	//considering column j
	for (std::size_t j = 0; j < a.cols(); j++) {
	//		GPX_INFO("considering column: " << j << " row: " << i);
		//find max pivot
		std::size_t iPivot = i;
		std::size_t jPivot = j;
		for (std::size_t ii = i + 1; ii < a.rows(); ii++)
			for (std::size_t jj = j + 1; jj < a.cols(); jj++)
//				if (std::abs(a(ii, j)) > std::abs(a(iPivot, j)))
				if (std::abs(a(ii, jj)) > std::abs(a(iPivot, jPivot))) {
					iPivot = ii;
					jPivot = jj;
				}
		if (iPivot != i) {
			std::swap(iWhat[i], iWhat[iPivot]);
			iWhere[iWhat[i]] = i;
			iWhere[iWhat[iPivot]] = iPivot;
			a.swapRows(i, iPivot);
			b.swap(i, iPivot);
		}
		if (jPivot != j) {
			a.swapCols(j, jPivot);
			std::swap(jWhat[j], jWhat[jPivot]);
		}
	//		GPX_INFO("m_a: " << std::endl << a);
	//		GPX_INFO("m_b: " << std::endl << b);
		T divisor = a(i, j);
	//		GPX_INFO("divisor(" << i << ", " << j << "): " << divisor);
		if (gpx::math::ape(divisor, T())) {
			for (std::size_t jj = 0; jj < a.cols(); jj++)
				a(i, jj) = T();
			b(i) = T();
		} else {
			//dividing upper triangle and lower triangle (b(i) contributions)
			for (std::size_t jj = 0; jj < a.cols(); jj++)
				a(i, jj) /= divisor;
			divisors(i) = divisor;
			b(i) /= divisor;

	//			GPX_INFO("m_a: " << std::endl << a);
	//			GPX_INFO("m_b: " << std::endl << b);

			for (std::size_t ii = i + 1; ii < a.rows(); ii++) {
				a(ii, j) = -a(ii, j); //multiplier
				for (std::size_t jj = 0; jj < a.cols(); jj++) {
					if (jj == j)
						continue;
					a(ii, jj) += a(ii, j) * a(i, jj);
				}
			}
			for (std::size_t ii = 0; ii < i; ii++) {
				a(ii, j) = -a(ii, j);	//multiplier
				for (std::size_t jj = 0; jj < a.cols(); jj++) {
					if (jj == j)
						continue;
					a(ii, jj) += a(ii, j) * a(i, jj);
				}
	//				for (std::size_t jj = j + 1; jj < a.cols(); jj++)
	//					a(ii, jj) -= multiplier * a(i, jj);
			}
		}
		GPX_INFO("m_a: " << std::endl << a);
		GPX_INFO("m_b: " << std::endl << b);
		i++;
	}

	i = 0;
#pragma message("temporary ctr code")
	int ctr = 0;	///< @todo ctr is temporary.
	while (i < a.rows()) {
	//		result(i) = b(i) * a(i, i);
		std::size_t jj = jWhat[i];
		for (std::size_t j = 0; j < a.cols(); j++)
			result(jj) += a(i, j) * b(j);

		if (ctr == 10) {
			GPX_WARN("could not remove negative value in 100 steps");
			i++;
			continue;
		}

		if (gpx::math::cgt(T(), result(jj))) {
			GPX_INFO("removing negative result(" << jj << "): " << result);
			GPX_INFO("b vector: " << b);
			std::size_t ii = iWhere[jj];
			b(ii) -= result(jj) / a(i, ii);
//			if (a(i, ii) )
//			if (b(i) < bOrg(i))
//				GPX_DEBUG("required b(" << i << ") = " << b(i) << " is smaller than original value");
//			b(i) = std::max(b(i), bOrg(i));
//			if (b(i) > 2.0 * bOrg(i))
//				GPX_DEBUG("required b(" << i << ") = " << b(i) << " is larger than original value doubled");
//			b(i) = std::min(b(i), 2.0 * bOrg(i));

	//			if (b(i) < T())
	//				b(i) = T();
			GPX_INFO("new b vector: " << b);


			#pragma message("temporary code")
			for (std::size_t iTmp = 0; iTmp < b.size(); iTmp++)
				result(iTmp) = b(iWhere[iTmp]) * divisors(iWhere[iTmp]);
			GPX_INFO("b vector with original values: " << bOrg);
			GPX_INFO("new b vector with original values: " << result);
			result.zero();
			for (std::size_t iTmp = 0; iTmp < a.rows(); iTmp++)
				for (std::size_t jTmp = 0; jTmp < a.cols(); jTmp++)
					result(jWhat[iTmp]) += a(iTmp, jTmp) * b(jTmp);
			GPX_INFO("new result vector: " << result);
			//end #pragma message("temporary code")

			result.zero();
			i = 0;
			ctr++;
		} else
			i++;
	}
	return result;
}

//template <int EQ_FLAGS, std::size_t N, typename T>
//gpx::math::Vector<N, T> NNSolver<EQ_FLAGS, N, T>::solve(gpx::math::VectorRef<N, T> b)
//{
//	//Rough, fast written piece of code... although it solves systems of dependent equations.

//	gpx::math::Vector<N, T> result(T(), b.size());
//	gpx::math::Matrix<N, N, T> a(m_a);

//	std::size_t i = 0;
//	//considering column j
//	for (std::size_t j = 0; j < a.cols(); j++) {
////		GPX_INFO("considering column: " << j << " row: " << i);
//		//find max pivot
//		std::size_t iPivot = 0;
//		for (std::size_t ii = i + 1; ii < a.rows(); ii++)
//			if (std::abs(a(ii, j)) > std::abs(a(iPivot, j)))
//				iPivot = ii;
//		if (iPivot) {
//			a.swapRows(i, iPivot);
//			b.swap(i, iPivot);
//		}
////		GPX_INFO("m_a: " << std::endl << a);
////		GPX_INFO("m_b: " << std::endl << b);
//		T divisor = a(i, j);
////		GPX_INFO("divisor(" << i << ", " << j << "): " << divisor);
//		if (!gpx::math::ape(divisor, T())) {
//			for (std::size_t jj = j; jj < a.cols(); jj++)
//				a(i, jj) /= divisor;
//			b(i) /= divisor;
////			GPX_INFO("m_a: " << std::endl << a);
////			GPX_INFO("m_b: " << std::endl << b);
//			for (std::size_t ii = i + 1; ii < a.rows(); ii++) {
//				T multiplier = a(ii, j);
//				for (std::size_t jj = j; jj < a.cols(); jj++)
//					a(ii, jj) -= multiplier * a(i, jj);
//				b(ii) -= multiplier * b(i);
//			}
//			GPX_INFO("m_a: " << std::endl << a);
////			GPX_INFO("m_b: " << std::endl << b);
//			i++;
//		}
//	}
//	for (std::size_t i = 0; i < a.rows(); i++) {
//		std::size_t numCoefs = 0;
//		for (std::size_t j = 0; j < a.cols(); j++)
//			if (result(j) != T()) {
//				b(i) -= a(i, j) * result(j);
//				a(i, j) = T();
//			} else if (!gpx::math::ape(a(i, j), T()))
//				numCoefs++;
//		if (numCoefs) {
//			b(i) /= static_cast<T>(numCoefs);
//			for (std::size_t j = 0; j < a.cols(); j++)
//				if (!gpx::math::ape(a(i, j), T()))
//					result(j) = b(i) / a(i, j);
//		}
//	}
////	GPX_DEBUG("result: " << result);

////	for (std::size_t i = 0; i < a.rows(); i++) {
////		T sumCoefs = T();
////		for (std::size_t j = 0; j < a.cols(); j++)
////			sumCoefs += a(i, j);
////		b(i) /= sumCoefs;
////	}
////	GPX_INFO("m_b: " << std::endl << b);
////	for (std::size_t j = 0; j < a.cols(); j++) {
////		std::size_t selRow = 0;
////		for (std::size_t i = 0; i < a.rows(); i++)
////			if (std::abs(a(i, j)) > std::abs(a(selRow, j)))
////				selRow = i;
////		result(j) = a(selRow, j) * b(selRow);
////	}
//	return result;
//}

}
}
}

#endif /* GPX_X_MATH_BASIC_PSOLVER_HPP_ */
