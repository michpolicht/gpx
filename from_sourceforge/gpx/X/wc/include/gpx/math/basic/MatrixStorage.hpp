/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_BASIC_MATRIXSTORAGE_HPP_
#define GPX_X_MATH_BASIC_MATRIXSTORAGE_HPP_

namespace gpx {
namespace math {
namespace basic {

/**
 * Matrix storage. Responsible for memory allocation and basic access.
 */
template <std::size_t M, std::size_t N, typename T>
class MatrixStorage
{
	friend class MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>;

	protected:
		MatrixStorage(std::size_t reserve = 0);

		MatrixStorage(std::size_t rows, std::size_t cols, std::size_t reserve = 0);

		MatrixStorage(const T * elements, std::size_t rows = M, std::size_t cols = N, std::size_t reserve = 0);

		MatrixStorage(T d, std::size_t rows = M, std::size_t cols = N, std::size_t reserve = 0);

	protected:
		std::size_t rows() const;

		std::size_t cols() const;

		std::size_t size() const;

		void resize(std::size_t rows, std::size_t cols);

		std::size_t reserve() const;

		void reserve(std::size_t size);

		const T * ptr() const;

		T * ptr();

		T element(std::size_t i) const;

		T & element(std::size_t i);

		void swapRows(std::size_t r1, std::size_t r2);

		void swapCols(std::size_t c1, std::size_t c2);

	private:
		//conversion ctor
		template <std::size_t OM, std::size_t ON>
		MatrixStorage(const MatrixStorage<OM, ON, T> & other, std::size_t reserve);

	private:
		//conversion assignment forbidden
		template <std::size_t OM, std::size_t ON>
		void operator =(const MatrixStorage<OM, ON, T> & other);

	private:
		T m_elements[M * N];
};

template <typename T>
class MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>
{
	protected:
		MatrixStorage(std::size_t reserve = 0);

		MatrixStorage(std::size_t rows, std::size_t cols, std::size_t reserve = 0);

		//copy ctor
		MatrixStorage(const MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & other);

		//conversion ctor
		template <std::size_t OM, std::size_t ON>
		MatrixStorage(const MatrixStorage<OM, ON, T> & other, std::size_t reserve);

		MatrixStorage(const T * elements, std::size_t rows = 0, std::size_t cols = 0, std::size_t reserve = 0);

		MatrixStorage(T d, std::size_t rows = 0, std::size_t cols = 0, std::size_t reserve = 0);

		//non-virtual since this class won't be instantiated alone <=> dtor is protected
		~MatrixStorage();

	protected:
		//copy-assignment
		void operator =(const MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & other);

		//conversion assignment
		template <std::size_t OM, std::size_t ON>
		void operator =(const MatrixStorage<OM, ON, T> & other);

		std::size_t rows() const;

		std::size_t cols() const;

		std::size_t size() const;

		void resize(std::size_t rows, std::size_t cols);

		std::size_t reserve() const;

		void reserve(std::size_t size);

		const T * ptr() const;

		T * ptr();

		T element(std::size_t i) const;

		T & element(std::size_t i);

		void swapRows(std::size_t r1, std::size_t r2);

		void swapCols(std::size_t c1, std::size_t c2);

	private:
		std::size_t m_rows;
		std::size_t m_cols;
		std::size_t m_reserve;
		T * m_elements;
};

template <std::size_t M, typename T>
class MatrixStorage<M, gpx::math::SIZE_DYNAMIC, T>
{
	private:
		//disabled
		MatrixStorage();
};

template <std::size_t N, typename T>
class MatrixStorage<gpx::math::SIZE_DYNAMIC, N, T>
{
	private:
		//disabled
		MatrixStorage();
};

}
}
}

#include "MatrixStorage.imp.hpp"

#endif /* GPX_X_MATH_BASIC_MATRIXSTORAGE_HPP_ */

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
