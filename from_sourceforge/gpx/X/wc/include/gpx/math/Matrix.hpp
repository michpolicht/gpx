/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_MATRIX_HPP_
#define GPX_X_MATH_MATRIX_HPP_

#include "structures.hpp"

namespace gpx {
namespace math {

/**
 * Base M x N (M rows, N cols) matrix.
 * @param M number of rows.
 * @param N number of columns.
 * @param T type of matrix elements.
 */
template <std::size_t M, std::size_t N, typename T>
class Matrix : public MatrixTrait<Matrix, M, N, T, true>
{
	typedef MatrixTrait<Matrix, M, N, T, true> Parent;
	typedef Matrix<M, N, T> Self;

	public:
		/**
		 * Default constructor. Matrix is initialized with zeros.
		 * @param rows number of rows to initialize.
		 * @param cols number of columns to initialize.
		 *
		 * @todo remove and use Matrix(T d = T(), rows, cols) ctor istead.
		 */
		explicit Matrix(std::size_t rows = M, std::size_t cols = N);

		//Matrix(const Matrix<M, N, T> & other) = default;

		/**
		 * Constructor.
		 * @param other other matrix.
		 */
		Matrix(const_MatrixRef<M, N, T> other);

		/**
		 * Constructor. Initializes matrix with specified value on diagonal.
		 * The rest of matrix is initialized with zeros.
		 * @param d value to be set on diagonal. E.g., Matrix(T(1)) will setup identity matrix.
		 * @param rows number of rows to initialize.
		 * @param cols number of columns to initialize.
		 */
		explicit Matrix(T d, std::size_t rows = M, std::size_t cols = N);

		/**
		 * Constructor. Create matrix from given data. Data is copied into internal storage.
		 * @param ptr pointer to array of elements in OpenGL column-major format. Array must
		 * contain number of elements required to make a copy (rows * cols).
		 * @param rows number of rows in array being copied.
		 * @param cols number of columns in array being copied.
		 */
		explicit Matrix(const T * ptr, std::size_t rows = M, std::size_t cols = N);

		//Matrix<M, N, T> & operator =(const Matrix<M, N, T> & other) = default;

		/**
		 * Matrix assignment.
		 * @param other other matrix.
		 * @return self-reference to matrix being assigned.
		 */
		Matrix<M, N, T> & operator =(const_MatrixRef<M, N, T> other);

		/**
		 * Assignment operator. Assigns given data. Elements are copied into internal
		 * storage.
		 * @param elements array of elements in OpenGL column-major format. Array must
		 * contain required number of elements (M * N).
		 * @return self-reference to matrix being assigned.
		 */
		Matrix<M, N, T> & operator =(const T * ptr);

		/**
		 * Conversion to const_MatrixRef<M, T>.
		 */
		operator const_MatrixRef<M, N, T> () const;

		/**
		 * Conversion to MatrixRef<M, N, T>.
		 */
		operator MatrixRef<M, N, T> ();

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
		T m_elements[M * N];
};

template <std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>::Matrix(std::size_t rows, std::size_t cols)
{
	GPX_ASSERT(rows <= Self::rows(), "Matrix(" << rows << ", " << cols << ") is out of bounds");
	GPX_ASSERT(cols <= Self::cols(), "Matrix(" << rows << ", " << cols << ") is out of bounds");

	//NP if all rows are initialized, so take into account only number of columns to make it simple
	std::fill(ptr(), ptr() + Self::rows() * cols, T());
}

template <std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>::Matrix(const_MatrixRef<M, N, T> other)
{
	std::copy(other.ptr(), other.ptr() + size(), m_elements);
}

template <std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>::Matrix(T d, std::size_t rows, std::size_t cols)
{
	GPX_ASSERT(rows <= Self::rows(), "Matrix(" << d << " , " << rows << ", " << cols << ") is out of bounds");
	GPX_ASSERT(cols <= Self::cols(), "Matrix(" << d << " , " << rows << ", " << cols << ") is out of bounds");

	//NP if all rows are initialized, so take into account only number of columns to make it simple
	std::fill(ptr(), ptr() + Self::rows() * cols, T());
	for (std::size_t i = 0; i < std::min(rows, cols); i++)
		m_elements[Self::rows() * i + i] = d;
}

template <std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>::Matrix(const T * ptr, std::size_t rows, std::size_t cols)
{
	GPX_ASSERT(rows * cols <= size(), "Matrix(" << ptr << " , " << rows << ", " << cols << ") data to be copied (rows * cols) is too big");

	std::copy(ptr, ptr + rows * cols, m_elements);
}

template <std::size_t M, std::size_t N, typename T>
Matrix<M, N, T> & Matrix<M, N, T>::operator =(const_MatrixRef<M, N, T> other)
{
	std::copy(other.ptr(), other.ptr() + size(), m_elements);
	return *this;
}

template <std::size_t M, std::size_t N, typename T>
Matrix<M, N, T> & Matrix<M, N, T>::operator =(const T * ptr)
{
	std::copy(ptr, ptr + size(), m_elements);
	return *this;
}

template <std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>::operator const_MatrixRef<M, N, T> () const
{
	return const_MatrixRef<M, N, T>(m_elements);
}

template <std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>::operator MatrixRef<M, N, T> ()
{
	return MatrixRef<M, N, T>(m_elements);
}

template <std::size_t M, std::size_t N, typename T>
std::size_t Matrix<M, N, T>::rows() const
{
	return M;
}

template <std::size_t M, std::size_t N, typename T>
std::size_t Matrix<M, N, T>::cols() const
{
	return N;
}

template <std::size_t M, std::size_t N, typename T>
std::size_t Matrix<M, N, T>::size() const
{
	return rows() * cols();
}

template <std::size_t M, std::size_t N, typename T>
const T * Matrix<M, N, T>::ptr() const
{
	return m_elements;
}

template <std::size_t M, std::size_t N, typename T>
T * Matrix<M, N, T>::ptr()
{
	return m_elements;
}

template <std::size_t M, std::size_t N, typename T>
T Matrix<M, N, T>::operator()(std::size_t i, std::size_t j) const
{
	return element(i, j);
}

template <std::size_t M, std::size_t N, typename T>
T & Matrix<M, N, T>::operator()(std::size_t i, std::size_t j)
{
	return element(i, j);
}

template <std::size_t M, std::size_t N, typename T>
T Matrix<M, N, T>::element(std::size_t i, std::size_t j) const
{
	GPX_ASSERT(i < rows(), "element(" << i << ", " << j << ") is out of bounds");
	GPX_ASSERT(j < cols(), "element(" << i << ", " << j << ") is out of bounds");
	return m_elements[j * rows() + i];
}

template <std::size_t M, std::size_t N, typename T>
T & Matrix<M, N, T>::element(std::size_t i, std::size_t j)
{
	GPX_ASSERT(i < rows(), "element(" << i << ", " << j << ") is out of bounds");
	GPX_ASSERT(j < cols(), "element(" << i << ", " << j << ") is out of bounds");
	return m_elements[j * rows() + i];
}

template <std::size_t M, std::size_t N, typename T>
T Matrix<M, N, T>::element(std::size_t n) const
{
	GPX_ASSERT(n < size(), "element(" << n << ") is out of bounds");
	return m_elements[n];
}

template <std::size_t M, std::size_t N, typename T>
T & Matrix<M, N, T>::element(std::size_t n)
{
	GPX_ASSERT(n < size(), "element(" << n << ") is out of bounds");
	return m_elements[n];
}

template <std::size_t M, std::size_t N, typename T>
const_VectorRef<M> Matrix<M, N, T>::column(std::size_t j) const
{
	GPX_ASSERT(j < cols(), "column(" << j << ") is out of bounds");
	return ptr() + j * rows();
}

template <std::size_t M, std::size_t N, typename T>
VectorRef<M> Matrix<M, N, T>::column(std::size_t j)
{
	GPX_ASSERT(j < cols(), "column(" << j << ") is out of bounds");
	return VectorRef<M>(ptr() + j * rows());
}

/**
 * Dynamically sized matrix.
 * @param T type of matrix elements.
 */
template <typename T>
class Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> : public MatrixTrait<Matrix, SIZE_DYNAMIC, SIZE_DYNAMIC, T, true>
{
	typedef MatrixTrait<Matrix, SIZE_DYNAMIC, SIZE_DYNAMIC, T, true> Parent;
	typedef Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> Self;

	public:
		/**
		 * Copy constructor.
		 * @param other other matrix.
		 */
		Matrix(const Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & other);

		/**
		 * Constructor.
		 * @param other other matrix.
		 */
		Matrix(const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> other);

		/**
		 * Default constructor. Matrix is initialized with zeros.
		 * @param rows number of rows to initialize.
		 * @param cols number of columns to initialize.
		 * @param reserve minimal amount of memory which should be reserved regardless
		 * of matrix size.
		 *
		 * @todo remove and use Matrix(T d = T(), rows, cols) ctor istead.
		 */
		Matrix(std::size_t rows, std::size_t cols, std::size_t reserve = 0);

		/**
		 * Constructor. Initializes matrix with specified value on diagonal.
		 * The rest of matrix is initialized with zeros.
		 * @param d value to be set on diagonal. E.g., Matrix(T(1)) will setup identity matrix.
		 * @param rows number of rows to initialize.
		 * @param cols number of columns to initialize.
		 * @param reserve minimal amount of memory which should be reserved regardless
		 * of matrix size.
		 */
		Matrix(T d, std::size_t rows, std::size_t cols, std::size_t reserve = 0);

		/**
		 * Constructor. Create matrix from given data. Data is copied into internal storage.
		 * @param ptr pointer to array of elements in OpenGL column-major format. Array must
		 * contain number of elements required to make a copy (rows * cols).
		 * @param rows number of rows in array being copied.
		 * @param cols number of columns in array being copied.
		 * @param reserve minimal amount of memory which should be reserved regardless
		 * of matrix size.
		 */
		Matrix(const T * ptr, std::size_t rows, std::size_t cols, std::size_t reserve = 0);

		/**
		 * Destructor.
		 */
		virtual ~Matrix();

		/**
		 * Copy assignment.
		 * @param other other matrix from which data is going to be copied.
		 * @return self-reference to an object being assigned.
		 *
		 * @note memory reserve remains unchanged.
		 */
		Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & operator =(const Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & other);

		/**
		 * Conversion assignment. Copies elements from other matrix and resizes matrix if
		 * necessary.
		 * @param other other matrix.
		 * @return self-reference to matrix being assigned.
		 *
		 * @note memory reserve remains unchanged.
		 */
		Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & operator =(const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> other);

		/**
		 * Array assignment.
		 * @param elements array of elements in OpenGL column-major format. Array must
		 * contain required number of elements (M * N).
		 * @return self-reference to matrix being assigned.
		 */
		Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & operator =(const T * ptr);

		/**
		 * Conversion to const_MatrixRef<M, T>.
		 */
		operator const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> () const;

		/**
		 * Conversion to MatrixRef<M, N, T>.
		 */
		operator MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> ();

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
		std::size_t m_rows;
		std::size_t m_cols;
		std::size_t m_reserved;
		T * m_elements;
};

template <typename T>
Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::Matrix(const Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & other):
	m_rows(other.rows()),
	m_cols(other.cols()),
	m_reserved(other.reserved())
{
	m_elements = new T[std::max(size(), reserved())];
	std::copy(other.ptr(), other.ptr() + size(), m_elements);
}

template <typename T>
Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::Matrix(const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> other):
	m_rows(other.rows()),
	m_cols(other.cols()),
	m_reserved(other.reserved())
{
	m_elements = new T[std::max(size(), reserved())];
	std::copy(other.ptr(), other.ptr() + size(), m_elements);
}

template <typename T>
Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::Matrix(std::size_t rows, std::size_t cols, std::size_t reserve):
	m_rows(rows),
	m_cols(cols),
	m_reserved(reserve)
{
	m_elements = new T[std::max(size(), reserved())];
	std::fill(ptr(), ptr() + size(), T());
}

template <typename T>
Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::Matrix(T d, std::size_t rows, std::size_t cols, std::size_t reserve):
	m_rows(rows),
	m_cols(cols),
	m_reserved(reserve)
{
	m_elements = new T[std::max(size(), reserved())];
	std::fill(ptr(), ptr() + size(), T());
	for (std::size_t i = 0; i < std::min(rows, cols); i++)
		m_elements[Self::rows() * i + i] = d;
}

template <typename T>
Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::Matrix(const T * ptr, std::size_t rows, std::size_t cols, std::size_t reserve):
	m_rows(rows),
	m_cols(cols),
	m_reserved(reserve)
{
	m_elements = new T[std::max(size(), reserved())];
	std::copy(ptr, ptr + size(), m_elements);
}

template <typename T>
Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::~Matrix()
{
	delete[] m_elements;
}

template <typename T>
Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::operator =(const Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & other)
{
	//handle self-assignment
	if (& other == this)
		return *this;
	resize(other.rows(), other.cols());
	std::copy(other.ptr(), other.ptr() + size(), m_elements);
	return *this;
}

template <typename T>
Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::operator =(const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> other)
{
	//handle self assignment (some weird cast may be performed)
	if (other.ptr() == this->ptr())
		return *this;
	resize(other.rows(), other.cols());
	std::copy(other.ptr(), other.ptr() + size(), m_elements);
	return *this;
}

template <typename T>
Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T> & Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::operator =(const T * ptr)
{
	//self-assignment not required
	std::copy(ptr, ptr + size(), m_elements);
	return *this;
}


template <typename T>
Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::operator const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> () const
{
	return const_MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>(this);
}

template <typename T>
Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::operator MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T> ()
{
	return MatrixRef<SIZE_DYNAMIC, SIZE_DYNAMIC, T>(this);
}

template <typename T>
std::size_t Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::rows() const
{
	return m_rows;
}

template <typename T>
std::size_t Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::cols() const
{
	return m_cols;
}

template <typename T>
std::size_t Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::size() const
{
	return rows() * cols();
}

template <typename T>
void Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::resize(std::size_t rows, std::size_t cols)
{
	//grow or shrink
	if (std::max(rows * cols, size()) > reserved()) {
		T * newElements = new T[std::max(rows * cols, reserved())];
		delete[] m_elements;
		m_elements = newElements;
	}
	m_rows = rows;
	m_cols = cols;
}

template <typename T>
std::size_t Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::reserved() const
{
	return m_reserved;
}

template <typename T>
void Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::reserve(std::size_t p_size)
{
	if (p_size <= size()) {
		//there's already more space allocated than requested
		m_reserved = p_size;
		return;
	}
	T * newElements = new T[p_size];
	//conserve matrix elements
	std::copy(m_elements, m_elements + size(), newElements);
	delete[] m_elements;
	m_elements = newElements;
	m_reserved = p_size;
}

template <typename T>
const T * Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::ptr() const
{
	return m_elements;
}

template <typename T>
T * Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::ptr()
{
	return m_elements;
}

template <typename T>
T Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::operator()(std::size_t i, std::size_t j) const
{
	GPX_ASSERT(i < rows(), "(" << i << ", " << j << ") is out of bounds");
	GPX_ASSERT(j < cols(), "(" << i << ", " << j << ") is out of bounds");
	return element(i, j);
}

template <typename T>
T & Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::operator()(std::size_t i, std::size_t j)
{
	GPX_ASSERT(i < rows(), "(" << i << ", " << j << ") is out of bounds");
	GPX_ASSERT(j < cols(), "(" << i << ", " << j << ") is out of bounds");
	return element(i, j);
}

template <typename T>
T Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::element(std::size_t i, std::size_t j) const
{
	GPX_ASSERT(i < rows(), "element(" << i << ", " << j << ") is out of bounds");
	GPX_ASSERT(j < cols(), "element(" << i << ", " << j << ") is out of bounds");
	return m_elements[j * rows() + i];
}

template <typename T>
T & Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::element(std::size_t i, std::size_t j)
{
	GPX_ASSERT(i < rows(), "element(" << i << ", " << j << ") is out of bounds");
	GPX_ASSERT(j < cols(), "element(" << i << ", " << j << ") is out of bounds");
	return m_elements[j * rows() + i];
}

template <typename T>
T Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::element(std::size_t n) const
{
	GPX_ASSERT(n < size(), "element(" << n << ") is out of bounds");
	return m_elements[n];
}

template <typename T>
T & Matrix<SIZE_DYNAMIC, SIZE_DYNAMIC, T>::element(std::size_t n)
{
	GPX_ASSERT(n < size(), "element(" << n << ") is out of bounds");
	return m_elements[n];
}

/**
 * Matrix with fixed number of rows. Disabled. Use matrix with dynamic number of rows
 * and columns instead.
 * @param M number of rows.
 * @param T type of matrix elements.
 */
template <std::size_t M, typename T>
class Matrix<M, SIZE_DYNAMIC, T>
{
	private:
		/**
		 * Default constructor.
		 */
		Matrix<M, SIZE_DYNAMIC, T>();
};

/**
 * Matrix with fixed number of columns. Disabled. Use matrix with dynamic number of rows
 * and columns instead.
 * @param N number of columns.
 * @param T type of matrix elements.
 */
template <std::size_t N, typename T>
class Matrix<SIZE_DYNAMIC, N, T>
{
	private:
		/**
		 * Default constructor.
		 */
		Matrix<SIZE_DYNAMIC, N, T>();
};

}
}

#endif /* GPX_X_MATH_MATRIX_HPP_ */
