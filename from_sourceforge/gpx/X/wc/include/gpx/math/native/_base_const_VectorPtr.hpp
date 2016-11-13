/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_NATIVE__BASE_CONST_VECTORPTR_HPP_
#define GPX_X_MATH_NATIVE__BASE_CONST_VECTORPTR_HPP_

//#note: "_base_const_VectorPtr.imp.hpp" included near eof

namespace gpx {
namespace math {
namespace native {

template <std::size_t N, typename T>
class const_VectorPtr;

template <std::size_t N, typename T>
class base_VectorPtr;

template <std::size_t N, typename T>
class VectorPtr;

template <std::size_t N, typename T>
class base_Vector;

template <std::size_t N, typename T>
class Vector;

/**
 * Base class for N-dimensional vector on top of N-element const pointer. This class can
 * not be instantiated directly. Do not use this class, but const_VectorPtr.
 */
template <std::size_t N, template <std::size_t, typename> class VECTOR, template <std::size_t, std::size_t, typename> class MATRIX, typename T = real_t>
class base_const_VectorPtr
{
	//friends are required to directly access ptr of *other* instance from derived classes (VectorPtr<N, T>, Vector<N, T>)
	friend class const_VectorPtr<N, T>;
//	friend class base_VectorPtr<N, VECTOR, MATRIX, T>;
	friend class VectorPtr<N, T>;
//	friend class base_Vector<N, VECTOR, MATRIX, T>;
	friend class Vector<N, T>;

	public:
		static int PrintPrecision;
		static const std::size_t SIZE = N;

	public:
		/**
		 * Conversion to const T *.
		 */
		operator const T * () const;

		/**
		 * Conversion to size_t. Useful when implementing STL hash functions.
		 *
		 * @warning this operator may not give unique value. Hash value is calculated
		 * from coords pointer passed to the constructor and not from object itself. Two
		 * base_const_VectorPtr<N, T> objects will have same hash value if they refer to
		 * the same pointer.
		 */
		operator size_t() const;

		/**
		 * Individual coordinate access over subscript operator.
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T operator [](int i) const;	//to prevent ambiguity because of T * conversion operator
		T operator [](std::size_t i) const; //default type for subscript access is int, so explicit conversion to size_t is required to call this version

		/**
		 * Individual coordinate access over function call operator.
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T operator ()(std::size_t i) const;

		/**
		 * Individual coordinate access.
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T coord(std::size_t i) const;

		/**
		 * Equality operator.
		 * @param other other vector.
		 * @return @p true if all coordinates of this vector are equal to the corresponding
		 * coordinates of other vector, @p false otherwise.
		 */
		bool operator ==(const const_VectorPtr<N, T> & other) const;

		/**
		 * Inequality operator.
		 * @param other other vector.
		 * @return @p true if at least one of the coordinates is not unequal to the
		 * corresponding coordinate of the other vector, @p false otherwise.
		 */
		bool operator !=(const const_VectorPtr<N, T> & other) const;

		/**
		 * Addition.
		 * @param other other vector.
		 * @return sum of this vector and the other.
		 */
		VECTOR<N, T> operator +(const const_VectorPtr<N, T> & other) const;

		/**
		 * Subtraction.
		 * @param other other vector.
		 * @return difference of this vector and the other.
		 */
		VECTOR<N, T> operator -(const const_VectorPtr<N, T> & other) const;

		/**
		 * Unary minus. Same as inverse().
		 * @return inverted vector.
		 */
		VECTOR<N, T> operator -() const;

		/**
		 * Division.
		 * @param scalar divisor value.
		 * @return this vector divided by scalar.
		 */
		VECTOR<N, T> operator /(T scalar) const;

		/**
		 * Multiplication.
		 * @param scalar multiplier value.
		 * @return this vector multiplied by scalar.
		 */
		VECTOR<N, T> operator *(T scalar) const;

		/**
		 * Dot (or scalar) product of this vector and the other.
		 * @param other other vector.
		 * @return dot product of this and other vector.
		 */
		T dot(const const_VectorPtr<N, T> & other) const;

		/**
		 * Dot product of vector by itself.
		 * @return dot product of vector by itself. For some vector "v", "v.dot()" is
		 * equivalent to calling "v.dot(v)".
		 */
		T dot() const;

		//inner product (like dot but result is vector<1>) ?
//		Vector<1> inn(const VectorPtr<2, T> & other) const;

		/**
		 * Get outer product of this vector and the other.
		 * @param other other vector.
		 * @return outer product matrix.
		 */
		MATRIX<N, N, T> out(const const_VectorPtr<N, T> & other) const;

		/**
		 * Get vector length.
		 * @return length of vector.
		 */
		T length() const;

		/**
		 * Is vector a zero vector.
		 * @return @p true if vector is a zero vector, @p false otherwise.
		 */
		bool isZero() const;

		/**
		 * Obtain inverse vector.
		 *
		 * @see invert(), orthoCW(), orthoCCW().
		 */
		Vector<2, T> inverse() const;

		/**
		 * Get versor of this vector.
		 * @return normalized vector.
		 *
		 * @warning vector must be non zero vector.
		 */
		Vector<2, T> versor() const;

		/**
		 * Get determinant of this vector and other. It's like cross product for Vector<3>
		 * but the result is scalar (length of resulting tensor).
		 * @param other other vector.
		 * @return determinant.
		 */
		T det(const base_const_VectorPtr<N, VECTOR, MATRIX, T> & other) const;

		/**
		 * Get cross product of this vector.
		 * @return cross product.
		 */
		Vector<2, T> cross() const;

		/**
		 * Get perpendicular vector to this vector, turning clockwise.
		 *
		 * @see orthoCCW(), rotate(), inverse().
		 */
		Vector<2, T> orthoCW() const;

		/**
		 * Get perpendicular vector to this vector, turning counter-clockwise.
		 *
		 * @see orthoCW(), rotate(), inverse().
		 */
		Vector<2, T> orthoCCW() const;

		/**
		 * Approximately equal.
		 */
		bool ape(const base_const_VectorPtr<N, VECTOR, MATRIX, T> & other) const;

		/**
		 * Almost equal.
		 */
		bool ale(const base_const_VectorPtr<N, VECTOR, MATRIX, T> & other) const;

		/**
		 * Considerably less than.
		 */
		bool clt(const base_const_VectorPtr<N, VECTOR, MATRIX, T> & other) const;

		/**
		 * Considerably greater than.
		 */
		bool cgt(const base_const_VectorPtr<N, VECTOR, MATRIX, T> & other) const;

		/**
		 * Get minimal vector against @a other vector.
		 * @param other vector for which minimal vector has to be prepared.
		 * @return parallel vector with coordinates' exponents reduced to smallest
		 * possible values, that added to @a other vector change both (if initial
		 * coordinates are non-zero) of its coordinates.
		 */
		VECTOR<N, T> minimal(const base_const_VectorPtr<N, VECTOR, MATRIX, T> & other) const;

		/**
		 * Assignment operator.
		 */
//		void operator=(const VectorPtr<2> & other);
//
//		/**
//		 * Subscript operator (coords access).
//		 */
//		real_t & operator[](int i);
//
//		/**
//		 * Const version of subscript operator.
//		 */
//		real_t operator[](int i) const;
//
//		/**
//		 * Function call operator. Same as subscript operator, however () operator
//		 * is preferred for accessing matrices.
//		 */
//		real_t & operator()(int i);
//
//		/**
//		 * Const version of function call operator.
//		 */
//		real_t operator()(int i) const;
//
//		/**
//		 * Equality operator.
//		 */
//		bool operator==(const VectorPtr<N> & other);
//
//		/**
//		 * Inequality operator.
//		 */
//		bool operator!=(const VectorPtr<N> & other);

		/**
		 * Addition assignment.
		 */
//		VectorPtr<N> & operator+=(const VectorPtr<N> & other);

		/**
		 * Addition.
		 */
//		Vector<N> operator+(const VectorPtr<N> & other);

		/**
		 * Subtraction.
		 */
//		Vector<N> operator-(const VectorPtr<N> & other);

		/**
		 * Subtraction assignment.
		 */
//		VectorPtr<N> & operator-=(const VectorPtr<N> & other);

		/**
		 * Division assignment. Divide all vector coordinates by scalar.
		 * @param scalar scalar.
		 */
//		VectorPtr<N> & operator/=(const real_t scalar);

		/**
		 * Division.
		 */
//		Vector<N> operator/(const real_t scalar);

		/**
		 * Multiplication assignment.
		 */
//		VectorPtr<N> & operator*=(const real_t scalar);

		/**
		 * Multiplication.
		 */
//		Vector<N> operator*(const real_t scalar);

		/**
		 * Conversion to const real_t * const.
		 */
//		operator const real_t * const() const;

		/**
		 * Conversion to real_t * const.
		 */
//		operator real_t * const();

		/**
		 * Reset vector coordinates to (0.0, 0.0).
		 */
//		VectorPtr<N> & zero();

		/**
		 * Add other vector to this vector.
		 * @param other other vector.
		 * @return reference to current vector.
		 */
//		VectorPtr<N> & add(const VectorPtr<2> & other);

		/**
		 * Subtract other vector from this vector.
		 * @param other other vector.
		 * @return reference to current vector.
		 */
//		VectorPtr<N> & sub(const VectorPtr<2> & other);

		/**
		 * Divide all vector coordinates by scalar.
		 * @param scalar scalar.
		 * @return reference to current vector.
		 */
//		VectorPtr<N> & div(const real_t scalar);

		/**
		 * Multiply all vector coordinates by scalar.
		 * @param scalar scalar.
		 * @return reference to current vector.
		 */
//		VectorPtr<N> & mult(const real_t scalar);

		/**
		 * Get dot (or scalar) product of this vector and other.
		 * @param other other vector.
		 * @return dot product.
		 */
//		real_t dot(const VectorPtr<N> & other) const;

		/**
		 * Get dot product of this vector.
		 * @return dot product of this vector.
		 */
//		real_t dot() const;

		//inner product (like dot but result is vector<1>) ?
//		Vector<1> inn(const VectorPtr<2> & other) const;

		/**
		 * Get outer product of this vector and other.
		 * @param other other vector.
		 * @return outer product matrix.
		 */
//		Matrix<N,N> out(const VectorPtr<N> & other) const;

		/**
		 * Get vector length.
		 * @return length of vector.
		 */
//		real_t length() const;

		/**
		 * Normalize this vector.
		 */
//		VectorPtr<N> & normalize();

		/**
		 * Invert this vector.
		 */
//		VectorPtr<N> & invert();

		/**
		 * Get versor of this vector.
		 * @return normalized vector.
		 *
		 * @warning vector must be non zero vector.
		 */
//		Vector<N> versor() const;

		/**
		 * Get cross product of this vector.
		 * @return cross product.
		 */
//		Vector<N> cross(... N-2 vectors) const;

		/**
		 * Rotate around specified (N-1)-dimensional hyper-axis (point - for 2 dimensional
		 * vector, line - for 3 dimensional vector, plane - for 4 dimensional vector and so on).
		 * Hyper-axis is determined by non-selected coordinates.
		 * @param i coordinate to rotate.
		 * @param j coordinate to rotate.
		 */
//		VectorPtr<N> & rotate(int i, int j);

	protected:
		T * const m_ptr;

	protected:
		/**
		 * Conversion constructor.
		 * @param coords pointer to N-element array of coordinates.
		 */
		base_const_VectorPtr(const T * coords);

		/**
		 * Copy constructor. Sets coords pointer to other's pointer. Data is
		 * not copied like when using assignment operator!
		 * @param other other vector.
		 */
		base_const_VectorPtr(const base_const_VectorPtr<N, VECTOR, MATRIX, T> & other);

	private:
		/**
		 * Default constructor. Forbidden; must set ptr.
		 */
		base_const_VectorPtr();

		/**
		 * Assignment operator disabled (const).
		 */
		const base_const_VectorPtr<N, VECTOR, MATRIX, T> & operator=(const base_const_VectorPtr<N, VECTOR, MATRIX, T> & other);
};

}
}
}

#include "_base_const_VectorPtr.imp.hpp"

#endif /* GPX_X_MATH_NATIVE__BASE_CONST_VECTORPTR_HPP_ */

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
