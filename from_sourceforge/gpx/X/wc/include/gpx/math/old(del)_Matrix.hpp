/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_MATRIX_HPP_
#define GPX_X_MATH_MATRIX_HPP_

#include "structures.hpp"

#include <iomanip>

#include GPX_X_MATH_BACKEND_HEADER
#include GPX_X_MATH_BACKEND_MATRIX_HEADER

namespace gpx {
namespace math {

/**
 * Base M x N (M rows, N cols) matrix.
 * @param M number of rows.
 * @param N number of columns.
 * @param T type of matrix elements.
 * @param DIMSPEC dimension specialization. This parameter is irrelevant for user created
 * objects, since they may be created only with @a DIMSPEC set to @p true. It is
 * used to simplify implementation of class specializations.
 */
template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
class Matrix : public GPX_X_MATH_BACKEND_NAMESPACE::Matrix<M, N, T>
{
	typedef GPX_X_MATH_BACKEND_NAMESPACE::Matrix<M, N, T> Parent;

	public:
		static const std::size_t ROWS = M;
		static const std::size_t COLS = N;

	public:
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
		 * @note fixed size matrix can not be resized, however, calling resize() with
		 * current number of rows and columns is considered to be valid resize operation.
		 * Matrix elements should be treated as if they were destroyed, like it is in case
		 * of true resize of dynamically sized matrix.
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
		 * stored without the need of memory reallocation. Fixed size matrices return their
		 * size().
		 */
		std::size_t reserve() const;

		/**
		 * Reserve memory. Purpose of this function is to reserve as much space as required
		 * to store given number of elements, so that memory reallocation won't be necessary
		 * during further resize operations. This is not imperative. Request may be
		 * scheduled for future realization or even ignored. In any case function is
		 * obliged to preserve matrix data.
		 * @param size amount of memory to reserve in terms of number of elements.
		 *
		 * @note function does nothing in case of fixed size matrices, although it is legal
		 * to perform a call.
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
		 * Get succeeding elements (const version). Direct access to elements succeeding (i,j)
		 * element of matrix. Returns const pointer to OpenGL style array that represents
		 * matrix in column-major format.
		 * @param i row.
		 * @param j column.
		 * @return elements succeeding (i,j) element of matrix. This is a const pointer to one
		 * dimensional array representing a matrix. A matrix is represented in column-major
		 * order, which is OpenGL style of matrix representation. Transpose matrix to
		 * obtain C (row-major) format.
		 */
		const T * ptr(std::size_t i, std::size_t j) const;

		/**
		 * Get succeeding elements. Direct access to elements succeeding (i,j) element of
		 * matrix. Returns pointer to OpenGL style array that represents matrix in
		 * column-major format.
		 * @param i row.
		 * @param j column.
		 * @return elements succeeding (i,j) element of matrix. This is a pointer to one
		 * dimensional array representing a matrix. A matrix is represented in column-major
		 * order, which is OpenGL style of matrix representation. Transpose matrix to
		 * obtain C (row-major) format.
		 */
		T * ptr(std::size_t i, std::size_t j);

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
		 * Equality operator.
		 * @param other other matrix.
		 * @return @p true if all elements of this matrix are equal to the corresponding
		 * elements of the other matrix; @p false otherwise.
		 */
		bool operator ==(const Matrix<M, N, T> & other) const;

		/**
		 * Scalar equality operator.
		 * @param val value of the diagonal elements.
		 * @return @p true if all diagonal matrix elements are equal to specified value
		 * and the rest are zeros; @p false otherwise.
		 */
		bool operator ==(T val) const;

		/**
		 * Approximately equal.
		 * @param other other matrix.
		 * @return @p true if all elements of this matrix are approximately equal to the
		 * corresponding elements of the other matrix; @p false otherwise.
		 */
		bool ape(const Matrix<M, N, T> & other) const;

		/**
		 * Scalar approximately equal.
		 * @param val value of the diagonal elements.
		 * @return @p true if all diagonal matrix elements are approximately equal to
		 * specified value and the rest are approximately zeros; @p false otherwise.
		 */
		bool ape(T val) const;

		/**
		 * Almost equal.
		 * @param other other matrix.
		 * @return @p true if all elements of this matrix are almost equal to the
		 * corresponding elements of the other matrix; @p false otherwise.
		 *
		 * @note ale() is stronger than ape().
		 */
		bool ale(const Matrix<M, N, T> & other) const;

		/**
		 * Scalar almost equal.
		 * @param val value of the diagonal elements.
		 * @return @p true if all diagonal matrix elements are almost equal to
		 * specified value and the rest are almost zeros; @p false otherwise.
		 *
		 * @note ale() is stronger than ape().
		 */
		bool ale(T val) const;

		/**
		 * Inequality operator.
		 * @param other other matrix.
		 * @return @p true if at least one element is not equal to the corresponding element
		 * of the other matrix; @p false otherwise.
		 */
		bool operator !=(const Matrix<M, N, T> & other) const;

		/**
		 * Scalar inequality operator.
		 * @param val value of the diagonal elements.
		 * @param @p true if at least one element on the diagonal is unequal to specified
		 * value or any of the elements outside the diagonal is non-zero; @p false otherwise.
		 */
		bool operator !=(T val) const;

		/**
		 * Addition. Add other matrix to this matrix.
		 * @param other matrix to be added.
		 * @return self-reference to matrix performing operation.
		 */
		Matrix<M, N, T> & add(const Matrix<M, N, T> & other);

		/**
		 * Addition assignment. Alias of add().
		 * @param other matrix to be added.
		 * @return self-reference to matrix performing operation.
		 */
		Matrix<M, N, T> & operator +=(const Matrix<M, N, T> & other);

		/**
		 * Subtraction. Subtract other matrix from this matrix.
		 * @param other matrix to be subtracted.
		 * @return self-reference to matrix performing operation.
		 */
		Matrix<M, N, T> & sub(const Matrix<M, N, T> & other);

		/**
		 * Subtraction assignment. Alias of sub().
		 * @param other matrix to be subtracted.
		 * @return self-reference to matrix performing operation.
		 */
		Matrix<M, N, T> & operator -=(const Matrix<M, N, T> & other);

		/**
		 * Multiplication. Multiply matrix by another matrix.
		 * @param other matrix multiplier.
		 * @return self-reference to matrix performing operation.
		 */
		Matrix<M, N, T> & mul(const Matrix<N, N, T> & other);

		/**
		 * Scalar multiplication. Multiply all matrix elements by scalar value.
		 * @param val scalar multiplier.
		 * @return self-reference to matrix performing operation.
		 */
		Matrix<M, N, T> & mul(T val);

		/**
		 * Multiplication assignment. Alias of mul().
		 * @param other matrix multiplier.
		 * @return self-reference to matrix performing operation.
		 */
		Matrix<M, N, T> & operator *=(const Matrix<N, N, T> & other);

		/**
		 * Scalar multiplication assignment. Alias of mul().
		 * @param val scalar multiplier.
		 * @return self-reference to matrix performing operation.
		 */
		Matrix<M, N, T> & operator *=(T val);

		/**
		 * Sum.
		 * @param other matrix to be added.
		 * @return sum of this matrix and the other.
		 */
		Matrix<M, N, T> sum(const Matrix<M, N, T> & other) const;

		/**
		 * Sum. Alias of sum().
		 * @param other matrix to be added.
		 * @return sum of this matrix and the other.
		 */
		Matrix<M, N, T> operator +(const Matrix<M, N, T> & other) const;

		/**
		 * Difference.
		 * @param other matrix to be subtracted.
		 * @return difference of this matrix and the other.
		 */
		Matrix<M, N, T> diff(const Matrix<M, N, T> & other) const;

		/**
		 * Difference. Alias of diff().
		 * @param other matrix to be subtracted.
		 * @return difference of this matrix and the other.
		 */
		Matrix<M, N, T> operator -(const Matrix<M, N, T> & other) const;

		/**
		 * Product.
		 * @param other matrix multiplier. Other matrix may have arbitrary number of
		 * @a ON columns.
		 * @return product of this matrix multiplied by other.
		 */
		template <std::size_t ON>
		Matrix<M, ON, T> prod(const Matrix<N, ON, T> & other) const;

		/**
		 * Vector product. Multiply matrix by vector.
		 * @param vec vector multiplier.
		 * @return product of matrix multiplied by vector.
		 */
		Vector<M, T> prod(const_VectorRef<N, T> vec) const;

		/**
		 * Scalar product.
		 * @param val scalar multiplier.
		 * @return product of this matrix multiplied by scalar.
		 */
		Matrix<M, N, T> prod(T val) const;

		/**
		 * Product. Alias of prod().
		 * @param other matrix multiplier. Other matrix may have arbitrary number of
		 * @a ON columns.
		 * @return product of this matrix multiplied by other.
		 */
		template <std::size_t ON>
		Matrix<M, ON, T> operator *(const Matrix<N, ON, T> & other) const;

		/**
		 * Vector product. Alias of prod().
		 * @param val scalar multiplier.
		 * @return product of this matrix multiplied by scalar.
		 */
		Vector<M, T> operator *(const_VectorRef<N, T> vec) const;

		/**
		 * Scalar product. Alias of prod().
		 * @param val scalar multiplier.
		 * @return product of this matrix multiplied by scalar.
		 */
		Matrix<M, N, T> operator *(T val) const;

		/**
		 * Transposed matrix.
		 * @return transposed matrix.
		 */
		Matrix<N, M, T> transposed() const;

		/**
		 * Swap rows.
		 * @param r1 row to be swapped with @a r2.
		 * @param r2 row to be swapped with @a r1.
		 */
		void swapRows(std::size_t r1, std::size_t r2);

		/**
		 * Swap columns.
		 * @param c1 column to be swapped with @a c2.
		 * @param c2 column to be swapped with @a c1.
		 */
		void swapCols(std::size_t c1, std::size_t c2);

	protected:
		/**
		 * Default constructor. Matrix is initialized with zeros.
		 */
		Matrix(); //note: matrix initialization is performed to be consistent with pseudo-ctors (T()) for built-in types, although C++ isn't consistent within itself, cause it distinguishes "int i = int();" from "int i;", thus not calling pseudo-ctor in second scenario, while it always calls ctors when it comes to custom classes: e.g., statement "MyClass obj;" in opposite to "int i;" calls default ctor (IMO either it should not or "int i;" should).

		/**
		 * Copy constructor.
		 * @param other other matrix.
		 */
		Matrix(const Matrix<M, N, T, DIMSPEC> & other);

		/**
		 * Constructor. Specified number of rows and columns is initialized with zeros.
		 * @param rows number of rows to be initialized with zeros.
		 * @param cols number of columns to be initialized with zeros.
		 * @param reserve amount of extra memory to reserve in terms of number of elements.
		 */
		Matrix(std::size_t rows, std::size_t cols, std::size_t reserve);

		/**
		 * Conversion constructor.
		 * @param other other matrix.
		 * @param reserve amount of extra memory to reserve in terms of number of elements.
		 */
		template <std::size_t OM, std::size_t ON>
		Matrix(const Matrix<OM, ON, T, DIMSPEC> & other, std::size_t reserve);

		/**
		 * Constructor. Create matrix from given data. Data is copied into internal storage.
		 * @param elements array of elements in OpenGL column-major format. Array must
		 * contain required number of elements (M * N).
		 * @param rows number of rows.
		 * @param cols number of columns.
		 * @param reserve amount of extra memory to reserve in terms of number of elements.
		 */
		Matrix(const T * elements, std::size_t rows, std::size_t cols, std::size_t reserve);

		/**
		 * Constructor. Initializes scalar matrix with specified diagonal elements.
		 * The rest of matrix is initialized with zeros.
		 * @param d value to be set on diagonal. Thus Matrix(1) will setup identity matrix.
		 * @param rows number of rows.
		 * @param cols number of columns.
		 * @param reserve amount of extra memory to reserve in terms of number of elements.
		 */
		Matrix(T d, std::size_t rows, std::size_t cols, std::size_t reserve);
};

/**
 * General M x N (M rows, N cols) matrix.
 * @param M number of rows.
 * @param N number of columns.
 * @param T type of matrix elements.
 */
template <std::size_t M, std::size_t N, typename T>
class Matrix<M, N, T, true> : public Matrix<M, N, T, false>
{
	typedef Matrix<M, N, T, false> Parent;

	public:
		/**
		 * Default constructor. Matrix is initialized with zeros.
		 */
		Matrix();		//note: matrix initialization is performed to be consistent with pseudo-ctors (T()) for built-in types, although C++ isn't consistent within itself, cause it distinguishes "int i = int();" from "int i;", thus not calling pseudo-ctor in second scenario, while it always calls ctors when it comes to custom classes: e.g., statement "MyClass obj;" in opposite to "int i;" calls default ctor (IMO either it should not or "int i;" should).

		//generated copy ctor OK
		//Matrix(const Matrix<M, N, T> & other);

		/**
		 * Constructor. Create matrix from given data. Data is copied into internal storage.
		 * @param elements array of elements in OpenGL column-major format. Array must
		 * contain required number of elements (M * N).
		 */
		explicit Matrix(const T * elements);

		/**
		 * Constructor. Initializes scalar matrix with specified diagonal elements.
		 * The rest of matrix is initialized with zeros.
		 * @param d value to be set on diagonal. E.g., Matrix(1) will setup identity matrix.
		 */
		explicit Matrix(T d);

		//ctors provided for compatibility with dynamically sized matrices

		/**
		 * Constructor.
		 * @param rows number of rows.
		 * @param cols number of columns.
		 * @param reserve provided for compatibility with dynamically sized matrices.
		 */
		Matrix(std::size_t rows, std::size_t cols, std::size_t reserve = M * N);

		/**
		 * Constructor. Create matrix from given data. Data is copied into internal storage.
		 * @param elements array of elements in OpenGL column-major format. Array must
		 * contain required number of elements (rows * cols).
		 * @param rows number of rows.
		 * @param cols number of columns.
		 * @param reserve provided for compatibility with dynamically sized matrices.
		 */
		Matrix(const T * elements, std::size_t rows, std::size_t cols, std::size_t reserve = M * N);

		/**
		 * Constructor. Initializes scalar matrix with specified diagonal elements.
		 * The rest of matrix is initialized with zeros.
		 * @param d value to be set on diagonal. E.g., Matrix(1) will setup identity matrix.
		 * @param rows number of rows.
		 * @param cols number of columns.
		 * @param reserve provided for compatibility with dynamically sized matrices.
		 */
		Matrix(T d, std::size_t rows, std::size_t cols, std::size_t reserve = M * N);

	public:
		//generated copy-assignment OK
		//Matrix<M, N, T> & operator =(const Matrix<M, N, T> & other);

		/**
		 * Assignment operator. Assigns given data. Elements are copied into internal
		 * storage.
		 * @param elements array of elements in OpenGL column-major format. Array must
		 * contain required number of elements (M * N).
		 * @return self-reference to matrix being assigned.
		 */
		Matrix<M, N, T> & operator =(const T * elements); //assignment operators hidden by generated copy-assignment

		/**
		 * Scalar assignment operator. Values on the diagonal are set to specified value,
		 * other elements are zeroed.
		 * @param val value to be set on matrix diagonal.
		 * @return self-reference to matrix being assigned.
		 */
		Matrix<M, N, T> & operator =(T val); //assignment operators hidden by generated copy-assignment
};

/**
 * Square N x N (N rows, N cols) matrix.
 * @param N number of rows.
 * @param N number of columns.
 * @param T type of matrix elements.
 */
template <std::size_t N, typename T>
class Matrix<N, N, T, true> : public Matrix<N, N, T, false>
{
	typedef Matrix<N, N, T, false> Parent;

	public:
		/**
		 * Default constructor. Matrix is initialized with zeros.
		 */
		Matrix();		//note: matrix initialization is performed to be consistent with pseudo-ctors (T()) for built-in types, although C++ isn't consistent within itself, cause it distinguishes "int i = int();" from "int i;", thus not calling pseudo-ctor in second scenario, while it always calls ctors when it comes to custom classes: e.g., statement "MyClass obj;" in opposite to "int i;" calls default ctor (IMO either it should not or "int i;" should).

		//generated copy ctor OK
		//Matrix(const Matrix<N, N, T> & other);

		/**
		 * Constructor. Create matrix from given data. Data is copied into internal storage.
		 * @param elements array of elements in OpenGL column-major format. Array must
		 * contain required number of elements (N * N).
		 */
		explicit Matrix(const T * elements);

		/**
		 * Constructor. Initializes scalar matrix with specified diagonal elements.
		 * The rest of matrix is initialized with zeros.
		 * @param d value to be set on diagonal. E.g., Matrix(1) will setup identity matrix.
		 */
		Matrix(T d);

		//ctors provided for compatibility with dynamically sized matrices

		/**
		 * Constructor.
		 * @param d value to be set on diagonal. E.g., Matrix(1) will setup identity matrix.
		 * @param rows number of rows.
		 * @param cols number of columns.
		 * @param reserve provided for compatibility with dynamically sized matrices.
		 */
		Matrix(std::size_t rows, std::size_t cols, std::size_t reserve = N * N);

		/**
		 * Constructor. Create matrix from given data. Data is copied into internal storage.
		 * @param elements array of elements in OpenGL column-major format. Array must
		 * contain required number of elements (rows * cols).
		 * @param rows number of rows.
		 * @param cols number of columns.
		 * @param reserve provided for compatibility with dynamically sized matrices.
		 */
		Matrix(const T * elements, std::size_t rows, std::size_t cols, std::size_t reserve = N * N);

		/**
		 * Constructor. Initializes scalar matrix with specified diagonal elements.
		 * The rest of matrix is initialized with zeros.
		 * @param d value to be set on diagonal. E.g., Matrix(1) will setup identity matrix.
		 * @param rows number of rows.
		 * @param cols number of columns.
		 * @param reserve provided for compatibility with dynamically sized matrices.
		 */
		Matrix(T d, std::size_t rows, std::size_t cols, std::size_t reserve = N * N);

	public:
		//generated copy-assignment OK
		//Matrix<N, N, T> & operator =(const Matrix<N, N, T> & other);

		/**
		 * Assignment operator. Assigns given data. Elements are copied into internal
		 * storage.
		 * @param elements array of elements in OpenGL column-major format. Array must
		 * contain required number of elements (N * N).
		 * @return self-reference to matrix being assigned.
		 */
		Matrix<N, N, T> & operator =(const T * elements); //assignment operators hidden by generated copy-assignment

		/**
		 * Scalar assignment operator. Values on the diagonal are set to specified value,
		 * other elements are zeroed.
		 * @param val value to be set on matrix diagonal.
		 * @return self-reference to matrix being assigned.
		 */
		Matrix<N, N, T> & operator =(T val); //assignment operators hidden by generated copy-assignment

		/**
		 * Transpose matrix.
		 * @return self-reference to matrix being transposed.
		 */
		Matrix<N, N, T> & transpose();

		/**
		 * Invert matrix.
		 * @param self-reference to inverted matrix.
		 *
		 * @warning matrix should be non-singular.
		 */
		Matrix<N, N, T> & invert();

		/**
		 * Determinant.
		 * @return matrix determinant.
		 */
		T det() const;
};

/**
 * Dynamically sized matrix.
 * @param T type of matrix elements.
 */
template <typename T>
class Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true> : public Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, false>
{
	typedef Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, false> Parent;

	public:
		/**
		 * Default constructor. Creates matrix with no elements (0x0 size).
		 * @param reserve amount of extra memory to reserve in terms of number of elements.
		 */
		Matrix();

		/**
		 * Constructor. Creates matrix with specified size. Matrix is initialized with zeros.
		 * @param rows number of rows.
		 * @param cols number of columns.
		 * @param reserve amount of extra memory to reserve in terms of number of elements.
		 */
		Matrix(std::size_t rows, std::size_t cols, std::size_t reserve = 0);

		//generated copy ctor OK
		//Matrix(const Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & other);

		/**
		 * Constructor.
		 * @param other other matrix.
		 * @param reserve amount of extra memory to reserve in terms of number of elements.
		 */
		template <std::size_t OM, std::size_t ON>
		explicit Matrix(const Matrix<OM, ON, T> & other, std::size_t reserve = 0);

		/**
		 * Constructor. Create matrix from given data. Data is copied into internal storage.
		 * @param elements array of elements in OpenGL column-major format. Array must
		 * contain required number of elements (rows * cols).
		 * @param rows number of rows.
		 * @param cols number of columns.
		 * @param reserve amount of extra memory to reserve in terms of number of elements.
		 */
		Matrix(const T * elements, std::size_t rows, std::size_t cols, std::size_t reserve = 0);

		/**
		 * Constructor. Initializes scalar matrix with specified diagonal elements.
		 * The rest of matrix is initialized with zeros.
		 * @param d value to be set on diagonal.
		 * @param rows number of rows.
		 * @param cols number of columns.
		 * @param reserve amount of extra memory to reserve in terms of number of elements.
		 */
		Matrix(T d, std::size_t rows, std::size_t cols, std::size_t reserve = 0);

	public:
		//generated copy-assignment OK
		//Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & operator =(const Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & other);

		/**
		 * Assignment operator. Assigns given data. Elements are copied into internal
		 * storage.
		 * @param elements array of elements in OpenGL column-major format. Array must
		 * contain required number of elements (rows() * cols()).
		 * @return self-reference to matrix being assigned.
		 */
		Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & operator =(const T * elements); //assignment operators hidden by generated copy-assignment

		/**
		 * Scalar assignment operator. Values on the diagonal are set to specified value,
		 * other elements are zeroed.
		 * @param val value to be set on matrix diagonal.
		 * @return self-reference to matrix being assigned.
		 */
		Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & operator =(T val); //assignment operators hidden by generated copy-assignment

		/**
		 * Conversion assignment. Copies elements from other matrix and resizes matrix if
		 * necessary.
		 * @param other other matrix.
		 * @return self-reference to matrix being assigned.
		 */
		template<std::size_t OM, std::size_t ON>
		Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & operator =(const Matrix<OM, ON, T> & other);

		/**
		 * Transpose matrix.
		 * @return self-reference to matrix being transposed.
		 */
		Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & transpose();

		/**
		 * Invert matrix.
		 * @param self-reference to inverted matrix.
		 *
		 * @warning matrix must be square and non-singular, otherwise function will fail.
		 */
		Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & invert();

		/**
		 * Determinant.
		 * @return matrix determinant.
		 *
		 * @warning matrix must be square, otherwise function will fail.
		 */
		T det() const;
};

/**
 * Matrix with fixed number of rows. Disabled. Use matrix with dynamic number of rows
 * and columns instead.
 * @param M number of rows.
 * @param T type of matrix elements.
 */
template <std::size_t M, typename T>
class Matrix<M, gpx::math::SIZE_DYNAMIC, T, true> : public Matrix<M, gpx::math::SIZE_DYNAMIC, T, false>
{
	typedef Matrix<M, gpx::math::SIZE_DYNAMIC, T, false> Parent;

	private:
		/**
		 * Default constructor.
		 */
		Matrix<M, gpx::math::SIZE_DYNAMIC, T, true>();
};

/**
 * Matrix with fixed number of columns. Disabled. Use matrix with dynamic number of rows
 * and columns instead.
 * @param N number of columns.
 * @param T type of matrix elements.
 */
template <std::size_t N, typename T>
class Matrix<gpx::math::SIZE_DYNAMIC, N, T, true> : public Matrix<gpx::math::SIZE_DYNAMIC, N, T, false>
{
	typedef Matrix<gpx::math::SIZE_DYNAMIC, N, T, false> Parent;

	private:
		/**
		 * Default constructor.
		 */
		Matrix<gpx::math::SIZE_DYNAMIC, N, T, true>();
};

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
std::size_t Matrix<M, N, T, DIMSPEC>::rows() const
{
	return Parent::rows();
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
std::size_t Matrix<M, N, T, DIMSPEC>::cols() const
{
	return Parent::cols();
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
std::size_t Matrix<M, N, T, DIMSPEC>::size() const
{
	return Parent::size();
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
void Matrix<M, N, T, DIMSPEC>::resize(std::size_t rows, std::size_t cols)
{
	Parent::resize(rows, cols);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
std::size_t Matrix<M, N, T, DIMSPEC>::reserve() const
{
	return Parent::reserve();
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
void Matrix<M, N, T, DIMSPEC>::reserve(std::size_t size)
{
	Parent::reserve(size);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
const T * Matrix<M, N, T, DIMSPEC>::ptr() const
{
	return Parent::ptr();
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
T * Matrix<M, N, T, DIMSPEC>::ptr()
{
	return Parent::ptr();
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
const T * Matrix<M, N, T, DIMSPEC>::ptr(std::size_t i, std::size_t j) const
{
	GPX_ASSERT(i < rows(), "ptr(" << i << ", " << j << ") is out of bounds");
	GPX_ASSERT(j < cols(), "ptr(" << i << ", " << j << ") is out of bounds");
	return Parent::ptr(i, j);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
T * Matrix<M, N, T, DIMSPEC>::ptr(std::size_t i, std::size_t j)
{
	GPX_ASSERT(i < rows(), "ptr(" << i << ", " << j << ") is out of bounds");
	GPX_ASSERT(j < cols(), "ptr(" << i << ", " << j << ") is out of bounds");
	return Parent::ptr(i, j);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
T Matrix<M, N, T, DIMSPEC>::operator()(std::size_t i, std::size_t j) const
{
	GPX_ASSERT(i < rows(), "row index (" << i << ", " << j << ") is out of bounds");
	GPX_ASSERT(j < cols(), "column index (" << i << ", " << j << ") is out of bounds");
	return Parent::operator()(i, j);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
T & Matrix<M, N, T, DIMSPEC>::operator()(std::size_t i, std::size_t j)
{
	GPX_ASSERT(i < rows(), "row index (" << i << ", " << j << ") is out of bounds");
	GPX_ASSERT(j < cols(), "column index (" << i << ", " << j << ") is out of bounds");
	return Parent::operator()(i, j);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
bool Matrix<M, N, T, DIMSPEC>::operator ==(const Matrix<M, N, T> & other) const
{
	return Parent::operator ==(other);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
bool Matrix<M, N, T, DIMSPEC>::operator ==(T val) const
{
	return Parent::operator ==(val);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
bool Matrix<M, N, T, DIMSPEC>::ape(const Matrix<M, N, T> & other) const
{
	return Parent::ape(other);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
bool Matrix<M, N, T, DIMSPEC>::ape(T val) const
{
	return Parent::ape(val);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
bool Matrix<M, N, T, DIMSPEC>::ale(const Matrix<M, N, T> & other) const
{
	return Parent::ale(other);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
bool Matrix<M, N, T, DIMSPEC>::ale(T val) const
{
	return Parent::ale(val);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
bool Matrix<M, N, T, DIMSPEC>::operator !=(const Matrix<M, N, T> & other) const
{
	return Parent::operator !=(other);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
bool Matrix<M, N, T, DIMSPEC>::operator !=(T val) const
{
	return Parent::operator !=(val);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T> & Matrix<M, N, T, DIMSPEC>::add(const Matrix<M, N, T> & other)
{
	Parent::add(other);
	return static_cast<Matrix<M, N, T> & >(*this);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T> & Matrix<M, N, T, DIMSPEC>::operator +=(const Matrix<M, N, T> & other)
{
	Parent::add(other);
	return static_cast<Matrix<M, N, T> & >(*this);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T> & Matrix<M, N, T, DIMSPEC>::sub(const Matrix<M, N, T> & other)
{
	Parent::sub(other);
	return static_cast<Matrix<M, N, T> & >(*this);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T> & Matrix<M, N, T, DIMSPEC>::operator -=(const Matrix<M, N, T> & other)
{
	Parent::sub(other);
	return static_cast<Matrix<M, N, T> & >(*this);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T> & Matrix<M, N, T, DIMSPEC>::mul(const Matrix<N, N, T> & other)
{
	Parent::mul(other);
	return static_cast<Matrix<M, N, T> & >(*this);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T> & Matrix<M, N, T, DIMSPEC>::mul(T val)
{
	Parent::mul(val);
	return static_cast<Matrix<M, N, T> & >(*this);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T> & Matrix<M, N, T, DIMSPEC>::operator *=(const Matrix<N, N, T> & other)
{
	Parent::mul(other);
	return static_cast<Matrix<M, N, T> & >(*this);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T> & Matrix<M, N, T, DIMSPEC>::operator *=(T val)
{
	Parent::mul(val);
	return static_cast<Matrix<M, N, T> & >(*this);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T> Matrix<M, N, T, DIMSPEC>::sum(const Matrix<M, N, T> & other) const
{
	return Parent::sum(other);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T> Matrix<M, N, T, DIMSPEC>::operator +(const Matrix<M, N, T> & other) const
{
	return Parent::sum(other);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T> Matrix<M, N, T, DIMSPEC>::diff(const Matrix<M, N, T> & other) const
{
	return Parent::diff(other);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T> Matrix<M, N, T, DIMSPEC>::operator -(const Matrix<M, N, T> & other) const
{
	return Parent::diff(other);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
template <std::size_t ON>
inline
Matrix<M, ON, T> Matrix<M, N, T, DIMSPEC>::prod(const Matrix<N, ON, T> & other) const
{
	return Parent::prod(other);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Vector<M, T> Matrix<M, N, T, DIMSPEC>::prod(const_VectorRef<N, T> vec) const
{
	return Parent::prod(vec);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T> Matrix<M, N, T, DIMSPEC>::prod(T val) const
{
	return Parent::prod(val);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
template <std::size_t ON>
inline
Matrix<M, ON, T> Matrix<M, N, T, DIMSPEC>::operator *(const Matrix<N, ON, T> & other) const
{
	return Parent::prod(other);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Vector<M, T> Matrix<M, N, T, DIMSPEC>::operator *(const_VectorRef<N, T> vec) const
{
	return Parent::prod(vec);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T> Matrix<M, N, T, DIMSPEC>::operator *(T val) const
{
	return Parent::prod(val);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<N, M, T> Matrix<M, N, T, DIMSPEC>::transposed() const
{
	return Parent::transposed();
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
void Matrix<M, N, T, DIMSPEC>::swapRows(std::size_t r1, std::size_t r2)
{
	Parent::swapRows(r1, r2);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
void Matrix<M, N, T, DIMSPEC>::swapCols(std::size_t c1, std::size_t c2)
{
	Parent::swapCols(c1, c2);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T, DIMSPEC>::Matrix():
	Parent(0)
{
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T, DIMSPEC>::Matrix(const Matrix<M, N, T, DIMSPEC> & other):
	Parent(other)
{
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T, DIMSPEC>::Matrix(std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(rows, cols, reserve)
{
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
template <std::size_t OM, std::size_t ON>
inline
Matrix<M, N, T, DIMSPEC>::Matrix(const Matrix<OM, ON, T, DIMSPEC> & other, std::size_t reserve):
	Parent(other, reserve)
{
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T, DIMSPEC>::Matrix(const T * elements, std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(elements, rows, cols, reserve)
{
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T, DIMSPEC>::Matrix(T d, std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(d, rows, cols, reserve)
{
}

// DIMSPEC = true

template <std::size_t M, std::size_t N, typename T>
inline
Matrix<M, N, T, true>::Matrix():
	Parent()
{
}

template <std::size_t M, std::size_t N, typename T>
inline
Matrix<M, N, T, true>::Matrix(const T * elements):
	Parent(elements, M, N, 0)
{
}

template <std::size_t M, std::size_t N, typename T>
inline
Matrix<M, N, T, true>::Matrix(T d):
	Parent(d, M, N, 0)
{
}

template <std::size_t M, std::size_t N, typename T>
inline
Matrix<M, N, T, true>::Matrix(std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(rows, cols, reserve)
{
}

template <std::size_t M, std::size_t N, typename T>
inline
Matrix<M, N, T, true>::Matrix(const T * elements, std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(elements, rows, cols, reserve)
{
}

template <std::size_t M, std::size_t N, typename T>
inline
Matrix<M, N, T, true>::Matrix(T d, std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(d, rows, cols, reserve)
{
}

template <std::size_t M, std::size_t N, typename T>
inline
Matrix<M, N, T> & Matrix<M, N, T, true>::operator =(const T * elements)
{
	//self assignment branch not required here
	GPX_X_MATH_BACKEND_NAMESPACE::Matrix<M, N, T>::operator =(elements);
	return *this;
}

template <std::size_t M, std::size_t N, typename T>
inline
Matrix<M, N, T> & Matrix<M, N, T, true>::operator =(T val)
{
	//self assignment branch not required here
	GPX_X_MATH_BACKEND_NAMESPACE::Matrix<M, N, T>::operator =(val);
	return *this;
}

// DIMSPEC = true, M = N

template <std::size_t N, typename T>
inline
Matrix<N, N, T, true>::Matrix():
	Parent()
{
}

template <std::size_t N, typename T>
inline
Matrix<N, N, T, true>::Matrix(const T * elements):
	Parent(elements, N, N, 0)
{
}

template <std::size_t N, typename T>
inline
Matrix<N, N, T, true>::Matrix(T d):
	Parent(d, N, N, 0)
{
}

template <std::size_t N, typename T>
inline
Matrix<N, N, T, true>::Matrix(std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(rows, cols, reserve)
{
}

template <std::size_t N, typename T>
inline
Matrix<N, N, T, true>::Matrix(const T * elements, std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(elements, rows, cols, reserve)
{
}

template <std::size_t N, typename T>
inline
Matrix<N, N, T, true>::Matrix(T d, std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(d, rows, cols, reserve)
{
}

template <std::size_t N, typename T>
inline
Matrix<N, N, T> & Matrix<N, N, T, true>::operator =(const T * elements)
{
	//self assignment branch not required here
	GPX_X_MATH_BACKEND_NAMESPACE::Matrix<N, N, T>::operator =(elements);
	return *this;
}

template <std::size_t N, typename T>
inline
Matrix<N, N, T> & Matrix<N, N, T, true>::operator =(T val)
{
	//self assignment branch not required here
	GPX_X_MATH_BACKEND_NAMESPACE::Matrix<N, N, T>::operator =(val);
	return *this;
}

template <std::size_t N, typename T>
inline
Matrix<N, N, T> & Matrix<N, N, T, true>::transpose()
{
	Parent::transpose();
	return *this;
}

template <std::size_t N, typename T>
inline
Matrix<N, N, T> & Matrix<N, N, T, true>::invert()
{
	Parent::invert();
	return *this;
}

template <std::size_t N, typename T>
inline
T Matrix<N, N, T, true>::det() const
{
	return Parent::det();
}

// DIMSPEC = true, M = SIZE_DYNAMIC, N = SIZE_DYNAMIC

template <typename T>
inline
Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::Matrix():
	Parent()
{
}

template <typename T>
inline
Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::Matrix(std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(rows, cols, reserve)
{
}

template <typename T>
template <std::size_t OM, std::size_t ON>
inline
Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::Matrix(const Matrix<OM, ON, T> & other, std::size_t reserve):
	Parent(other, reserve)
{
}

template <typename T>
inline
Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::Matrix(const T * elements, std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(elements, rows, cols, reserve)
{
}

template <typename T>
inline
Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::Matrix(T d, std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(d, rows, cols, reserve)
{
}

template <typename T>
inline
Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::operator =(const T * elements)
{
	GPX_X_MATH_BACKEND_NAMESPACE::Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::operator =(elements);
	return *this;
}

template <typename T>
inline
Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::operator =(T val)
{
	GPX_X_MATH_BACKEND_NAMESPACE::Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::operator =(val);
	return *this;
}

template <typename T>
template <std::size_t OM, std::size_t ON>
inline
Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::operator =(const Matrix<OM, ON, T> & other)
{
	GPX_X_MATH_BACKEND_NAMESPACE::Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::operator =(other);
	return *this;
}

template <typename T>
inline
Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::transpose()
{
	Parent::transpose();
	return *this;
}

template <typename T>
inline
Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::invert()
{
	Parent::invert();
	return *this;
}

template <typename T>
inline
T Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::det() const
{
	return Parent::det();
}

}
}

#endif /* GPX_X_MATH_MATRIX_HPP_ */

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
