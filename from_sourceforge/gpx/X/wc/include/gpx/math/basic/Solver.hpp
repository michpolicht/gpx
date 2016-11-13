/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_BASIC_SOLVER_HPP_
#define GPX_X_MATH_BASIC_SOLVER_HPP_

//#note: "Solver.imp.hpp" included near eof

namespace gpx {
namespace math {
namespace basic {

/**
 * Linear equation solver. Basic implementation, using Jordan elimination with
 * pivoting.
 * @param EQ_FLAGS flags indicating equation type.
 * @param N linear system size in terms of number of equations.
 * @param T underlying type.
 */
template <int EQ_FLAGS, std::size_t N, typename T>
class Solver
{
	protected:
		Solver(gpx::math::Matrix<N, N, T> & a);

	protected:
		gpx::math::Vector<N, T> solve(gpx::math::VectorRef<N, T> b);

	private:
		gpx::math::Matrix<N, N, T> & m_a;
};

}
}
}

#include "Solver.imp.hpp"

#endif /* GPX_X_MATH_BASIC_SOLVER_HPP_ */

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
