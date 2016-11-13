/**
 * @file
 * @brief VectorPtr<2> definition.
 */

#include "_structures_warning.hpp"


namespace gpx {
namespace math {


template <std::size_t N, typename T>
class Vector;

template <std::size_t N, typename T>
class VectorPtr;


template <typename T>
class const_VectorPtr<2, T>
{
	//friends are required to directly access ptr of *other* instance from derived classes (VectorPtr<2, T>, Vector<2, T>)
	friend class Vector<2, T>;
	friend class VectorPtr<2, T>;

	protected:
		T * const m_ptr;

	public:
		static int PrintPrecision;
		static const std::size_t SIZE = 2;

	private:
		/**
		 * Assignment operator disabled.
		 */
		const const_VectorPtr<2, T> & operator=(const const_VectorPtr<2, T> & other);

	protected:
		/**
		 * Default constructor forbidden. Must set ptr.
		 */
		const_VectorPtr();

	public:
		/**
		 * Copy constructor. Sets coords pointer to other's pointer. Data is
		 * not copied like when using assignment operator!
		 * @param other other vector.
		 */
		const_VectorPtr(const const_VectorPtr<2, T> & other);

		/**
		 * Conversion constructor.
		 * @param coords pointer to 2 element coordinates array.
		 */
		const_VectorPtr(const T * coords);

		/**
		 * Conversion constructor.
		 * @param other other vector.
		 */
		const_VectorPtr(const Vector<2, T> & other);

		/**
		 * Const version of subscript operator.
		 */
		T operator[](int i) const;

		/**
		 * Const version of function call operator.
		 */
		T operator()(int i) const;

		/**
		 * Get coordinate. Const version of ith-element access.
		 */
		T coord(int i) const;

		/**
		 * Get x coordinate of vector. Alias of coord(0). Const version.
		 */
		T x() const;

		/**
		 * Get y coordinate of vector. Alias of coord(1). Const version.
		 */
		T y() const;

		/**
		 * Equality operator.
		 */
		bool operator==(const const_VectorPtr<2, T> & other) const;

		/**
		 * Inequality operator.
		 */
		bool operator!=(const const_VectorPtr<2, T> & other) const;

		/**
		 * Addition.
		 */
		Vector<2, T> operator+(const const_VectorPtr<2, T> & other) const;

		/**
		 * Subtraction.
		 */
		Vector<2, T> operator-(const const_VectorPtr<2, T> & other) const;

		/**
		 * Unary -. Same as inverse().
		 */
		Vector<2, T> operator-() const;

		/**
		 * Division.
		 */
		Vector<2, T> operator/(T scalar) const;

		/**
		 * Multiplication.
		 */
		Vector<2, T> operator*(T scalar) const;

		/**
		 * Conversion to const T *.
		 */
		operator const T * () const;

		/**
		 * Conversion to size_t. Useful for hash functions. Hash value is calculated
		 * from ptr pointer and not from VectorPtr<2, T> object itself. Two VectorPtr<2, T>
		 * objects will have same value if they refer to the same pointer.
		 *
		 * @warning this operator may not give unique value.
		 */
		operator size_t() const;

		/**
		 * Get dot (or scalar) product of this vector and other.
		 * @param other other vector.
		 * @return dot product.
		 */
		T dot(const const_VectorPtr<2, T> & other) const;

		/**
		 * Get dot product of this vector.
		 * @return dot product of this vector.
		 */
		T dot() const;

		//inner product (like dot but result is vector<1>) ?
//		Vector<1> inn(const VectorPtr<2, T> & other) const;

		/**
		 * Get outer product of this vector and other.
		 * @param other other vector.
		 * @return outer product matrix.
		 */
		Matrix<2,2> out(const const_VectorPtr<2, T> & other) const;

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
		T det(const const_VectorPtr<2, T> & other) const;

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
		bool ape(const const_VectorPtr<2, T> & other) const;

		/**
		 * Almost equal.
		 */
		bool ale(const const_VectorPtr<2, T> & other) const;

		/**
		 * Considerably less than.
		 */
		bool clt(const const_VectorPtr<2, T> & other) const;

		/**
		 * Considerably greater than.
		 */
		bool cgt(const const_VectorPtr<2, T> & other) const;

		/**
		 * Get minimal vector against @a other vector.
		 * @param other vector for which minimal vector has to be prepared.
		 * @return parallel vector with coordinates' exponents reduced to smallest
		 * possible values, that added to @a other vector change both (if initial
		 * coordinates are non-zero) of its coordinates.
		 */
		Vector<2, T> minimal(const const_VectorPtr<2, T> & other) const;
};


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
