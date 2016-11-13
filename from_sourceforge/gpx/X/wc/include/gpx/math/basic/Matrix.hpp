/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_BASIC_MATRIX_HPP_
#define GPX_X_MATH_BASIC_MATRIX_HPP_

#include "MatrixStorage.hpp"

namespace gpx {
namespace math {
namespace basic {

template <std::size_t M, std::size_t N, typename T = real_t, bool DIMSPEC = true>
class Matrix : protected MatrixStorage<M, N, T>
{
	typedef MatrixStorage<M, N, T> Parent;

	public:
		const Parent & storage() const;

	protected:
		Matrix(std::size_t reserve);

		Matrix(std::size_t rows, std::size_t cols, std::size_t reserve);

		//necessary, since Parent is protected and this class can not be implicitly down-casted
		Matrix(const Matrix<M, N, T, DIMSPEC> & other);

		template <std::size_t OM, std::size_t ON>
		Matrix(const Matrix<OM, ON, T, DIMSPEC> & other, std::size_t reserve);

		Matrix(const T * elements, std::size_t rows, std::size_t cols, std::size_t reserve);

		Matrix(T d, std::size_t rows, std::size_t cols, std::size_t reserve);

	protected:
		std::size_t rows() const;

		std::size_t cols() const;

		std::size_t size() const;

		void resize(std::size_t rows, std::size_t cols);

		std::size_t reserve() const;

		void reserve(std::size_t size);

		const T * ptr() const;

		T * ptr();

		const T * ptr(std::size_t i, std::size_t j) const;

		T * ptr(std::size_t i, std::size_t j);

		//necessary, since Parent is protected and this class can not be implicitly down-casted
		void operator =(const Matrix<M, N, T, DIMSPEC> & other);

		template <std::size_t OM, std::size_t ON>
		void operator =(const Matrix<OM, ON, T, DIMSPEC> & other);

		void operator =(const T * elements);

		void operator =(T val);

		T operator()(std::size_t i, std::size_t j) const;

		T & operator()(std::size_t i, std::size_t j);

		bool operator ==(const gpx::math::Matrix<M, N, T> & other) const;

		bool operator ==(T val) const;

		bool ape(const gpx::math::Matrix<M, N, T> & other) const;

		bool ape(T val) const;

		bool ale(const gpx::math::Matrix<M, N, T> & other) const;

		bool ale(T val) const;

		bool operator !=(const gpx::math::Matrix<M, N, T> & other) const;

		bool operator !=(T val) const;

		void add(const gpx::math::Matrix<M, N, T> & other);

		void sub(const gpx::math::Matrix<M, N, T> & other);

		void mul(const gpx::math::Matrix<N, N, T> & other);

		void mul(T val);

		gpx::math::Matrix<M, N, T> sum(const gpx::math::Matrix<M, N, T> & other) const;

		gpx::math::Matrix<M, N, T> diff(const gpx::math::Matrix<M, N, T> & other) const;

		template <std::size_t ON>
		gpx::math::Matrix<M, ON, T> prod(const gpx::math::Matrix<N, ON, T> & other) const;

		gpx::math::Vector<M, T> prod(gpx::math::const_VectorRef<N, T> other) const;

		gpx::math::Matrix<M, N, T> prod(T val) const;

		gpx::math::Matrix<N, M, T> transposed() const;

		void swapRows(std::size_t r1, std::size_t r2);

		void swapCols(std::size_t c1, std::size_t c2);
};

template <std::size_t N, typename T>
class Matrix<N, N, T, true> : public Matrix<N, N, T, false>
{
	typedef Matrix<N, N, T, false> Parent;

	protected:
		Matrix(std::size_t reserve);

		Matrix(std::size_t rows, std::size_t cols, std::size_t reserve);

		//generated copy-ctor OK
		//Matrix(const Matrix<N, N, T> & other);

		Matrix(const T * elements, std::size_t rows, std::size_t cols, std::size_t reserve);

		Matrix(T d, std::size_t rows, std::size_t cols, std::size_t reserve);

	protected:
		//generated copy-assignment OK
		//void operator =(const Matrix<N, N, T, true> & other);

		void operator =(const T * elements);	//assignment operators are not inherited

		void operator =(T val);	//assignment operators are not inherited

		void transpose();

		/*
		 * Basic implementation which uses Gauss-Jordan transformations with pivoting.
		 * @warning if matrix is singular method will fail.
		 */
		void invert();

		T det() const;

	private:
		/**
		 * Determinant helper.
		 * @param elements matrix elements (column-major order).
		 * @param size number of rows or columns, thus matrix size is @a size * @a size.
		 * @return determinant of matrix defined by @a elements and @a size.
		 */
		T _det(const T * elements, std::size_t size) const;
};

template <typename T>
class Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true> : public Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, false>
{
	typedef Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, false> Parent;

	protected:
		Matrix(std::size_t reserve);

		Matrix(std::size_t rows, std::size_t cols, std::size_t reserve);

		//generated copy ctor OK
		//Matrix(const Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & other);

		template <std::size_t OM, std::size_t ON>
		Matrix(const Matrix<OM, ON, T> & other, std::size_t reserve);

		Matrix(const T * elements, std::size_t rows, std::size_t cols, std::size_t reserve);

		Matrix(const T d, std::size_t rows, std::size_t cols, std::size_t reserve);

	protected:
		//generated copy-assignment OK
		//void operator =(const Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & other);

		void operator =(const T * elements);

		void operator =(T val);

		template <std::size_t OM, std::size_t ON>
		void operator =(const Matrix<OM, ON, T> & other);

		void transpose();

		/*
		 * Basic implementation which uses Gauss-Jordan transformations with pivoting.
		 * @warning if matrix is singular method will fail.
		 */
		void invert();

		T det() const;

	private:
		/**
		 * Determinant helper.
		 * @param elements matrix elements (column-major order).
		 * @param size number of rows or columns, thus matrix size is @a size * @a size.
		 * @return determinant of matrix defined by @a elements and @a size.
		 */
		T _det(const T * elements, std::size_t size) const;
};

}
}
}

#include "Matrix.imp.hpp"

#endif /* GPX_X_MATH_BASIC_MATRIX_HPP_ */

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
