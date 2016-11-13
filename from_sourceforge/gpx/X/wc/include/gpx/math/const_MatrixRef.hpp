#ifndef CONST_MATRIXREF_HPP
#define CONST_MATRIXREF_HPP

#include "structures.hpp"

namespace gpx {
namespace math {

/**
 * M x N (M rows, N cols) matrix const reference mimic.
 * @param M number of rows.
 * @param N number of columns.
 * @param T type of matrix elements.
 */
template <std::size_t M, std::size_t N, typename T>
class const_MatrixRef : public const_MatrixTrait<const_MatrixRef, M, N, T, true>
{
	public:
		/**
		 * Conversion constructor.
		 * @param elements pointer to array of elements stored in OpenGL column-major format.
		 * Array must contain required number of elements (M * N).
		 */
		const_MatrixRef(const T * elements);

		/**
		 * Get number of rows.
		 * @return number of rows.
		 */
		std::size_t rows() const;

		/**
		 * Get number of columns.
		 * @return number of columns.
		 */
		std::size_t cols() const;

		/**
		 * Get size.
		 * @return number of elements in matrix.
		 *
		 * @note this is not size measured as number of bytes in memory.
		 */
		std::size_t size() const;

		/**
		 * Const data pointer. Returns const pointer to OpenGL style array that
		 * represents matrix in column-major format.
		 * @return const pointer to one dimensional array representing a matrix. A
		 * matrix is represented in column-major order, which is OpenGL style
		 * of matrix representation. Transpose matrix to obtain C (row-major)
		 * format.
		 */
		const T * ptr() const;

		/**
		 * Get (i, j) element of matrix (const version).
		 * @param i row.
		 * @param j column.
		 * @return (i,j) element.
		 */
		T operator()(std::size_t i, std::size_t j) const;

		/**
		 * Get (i, j) element of matrix (const version).
		 * @param i row.
		 * @param j column.
		 * @return (i,j) element.
		 */
		T element(std::size_t i, std::size_t j) const;

		/**
		 * Get n-th element of matrix (const version).
		 * @param n element number.
		 * @return n-th element.
		 */
		T element(std::size_t n) const;

		/**
		 * Column access (const version). Provides direct access to a column.
		 * @param j column.
		 * @return vector containing elements of column @a j.
		 */
		const_VectorRef<M> column(std::size_t j) const;

	private:
		/**
		 * Copy assignment. Forbidden (const reference).
		 */
		void operator =(const const_MatrixRef<M, N, T> & );

		const T * m_elements;
};

template <std::size_t M, std::size_t N, typename T>
const_MatrixRef<M, N, T>::const_MatrixRef(const T * elements):
	m_elements(elements)
{
}

template <std::size_t M, std::size_t N, typename T>
std::size_t const_MatrixRef<M, N, T>::rows() const
{
	return M;
}

template <std::size_t M, std::size_t N, typename T>
std::size_t const_MatrixRef<M, N, T>::cols() const
{
	return N;
}

template <std::size_t M, std::size_t N, typename T>
std::size_t const_MatrixRef<M, N, T>::size() const
{
	return rows() * cols();
}

template <std::size_t M, std::size_t N, typename T>
const T * const_MatrixRef<M, N, T>::ptr() const
{
	return m_elements;
}

template <std::size_t M, std::size_t N, typename T>
T const_MatrixRef<M, N, T>::operator()(std::size_t i, std::size_t j) const
{
	return element(i, j);
}

template <std::size_t M, std::size_t N, typename T>
T const_MatrixRef<M, N, T>::element(std::size_t i, std::size_t j) const
{
	GPX_ASSERT(i < rows(), "row index (" << i << ", " << j << ") is out of bounds");
	GPX_ASSERT(j < cols(), "column index (" << i << ", " << j << ") is out of bounds");
	return m_elements[j * rows() + i];
}

template <std::size_t M, std::size_t N, typename T>
T const_MatrixRef<M, N, T>::element(std::size_t n) const
{
	GPX_ASSERT(n < size(), "element(" << n << ") is out of bounds");
	return m_elements[n];
}

template <std::size_t M, std::size_t N, typename T>
const_VectorRef<M> const_MatrixRef<M, N, T>::column(std::size_t j) const
{
	GPX_ASSERT(j < cols(), "column(" << j << ") is out of bounds");
	return ptr() + j * rows();
}

/**
 * Dynamically sized matrix const reference mimic.
 * @param T type of matrix elements.
 */
template <typename T>
class const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> : public const_MatrixTrait<const_MatrixRef, SIZE_DYNAMIC, SIZE_DYNAMIC, T, true>
{
	typedef const_MatrixTrait<const_MatrixRef, SIZE_DYNAMIC, SIZE_DYNAMIC, T, true> Parent;

	public:
		//const_MatrixRef(const const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & other) = default;

		explicit const_MatrixRef(const Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> * mPtr);

		//~const_MatrixRef() = default;

		/**
		 * Get number of rows.
		 * @return number of rows.
		 */
		std::size_t rows() const;

		/**
		 * Get number of columns.
		 * @return number of columns.
		 */
		std::size_t cols() const;

		/**
		 * Get size.
		 * @return number of elements in matrix.
		 *
		 * @note this is not size measured as number of bytes in memory.
		 */
		std::size_t size() const;

		/**
		 * Get amount of reserved memory.
		 * @return amount of excessively reserved memory as number of elements which can be
		 * stored without the need of memory reallocation.
		 */
		std::size_t reserved() const;

		/**
		 * Const data pointer. Returns const pointer to OpenGL style array that
		 * represents matrix in column-major format.
		 * @return const pointer to one dimensional array representing a matrix. A
		 * matrix is represented in column-major order, which is OpenGL style
		 * of matrix representation. Transpose matrix to obtain C (row-major)
		 * format.
		 */
		const T * ptr() const;

		/**
		 * Const version of function call operator.
		 * @param i row.
		 * @param j column.
		 * @return (i,j) element.
		 */
		T operator()(std::size_t i, std::size_t j) const;

		/**
		 * Get (i,j) element of matrix (const version).
		 * @param i row.
		 * @param j column.
		 * @return (i,j) element.
		 */
		T element(std::size_t i, std::size_t j) const;

		/**
		 * Get n-th element of matrix (const version).
		 * @param n element number.
		 * @return n-th element.
		 */
		T element(std::size_t n) const;

	private:
		/**
		 * Copy assignment. Forbidden (const reference).
		 */
		void operator =(const const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & );

		const Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> * m_mPtr;
};

template <typename T>
const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::const_MatrixRef(const Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> * mPtr):
	m_mPtr(mPtr)
{
}

template <typename T>
std::size_t const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::rows() const
{
	return m_mPtr->rows();
}

template <typename T>
std::size_t const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::cols() const
{
	return m_mPtr->cols();
}

template <typename T>
std::size_t const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::size() const
{
	return m_mPtr->size();
}

template <typename T>
std::size_t const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::reserved() const
{
	return m_mPtr->reserved();
}

template <typename T>
const T * const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::ptr() const
{
	return m_mPtr->ptr();
}

template <typename T>
T const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::operator()(std::size_t i, std::size_t j) const
{
	return m_mPtr->operator ()(i, j);
}

template <typename T>
T const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::element(std::size_t i, std::size_t j) const
{
	return m_mPtr->element(i, j);
}

template <typename T>
T const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::element(std::size_t n) const
{
	return m_mPtr->element(n);
}

}
}

#endif // CONST_MATRIXREF_HPP
