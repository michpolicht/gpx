/**
 * @file
 * @brief Vector<N> definition.
 */

#include "_structures_warning.hpp"


namespace gpx {
namespace math {


/**
 * General n-dimensional vector. Not implemented yet.
 */
template <std::size_t N, typename T = real_t>
class const_VectorPtr
{
	protected:
		T * const m_ptr;

	public:
		/**
		 * Constructor.
		 * @param coords pointer to 2 element coordinates array.
		 */
		const_VectorPtr(T * coords);

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
};


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
