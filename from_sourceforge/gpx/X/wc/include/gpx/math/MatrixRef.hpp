#ifndef MATRIXREF_HPP
#define MATRIXREF_HPP

#include "structures.hpp"

namespace gpx {
namespace math {

/**
 * M x N (M rows, N cols) matrix reference mimic.
 * @param M number of rows.
 * @param N number of columns.
 * @param T type of matrix elements.
 */
template <std::size_t M, std::size_t N, typename T>
class MatrixRef : public MatrixTrait<MatrixRef, M, N, T, true>
{
	public:
		/**
		 * Constructor.
		 * @param elements pointer to array of elements stored in OpenGL column-major format.
		 * Array must contain required number of elements (M * N).
		 */
		explicit MatrixRef(T * elements);

		/**
		 * Conversion to const_MatrixRef<M, T>.
		 */
		operator const_MatrixRef<M, N, T> () const;

		/**
		 * Copy assignment. Data will be copied from other matrix.
		 * @param other matrix from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		MatrixRef<M, N, T> & operator =(const MatrixRef<M, N, T> & other);

		/**
		 * Matrix assignment. Data will be copied from other matrix.
		 * @param other matrix from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		MatrixRef<M, N, T> & operator =(const const_MatrixRef<M, N, T> & other);

		/**
		 * Matrix assignment. Data will be copied from other matrix.
		 * @param other matrix from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		MatrixRef<M, N, T> & operator =(const Matrix<M, N, T> & other);

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
		 * Data pointer. Returns pointer to OpenGL style array that represents
		 * matrix in column-major format.
		 * @return pointer to one dimensional array representing a matrix. A
		 * matrix is represented in column-major order, which is OpenGL style
		 * of matrix representation. Transpose matrix to obtain C (row-major)
		 * format.
		 */
		T * ptr();

		/**
		 * Get (i,j) element of matrix (const version).
		 * @param i row.
		 * @param j column.
		 * @return (i,j) element.
		 */
		T operator()(std::size_t i, std::size_t j) const;

		/**
		 * Get (i,j) element of matrix.
		 * for accessing matrix elements.
		 * @param i row.
		 * @param j column.
		 * @return (i,j) element.
		 */
		T & operator()(std::size_t i, std::size_t j);

		/**
		 * Get (i,j) element of matrix (const version).
		 * @param i row.
		 * @param j column.
		 * @return (i,j) element.
		 */
		T element(std::size_t i, std::size_t j) const;

		/**
		 * Get (i,j) element of matrix.
		 * @param i row.
		 * @param j column.
		 * @return (i,j) element.
		 */
		T & element(std::size_t i, std::size_t j);

		/**
		 * Get n-th element of matrix (const version).
		 * @param n element number.
		 * @return n-th element.
		 */
		T element(std::size_t n) const;

		/**
		 * Get n-th element of matrix.
		 * @param n element number.
		 * @return n-th element.
		 */
		T & element(std::size_t n);

		/**
		 * Column access (const version). Provides direct access to a column.
		 * @param j column.
		 * @return vector containing elements of column @a j.
		 */
		const_VectorRef<M> column(std::size_t j) const;

		/**
		 * Column access. Provides direct access to a column.
		 * @param j column.
		 * @return vector containing elements of column @a j.
		 */
		VectorRef<M> column(std::size_t j);

	private:
		T * m_elements;
};

template <std::size_t M, std::size_t N, typename T>
MatrixRef<M, N, T>::MatrixRef(T * elements):
	m_elements(elements)
{
}

template <std::size_t M, std::size_t N, typename T>
MatrixRef<M, N, T>::operator const_MatrixRef<M, N, T> () const
{
	return const_MatrixRef<M, N, T>(m_elements);
}

template <std::size_t M, std::size_t N, typename T>
MatrixRef<M, N, T> & MatrixRef<M, N, T>::operator =(const MatrixRef<M, N, T> & other)
{
	//self assignment branch not required here
	std::copy(other.ptr(), other.ptr() + size(), m_elements);
	return *this;
}

template <std::size_t M, std::size_t N, typename T>
MatrixRef<M, N, T> & MatrixRef<M, N, T>::operator =(const const_MatrixRef<M, N, T> & other)
{
	std::copy(other.ptr(), other.ptr() + size(), m_elements);
	return *this;
}

template <std::size_t M, std::size_t N, typename T>
MatrixRef<M, N, T> & MatrixRef<M, N, T>::operator =(const Matrix<M, N, T> & other)
{
	std::copy(other.ptr(), other.ptr() + size(), m_elements);
	return *this;
}

template <std::size_t M, std::size_t N, typename T>
std::size_t MatrixRef<M, N, T>::rows() const
{
	return M;
}

template <std::size_t M, std::size_t N, typename T>
std::size_t MatrixRef<M, N, T>::cols() const
{
	return N;
}

template <std::size_t M, std::size_t N, typename T>
std::size_t MatrixRef<M, N, T>::size() const
{
	return rows() * cols();
}

template <std::size_t M, std::size_t N, typename T>
const T * MatrixRef<M, N, T>::ptr() const
{
	return m_elements;
}

template <std::size_t M, std::size_t N, typename T>
T * MatrixRef<M, N, T>::ptr()
{
	return m_elements;
}

template <std::size_t M, std::size_t N, typename T>
T MatrixRef<M, N, T>::operator()(std::size_t i, std::size_t j) const
{
	return element(i, j);
}

template <std::size_t M, std::size_t N, typename T>
T & MatrixRef<M, N, T>::operator()(std::size_t i, std::size_t j)
{
	return element(i, j);
}

template <std::size_t M, std::size_t N, typename T>
T MatrixRef<M, N, T>::element(std::size_t i, std::size_t j) const
{
	GPX_ASSERT(i < rows(), "row index (" << i << ", " << j << ") is out of bounds");
	GPX_ASSERT(j < cols(), "column index (" << i << ", " << j << ") is out of bounds");
	return m_elements[j * rows() + i];
}

template <std::size_t M, std::size_t N, typename T>
T & MatrixRef<M, N, T>::element(std::size_t i, std::size_t j)
{
	GPX_ASSERT(i < rows(), "row index (" << i << ", " << j << ") is out of bounds");
	GPX_ASSERT(j < cols(), "column index (" << i << ", " << j << ") is out of bounds");
	return m_elements[j * rows() + i];
}

template <std::size_t M, std::size_t N, typename T>
T MatrixRef<M, N, T>::element(std::size_t n) const
{
	GPX_ASSERT(n < size(), "element(" << n << ") is out of bounds");
	return m_elements[n];
}

template <std::size_t M, std::size_t N, typename T>
T & MatrixRef<M, N, T>::element(std::size_t n)
{
	GPX_ASSERT(n < size(), "element(" << n << ") is out of bounds");
	return m_elements[n];
}

template <std::size_t M, std::size_t N, typename T>
const_VectorRef<M> MatrixRef<M, N, T>::column(std::size_t j) const
{
	GPX_ASSERT(j < cols(), "column(" << j << ") is out of bounds");
	return ptr() + j * rows();
}

template <std::size_t M, std::size_t N, typename T>
VectorRef<M> MatrixRef<M, N, T>::column(std::size_t j)
{
	GPX_ASSERT(j < cols(), "column(" << j << ") is out of bounds");
	return ptr() + j * rows();
}

/**
 * Dynamically sized matrix reference mimic.
 * @param T type of matrix elements.
 */
template <typename T>
class MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> : public MatrixTrait<MatrixRef, SIZE_DYNAMIC, SIZE_DYNAMIC, T, true>
{
	typedef MatrixTrait<MatrixRef, SIZE_DYNAMIC, SIZE_DYNAMIC, T, true> Parent;

	public:
		//MatrixRef(const MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & other) = default;

		explicit MatrixRef(Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> * mPtr);

		//~MatrixRef() = default;

		operator const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> () const;

		/**
		 * Copy assignment.
		 * @param other other matrix from which data is going to be copied.
		 * @return self-reference to an object being assigned.
		 *
		 * @note memory reserve remains unchanged.
		 */
		MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & operator =(const MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & other);

		/**
		 * Conversion assignment. Copies elements from other matrix and resizes matrix if
		 * necessary.
		 * @param other other matrix.
		 * @return self-reference to matrix being assigned.
		 *
		 * @note memory reserve remains unchanged.
		 */
		MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & operator =(const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> other);

		/**
		 * Conversion assignment. Copies elements from other matrix and resizes matrix if
		 * necessary.
		 * @param other other matrix.
		 * @return self-reference to matrix being assigned.
		 *
		 * @note memory reserve remains unchanged.
		 */
		MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & operator =(const Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & other);

		/**
		 * Array assignment.
		 * @param elements array of elements in OpenGL column-major format. Array must
		 * contain required number of elements (M * N).
		 * @return self-reference to matrix being assigned.
		 */
		MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & operator =(const T * ptr);

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
		 * Resize matrix.
		 * @param rows new number of rows.
		 * @param cols new number of columns.
		 *
		 * @warning resize is destructive operation. Current values of matrix elements are
		 * lost and replaced by undefined ones.
		 *
		 * @warning resize operation invalidates pointer to matrix elements.
		 */
		void resize(std::size_t rows, std::size_t cols);

		/**
		 * Get amount of reserved memory.
		 * @return amount of excessively reserved memory as number of elements which can be
		 * stored without the need of memory reallocation.
		 */
		std::size_t reserved() const;

		/**
		 * Reserve memory. Purpose of this method is to forward reserve memory
		 * for the matrix elements, so that memory reallocation will not be necessary
		 * during further resize operations. Method is not imperative; implementation
		 * *may* schedule request for future realization or even ignore it. In any case
		 * matrix data is conserved.
		 * @param size amount of memory to reserve in terms of number of elements.
		 */
		void reserve(std::size_t size);

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
		 * Data pointer. Returns pointer to OpenGL style array that represents
		 * matrix in column-major format.
		 * @return pointer to one dimensional array representing a matrix. A
		 * matrix is represented in column-major order, which is OpenGL style
		 * of matrix representation. Transpose matrix to obtain C (row-major)
		 * format.
		 */
		T * ptr();

		/**
		 * Const version of function call operator.
		 * @param i row.
		 * @param j column.
		 * @return (i,j) element.
		 */
		T operator()(std::size_t i, std::size_t j) const;

		/**
		 * Function call operator. Get (i,j) element of matrix. This is row-major interface
		 * for accessing matrix elements.
		 * @param i row.
		 * @param j column.
		 * @return (i,j) elements.
		 */
		T & operator()(std::size_t i, std::size_t j);

		/**
		 * Get (i,j) element of matrix (const version).
		 * @param i row.
		 * @param j column.
		 * @return (i,j) element.
		 */
		T element(std::size_t i, std::size_t j) const;

		/**
		 * Get (i,j) element of matrix.
		 * @param i row.
		 * @param j column.
		 * @return (i,j) element.
		 */
		T & element(std::size_t i, std::size_t j);

		/**
		 * Get n-th element of matrix (const version).
		 * @param n element number.
		 * @return n-th element.
		 */
		T element(std::size_t n) const;

		/**
		 * Get n-th element of matrix.
		 * @param n element number.
		 * @return n-th element.
		 */
		T & element(std::size_t n);

	private:
		Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> * m_mPtr;
};

template <typename T>
MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::MatrixRef(Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> * mPtr):
	m_mPtr(mPtr)
{
}

template <typename T>
MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::operator const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> () const
{
	return const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>(m_mPtr);
}

template <typename T>
MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::operator =(const MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & other)
{
	*m_mPtr = other;
	return *this;
}

template <typename T>
MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::operator =(const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> other)
{
	*m_mPtr = other;
	return *this;
}

template <typename T>
MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::operator =(const Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & other)
{
	*m_mPtr = other;
	return *this;
}

template <typename T>
MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::operator =(const T * ptr)
{
	*m_mPtr = ptr;
	return *this;
}

template <typename T>
std::size_t MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::rows() const
{
	return m_mPtr->rows();
}

template <typename T>
std::size_t MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::cols() const
{
	return m_mPtr->cols();
}

template <typename T>
std::size_t MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::size() const
{
	return m_mPtr->size();
}

template <typename T>
void MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::resize(std::size_t rows, std::size_t cols)
{
	m_mPtr->resize(rows, cols);
}

template <typename T>
std::size_t MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::reserved() const
{
	return m_mPtr->reserved();
}

template <typename T>
void MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::reserve(std::size_t p_size)
{
	m_mPtr->reserve(p_size);
}

template <typename T>
const T * MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::ptr() const
{
	return m_mPtr->ptr();
}

template <typename T>
T * MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::ptr()
{
	return m_mPtr->ptr();
}

template <typename T>
T MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::operator()(std::size_t i, std::size_t j) const
{
	return m_mPtr->operator ()(i, j);
}

template <typename T>
T & MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::operator()(std::size_t i, std::size_t j)
{
	return m_mPtr->operator ()(i, j);
}

template <typename T>
T MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::element(std::size_t i, std::size_t j) const
{
	return m_mPtr->element(i, j);
}

template <typename T>
T & MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::element(std::size_t i, std::size_t j)
{
	return m_mPtr->element(i, j);
}

template <typename T>
T MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::element(std::size_t n) const
{
	return m_mPtr->element(n);
}

template <typename T>
T & MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::element(std::size_t n)
{
	return m_mPtr->element(n);
}

}
}

#endif // MATRIXREF_HPP
