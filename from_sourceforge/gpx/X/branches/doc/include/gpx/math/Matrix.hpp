/**
 * @file
 * @brief .
 */

#include "_structures_warning.hpp"


namespace gpx {
namespace math {


/**
 * General MxN (M rows, N cols) matrix. Not implemented yet.
 */
template <std::size_t M, std::size_t N>
class Matrix
{
	public:
		static const std::size_t ROWS = M;
		static const std::size_t COLS = N;
		static const std::size_t SIZE = M*N;
//		static int PrintWidth;	//todo uncomment and initialize

	public:
		real_t m_elements[N*M];
};

/**
 * NxN matrix specialization. Matrix is internally represented in OpenGL column-major
 * style. This class should act as a container only. Numerical algorithms are naive
 * implementations to fulfill basic functionality.
 */
template <std::size_t N>
class Matrix<N, N>
{
	public:
		static const std::size_t ROWS = N;
		static const std::size_t COLS = N;
		static const std::size_t SIZE = N*N;
		static int PrintWidth;

	protected:
		real_t m_elements[N*N];


	private:
		/**
		 * Determinant helper.
		 */
		real_t _det(const real_t * elements, std::size_t size) const;

	public:
		/**
		 * Default constructor. Initializes matrix with identity values.
		 */
		Matrix();

		/**
		 * Constructor. Constructs uninitialized matrix or matrix initialized with zeros.
		 * @param init if @p true, matrix is initialized with zeros. Otherwise
		 * no initialization is performed.
		 */
		Matrix(bool init);

		/**
		 * Constructor. Construct matrix with all elements set to value specified by @a d.
		 * @param d value to be set on all matrix elements.
		 */
		Matrix(real_t d);

		/**
		 * Constructor. Create matrix from given data.
		 * @param elements array of elements in OpenGL column-major format.
		 */
		Matrix(real_t * elements);

		/**
		 * Function call operator. Get i,j element of matrix. This is row-major interface
		 * for accessing matrix elements.
		 * @param i row.
		 * @param j column.
		 * @return i,j elements.
		 */
		real_t & operator()(std::size_t i, std::size_t j);

		/**
		 * Const version of function call operator.
		 * @param i row.
		 * @param j column.
		 *
		 * @return i,j element.
		 */
		real_t operator()(std::size_t i, std::size_t j) const;

		/**
		 * Conversion to real_t *. Returns pointer to OpenGL style array that
		 * represents matrix in column-major format.
		 *
		 * @return pointer to one dimensional array representing a matrix. A
		 * matrix is represented in column-major order, which is OpenGL style
		 * of matrix representation. Transpose matrix to obtain common row-major
		 * format.
		 */
		operator real_t *();

		/**
		 * Conversion to const real_t *. Const version of conversion operator.
		 *
		 * @return pointer to array representing matrix.
		 *
		 * @see operator real_t *().
		 */
		operator const real_t *() const;

		/**
		 * Addition assignment.
		 */
		Matrix<N,N> & operator+=(const Matrix<N,N> & other);

		/**
		 * Addition.
		 */
		Matrix<N,N> operator+(const Matrix<N,N> & other);

		/**
		 * Subtraction assignment.
		 */
		Matrix<N,N> & operator-=(const Matrix<N,N> & other);

		/**
		 * Subtraction.
		 */
		Matrix<N,N> operator-(const Matrix<N,N> & other);

		/**
		 * Multiplication assignment.
		 */
		Matrix<N,N> & operator*=(const Matrix<N,N> & other);

		/**
		 * Multiplication.
		 */
		Matrix<N,N> operator*(const Matrix<N,N> & other);

		/**
		 * Get elements. Direct access to array of elements.
		 */
		real_t * elements();

		/**
		 * Get succeeding elements. Direct access to elements succeeding (i,j) element of
		 * matrix.
		 * @param i row.
		 * @param j column.
		 * @return elements succeeding (i,j) element of matrix.
		 */
		real_t * elements(std::size_t i, std::size_t j);

		/**
		 * Reset matrix to zero matrix.
		 *
		 * @return matrix reference.
		 */
		Matrix<N,N> & zero();

		/**
		 * Reset matrix to identity matrix.
		 *
		 * @return matrix reference.
		 */
		Matrix<N,N> & identity();

		/**
		 * Transpose matrix.
		 *
		 * @return matrix reference.
		 */
		virtual Matrix<N,N> & transpose()
		{
			real_t save;

			for (std::size_t i = 0; i < N; i++)
				for(std::size_t j = i+1; j < N; j++)  {
					save = (*this)(i,j);
					(*this)(i,j) = (*this)(j,i);
					(*this)(j,i) = save;
				}
			return *this;
		}

		/**
		 * Invert matrix. Basic implementation which uses Gauss-Jordan transformations
		 * with pivoting.
		 *
		 * @return matrix reference.
		 *
		 * @warning if matrix is singular method will fail.
		 */
		virtual Matrix<N,N> & invert()
		{
			Matrix<N,N> I; //identity matrix
			std::size_t index[N]; //index holds columns order

			for (std::size_t j = 0; j < N; j++)
				index[j] = j;

			//perform operations on col j (leading element(j,j))
			for (std::size_t j = 0; j < N; j++) {
				//find max pivot
				for (std::size_t jj = j+1; jj < N; jj++)
					if (std::abs(m_elements[index[jj]*N + j]) > std::abs(m_elements[index[j]*N + j])) {
						//swap cols
						std::size_t swap = index[jj];
						index[jj] = index[j];
						index[j] = swap;
					}
				//divisor may be 0, then matrix is singular and function will fail
				real_t divisor = m_elements[index[j]*N + j];
				for (std::size_t i = 0; i < N; i++) {
					I.m_elements[index[j]*N + i] /= divisor;
					m_elements[index[j]*N + i] /= divisor;
				}
				for (std::size_t ii = 0; ii < N; ii++)
					if (ii != j) {
						real_t multiplier = m_elements[index[ii]*N + j];
						for (std::size_t i = 0; i < N; i++) {
							I.m_elements[index[ii]*N + i] -= multiplier * I.m_elements[index[j]*N + i];
							m_elements[index[ii]*N + i] -= multiplier * m_elements[index[j]*N + i];
						}
					}
			}
			for (std::size_t j = 0; j < N; j++)
				memcpy(& m_elements[j*N], & I.m_elements[index[j] * N], sizeof(m_elements));
			return *this;
		}

		/**
		 * Calculate matrix determinant (naive implementation).
		 * @return matrix determinant.
		 */
		virtual real_t det() const
		{
			return _det(m_elements, N);
		}

		/**
		 * Add other matrix to this matrix.
		 * @param other matrix to add.
		 *
		 * @return reference to current matrix after performing operation.
		 */
		Matrix<N,N> & add(const Matrix<N,N> & other);

		/**
		 * Subtract other matrix from this matrix.
		 * @param other subtraction term.
		 *
		 * @return reference to current matrix after performing operation.
		 */
		Matrix<N,N> & sub(const Matrix<N,N> & other);

		/**
		 * Multiply matrix by another matrix.
		 * @param other matrix to multiply.
		 *
		 * @return reference to current matrix after performing operation.
		 */
		virtual Matrix<N,N> & mult(const Matrix<N,N> & other)
		{
			Matrix<N,N> tmp = *this;

			for (std::size_t r = 0; r < N; r++) {
				//iN_j = i*N + j = i*N  (i = 0..N, j = 0)
				for (std::size_t iN_j = 0; iN_j < N*N; iN_j += N) {
					std::size_t el = iN_j + r;
					m_elements[el] = 0.0;
					//jN_r = j*N + r  (j = 0..N)
					for (std::size_t jN_r = r; jN_r < N*N; jN_r += N)
						//iN_j = i*N + j  (j = 0..N)
						m_elements[el] += tmp.m_elements[jN_r] * other.m_elements[iN_j++]; //j++
					iN_j -= N; //back to j = 0
				}
			}
			return *this;
		}
};

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
