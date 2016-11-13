/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_VECTORTRAIT_HPP_
#define GPX_X_MATH_VECTORTRAIT_HPP_

#include "structures.hpp"

#include GPX_X_MATH_BACKEND_HEADER
#include GPX_X_MATH_BACKEND_VECTORTRAIT_HEADER

namespace gpx {
namespace math {

/**
 * Methods for N-dimensional DERIVED vector of type T.
 *
 * @internal There is no =(T val) and ==(T val)/!=(T val) operators, because interpretation
 * is not obvious. Those operators could be interpreted either by short for setting/comparing
 * all coordinates at once or setting/comparing length of the vector.
 */
template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
class VectorTrait : public const_VectorTrait<DERIVED, N, T, true>,
					private GPX_X_MATH_BACKEND_NAMESPACE::VectorTrait<DERIVED, N, T, true>
{
	typedef const_VectorTrait<DERIVED, N, T, true> Parent;
	typedef GPX_X_MATH_BACKEND_NAMESPACE::VectorTrait<DERIVED, N, T, true> Impl;
	friend class GPX_X_MATH_BACKEND_NAMESPACE::VectorTrait<DERIVED, N, T, true>;
	friend class GPX_X_MATH_BACKEND_NAMESPACE::VectorTrait<DERIVED, N, T, false>;
	friend class VectorTrait<DERIVED, 2, T, true>;

	public:
		/**
		 * Addition. Add other vector to this vector.
		 * @param other vector to be added.
		 * @return self-reference to this vector.
		 */
		DERIVED<N, T> & add(const_VectorRef<N, T> other);

		/**
		 * Addition assignment. Alias of add().
		 * @param other vector to be added.
		 * @return self-reference to an object being assigned.
		 */
		DERIVED<N, T> & operator +=(const_VectorRef<N, T> other);

		/**
		 * Subtraction. Subtract other vector from this vector.
		 * @param other vector to be subtracted.
		 * @return self-reference to this vector.
		 */
		DERIVED<N, T> & sub(const_VectorRef<N, T> other);

		/**
		 * Subtraction assignment. Alias of sub().
		 * @param other vector to be subtracted.
		 * @return self-reference to an object being subtracted.
		 */
		DERIVED<N, T> & operator -=(const_VectorRef<N, T> other);

		/**
		 * Multiplication by scalar. Multiply all vector coordinates by scalar.
		 * @param scalar multiplier.
		 * @return self-reference to an object being multiplied.
		 */
		DERIVED<N, T> & mul(T scalar);

		/**
		 * Multiplication assignment. Multiply all vector coordinates by scalar. Alias of mul().
		 * @param scalar multiplier.
		 * @return self-reference to an object being multiplied.
		 */
		DERIVED<N, T> & operator *=(T scalar);

		/**
		 * Multiplication by matrix. Vector is considered to lie horizontally (bra vector).
		 * @param matrix multiplier.
		 * @return self-reference to an object being multiplied.
		 */
		DERIVED<N, T> & mul(const_MatrixRef<N, N, T> matrix);

		/**
		 * Multiplication assignment. Vector is considered to lie horizontally (bra vector).
		 * Aliast of mul().
		 * @param matrix multiplier.
		 * @return self-reference to an object being multiplied.
		 */
		DERIVED<N, T> & operator *=(const_MatrixRef<N, N, T> matrix);

		/**
		 * Division. Divide all vector coordinates by scalar.
		 * @param scalar divisor.
		 * @return self-reference to an object being divided.
		 */
		DERIVED<N, T> & div(T scalar);

		/**
		 * Division assignment. Divide all vector coordinates by a scalar. Alias of div().
		 * @param scalar divisor.
		 * @return self-reference to an object being divided.
		 */
		DERIVED<N, T> & operator /=(T scalar);

		/**
		 * Zero vector coordinates.
		 * @return self-reference to zeroed object.
		 */
		DERIVED<N, T> & zero();

		/**
		 * Invert this vector.
		 * @return self-reference to inverted object.
		 *
		 * @see inverse().
		 */
		DERIVED<N, T> & invert();

		/**
		 * Normalize this vector.
		 * @return self-reference to normalized object.
		 *
		 * @see versor().
		 */
		DERIVED<N, T> & normalize();

		/**
		 * Rotate by given values of sine and cosine on a specific base-plane.
		 * @param sin sine.
		 * @param cos cosine.
		 * @param c1 first coordinate that describes base-plane.
		 * @param c2 second coordinate that describes base-plane.
		 * @return self-reference to rotated object.
		 */
		DERIVED<N, T> & rotate(T sin, T cos, std::size_t c1, std::size_t c2);

		/**
		 * Rotate vector by given angle on a specific base-plane.
		 * @param angle rotation angle in radians. Angle is oriented according to
		 * right angle formed on base-plane between coordinates @a c1, @a c2.
		 * @param c1 first coordinate that describes base-plane.
		 * @param c2 second coordinate that describes base-plane.
		 * @return self-reference to rotated object.
		 */
		DERIVED<N, T> & rotate(T angle, std::size_t c1, std::size_t c2);

		/**
		 * Minimize this vector against @a other vector.
		 * @param other vector for which minimal vector has to be prepared.
		 * @return parallel vector with exponents of coordinates reduced to smallest
		 * possible values, so that if vector is added to @a other vector it still
		 * affects other vector coordinates (if minimized coordinate is non-zero).
		 * @return self-reference to minimized object.
		 */
		DERIVED<N, T> & minimize(const_VectorRef<N, T> other);

		/**
		 * Swap elements.
		 * @param c1 coordinate of element to be swapped with @a c2;
		 * @param c2 coordinate of element to be swapped with @a c1;
		 */
		void swap(std::size_t c1, std::size_t c2);
};

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::add(const_VectorRef<N, T> other)
{
	Impl::add(other);
	return Impl::derived();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::operator +=(const_VectorRef<N, T> other)
{
	Impl::add(other);
	return Impl::derived();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::sub(const_VectorRef<N, T> other)
{
	Impl::sub(other);
	return Impl::derived();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::operator -=(const_VectorRef<N, T> other)
{
	Impl::sub(other);
	return Impl::derived();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::mul(T scalar)
{
	Impl::mul(scalar);
	return Impl::derived();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::operator *=(T scalar)
{
	Impl::mul(scalar);
	return Impl::derived();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::mul(const_MatrixRef<N, N, T> matrix)
{
	GPX_ASSERT(matrix.rows() == Impl::derived().size(), "number of rows in matrix must be equal to vector size");
	GPX_ASSERT(matrix.cols() == Impl::derived().size(), "number of columns in matrix must be equal to vector size");
	Impl::mul(matrix);
	return Impl::derived();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::operator *=(const_MatrixRef<N, N, T> matrix)
{
	return mul(matrix);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::div(T scalar)
{
	Impl::div(scalar);
	return Impl::derived();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::operator /=(T scalar)
{
	Impl::div(scalar);
	return Impl::derived();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::zero()
{
	Impl::zero();
	return Impl::derived();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::invert()
{
	Impl::invert();
	return Impl::derived();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::normalize()
{
	Impl::normalize();
	return Impl::derived();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::rotate(T sin, T cos, std::size_t c1, std::size_t c2)
{
	Impl::rotate(sin, cos, c1, c2);
	return Impl::derived();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::rotate(T angle, std::size_t c1, std::size_t c2)
{
	Impl::rotate(angle, c1, c2);
	return Impl::derived();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::minimize(const_VectorRef<N, T> other)
{
	Impl::minimize(other);
	return Impl::derived();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
void VectorTrait<DERIVED, N, T, DIMSPEC>::swap(std::size_t c1, std::size_t c2)
{
	Impl::swap(c1, c2);
}

/**
 * Methods for two-dimensional DERIVED vector of type T.
 */
template <template <std::size_t, typename> class DERIVED, typename T>
class VectorTrait<DERIVED, 2, T, true> : public VectorTrait<DERIVED, 2, T, false>
{
	typedef VectorTrait<DERIVED, 2, T, false> Parent;
	typedef GPX_X_MATH_BACKEND_NAMESPACE::VectorTrait<DERIVED, 2, T, true> Impl;

	public:
		///////////////////////////////////////////////////////////////////////
		//
		//        ^ y          OpenGL coordinates layout (without z-axis)
		//        |
		//        |
		//        .------> x
		//

		using Parent::rotate;

		/**
		 * Rotate by given values of sine and cosine.
		 * @param sin sine. Angle is oriented counterclockwise according to OpenGL
		 * coordinates layout.
		 * @param cos cosine. Angle is oriented counterclockwise according to OpenGL
		 * coordinates layout.
		 * @return self-reference to rotated object.
		 */
		DERIVED<2, T> & rotate(T sin, T cos);

		/**
		 * Rotate vector by given angle.
		 * @param angle rotation angle in radians. Angle is oriented counterclockwise
		 * according to OpenGL coordinates layout.
		 * @return self-reference to rotated object.
		 */
		DERIVED<2, T> & rotate(T angle);
};

template <template <std::size_t, typename> class DERIVED, typename T>
DERIVED<2, T> & VectorTrait<DERIVED, 2, T, true>::rotate(T sin, T cos)
{
	Impl::rotate(sin, cos);
	return Impl::derived();
}

template <template <std::size_t, typename> class DERIVED, typename T>
DERIVED<2, T> & VectorTrait<DERIVED, 2, T, true>::rotate(T angle)
{
	Impl::rotate(angle);
	return Impl::derived();
}

}
}

#endif
