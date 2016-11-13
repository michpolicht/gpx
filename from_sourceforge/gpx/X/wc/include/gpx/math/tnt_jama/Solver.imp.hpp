/**
 * @file
 * @brief .
 */

#include <algorithm>

namespace gpx {
namespace math {
namespace tnt_jama {

template <int EQ_FLAGS, std::size_t N, typename T>
inline
Solver<EQ_FLAGS, N, T>::Solver(gpx::math::Matrix<N, N, T> & a)
{
	std::size_t dim = a.rows();

	a.transpose();
	TNT::Array2D<T> AT(dim, dim, a.ptr());
	TNT::Array1D<T> s(dim);
	TNT::Array2D<T> U(dim, dim);
	TNT::Array2D<T> V(dim, dim);

	JAMA::SVD<T> svd(AT);
	svd.getSingularValues(s);
	for (std::size_t i = 0; i < dim; i++)
		if (s[i] != T())
			s[i] = static_cast<T>(1.0) / s[i];
	svd.getU(U);
	svd.getV(V);

	for (std::size_t i = 0; i < dim; i++)
		for(std::size_t j = i + 1; j < dim; j++)
			std::swap(U[i][j], U[j][i]);

	for (std::size_t i = 0; i < dim; i++)
		for (std::size_t j = 0; j < dim; j++)
			V[i][j] *= s[j];

	Array2D<T> VUT = TNT::matmult(V, U);
	m_VUT.resize(dim, dim);
	for (std::size_t i = 0; i < a.rows(); i++)
		for (std::size_t j = 0; j < a.cols(); j++)
			m_VUT(i, j) = VUT[i][j];
}

template <int EQ_FLAGS, std::size_t N, typename T>
inline
gpx::math::Vector<N, T> Solver<EQ_FLAGS, N, T>::solve(gpx::math::VectorPtr<N, T> & b)
{
	gpx::math::Vector<N, T> result;
	result.resize(b.size());

	for (std::size_t i = 0; i < result.size(); i++)
		for (std::size_t j = 0; j < result.size(); j++)
			result(i) += m_VUT(i, j) * b(j);

	return result;
}

}
}
}

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
