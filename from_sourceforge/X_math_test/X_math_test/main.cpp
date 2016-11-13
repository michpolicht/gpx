#include "tests.hpp"
#include "const_VectorRefTest.hpp"
#include "VectorRefTest.hpp"
#include "VectorTest.hpp"
#include "MatrixTest.hpp"

//#include <gpx/model/Segment.hpp>
//#include <gpx/model/SegmentPtr.hpp>
//#include <gpx/model/const_SegmentPtr.hpp>
//#include <gpx/model/SegmentPrint.hpp>

//using namespace std;

//explicit instantiation
//template class gpx::math::const_MatrixRef<2, 2>;

#include <gpx/math/Solver.hpp>

void setSys0(gpx::math::MatrixRef<> a, gpx::math::VectorRef<> b)
{
	a.resize(2, 2);
	a(0, 0) = 4.0;
	a(0, 1) = 2.0;
	a(1, 0) = 1.0;
	a(1, 1) = 2.0;

	b.resize(2);
	b(0) = 1.0;
	b(1) = -1.0;
}

//void setSys0b
//{
//	//a and b giving negative impulses
//	//a
//	//	[       3.873586631       3.902817817      0.5349168472 ]
//	//	[       3.902817817       3.937316184      0.5994243385 ]
//	//	[      0.5349168472      0.5994243385       2.599424859 ]
//	//	b [44.817703925461728, 44.824133576154807, 0.65314083334932327]
//}

void setSys1(gpx::math::MatrixRef<> a, gpx::math::VectorRef<> b)
{
//a:
//	[       2.079471626     -0.9335087488     -0.3380226773 ]
//	[     -0.9335087488       2.400230364       2.094904544 ]
//	[     -0.3380226773       2.094904544       2.411647069 ]
//b:
//	[6.7218104232334941, 5.6194176572294339, 0.35301334529768269]

	a.resize(3, 3);
	a(0, 0) = 2.079471626;
	a(0, 1) = -0.9335087488;
	a(0, 2) = -0.3380226773;
	a(1, 0) = -0.9335087488;
	a(1, 1) = 2.400230364;
	a(1, 2) = 2.094904544;
	a(2, 0) = -0.3380226773;
	a(2, 1) = 2.094904544;
	a(2, 2) = 2.411647069;

	b.resize(3);
	b(0) = 6.7218104232334941;
	b(1) = 5.6194176572294339;
	b(2) = 0.35301334529768269;
}

void setSys2(gpx::math::MatrixRef<> a, gpx::math::VectorRef<> b)
{
//a:
//	[       5.380943676       5.383212623 ]
//	[       5.383212623       5.396045324 ]
//b:
//	[2.7841718483944504, 2.9357418382201352]

	a.resize(2, 2);
	a(0, 0) = 5.380943676;
	a(0, 1) = 5.383212623;
	a(1, 0) = 5.383212623;
	a(1, 1) = 5.396045324;

	b.resize(2);
	b(0) = 2.7841718483944504;
	b(1) = 2.9357418382201352;
}

void setSys3(gpx::math::MatrixRef<> a, gpx::math::VectorRef<> b)
{
//	Debug message: A:
//	[       2.766685696      0.4268694056      0.7491300727                 0 ]
//	[      0.4268694056       3.505261096       3.789010173     -0.8744359351 ]
//	[      0.7491300727       3.789010173       4.314982616     -0.9887511755 ]
//	[                 0     -0.8744359351     -0.9887511755        2.13623184 ]
//	Debug message: b:
//	[2.3529285679029286, 6.5673748509071821, 15.703644126422327, 9.9518879311846327]

	a.resize(4, 4);
	a(0, 0) = 2.766685696;
	a(0, 1) = 0.4268694056;
	a(0, 2) = 0.7491300727;
	a(0, 3) = 0.0;

	a(1, 0) = 0.4268694056;
	a(1, 1) = 3.505261096;
	a(1, 2) = 3.789010173;
	a(1, 3) = -0.8744359351;

	a(2, 0) = 0.7491300727;
	a(2, 1) = 3.789010173;
	a(2, 2) = 4.314982616;
	a(2, 3) = -0.9887511755;

	a(3, 0) = 0.0;
	a(3, 1) = -0.8744359351;
	a(3, 2) = -0.9887511755;
	a(3, 3) = 2.13623184;

	b.resize(4);
	b(0) = 2.3529285679029286;
	b(1) = 6.5673748509071821;
	b(2) = 15.703644126422327;
	b(3) = 9.9518879311846327;
}

void setSys4(gpx::math::MatrixRef<> a, gpx::math::VectorRef<> b)
{
//	a:
//	[               2.6              -0.6               0.8              -0.8 ]
//	[              -0.6               2.6              -0.8               0.8 ]
//	[               0.8              -0.8               1.4               0.6 ]
//	[              -0.8               0.8               0.6               1.4 ]
//	b:
//	[0.25125000000000014, 0.25125000000000003, 330, 330]

		a.resize(4, 4);
		a(0, 0) = 2.6;
		a(0, 1) = -0.6;
		a(0, 2) = 0.8;
		a(0, 3) = -0.8;

		a(1, 0) = -0.6;
		a(1, 1) = 2.6;
		a(1, 2) = -0.8;
		a(1, 3) = 0.8;

		a(2, 0) = 0.8;
		a(2, 1) = -0.8;
		a(2, 2) = 1.4;
		a(2, 3) = 0.6;

		a(3, 0) = -0.8;
		a(3, 1) = 0.8;
		a(3, 2) = 0.6;
		a(3, 3) = 1.4;

		b.resize(4);
		b(0) = 0.25125000000000014;
		b(1) = 0.25125000000000003;
		b(2) = 330;
		b(3) = 330;

//		const int el = 0;
//		for (int i = 0; i < 4; i++) {
//			a(el, i) = 0.0;
//			a(i, el) = 0.0;
//			b(el) = 0.0;
//		}
}

void setSys5(gpx::math::MatrixRef<> a, gpx::math::VectorRef<> b)
{
//	a:
//	[              2.6              -0.8               0.8 ]
//	[             -0.8               1.4               0.6 ]
//	[              0.8               0.6               1.4 ]
//	b:
//	[0.25125000000000003, 330, 330]

		a.resize(3, 3);

		a(0, 0) = 2.6;
		a(0, 1) = -0.8;
		a(0, 2) = 0.8;

		a(1, 0) = -0.8;
		a(1, 1) = 1.4;
		a(1, 2) = 0.6;

		a(2, 0) = 0.8;
		a(2, 1) = 0.6;
		a(2, 2) = 1.4;

		b.resize(3);
		b(0) = 0.25125000000000003;
		b(1) = 330;
		b(2) = 330;
}

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
	public:
		NNSolver(gpx::math::MatrixRef<N, N, T> a);

		gpx::math::Vector<N, T> solve(gpx::math::VectorRef<N, T> b);

		gpx::math::Vector<N, T> solve2(gpx::math::VectorRef<N, T> b);

		gpx::math::Vector<N, T> solve3(gpx::math::VectorRef<N, T> b);

		gpx::math::Vector<N, T> solve4(gpx::math::VectorRef<N, T> b);

	private:
		/**
		 * Zero matrix elements related to specific point. Zeroes i-th row and column
		 * elements of matrix @a.
		 * @param a matrix, which elements should be zeroed.
		 * @param i index of point for which matrix elements should be zeroed.
		 */
		void zeroMatrixPoint(gpx::math::MatrixRef<N, N, T> a, std::size_t el);

		/**
		 * Restore matrix elements related to specific point. Restores i-th row and column
		 * elements of matrix @a a using original matrix elements.
		 * @param a matrix, which elements should be restored.
		 * @param i index of point for which matrix elements should be restored.
		 */
		void restoreMatrixPoint(gpx::math::MatrixRef<N, N, T> a, std::size_t el);

		//standard solve
		void ssolve(gpx::math::MatrixRef<N, N, T> a, gpx::math::VectorRef<N, T> b, gpx::math::VectorRef<N, T> result);

		//recursive solve
		//returns lowest depth for which non-negative result has been calculated
		std::size_t rsolve(gpx::math::MatrixRef<N, N, T> a, gpx::math::VectorRef<N, T> b, gpx::math::VectorRef<N, T> result, std::size_t depth);

		void removeNegative(std::size_t i, gpx::math::MatrixRef<N, N, T> a, gpx::math::VectorRef<N, T> result);

		gpx::math::Matrix<N, N, T> m_a;
		gpx::math::Vector<N, T> m_b;
};

template <int EQ_FLAGS, std::size_t N, typename T>
NNSolver<EQ_FLAGS, N, T>::NNSolver(gpx::math::MatrixRef<N, N, T> a):
	m_a(a),
	m_b(0u)
{
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
//			//dividing upper triangle and lower triangle (b(i) contributions)
//			for (std::size_t jj = 0; jj < a.cols(); jj++)
//				a(i, jj) /= divisor;
//			b(i) /= divisor;
////			GPX_INFO("m_a: " << std::endl << a);
////			GPX_INFO("m_b: " << std::endl << b);
//			for (std::size_t ii = i + 1; ii < a.rows(); ii++) {
////				GPX_INFO("multiplier: " << a(ii, j));
//				T multiplier = a(ii, j);
//				//upper triangle
//				for (std::size_t jj = j + 1; jj < a.cols(); jj++)
//					a(ii, jj) -= multiplier * a(i, jj);
//				//lower triangle (calculating b(i) contributions)
//				for (std::size_t jj = 0; jj < j; jj++)
//					a(ii, jj) -= multiplier * a(i, jj);
//				//b vector
//				b(ii) -= multiplier * b(i);
//			}
//			GPX_INFO("m_a: " << std::endl << a);
//			GPX_INFO("m_b: " << std::endl << b);
//			i++;
//		}
//	}
//	//get solution from triangular matrix
//	i = a.rows();
//	do {
//		i--;
//		if (gpx::math::ape(a(i, i), T()))
//			result(i) = T();
//		else {
//			result(i) = b(i);
//			for (std::size_t j = i + 1; j < a.cols(); j++)
//				result(i) -= result(j) * a(i, j);
//			if (result(i) < 0) {
//				GPX_INFO("removing negative result(" << i << "): " << result);
//				for (std::size_t ii = i + 1; ii < a.rows(); ii++)
//					b(ii) += a(ii, i) * result(i);
//				b(i) -= result(i);
//				GPX_INFO("modified b vector: " << b);
//				i = a.rows();
//			}
//		}
//	} while (i > 0);
//	return result;
//}


template <int EQ_FLAGS, std::size_t N, typename T>
gpx::math::Vector<N, T> NNSolver<EQ_FLAGS, N, T>::solve(gpx::math::VectorRef<N, T> b)
{
	//Rough, fast written piece of code... although it solves systems of dependent equations.
	gpx::math::Vector<N, T> divisors(T(), b.size());
	std::vector<std::size_t> indices(b.size(), 0u);
	std::iota(indices.begin(), indices.end(), 0);
	gpx::math::Vector<N, T> bOrg(b);
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
			bOrg.swap(i, iPivot);
			std::swap(indices[i], indices[iPivot]);
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

//			for (std::size_t ii = i + 1; ii < a.rows(); ii++) {
////				GPX_INFO("multiplier: " << a(ii, j));
//				T multiplier = a(ii, j);
//				//upper triangle
//				for (std::size_t jj = j + 1; jj < a.cols(); jj++)
//					a(ii, jj) -= multiplier * a(i, jj);
//				//lower triangle (calculating b(i) contributions)
////				for (std::size_t jj = 0; jj < j; jj++)
////					a(ii, jj) -= multiplier * a(i, jj);
//				//b vector
////				b(ii) -= multiplier * b(i);
//			}
		}
		GPX_INFO("m_a: " << std::endl << a);
		GPX_INFO("m_b: " << std::endl << b);
		i++;
	}

	i = 0;
	while (i < a.rows()) {
//		result(i) = b(i) * a(i, i);
		for (std::size_t j = 0; j < a.cols(); j++)
			result(i) += a(i, j) * b(j);
		if (gpx::math::cgt(T(), result(i))) {
			GPX_INFO("removing negative result(" << i << "): " << result);
			GPX_INFO("b vector: " << b);
			GPX_INFO("divisors: " << divisors);
			GPX_INFO("indices[" << i << "]: " << indices[i]);
			std::size_t ii = indices[i];
			b(ii) -= result(i) / a(i, ii);
			if (b(ii) * divisors(ii) < bOrg(ii)) {
				GPX_DEBUG("required b(" << ii << ") = " << b(ii) * divisors(ii) << " is smaller than original value");
//				b(i) = bOrg(i) / divisors(i);
			}
//			if (b(i) < T())
//				b(i) = T();
			GPX_INFO("new b vector: " << b);

			#pragma message("temporary code")
			for (std::size_t iTmp = 0; iTmp < b.size(); iTmp++)
				result(iTmp) = b(iTmp) * divisors(iTmp);
			GPX_INFO("new b vector with original values: " << result);
			result.zero();
			for (std::size_t iTmp = 0; iTmp < a.rows(); iTmp++)
				for (std::size_t jTmp = 0; jTmp < a.cols(); jTmp++)
					result(iTmp) += a(iTmp, jTmp) * b(jTmp);
			GPX_INFO("new result vector: " << result);
			//end #pragma message("temporary code")

			result.zero();
			i = 0;
		} else
			i++;
	}

	//get solution from triangular matrix
//	i = a.rows();
//	do {
//		i--;
//		if (gpx::math::ape(a(i, i), T()))
//			result(i) = T();
//		else {
//			result(i) = b(i);
//			for (std::size_t j = i + 1; j < a.cols(); j++)
//				result(i) -= result(j) * a(i, j);
//			if (result(i) < 0) {
//				GPX_INFO("removing negative result(" << i << "): " << result);
//				for (std::size_t ii = i + 1; ii < a.rows(); ii++)
//					b(ii) += a(ii, i) * result(i);
//				b(i) -= result(i);
//				GPX_INFO("modified b vector: " << b);
//				i = a.rows();
//			}
//		}
//	} while (i > 0);
	return result;
}

template <int EQ_FLAGS, std::size_t N, typename T>
gpx::math::Vector<N, T> NNSolver<EQ_FLAGS, N, T>::solve2(gpx::math::VectorRef<N, T> b)
{
	//Rough, fast written piece of code... although it solves systems of dependent equations.

	gpx::math::Vector<N, T> result(T(), b.size());
#pragma message("temporary code")
	gpx::math::Vector<> bOrg(b);
	gpx::math::Vector<N, T> divisors(T(), b.size());	//tmp
//end pragma
	gpx::math::Matrix<N, N, T> a(m_a);
	std::vector<std::size_t> iWhere(b.size(), 0u);
	std::vector<std::size_t> iWhat(b.size(), 0u);
	std::vector<std::size_t> jWhat(b.size(), 0u);

	for (std::size_t i = 0; i < b.size(); i++) {
		iWhat[i] = i;	//where is
		iWhere[i] = i;	//where is
		jWhat[i] = i;	//what is
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
			a.swapRows(i, iPivot);
			b.swap(i, iPivot);
			std::swap(iWhat[i], iWhat[iPivot]);
			iWhere[iWhat[i]] = i;
			iWhere[iWhat[iPivot]] = iPivot;
//			std::swap(iWhere[iWhere[i]], iWhere[iWhere[iPivot]]);
			GPX_DEBUG("swaping row " << i << " with row " << iPivot);
			std::cout << "iInd: ";
			for (auto it = iWhere.begin(); it != iWhere.end(); ++it)
				std::cout << *it << " ";
		}
		if (jPivot != j) {
			a.swapCols(j, jPivot);
			std::swap(jWhat[j], jWhat[jPivot]);
			GPX_DEBUG("swaping col " << jWhat[j] << " with col " << jWhat[jPivot]);
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
			GPX_WARN("could not remove negative value in 10 steps");
			i++;
			continue;
		}

		if (gpx::math::cgt(T(), result(jj))) {
#pragma message("temporary code")
			result.zero();
			for (std::size_t iTmp = 0; iTmp < a.rows(); iTmp++)
				for (std::size_t jTmp = 0; jTmp < a.cols(); jTmp++)
					result(jWhat[iTmp]) += a(iTmp, jTmp) * b(jTmp);
//			GPX_INFO("result vector: " << result);
//endtmp

			GPX_INFO("removing negative result(" << jj << "): " << result);
			GPX_INFO("b vector: " << b);
			std::size_t ii = iWhere[jj];
			std::cout << "iInd: ";
			for (auto it = iWhere.begin(); it != iWhere.end(); ++it)
				std::cout << *it << " ";
			std::cout << "\n";
			std::cout << "jInd: ";
			for (auto it = jWhat.begin(); it != jWhat.end(); ++it)
				std::cout << *it << " ";
			std::cout << "\n";
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

template <int EQ_FLAGS, std::size_t N, typename T>
gpx::math::Vector<N, T> NNSolver<EQ_FLAGS, N, T>::solve3(gpx::math::VectorRef<N, T> b)
{
	gpx::math::Vector<N, T> result(T(), b.size());
	gpx::math::Matrix<N, N, T> a(m_a);

	std::size_t i = 0;
	//considering column j
	for (std::size_t j = 0; j < a.cols(); j++) {
		//find max pivot
		std::size_t iPivot = i;
		for (std::size_t ii = i + 1; ii < a.rows(); ii++)
			if (std::abs(a(ii, j)) > std::abs(a(iPivot, j)))
				iPivot = ii;
		if (iPivot != i) {
			a.swapRows(i, iPivot);
			b.swap(i, iPivot);
		}
		T divisor = a(i, j);
		if (!gpx::math::ape(divisor, T())) {
			for (std::size_t jj = j; jj < a.cols(); jj++)
				a(i, jj) /= divisor;
			b(i) /= divisor;
			for (std::size_t ii = i + 1; ii < a.rows(); ii++) {
				// a(ii, j) is a multiplier;
				for (std::size_t jj = j + 1; jj < a.cols(); jj++)
					a(ii, jj) -= a(ii, j) * a(i, jj);
				b(ii) -= a(ii, j) * b(i);
			}
			GPX_INFO("m_a: " << std::endl << a);
			GPX_INFO("m_b: " << std::endl << b);
		}
		i++;
	}
	//obtain solution from triangular matrix
//	std::vector<std::size_t> negatives;
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
		if (gpx::math::cgt(T(), result(i))) {
			//zero column i of original matrix m_a
//			if (!solve(result, a, b))



		}
//			negatives.push_back(i);
	} while (i > 0);
	return result;
}

template <int EQ_FLAGS, std::size_t N, typename T>
gpx::math::Vector<N, T> NNSolver<EQ_FLAGS, N, T>::solve4(gpx::math::VectorRef<N, T> b)
{
	gpx::math::Vector<N, T> result(T(), b.size());
	gpx::math::Vector<N, T> presult(T(), b.size());
	gpx::math::Matrix<N, N, T> a_copy(m_a);
	m_b = b;

	solve(a_copy, b, result);
	bool negatives = false;
	std::size_t i = 0;
	do {
		if (gpx::math::cgt(T(), result(i))) {
			a_copy =
			negatives = true;
			zeroMatrixPoint(a_copy, i);
			b_copy = b;
			gpx::math::Vector<N, T> rresult(T(), b.size());
			if (rsolve(a_copy, b_copy, rresult, 0) < depth)
				presult = rresult;
			restoreMatrixPoint(a_copy, i);
		}
		i++;
	} while (negatives && i < result.size());

	for (std::size_t i = 0; i < result.size(); i++) {
		if (gpx::math::cgt(T(), result(i))) {
			gpx::math::Vector<N, T> rresult(T(), b.size());
			zeroMatrixPoint(a_copy, i);
			solve(a_copy, b_copy, rresult);
			for (std::size_t j = 0; j < rresult.size(); j++)
				if (gpx::math::cgt(T(), rresult(j))) {
					result = rresult;
					i = result.size(); //exit loop
				}
			restoreMatrixPoint(a_copy, i);
		}
	}
	return result;
}

template <int EQ_FLAGS, std::size_t N, typename T>
void NNSolver<EQ_FLAGS, N, T>::zeroMatrixPoint(gpx::math::MatrixRef<N, N, T> a, std::size_t el)
{
	for (int i = 0; i < a.rows(); i++) {
		a(el, i) = T();
		a(i, el) = T();
	}
}

template <int EQ_FLAGS, std::size_t N, typename T>
void NNSolver<EQ_FLAGS, N, T>::restoreMatrixPoint(gpx::math::MatrixRef<N, N, T> a, std::size_t el)
{
	for (int i = 0; i < a.rows(); i++) {
		a(el, i) = m_a(el, i);
		a(i, el) = m_a(i, el);
	}
}

template <int EQ_FLAGS, std::size_t N, typename T>
void NNSolver<EQ_FLAGS, N, T>::solve(gpx::math::MatrixRef<N, N, T> a, gpx::math::VectorRef<N, T> b, gpx::math::VectorRef<N, T> result)
{
	std::size_t i = 0;
	//considering column j
	for (std::size_t j = 0; j < a.cols(); j++) {
		//find max pivot
		std::size_t iPivot = i;
		for (std::size_t ii = i + 1; ii < a.rows(); ii++)
			if (std::abs(a(ii, j)) > std::abs(a(iPivot, j)))
				iPivot = ii;
		if (iPivot != i) {
			a.swapRows(i, iPivot);
			b.swap(i, iPivot);
		}
		T divisor = a(i, j);
		if (!gpx::math::ape(divisor, T())) {
			for (std::size_t jj = j; jj < a.cols(); jj++)
				a(i, jj) /= divisor;
			b(i) /= divisor;
			for (std::size_t ii = i + 1; ii < a.rows(); ii++) {
				// a(ii, j) is a multiplier;
				for (std::size_t jj = j + 1; jj < a.cols(); jj++)
					a(ii, jj) -= a(ii, j) * a(i, jj);
				b(ii) -= a(ii, j) * b(i);
			}
			GPX_INFO("m_a: " << std::endl << a);
			GPX_INFO("m_b: " << std::endl << b);
		}
		i++;
	}
	//obtain solution from triangular matrix
//	std::vector<std::size_t> negatives;
//	gpx::math::Vector<N, T> result(T(), b.size());
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
}

template <int EQ_FLAGS, std::size_t N, typename T>
std::size_t NNSolver<EQ_FLAGS, N, T>::rsolve(gpx::math::MatrixRef<N, N, T> a, gpx::math::VectorRef<N, T> b, gpx::math::VectorRef<N, T> result, std::size_t depth)
{
	std::size_t newDepth = std::numeric_limits<std::size_t>::max();
	solve(a, b, result);
	for (std::size_t i = 0; i < result.size(); i++) {
		if (gpx::math::cgt(T(), result(i))) {
			gpx::math::Vector<N, T> presult(T(), b.size());
			zeroMatrixPoint(a, i);
			//zero column i of original matrix m_a
			b = m_b;
			std::size_t oldDepth = newDepth;
			newDepth = rsolve(a, b, presult, depth + 1);
			if (newDepth < oldDepth)
				result = presult;
			restoreMatrixPoint(a, i);
		}
	}
	if (newDepth != std::numeric_limits<std::size_t>::max())
		return newDepth;
	else
		return depth;
}

template <int EQ_FLAGS, std::size_t N, typename T>
void NNSolver<EQ_FLAGS, N, T>::removeNegative(std::size_t i, gpx::math::MatrixRef<N, N, T> a, gpx::math::VectorRef<N, T> result)
{
	GPX_INFO("removing negative result(" << i << "): " << result);
	for (std::size_t ii = i + 1; ii < a.rows(); ii++)
		result(ii) += a(ii, i) * result(i);
	result(i) = T();
	GPX_INFO("modified result vector: " << result);
}

int main()
{
#ifdef NDEBUG
	cout << "NDEBUG" << endl;
#endif


//	std::srand(time(0));
	std::srand(3434);
	std::size_t m = 3u;
	std::size_t n = 3u;
	gpx::math::Matrix<> a(m, n);
	for (std::size_t i = 0; i < a.rows(); i++)
		for (std::size_t j = 0; j < a.cols(); j++)
			a(i, j) = drand<gpx::real_t>();

	gpx::math::Vector<> b(n);
	for (std::size_t i = 0; i < b.size(); i++)
		b(i) = drand<gpx::real_t>();

	setSys4(a, b);

	gpx::math::Matrix<> aCopy(a);
	cout << "a:" << endl << a;

	gpx::math::Vector<> bCopy(b);
	cout << "b:" << endl << b;

	cout << "solving..." << endl;
//	gpx::math::Solver<gpx::math::EQ_GENERAL, gpx::math::SIZE_DYNAMIC, gpx::real_t> solver(a);
	NNSolver<gpx::math::EQ_GENERAL, gpx::math::SIZE_DYNAMIC, gpx::real_t> solver(a);
//	gpx::math::Vector<> result = solver.solve(b);
//	gpx::math::Vector<> result = solver.solve2(b);
	gpx::math::Vector<> result = solver.solve3(b);
	cout << "result: " << result;
	cout << "ax:" << endl;
	cout << aCopy.prod(result);
	cout << "b:" << endl;
	cout << bCopy;

//	TestStringStream::Silent = false;
//	silent = false;
	std::srand(time(0));

	//@todo turn on Vector and VectorPtr dependend tests
//	const_VectorRefTest<gpx::math::const_VectorRef, 1, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::Matrix>();
//	const_VectorRefTest<gpx::math::const_VectorRef, 2, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::Matrix>();
//	const_VectorRefTest<gpx::math::const_VectorRef, 3, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::Matrix>();
//	const_VectorRefTest<gpx::math::const_VectorRef, 4, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::Matrix>();
//	const_VectorRefTest<gpx::math::const_VectorRef, 5, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::Matrix>();
//	const_VectorRef2Test<gpx::math::const_VectorRef, 2, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef>();
//	const_VectorRef3Test<gpx::math::const_VectorRef, 3, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef>();
////	const_VectorRefTest<Dconst_VectorPtrWrapper, 1, gpx::real_t, DVectorWrapper, DVectorPtrWrapper>();
////	const_VectorRefTest<Dconst_VectorPtrWrapper, 2, gpx::real_t, DVectorWrapper, DVectorPtrWrapper>();
////	const_VectorRefTest<Dconst_VectorPtrWrapper, 3, gpx::real_t, DVectorWrapper, DVectorPtrWrapper>();
////	const_VectorRefTest<Dconst_VectorPtrWrapper, 4, gpx::real_t, DVectorWrapper, DVectorPtrWrapper>();
//	const_VectorRefTest<Dconst_VectorPtrWrapper, 5, gpx::real_t, DVectorWrapper, DVectorPtrWrapper>();
//	const_VectorRefDynamicTest<gpx::math::const_VectorRef, 1, gpx::real_t>();

//	VectorRefTest<gpx::math::VectorRef, 1, gpx::real_t, gpx::math::Vector, gpx::math::const_VectorRef>();
//	VectorRefTest<gpx::math::VectorRef, 2, gpx::real_t, gpx::math::Vector, gpx::math::const_VectorRef>();
//	VectorRefTest<gpx::math::VectorRef, 3, gpx::real_t, gpx::math::Vector, gpx::math::const_VectorRef>();
//	VectorRefTest<gpx::math::VectorRef, 4, gpx::real_t, gpx::math::Vector, gpx::math::const_VectorRef>();
//	VectorRefTest<gpx::math::VectorRef, 5, gpx::real_t, gpx::math::Vector, gpx::math::const_VectorRef>();
//	VectorRef2Test<gpx::math::VectorRef, 2, gpx::real_t, gpx::math::Vector, gpx::math::const_VectorRef>();
//	VectorRef3Test<gpx::math::VectorRef, 3, gpx::real_t, gpx::math::Vector, gpx::math::const_VectorRef>();
//	const_VectorRefTest<gpx::math::VectorRef, 1, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::Matrix>();
//	const_VectorRefTest<gpx::math::VectorRef, 2, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::Matrix>();
//	const_VectorRefTest<gpx::math::VectorRef, 3, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::Matrix>();
//	const_VectorRefTest<gpx::math::VectorRef, 4, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::Matrix>();
//	const_VectorRefTest<gpx::math::VectorRef, 5, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::Matrix>();
//	const_VectorRef2Test<gpx::math::VectorRef, 2, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef>();
//	const_VectorRef3Test<gpx::math::VectorRef, 3, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef>();
////	VectorPtrTest<DVectorPtrWrapper, 1, gpx::real_t, DVectorWrapper, Dconst_VectorPtrWrapper>();
////	VectorPtrTest<DVectorPtrWrapper, 2, gpx::real_t, DVectorWrapper, Dconst_VectorPtrWrapper>();
////	VectorPtrTest<DVectorPtrWrapper, 3, gpx::real_t, DVectorWrapper, Dconst_VectorPtrWrapper>();
////	VectorPtrTest<DVectorPtrWrapper, 4, gpx::real_t, DVectorWrapper, Dconst_VectorPtrWrapper>();
//	VectorPtrTest<DVectorPtrWrapper, 5, gpx::real_t, DVectorWrapper, Dconst_VectorPtrWrapper>();
//	VectorPtrDynamicTest<gpx::math::VectorRef, 1, gpx::real_t>();

//	VectorTest<gpx::math::Vector, 1, gpx::real_t, gpx::math::const_VectorRef, gpx::math::VectorRef>();
//	VectorTest<gpx::math::Vector, 2, gpx::real_t, gpx::math::const_VectorRef, gpx::math::VectorRef>();
//	VectorTest<gpx::math::Vector, 3, gpx::real_t, gpx::math::const_VectorRef, gpx::math::VectorRef>();
//	VectorTest<gpx::math::Vector, 4, gpx::real_t, gpx::math::const_VectorRef, gpx::math::VectorRef>();
//	VectorTest<gpx::math::Vector, 5, gpx::real_t, gpx::math::const_VectorRef, gpx::math::VectorRef>();
//	Vector2Test<gpx::math::Vector, 2, gpx::real_t, gpx::math::const_VectorRef, gpx::math::VectorRef>();
//	Vector3Test<gpx::math::Vector, 3, gpx::real_t, gpx::math::const_VectorRef, gpx::math::VectorRef>();
////	VectorPtrTest<gpx::math::Vector, 1, gpx::real_t>();
////	VectorPtrTest<gpx::math::Vector, 2, gpx::real_t>();
////	VectorPtrTest<gpx::math::Vector, 3, gpx::real_t>();
////	VectorPtrTest<gpx::math::Vector, 4, gpx::real_t>();
////	VectorPtrTest<gpx::math::Vector, 5, gpx::real_t>();
////	const_VectorPtrTest<gpx::math::Vector, 1, gpx::real_t>();
////	const_VectorPtrTest<gpx::math::Vector, 2, gpx::real_t>();
////	const_VectorPtrTest<gpx::math::Vector, 3, gpx::real_t>();
////	const_VectorPtrTest<gpx::math::Vector, 4, gpx::real_t>();
////	const_VectorPtrTest<gpx::math::Vector, 5, gpx::real_t>();
//	VectorDynamicTest<gpx::math::Vector, 1, gpx::real_t>();
//	VectorDynamicTest<gpx::math::Vector, 2, gpx::real_t>();
//	VectorDynamicTest<gpx::math::Vector, 3, gpx::real_t>();
//	VectorDynamicTest<gpx::math::Vector, 4, gpx::real_t>();
//	VectorDynamicTest<gpx::math::Vector, 5, gpx::real_t>();
//	VectorTest<DVectorWrapper, 1, gpx::real_t, gpx::math::const_VectorRef, gpx::math::VectorRef>();
//	VectorTest<DVectorWrapper, 2, gpx::real_t, gpx::math::const_VectorRef, gpx::math::VectorRef>();
//	VectorTest<DVectorWrapper, 3, gpx::real_t, gpx::math::const_VectorRef, gpx::math::VectorRef>();
//	VectorTest<DVectorWrapper, 4, gpx::real_t, gpx::math::const_VectorRef, gpx::math::VectorRef>();
//	VectorTest<DVectorWrapper, 5, gpx::real_t, gpx::math::const_VectorRef, gpx::math::VectorRef>();
//	const_VectorRefTest<Dconst_VectorRefWrapper, 1, gpx::real_t, DVectorWrapper, DVectorRefWrapper, DMatrixWrapper>();
//	const_VectorRefTest<Dconst_VectorRefWrapper, 2, gpx::real_t, DVectorWrapper, DVectorRefWrapper, DMatrixWrapper>();
//	const_VectorRefTest<Dconst_VectorRefWrapper, 3, gpx::real_t, DVectorWrapper, DVectorRefWrapper, DMatrixWrapper>();
//	const_VectorRefTest<Dconst_VectorRefWrapper, 4, gpx::real_t, DVectorWrapper, DVectorRefWrapper, DMatrixWrapper>();
//	const_VectorRefTest<Dconst_VectorRefWrapper, 5, gpx::real_t, DVectorWrapper, DVectorRefWrapper, DMatrixWrapper>();
//	VectorRefTest<DVectorWrapper, 1, gpx::real_t, DVectorWrapper, DVectorWrapper, DMatrixWrapper>();
//	VectorRefTest<DVectorWrapper, 2, gpx::real_t, DVectorWrapper, DVectorWrapper, DMatrixWrapper>();
//	VectorRefTest<DVectorWrapper, 3, gpx::real_t, DVectorWrapper, DVectorWrapper, DMatrixWrapper>();
//	VectorRefTest<DVectorWrapper, 4, gpx::real_t, DVectorWrapper, DVectorWrapper, DMatrixWrapper>();
//	VectorRefTest<DVectorWrapper, 5, gpx::real_t, DVectorWrapper, DVectorWrapper, DMatrixWrapper>();


//	MatrixTest<gpx::math::Matrix, 1, 1, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 1, 2, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 1, 3, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 1, 4, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 1, 5, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 2, 1, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 2, 2, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 2, 3, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 2, 4, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 2, 5, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 3, 1, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 3, 2, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 3, 3, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 3, 4, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 3, 5, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 4, 1, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 4, 2, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 4, 3, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 4, 4, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 4, 5, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 5, 1, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 5, 2, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 5, 3, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 5, 4, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();
//	MatrixTest<gpx::math::Matrix, 5, 5, gpx::real_t, gpx::math::Vector, gpx::math::VectorRef, gpx::math::const_VectorRef>();

//	MatrixSqTest<gpx::math::Matrix, 1, gpx::real_t>();
//	MatrixSqTest<gpx::math::Matrix, 2, gpx::real_t>();
//	MatrixSqTest<gpx::math::Matrix, 3, gpx::real_t>();
//	MatrixSqTest<gpx::math::Matrix, 4, gpx::real_t>();
//	MatrixSqTest<gpx::math::Matrix, 5, gpx::real_t>();

//	MatrixDynamicTest<0, 0, gpx::real_t>();
//	MatrixDynamicTest<0, 1, gpx::real_t>();
//	MatrixDynamicTest<0, 2, gpx::real_t>();
//	MatrixDynamicTest<1, 1, gpx::real_t>();
//	MatrixTest<DMatrixWrapper, 1, 1, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 1, 2, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 1, 3, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 1, 4, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 1, 5, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 2, 1, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 2, 2, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 2, 3, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 2, 4, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 2, 5, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 3, 1, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 3, 2, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 3, 3, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 3, 4, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 3, 5, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 4, 1, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 4, 2, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 4, 3, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 4, 4, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 4, 5, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 5, 1, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 5, 2, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 5, 3, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 5, 4, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixTest<DMatrixWrapper, 5, 5, gpx::real_t,  DVectorWrapper, DVectorRefWrapper, Dconst_VectorRefWrapper>();
//	MatrixSqTest<DMatrixWrapper, 1, gpx::real_t>();
//	MatrixSqTest<DMatrixWrapper, 2, gpx::real_t>();
//	MatrixSqTest<DMatrixWrapper, 3, gpx::real_t>();
//	MatrixSqTest<DMatrixWrapper, 4, gpx::real_t>();
//	MatrixSqTest<DMatrixWrapper, 5, gpx::real_t>();

	return 0;
}
