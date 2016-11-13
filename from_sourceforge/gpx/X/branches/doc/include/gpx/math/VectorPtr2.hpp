/**
 * @file
 * @brief VectorPtr<2> definition.
 */

#include "_structures_warning.hpp"


namespace gpx {
namespace math {


template <std::size_t N, typename T>
class Vector;

/**
 * Two dimensional vector specialization. Coords variable may be accessed directly.
 * Coordinates system:
 * @verbatim

   ^ coords[1] (y)
   |
  2|
  1|
   .--------> coords[0] (x)
  0 1 2

 * @endverbatim
 *
 */
template <typename T>
class VectorPtr<2, T>: public const_VectorPtr<2, T>
{
	//friends are required to directly access ptr of *other* instance from derived class (Vector<2, T>)
	friend class Vector<2, T>;

	private:
		typedef const_VectorPtr<2, T> Parent;

	protected:
		/**
		 * Default constructor forbidden. Must set ptr.
		 */
		VectorPtr();

		/**
		 * Conversion constructor. Conversion from const_VectorPtr<2, T> forbidden.
		 * @param other other vector.
		 */
		VectorPtr(const const_VectorPtr<2, T> & other);

	public:
		/**
		 * Copy constructor. Sets coords pointer to other's pointer. Data is
		 * not copied like when using assignment operator!
		 * @param other other vector.
		 */
		VectorPtr(const VectorPtr<2, T> & other);

		/**
		 * Conversion constructor.
		 * @param coords pointer to 2 element coordinates array.
		 */
		VectorPtr(T * coords);

		/**
		 * Conversion constructor.
		 * @param other other vector.
		 */
		VectorPtr(const Vector<2, T> & other);

		/**
		 * Assignment operator. Data will be copied from other to ptr.
		 */
		const VectorPtr<2, T> & operator=(const real_t other[2]);

		/**
		 * Assignment operator. Data will be copied from other to ptr.
		 */
		const VectorPtr<2, T> & operator=(const const_VectorPtr<2, T> & other);

		/**
		 * Assignment operator. Data will be copied from other to ptr.
		 */
		const VectorPtr<2, T> & operator=(const VectorPtr<2, T> & other);

		/**
		 * Subscript operator (coords access).
		 */
		T & operator[](int i);

		/**
		 * Function call operator. Provided as an alternative to subscript operator.
		 *
		 * @note: using function call operator () is preferred for accessing matrices.
		 */
		T & operator()(int i);

		/**
		 * Get coordinate. Yet another way to access i-element in addition to subscript []
		 * and function call () operators. Convenient when dealing with Vector* pointers.
		 */
		T & coord(int i);

		/**
		 * Const version of subscript operator.
		 */
		T operator[](int i) const;

		/**
		 * Const version of function call operator.
		 */
		T operator()(int i) const;

		/**
		 * Get coordinate. Const version of i-element access.
		 */
		T coord(int i) const;

		/**
		 * Addition assignment.
		 */
		VectorPtr<2, T> & operator+=(const const_VectorPtr<2, T> & other);

		/**
		 * Subtraction assignment.
		 */
		VectorPtr<2, T> & operator-=(const const_VectorPtr<2, T> & other);

		/**
		 * Division assignment. Divide all vector coordinates by scalar.
		 * @param scalar scalar.
		 */
		VectorPtr<2, T> & operator/=(T scalar);

		/**
		 * Multiplication assignment.
		 */
		VectorPtr<2, T> & operator*=(T scalar);

		/**
		 * Conversion to T *.
		 */
		operator T *();

		/**
		 * Set coordinates.
		 * @param x x coordinate.
		 * @param y y coordinate.
		 */
		VectorPtr<2, T> & set(T x, T y);

		/**
		 * Reset vector coordinates to (0.0, 0.0).
		 */
		VectorPtr<2, T> & zero();

		/**
		 * Add other vector to this vector.
		 * @param other other vector.
		 * @return reference to current vector.
		 */
		VectorPtr<2, T> & add(const const_VectorPtr<2, T> & other);

		/**
		 * Add vector (x,y) to this vector. Provided for convenience.
		 * @param x x coordinate of other vector.
		 * @param y y coordinate of other vector.
		 * @return reference to current vector.
		 */
		VectorPtr<2, T> & add(T x, T y);

		/**
		 * Subtract other vector from this vector.
		 * @param other other vector.
		 * @return reference to current vector.
		 */
		VectorPtr<2, T> & sub(const const_VectorPtr<2, T> & other);

		/**
		 * Subtract vector (x,y) from this vector. Provided for convenience.
		 * @param x x coordinate of other vector.
		 * @param y y coordinate of other vector.
		 * @return reference to current vector.
		 */
		VectorPtr<2, T> & sub(T x, T y);

		/**
		 * Divide all vector coordinates by scalar.
		 * @param scalar scalar.
		 * @return reference to current vector.
		 */
		VectorPtr<2, T> & div(T scalar);

		/**
		 * Multiply all vector coordinates by scalar.
		 * @param scalar scalar.
		 * @return reference to current vector.
		 */
		VectorPtr<2, T> & mult(T scalar);

		/**
		 * Multiply vector by 2x2 matrix. Vector is considered to lie horizontally (bra vector).
		 * @param matrix transformation matrix.
		 * @return transformed vector.
		 */
		VectorPtr<2, T> & mult(const Matrix<2,2> & matrix);

		/**
		 * Multiply vector by 4x4 matrix. This irregular function is provided for convenience
		 * to work with 4D homogeneous coordinates. Vector (x, y) is mapped to (x, y, 0.0, 1.0).
		 * @param matrix transformation matrix.
		 * @return transformed vector.
		 */
		VectorPtr<2, T> & mult(const Matrix<4,4> & matrix);

		//inner product (like dot but result is vector<1>) ?
//		Vector<1> inn(const VectorPtr<2, T> & other) const;

		/**
		 * Normalize this vector.
		 *
		 * @see versor().
		 */
		VectorPtr<2, T> & normalize();

		/**
		 * Invert this vector.
		 *
		 * @see inverse().
		 */
		VectorPtr<2, T> & invert();

		/**
		 * Rotate by given values of sinus and cosinus.
		 * @param sin sinus.
		 * @param cos cosinus.
		 */
		VectorPtr<2, T> & rotate(T sin, T cos);

		/**
		 * Rotate vector counterclockwise. Rotation will be performed around (0, 0) point.
		 * @param angle rotation angle in radians.
		 */
		VectorPtr<2, T> & rotate(T angle);

		/**
		 * Rotate vector around specified point.
		 * @param angle rotation angle in radians.
		 * @param point point coordinates around which rotation will be performed.
		 */
		VectorPtr<2, T> & rotate(T angle, const const_VectorPtr<2, T> & point);

		/**
		 * Minimize this vector against other vector. Reduces vector coordinates'
		 * exponents to smallest possible values, that added to @a other vector affect
		 * both (if initial coordinates are non-zero) of its coordinates.
		 * @param other vector for which minimized vector has to be prepared.
		 * @return reference to minimized parallel vector.
		 */
		VectorPtr<2, T> & minimize(const const_VectorPtr<2, T> & other);
};


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
