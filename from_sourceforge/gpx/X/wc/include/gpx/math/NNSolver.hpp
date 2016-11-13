/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_NNSOLVER_HPP_
#define GPX_X_MATH_NNSOLVER_HPP_

#include "structures.hpp"

#include GPX_X_MATH_BACKEND_HEADER
#include GPX_X_MATH_BACKEND_NNSOLVER_HEADER

namespace gpx {
namespace math {

/**
 * Solver members initialization. Base-from-member idiom to initialize members
 * before calling parent class constructor.
 */
template <int EQ_FLAGS, std::size_t N = SIZE_DYNAMIC, typename T = real_t>
class NNSolverMembersInit
{
	protected:
		NNSolverMembersInit(const_MatrixRef<N, N, T> a);

#ifndef NDEBUG
	protected:
		Matrix<N, N, T> m_aCopy;	///< Untouched copy of matrix A for solution check.
#endif /* NDEBUG */
};

/**
 * Non-negative linear equation solver. Results produced by this solver are guaranteed to be
 * non negative. If negative solution occurs solver is obligged to clip system of equations,
 * so that negative result is eliminated. Solver may use arbitrary method to solve equation.
 * @param EQ_FLAGS flags indicating equation type.
 * @param N linear system size in terms of number of equations.
 * @param T underlying type.
 */
template <int EQ_FLAGS, std::size_t N = SIZE_DYNAMIC, typename T = real_t>
class NNSolver : private NNSolverMembersInit<EQ_FLAGS, N, T>,
				 public GPX_X_MATH_BACKEND_NAMESPACE::NNSolver<EQ_FLAGS, N, T>
{
	typedef GPX_X_MATH_BACKEND_NAMESPACE::NNSolver<EQ_FLAGS, N, T> Parent;

	public:
		/**
		 * Constructor.
		 * @param a matrix representing left hand side of equation system (ax = b).
		 *
		 * @warning matrix @a a should be accessible during whole solver lifetime.
		 * Solver is free to modify matrix.
		 */
		NNSolver(MatrixRef<N, N, T> a);

		/**
		 * Solve. Finds solution of equation system given in form ax = b.
		 * @param b vector representing right hand side of equation system.
		 * @return solution of equation system, which is a formerly unknown vector x.
		 *
		 * @warning solver is free to modify @a b vector.
		 */
		Vector<N, T> solve(VectorRef<N, T> b);
};

template <int EQ_FLAGS, std::size_t N, typename T>
inline
NNSolverMembersInit<EQ_FLAGS, N, T>::NNSolverMembersInit(const_MatrixRef<N, N, T> a)
#ifndef NDEBUG
	: m_aCopy(a)
#endif /* NDEBUG */
{
}

template <int EQ_FLAGS, std::size_t N, typename T>
inline
NNSolver<EQ_FLAGS, N, T>::NNSolver(MatrixRef<N, N, T> a):
	NNSolverMembersInit<EQ_FLAGS, N, T>(a),
	Parent(a)
{
}

template <int EQ_FLAGS, std::size_t N, typename T>
inline
Vector<N, T> NNSolver<EQ_FLAGS, N, T>::solve(VectorRef<N, T> b)
{
#ifndef NDEBUG
	//check solution
	const Vector<N, T> bCopy(b);
	const Vector<N, T> result = Parent::solve(b);
	const Vector<N, T> ax = NNSolverMembersInit<EQ_FLAGS, N, T>::m_aCopy.prod(result);
//	GPX_INFO("bcopy: " << bCopy);
//	GPX_INFO("ax: " << ax);
	for (std::size_t i = 0; i < bCopy.size(); i++)
		if (!ape(bCopy(i) - ax(i), T()))
			GPX_WARN("solution Ax(" << i << ")=" << ax(i) << " does not match right hand side b=" << bCopy(i) << " of Ax = b system");
	return result;
#else
	return Parent::solve(b);
#endif /* NDEBUG */
}

}
}

#endif /* GPX_X_MATH_NNSOLVER_HPP_ */
