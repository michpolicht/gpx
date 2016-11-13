/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_CONST_VECTORTRAIT_HPP_
#define GPX_X_MATH_CONST_VECTORTRAIT_HPP_

#include "structures.hpp"

#include GPX_X_MATH_BACKEND_HEADER
#include GPX_X_MATH_BACKEND_CONST_VECTORTRAIT_HEADER

namespace gpx {
namespace math {

/**
 * Const methods for N-dimensional DERIVED vector of type T.
 *
 * @internal There is no =(T val) and ==(T val)/!=(T val) operators, because interpretation
 * is not obvious. Those operators could be interpreted either by short for setting/comparing
 * all coordinates at once or setting/comparing length of the vector.
 */
template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
class const_VectorTrait : private GPX_X_MATH_BACKEND_NAMESPACE::const_VectorTrait<DERIVED, N, T, true>
{
	typedef GPX_X_MATH_BACKEND_NAMESPACE::const_VectorTrait<DERIVED, N, T, true> Impl;
	friend class GPX_X_MATH_BACKEND_NAMESPACE::const_VectorTrait<DERIVED, N, T, true>;
	friend class GPX_X_MATH_BACKEND_NAMESPACE::const_VectorTrait<DERIVED, N, T, false>;
	friend class const_VectorTrait<DERIVED, 2, T, true>;

	public:
		/**
		 * Equality operator.
		 * @param other other vector.
		 * @return @p true if all coordinates of this vector are equal to the corresponding
		 * coordinates of other vector, @p false otherwise.
		 */
		bool operator ==(const_VectorRef<N, T> other) const;

		/**
		 * Inequality operator.
		 * @param other other vector.
		 * @return @p true if at least one of the coordinates is not unequal to the
		 * corresponding coordinate of the other vector, @p false otherwise.
		 */
		bool operator !=(const_VectorRef<N, T> other) const;

		/**
		 * Almost equal.
		 * @return @p true if all coordinates are almost equal to coordinates
		 * of other vector, @p false otherwise.
		 *
		 * @note ale() is stronger than ape().
		 */
		bool ale(const_VectorRef<N, T> other) const;

		/**
		 * Approximately equal.
		 * @return @p true if all coordinates are approximately equal to coordinates
		 * of other vector, @p false otherwise.
		 *
		 * @note ale() is stronger than ape().
		 */
		bool ape(const_VectorRef<N, T> other) const;

		/**
		 * Check if all coordinates are equal zero.
		 * @return @p true if all coordinates are equal zero, @p false otherwise.
		 */
		bool isZero() const;

		/**
		 * Check if all coordinates are almost equal zero.
		 * @return @p true if all coordinates are almost equal zero, @p false otherwise.
		 *
		 * @warning basic implementation of this function will almost certainly return same
		 * results as isZero(). This may differ only for huge gpx::EPS constant values.
		 * Implementation relies on gpx::math::ale() function, which is critically sensitive
		 * when comparing values to zero. It's probably better to use apeZero().
		 */
		bool aleZero() const;

		/**
		 * Check if all coordinates are approximately equal zero.
		 * @return @p true if all coordinates are approximately equal zero, @p false otherwise.
		 */
		bool apeZero() const;

		/**
		 * Obtain inverse vector.
		 * @return inverted vector.
		 *
		 * @see invert(), orthoCW(), orthoCCW().
		 */
		Vector<N, T> inverse() const;

		/**
		 * Unary minus. Alias of inverse().
		 * @return inverted vector.
		 */
		Vector<N, T> operator -() const;

		/**
		 * Sum.
		 * @param other vector to be added.
		 * @return sum of this vector and the other.
		 */
		Vector<N, T> sum(const_VectorRef<N, T> other) const;

		/**
		 * Sum. Alias of sum().
		 * @param other vector to be added.
		 * @return sum of this vector and the other.
		 */
		Vector<N, T> operator +(const_VectorRef<N, T> other) const;

		/**
		 * Difference.
		 * @param other vector to be subtracted.
		 * @return difference of this vector and the other.
		 */
		Vector<N, T> diff(const_VectorRef<N, T> other) const;

		/**
		 * Difference. Alias of diff().
		 * @param other vector to be subtracted.
		 * @return difference of this vector and the other.
		 */
		Vector<N, T> operator -(const_VectorRef<N, T> other) const;

		/**
		 * Product.
		 * @param scalar multiplier.
		 * @return product of this vector multiplied by scalar.
		 */
		Vector<N, T> prod(T scalar) const;

		/**
		 * Product. Alias of prod().
		 * @param scalar multiplier.
		 * @return product of this vector multiplied by scalar.
		 */
		Vector<N, T> operator *(T scalar) const;

		/**
		 * Matrix product.
		 * @param matrix multiplier.
		 * @return product of this vector multiplied by matrix.
		 */
		Vector<N, T> prod(const_MatrixRef<N, N, T> matrix) const;

		/**
		 * Matrix product. Aliast of prod().
		 * @param matrix multiplier.
		 * @return product of this vector multiplied by matrix.
		 */
		Vector<N, T> operator *(const_MatrixRef<N, N, T> matrix) const;

		/**
		 * Quotient.
		 * @param scalar divisor.
		 * @return quotient of this vector divided by scalar.
		 */
		Vector<N, T> quot(T scalar) const;

		/**
		 * Quotient. Alias of quot().
		 * @param scalar divisor.
		 * @return quotient of this vector divided by scalar.
		 */
		Vector<N, T> operator /(T scalar) const;

		/**
		 * Dot (or scalar) product of this vector and the other.
		 * @param other other vector.
		 * @return dot product of this and other vector.
		 */
		T dot(const_VectorRef<N, T> other) const;

		/**
		 * Dot product of this vector by itself.
		 * @return dot product of vector by itself. For some vector "v", "v.dot()" is
		 * equivalent of calling "v.dot(v)".
		 */
		T dot() const;

		/**
		 * Get vector length.
		 * @return length of vector.
		 */
		T length() const;

		/**
		 * Get versor of this vector.
		 * @return normalized vector (versor).
		 *
		 * @warning vector must have at least one non-zero coordinate. Otherwise results
		 * are undefined.
		 */
		Vector<N, T> versor() const;

		/**
		 * Get determinant of this vector and other on a specific base-plane. Base-plane is
		 * determined by selection of two coordinates from a system of coordinates.
		 * @param other other vector.
		 * @param c1 first coordinate defining a plane.
		 * @param c2 second coordinate defining a plane.
		 * @return determinant of this and other vector or 0 in case of c1 = c2.
		 *
		 * @note for 1-dimensional vector this function will always return 0, since
		 * there is no plane in 1-dimensional space and c1 = c2.
		 */
		T det(const_VectorRef<N, T> other, std::size_t c1, std::size_t c2) const;

		/**
		 * Get cross product of this vector and others. Resulting vector is orthogonal
		 * to given arguments.
		 * @param others array of N-2 vectors (0 elements for two- and one-dimensional vectors).
		 * @return cross product.
		 *
		 * @note resulting vector can also be a zero vector. This is always a case
		 * for 1-dimensional vector.
		 *
		 * @note resulting vector of cross product is often recognized as pseudo-vector,
		 * axial vector or tensor. Here, result is a standard vector, thus all
		 * transformations are delegated to the nature of operation.
		 */
		Vector<N, T> cross(const_VectorRef<N, T> * others) const;

		/**
		 * Get counter-cross product of this vector and others. Resulting vector is
		 * perpendicular to given arguments. Counter-cross product is opposite in direction
		 * to cross product. It is also orthogonal to given arguments.
		 * @param others array of N-2 vectors (0 elements for two- and one-dimensional vectors).
		 * @return counter-cross product.
		 *
		 * @note resulting vector can also be a zero vector. This is always a case
		 * for 1-dimensional vector.
		 */
		Vector<N, T> ccross(const_VectorRef<N, T> * others) const;

		/**
		 * Get minimal parallel vector against @a other vector.
		 * @param other vector for which minimal vector has to be prepared.
		 * @return parallel vector with exponents of coordinates reduced to smallest
		 * possible values, so that if vector is added to @a other vector it still
		 * affects other vector coordinates (if minimized coordinate is non-zero).
		 */
		Vector<N, T> minimal(const_VectorRef<N, T> other) const;

		/**
		 * Obtain vector rotated by given values of sine and cosine on a specific base-plane.
		 * @param sin sine.
		 * @param cos cosine.
		 * @param c1 first coordinate that describes base-plane.
		 * @param c2 second coordinate that describes base-plane.
		 * @return self-reference to rotated object.
		 */
		Vector<N, T> rotated(T sin, T cos, std::size_t c1, std::size_t c2) const;

		/**
		 * Obtain vector rotated by given angle on a specific base-plane.
		 * @param angle rotation angle in radians. Angle is oriented according to
		 * right angle formed on base-plane between coordinates @a c1, @a c2.
		 * @param c1 first coordinate that describes base-plane.
		 * @param c2 second coordinate that describes base-plane.
		 * @return self-reference to rotated object.
		 */
		Vector<N, T> rotated(T angle, std::size_t c1, std::size_t c2) const;
};

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_VectorTrait<DERIVED, N, T, DIMSPEC>::operator ==(const_VectorRef<N, T> other) const
{
	return Impl::operator ==(other);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_VectorTrait<DERIVED, N, T, DIMSPEC>::operator !=(const_VectorRef<N, T> other) const
{
	return Impl::operator !=(other);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_VectorTrait<DERIVED, N, T, DIMSPEC>::ale(const_VectorRef<N, T> other) const
{
	return Impl::ale(other);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_VectorTrait<DERIVED, N, T, DIMSPEC>::ape(const_VectorRef<N, T> other) const
{
	return Impl::ape(other);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_VectorTrait<DERIVED, N, T, DIMSPEC>::isZero() const
{
	return Impl::isZero();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_VectorTrait<DERIVED, N, T, DIMSPEC>::aleZero() const
{
	return Impl::aleZero();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_VectorTrait<DERIVED, N, T, DIMSPEC>::apeZero() const
{
	return Impl::apeZero();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::inverse() const
{
	return Impl::inverse();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::operator -() const
{
	return Impl::inverse();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::sum(const_VectorRef<N, T> other) const
{
	return Impl::sum(other);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::operator +(const_VectorRef<N, T> other) const
{
	return Impl::sum(other);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::diff(const_VectorRef<N, T> other) const
{
	return Impl::diff(other);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::operator -(const_VectorRef<N, T> other) const
{
	return Impl::diff(other);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::prod(T scalar) const
{
	return Impl::prod(scalar);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::operator *(T scalar) const
{
	return Impl::prod(scalar);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::prod(const_MatrixRef<N, N, T> matrix) const
{
	GPX_ASSERT(matrix.rows() == Impl::derived().size(), "number of rows in matrix must be equal to vector size");
	GPX_ASSERT(matrix.cols() == Impl::derived().size(), "number of columns in matrix must be equal to vector size");
	return Impl::prod(matrix);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::operator *(const_MatrixRef<N, N, T> matrix) const
{
	return prod(matrix);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::quot(T scalar) const
{
	return Impl::quot(scalar);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::operator /(T scalar) const
{
	return Impl::quot(scalar);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
T const_VectorTrait<DERIVED, N, T, DIMSPEC>::dot(const_VectorRef<N, T> other) const
{
	return Impl::dot(other);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
T const_VectorTrait<DERIVED, N, T, DIMSPEC>::dot() const
{
	return Impl::dot();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
T const_VectorTrait<DERIVED, N, T, DIMSPEC>::length() const
{
	return Impl::length();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::versor() const
{
	return Impl::versor();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
T const_VectorTrait<DERIVED, N, T, DIMSPEC>::det(const_VectorRef<N, T> other, std::size_t c1, std::size_t c2) const
{
	GPX_ASSERT(c1 < Impl::derived().size(), "det(other, c1, c2) invalid coordinate c1: " << c1);
	GPX_ASSERT(c2 < Impl::derived().size(), "det(other, c1, c2) invalid coordinate c2: " << c2);
	return Impl::det(other, c1, c2);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::cross(const_VectorRef<N, T> * others) const
{
	return Impl::cross(others);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::ccross(const_VectorRef<N, T> * others) const
{
	return Impl::ccross(others);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::minimal(const_VectorRef<N, T> other) const
{
	return Impl::minimal(other);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::rotated(T sin, T cos, std::size_t c1, std::size_t c2) const
{
	return Impl::rotated(sin, cos, c1, c2);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::rotated(T angle, std::size_t c1, std::size_t c2) const
{
	return Impl::rotated(angle, c1, c2);
}

//template <std::size_t N, typename T>
//class const_VectorPtr<N, T, true> : public const_VectorPtr<N, T, false>
//{
//	typedef const_VectorPtr<N, T, false> Parent;

//	public:
//		//generated copy ctor OK

//		/**
//		 * Conversion constructor.
//		 * @param coords pointer to N-element array of coordinates. Since no allocation
//		 * is done, this array must exist and be accessible during object lifetime.
//		 */
//		const_VectorPtr(const T * coords);

//	private:
//		/**
//		 * Copy assignment. Explicitly forbidden; modeling const pointer, thus can not copy
//		 * from other object.
//		 */
//		const const_VectorRef<N, T> & operator =(const const_VectorRef<N, T> & other);
//};

///**
// * Dynamically sized vector on top of const pointer.
// *
// * @note there is main difference between dynamic and fixed size const_VectorPtr.
// * Coordinates pointer of fixed size const_VectorPtr is guaranteed to point to the same
// * location during whole object lifetime. Dynamic const_VectorPtr provides setPtr()
// * methods, which allow pointer to be modified during runtime.
// *
// */
//template <typename T>
//class const_VectorPtr<SIZE_DYNAMIC, T, true> : public const_VectorPtr<SIZE_DYNAMIC, T, false>
//{
//	typedef const_VectorPtr<SIZE_DYNAMIC, T, false> Parent;

//	public:
//		//generated copy ctor OK

//		/**
//		 * Conversion constructor.
//		 * @param coords pointer to N-element array of coordinates. Since no allocation
//		 * is done, this array must exist and be accessible during object lifetime.
//		 * @param size vector size in terms of number of coordinates.
//		 */
//		const_VectorPtr(const T * coords, std::size_t size = 0);

//		//generated copy ctor OK
//		//const_VectorPtr(const const_VectorPtr<SIZE_DYNAMIC, T> & other);

//		/**
//		 * Conversion constructor.
//		 * @param other other vector. Coordinates pointer will point to the same array as
//		 * in other. Since no allocation is done, this array must be accessible during
//		 * object lifetime.
//		 */
//		template <std::size_t ON>
//		const_VectorPtr(const const_VectorPtr<ON, T> & other);

//	public:
//		using Impl::prod;

//		/**
//		 * Matrix product.
//		 * @param matrix multiplier.
//		 * @return product of this vector multiplied by matrix.
//		 */
//		template <std::size_t ON>
//		Vector<SIZE_DYNAMIC, T> prod(const Matrix<ON, ON, T> & matrix) const;

//		using Impl::operator *;

//		/**
//		 * Matrix product. Aliast of prod().
//		 * @param matrix multiplier.
//		 * @return product of this vector multiplied by matrix.
//		 */
//		template <std::size_t ON>
//		Vector<SIZE_DYNAMIC, T> operator *(const Matrix<ON, ON, T> & matrix) const;

//		/**
//		 * Set coordinates pointer.
//		 * @param ptr pointer to array of coordinates.
//		 */
//		void setPtr(const T * ptr);

//		/**
//		 * Set coordinates pointer and size.
//		 * @param ptr pointer to array of coordinates.
//		 * @param size vector size in terms of number of elements.
//		 */
//		void setPtr(const T * ptr, std::size_t size);

//	private:
//		/**
//		 * Copy assignment. Explicitly forbidden; modeling const pointer, thus can not copy
//		 * from other object.
//		 */
//		const const_VectorPtr<SIZE_DYNAMIC, T> & operator =(const const_VectorPtr<SIZE_DYNAMIC, T> & other);
//};

/**
 * Const methods for two-dimensional DERIVED vector of type T.
 */
template <template <std::size_t, typename> class DERIVED, typename T>
class const_VectorTrait<DERIVED, 2, T, true> : public const_VectorTrait<DERIVED, 2, T, false>
{
	typedef const_VectorTrait<DERIVED, 2, T, false> Parent;
	typedef GPX_X_MATH_BACKEND_NAMESPACE::const_VectorTrait<DERIVED, 2, T, true> Impl;

	public:
		using Parent::cross;

		/**
		 * Get cross product of this vector. Resulting vector is orthogonal to this vector.
		 * @return cross product.
		 *
		 * @note for zero vector, resulting vector is also a zero vector.
		 */
		Vector<2, T> cross() const;

		/**
		 * Get perpendicular vector to this vector, turning clockwise. Alias of cross().
		 * @return vector perpendicular to this vector, turning clockwise.
		 *
		 * @note for zero vector, resulting vector is also a zero vector.
		 */
		Vector<2, T> orthoCW() const;

		using Parent::ccross;

		/**
		 * Get counter-cross product of this vector. Resulting vector is orthogonal to
		 * this vector.
		 * @return counter-cross product.
		 *
		 * @note for zero vector, resulting vector is also a zero vector.
		 */
		Vector<2, T> ccross() const;

		/**
		 * Get perpendicular vector to this vector, turning counter-clockwise. Alias of ccross().
		 * @return vector perpendicular to this vector, turning counter-clockwise.
		 *
		 * @note for zero vector, resulting vector is also a zero vector.
		 */
		Vector<2, T> orthoCCW() const;

		using Parent::det;

		/**
		 * Get determinant of this vector and other.
		 * @param other other vector.
		 * @return determinant of this and other vector.
		 */
		T det(const_VectorRef<2, T> other) const;

		using Parent::rotated;

		/**
		 * Obtain vector rotated by given values of sine and cosine.
		 * @param sin sine. Angle is oriented counterclockwise according to OpenGL
		 * coordinates layout.
		 * @param cos cosine. Angle is oriented counterclockwise according to OpenGL
		 * coordinates layout.
		 * @return rotated vector.
		 */
		Vector<2, T> rotated(T sin, T cos) const;

		/**
		 * Obtain vector rotated by given angle.
		 * @param angle rotation angle in radians. Angle is oriented counterclockwise
		 * according to OpenGL coordinates layout.
		 * @return rotated vector.
		 */
		Vector<2, T> rotated(T angle) const;
};

template <template <std::size_t, typename> class DERIVED, typename T>
Vector<2, T> const_VectorTrait<DERIVED, 2, T, true>::cross() const
{
	return Impl::cross();
}

template <template <std::size_t, typename> class DERIVED, typename T>
Vector<2, T> const_VectorTrait<DERIVED, 2, T, true>::orthoCW() const
{
	return Impl::cross();
}

template <template <std::size_t, typename> class DERIVED, typename T>
Vector<2, T> const_VectorTrait<DERIVED, 2, T, true>::ccross() const
{
	return Impl::ccross();
}

template <template <std::size_t, typename> class DERIVED, typename T>
Vector<2, T> const_VectorTrait<DERIVED, 2, T, true>::orthoCCW() const
{
	return Impl::ccross();
}

template <template <std::size_t, typename> class DERIVED, typename T>
T const_VectorTrait<DERIVED, 2, T, true>::det(const_VectorRef<2, T> other) const
{
	return Impl::det(other);
}

template <template <std::size_t, typename> class DERIVED, typename T>
Vector<2, T> const_VectorTrait<DERIVED, 2, T, true>::rotated(T sin, T cos) const
{
	return Impl::rotated(sin, cos);
}

template <template <std::size_t, typename> class DERIVED, typename T>
Vector<2, T> const_VectorTrait<DERIVED, 2, T, true>::rotated(T angle) const
{
	return Impl::rotated(angle);
}

///**
// * Three-dimensional vector on top of const pointer.
// */
//template <typename T>
//class const_VectorPtr<3, T, true> : public const_VectorPtr<3, T, false>
//{
//	typedef const_VectorPtr<3, T, false> Parent;

//	public:
//		//generated copy ctor OK

//		/**
//		 * Conversion constructor.
//		 * @param coords pointer to 3-element array of coordinates. Since no allocation
//		 * is done, this array must exist and be accessible during object lifetime.
//		 */
//		const_VectorPtr(const T * coords);

//	public:
//		using Impl::cross;

//		/**
//		 * Get cross product of this vector and other. Resulting vector is orthogonal
//		 * to this vector and other.
//		 * @param other other vector.
//		 * @return cross product.
//		 *
//		 * @note resulting vector can also be a zero vector.
//		 */
//		Vector<3, T> cross(const const_VectorPtr<3, T> & other) const;

//		using Impl::ccross;

//		/**
//		 * Get counter-cross product of this vector and other. Resulting vector is orthogonal
//		 * to this vector and other.
//		 * @param other other vector.
//		 * @return counter-cross product.
//		 *
//		 * @note resulting vector can also be a zero vector.
//		 */
//		Vector<3, T> ccross(const const_VectorPtr<3, T> & other) const;

//		using Impl::sum;

//		/**
//		 * Sum.
//		 * @param x x coordinate of vector to be added.
//		 * @param y y coordinate of vector to be added.
//		 * @param z z coordinate of vector to be added.
//		 * @return sum of this vector and (x, y, z).
//		 */
//		Vector<3, T> sum(T x, T y, T z) const;

//		using Impl::diff;

//		/**
//		 * Difference.
//		 * @param x x coordinate of vector to be subtracted.
//		 * @param y y coordinate of vector to be subtracted.
//		 * @param z z coordinate of vector to be subtracted.
//		 * @return sum of this vector and (x, y, z).
//		 */
//		Vector<3, T> diff(T x, T y, T z) const;

//		using Impl::prod;

//		/**
//		 * 4 x 4 matrix product. This irregular function is provided for convenience to
//		 * work with 4D homogeneous coordinates. Vector (x, y, z) is mapped to
//		 * (x, y, z, 1.0).
//		 * @param matrix matrix multiplier.
//		 * @return product of this vector multiplied by matrix.
//		 */
//		Vector<3, T> prod(const Matrix<4, 4, T> & matrix) const;

//		using Impl::operator *;

//		/**
//		 * 4 x 4 matrix product. Alias of prod().
//		 * @param matrix matrix multiplier.
//		 * @return product of this vector multiplied by matrix.
//		 */
//		Vector<3, T> operator *(const Matrix<4, 4, T> & matrix) const;

//		using Impl::rotated;

//		/**
//		 * Obtain vector rotated by given values of sine and cosine around specific axis.
//		 * @param sin sine.
//		 * @param cos cosine.
//		 * @param axis axis of rotation. Angle is oriented according to right hand rule
//		 * in OpenGL coordinates layout.
//		 * @return self-reference to rotated object.
//		 */
//		Vector<3, T> rotated(T sin, T cos, std::size_t axis) const;

//		/**
//		 * Obtain vector rotated by given angle around specific axis.
//		 * @param angle rotation angle in radians. Angle is oriented according to right
//		 * hand rule in OpenGL coordinates layout.
//		 * @param c1 first coordinate that describes base-plane.
//		 * @param c2 second coordinate that describes base-plane.
//		 * @return self-reference to rotated object.
//		 */
//		Vector<3, T> rotated(T angle, std::size_t axis) const;

//	private:
//		/**
//		 * Copy assignment. Explicitly forbidden; modeling const pointer, thus can not copy
//		 * from other object.
//		 */
//		const const_VectorPtr<3, T> & operator =(const const_VectorPtr<3, T> & other);
//};


////DIMSPEC = true

//template <std::size_t N, typename T>
//inline
//const_VectorPtr<N, T, true>::const_VectorPtr(const T * coords):
//	Parent(coords)
//{
//};

////DIMSPEC = true, N = SIZE_DYNAMIC

//template <typename T>
//inline
//const_VectorPtr<SIZE_DYNAMIC, T, true>::const_VectorPtr(const T * coords, std::size_t size):
//	Parent(coords, size)
//{
//};

//template <typename T>
//template <std::size_t ON>
//inline
//const_VectorPtr<SIZE_DYNAMIC, T, true>::const_VectorPtr(const const_VectorPtr<ON, T> & other):
//	Parent(other.ptr(), other.size())
//{
//}

//template <typename T>
//template <std::size_t ON>
//inline
//Vector<SIZE_DYNAMIC, T> const_VectorPtr<SIZE_DYNAMIC, T, true>::prod(const Matrix<ON, ON, T> & matrix) const
//{
//	GPX_ASSERT(matrix.rows() == Impl::size(), "number of rows in matrix must be equal to vector size");
//	GPX_ASSERT(matrix.cols() == Impl::size(), "number of columns in matrix must be equal to vector size");
//	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<SIZE_DYNAMIC, T>::prod(matrix);
//}

//template <typename T>
//template <std::size_t ON>
//inline
//Vector<SIZE_DYNAMIC, T> const_VectorPtr<SIZE_DYNAMIC, T, true>::operator *(const Matrix<ON, ON, T> & matrix) const
//{
//	return prod(matrix);
//}

//template <typename T>
//inline
//void const_VectorPtr<SIZE_DYNAMIC, T, true>::setPtr(const T * ptr)
//{
//	Impl::setPtr(ptr);
//}

//template <typename T>
//inline
//void const_VectorPtr<SIZE_DYNAMIC, T, true>::setPtr(const T * ptr, std::size_t size)
//{
//	Impl::setPtr(ptr, size);
//}

////DIMSPEC = true, N = 3

//template <typename T>
//inline
//const_VectorPtr<3, T, true>::const_VectorPtr(const T * coords):
//	Parent(coords)
//{
//}

//template <typename T>
//inline
//Vector<3, T> const_VectorPtr<3, T, true>::cross(const const_VectorPtr<3, T> & other) const
//{
//	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<3, T>::cross(other);
//}

//template <typename T>
//inline
//Vector<3, T> const_VectorPtr<3, T, true>::ccross(const const_VectorPtr<3, T> & other) const
//{
//	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<3, T>::ccross(other);
//}

//template <typename T>
//inline
//Vector<3, T> const_VectorPtr<3, T, true>::sum(T x, T y, T z) const
//{
//	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<3, T>::sum(x, y, z);
//}

//template <typename T>
//inline
//Vector<3, T> const_VectorPtr<3, T, true>::diff(T x, T y, T z) const
//{
//	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<3, T>::diff(x, y, z);
//}

//template <typename T>
//inline
//Vector<3, T> const_VectorPtr<3, T, true>::prod(const Matrix<4, 4, T> & matrix) const
//{
//	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<3, T>::prod(matrix);
//}

//template <typename T>
//inline
//Vector<3, T> const_VectorPtr<3, T, true>::operator *(const Matrix<4, 4, T> & matrix) const
//{
//	return prod(matrix);
//}

//template <typename T>
//inline
//Vector<3, T> const_VectorPtr<3, T, true>::rotated(T sin, T cos, std::size_t axis) const
//{
//	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<3, T>::rotated(sin, cos, axis);
//}

//template <typename T>
//inline
//Vector<3, T> const_VectorPtr<3, T, true>::rotated(T angle, std::size_t axis) const
//{
//	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<3, T>::rotated(angle, axis);
//}

}
}

#endif
