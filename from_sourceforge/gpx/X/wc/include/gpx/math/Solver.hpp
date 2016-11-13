/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_SOLVER_HPP_
#define GPX_X_MATH_SOLVER_HPP_

#include "structures.hpp"

#include GPX_X_MATH_BACKEND_HEADER
#include GPX_X_MATH_BACKEND_SOLVER_HEADER

namespace gpx {
namespace math {

/**
 * Solver members initialization. Base-from-member idiom to initialize members
 * before calling parent class constructor.
 */
template <int EQ_FLAGS, std::size_t N = SIZE_DYNAMIC, typename T = real_t>
class SolverMembersInit
{
	protected:
		SolverMembersInit(Matrix<N, N, T> & a);

#ifndef NDEBUG
	protected:
		Matrix<N, N, T> m_aCopy;	///< Untouched copy of matrix A for solution check.
#endif /* NDEBUG */
};

/**
 * Linear equation solver. Solver may use arbitrary method to solve equation.
 * @param EQ_FLAGS flags indicating equation type.
 * @param N linear system size in terms of number of equations.
 * @param T underlying type.
 */
template <int EQ_FLAGS, std::size_t N = SIZE_DYNAMIC, typename T = real_t>
class Solver : private SolverMembersInit<EQ_FLAGS, N, T>,
			   public GPX_X_MATH_BACKEND_NAMESPACE::Solver<EQ_FLAGS, N, T>
{
	typedef GPX_X_MATH_BACKEND_NAMESPACE::Solver<EQ_FLAGS, N, T> Parent;

	public:
		/**
		 * Constructor.
		 * @param a matrix representing left hand side of equation system (ax = b).
		 *
		 * @warning matrix @a a should be accessible during whole solver lifetime.
		 * Solver is free to modify matrix.
		 */
		Solver(Matrix<N, N, T> & a);

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
SolverMembersInit<EQ_FLAGS, N, T>::SolverMembersInit(Matrix<N, N, T> & a)
#ifndef NDEBUG
	: m_aCopy(a)
#endif /* NDEBUG */
{
}

template <int EQ_FLAGS, std::size_t N, typename T>
inline
Solver<EQ_FLAGS, N, T>::Solver(Matrix<N, N, T> & a):
	SolverMembersInit<EQ_FLAGS, N, T>(a),
	Parent(a)
{
}

template <int EQ_FLAGS, std::size_t N, typename T>
inline
Vector<N, T> Solver<EQ_FLAGS, N, T>::solve(VectorRef<N, T> b)
{
#ifndef NDEBUG
	//check solution
	const Vector<N, T> bCopy(b);
	const Vector<N, T> result = Parent::solve(b);
	const Vector<N, T> ax = SolverMembersInit<EQ_FLAGS, N, T>::m_aCopy.prod(result);
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

#endif /* GPX_X_MATH_SOLVER_HPP_ */

//(c)MP: Copyright © 2011, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
