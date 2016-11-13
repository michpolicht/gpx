/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_CONST_VECTORPTR_HPP_
#define GPX_X_MATH_CONST_VECTORPTR_HPP_

#include "../platform.hpp"
#include "functions.hpp"

//forward declare classes required by backend
namespace gpx { namespace math { template <std::size_t M = SIZE_DYNAMIC, std::size_t N = SIZE_DYNAMIC, typename T = real_t, bool DIMSPEC = true> class Matrix; }}
namespace gpx { namespace math { template <std::size_t N = SIZE_DYNAMIC, typename T = real_t, bool DIMSPEC = true> class const_VectorPtr; }}
namespace gpx { namespace math { template <std::size_t N = SIZE_DYNAMIC, typename T = real_t, bool DIMSPEC = true> class VectorPtr; }}
namespace gpx { namespace math { template <std::size_t N = SIZE_DYNAMIC, typename T = real_t> class Vector; }}

#include GPX_X_MATH_BACKEND_HEADER
#include GPX_X_MATH_BACKEND_CONST_VECTORPTR_HEADER
//#note: "VectorPtr.hpp" included near eof

namespace gpx {
namespace math {

//template <std::size_t N, typename T> class const_VectorPtr;

/**
 * N-dimensional vector on top of N-element const pointer.
 */
template <std::size_t N, typename T, bool DIMSPEC>
class const_VectorPtr : public GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<N, T>
{
	typedef GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<N, T> Parent;

	public:
		static int PrintPrecision;
		static const std::size_t SIZE = N;

	public:
		/**
		 * Set vector size.
		 * @param size new size in terms of number of coordinates.
		 *
		 * @note specified number of coordinates must be available. This function does
		 * not manage memory - it is external responsibility to assure that specified
		 * number of coordinates is available through modeled pointer.
		 *
		 * @warning in case of fixed size vectors, setting size different than size of
		 * vector is illegal.
		 */
		void setSize(std::size_t size);

		/**
		 * Get vector size.
		 * @return vector size in terms of number of coordinates.
		 */
		std::size_t size() const;

		/**
		 * Get const pointer pointing to coordinates.
		 * @return const pointer pointing to coordinates.
		 */
		const T * ptr() const;

		/**
		 * Conversion to size_t. Useful when implementing STL hash functions.
		 *
		 * @warning this operator may not give unique value. Hash value is calculated
		 * from coords pointer passed to the constructor and not from object itself. Two
		 * const_VectorPtr<N, T, DIMSPEC> objects will have same hash value if they refer to
		 * the same pointer.
		 */
//		operator std::size_t () const;

		/**
		 * Individual coordinate access over subscript operator.
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
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
		 * Get x coordinate. Alias of coord(0).
		 * @return value of x coordinate.
		 */
		T x() const;

		/**
		 * Get y coordinate. Alias of coord(1).
		 * @return value of y coordinate.
		 */
		T y() const;

		/**
		 * Get z coordinate. Alias of coord(2).
		 * @return value of z coordinate.
		 */
		T z() const;

		/**
		 * Get w coordinate. Alias of coord(3).
		 * @return value of w coordinate.
		 */
		T w() const;

		/**
		 * Equality operator.
		 * @param other other vector.
		 * @return @p true if all coordinates of this vector are equal to the corresponding
		 * coordinates of other vector, @p false otherwise.
		 */
		bool operator ==(const const_VectorPtr<N, T> & other) const;

		/**
		 * Scalar equality operator.
		 * @param val value.
		 * @return @p true if all vector coordinates are equal to specific value, @p false
		 * otherwise.
		 */
		bool operator ==(T val) const;

		/**
		 * Inequality operator.
		 * @param other other vector.
		 * @return @p true if at least one of the coordinates is not unequal to the
		 * corresponding coordinate of the other vector, @p false otherwise.
		 */
		bool operator !=(const const_VectorPtr<N, T> & other) const;

		/**
		 * Scalar inequality operator.
		 * @param val value.
		 * @return @p true if at least one vector coordinates is unequal to specific value,
		 * @p false otherwise.
		 */
		bool operator !=(T val) const;

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
		Vector<N, T> sum(const const_VectorPtr<N, T> & other) const;

		/**
		 * Sum. Alias of sum().
		 * @param other vector to be added.
		 * @return sum of this vector and the other.
		 */
		Vector<N, T> operator +(const const_VectorPtr<N, T> & other) const;

		/**
		 * Difference.
		 * @param other vector to be subtracted.
		 * @return difference of this vector and the other.
		 */
		Vector<N, T> diff(const const_VectorPtr<N, T> & other) const;

		/**
		 * Difference. Alias of diff().
		 * @param other vector to be subtracted.
		 * @return difference of this vector and the other.
		 */
		Vector<N, T> operator -(const const_VectorPtr<N, T> & other) const;

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
		Vector<N, T> prod(const Matrix<N, N, T> & matrix) const;

		/**
		 * Matrix product. Aliast of prod().
		 * @param matrix multiplier.
		 * @return product of this vector multiplied by matrix.
		 */
		Vector<N, T> operator *(const Matrix<N, N, T> & matrix) const;

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
		T dot(const const_VectorPtr<N, T> & other) const;

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
		T det(const const_VectorPtr<N, T> & other, std::size_t c1, std::size_t c2) const;

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
		Vector<N, T> cross(const const_VectorPtr<N, T> * others) const;

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
		Vector<N, T> ccross(const const_VectorPtr<N, T> * others) const;

		/**
		 * Approximately equal.
		 * @return @p true if all coordinates are approximately equal to coordinates
		 * of other vector, @p false otherwise.
		 *
		 * @note ale() is stronger than ape().
		 */
		bool ape(const const_VectorPtr<N, T> & other) const;

		/**
		 * Approximately equal to value.
		 * @return @p true if all coordinates are approximately equal to specified
		 * value, @p false otherwise.
		 *
		 * @note ale() is stronger than ape().
		 */
		bool ape(T val) const;

		/**
		 * Almost equal.
		 * @return @p true if all coordinates are almost equal to coordinates
		 * of other vector, @p false otherwise.
		 *
		 * @note ale() is stronger than ape().
		 */
		bool ale(const const_VectorPtr<N, T> & other) const;

		/**
		 * Almost equal to value.
		 * @return @p true if all coordinates are almost equal to specified
		 * value, @p false otherwise.
		 *
		 * @note ale() is stronger than ape().
		 */
		bool ale(T val) const;

		/**
		 * Get minimal parallel vector against @a other vector.
		 * @param other vector for which minimal vector has to be prepared.
		 * @return parallel vector with exponents of coordinates reduced to smallest
		 * possible values, so that if vector is added to @a other vector it still
		 * affects other vector coordinates (if minimized coordinate is non-zero).
		 */
		Vector<N, T> minimal(const const_VectorPtr<N, T> & other) const;

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

		/**
		 * Obtain vector rotated by given angle around given point on a specific base-plane.
		 * @param angle rotation angle in radians. Angle is oriented according to
		 * right angle formed on base-plane between coordinates @a c1, @a c2.
		 * @param c1 first coordinate that describes base-plane.
		 * @param c2 second coordinate that describes base-plane.
		 * @param point point on [@a c1, @a c2] base-plane, around which rotation should be
		 * performed.
		 * @return self-reference to rotated object.
		 */
		Vector<N, T> rotated(T angle, const const_VectorPtr<2, T> & point, std::size_t c1, std::size_t c2) const;

//todo remove
		bool isZero() const
		{
			GPX_ASSERT(false, "obsolete");
			GPX_FATAL("isZero() is obsolete, use operator == 0 instead");
		}


//		//inner product (like dot but result is vector<1>) ?
////		Vector<1> inn(const VectorPtr<2, T> & other) const;
//
//		/**
//		 * Get outer product of this vector and the other.
//		 * @param other other vector.
//		 * @return outer product matrix.
//		 */
//		Matrix<N, N, T> out(const const_VectorPtr<N, T> & other) const;
		//further possible specializations:
		//cross for N = 1, 4
		//ccross for N = 1, 4
		//det for N = 1

	protected:
		/**
		 * Copy constructor. Sets coordinates pointer as in another vector.
		 * @param other other object. Coordinates pointer will point to the same array as
		 * other. Since no allocation is done, this array must be accessible during object
		 * lifetime.
		 */
		const_VectorPtr(const const_VectorPtr<N, T, DIMSPEC> & other);

		const_VectorPtr(const T * coords);

		const_VectorPtr(const T * coords, std::size_t size);

	private:
		/**
		 * Default constructor. Explicitly forbidden; coordinates pointer must be set.
		 */
		const_VectorPtr();

	private:
		/**
		 * Copy assignment. Explicitly forbidden; modeling const pointer, thus can not copy
		 * from other object.
		 */
		const const_VectorPtr<N, T> & operator =(const const_VectorPtr<N, T, DIMSPEC> & other);
};

template <std::size_t N, typename T>
class const_VectorPtr<N, T, true> : public const_VectorPtr<N, T, false>
{
	typedef const_VectorPtr<N, T, false> Parent;

	public:
		//generated copy ctor OK

		/**
		 * Conversion constructor.
		 * @param coords pointer to N-element array of coordinates. Since no allocation
		 * is done, this array must exist and be accessible during object lifetime.
		 */
		const_VectorPtr(const T * coords);

	private:
		/**
		 * Copy assignment. Explicitly forbidden; modeling const pointer, thus can not copy
		 * from other object.
		 */
		const const_VectorPtr<N, T> & operator =(const const_VectorPtr<N, T> & other);
};

/**
 * Dynamically sized vector on top of const pointer.
 *
 * @note there is main difference between dynamic and fixed size const_VectorPtr.
 * Coordinates pointer of fixed size const_VectorPtr is guaranteed to point to the same
 * location during whole object lifetime. Dynamic const_VectorPtr provides setPtr()
 * methods, which allow pointer to be modified during runtime.
 *
 */
template <typename T>
class const_VectorPtr<SIZE_DYNAMIC, T, true> : public const_VectorPtr<SIZE_DYNAMIC, T, false>
{
	typedef const_VectorPtr<SIZE_DYNAMIC, T, false> Parent;

	public:
		//generated copy ctor OK

		/**
		 * Conversion constructor.
		 * @param coords pointer to N-element array of coordinates. Since no allocation
		 * is done, this array must exist and be accessible during object lifetime.
		 * @param size vector size in terms of number of coordinates.
		 */
		const_VectorPtr(const T * coords, std::size_t size = 0);

		//generated copy ctor OK
		//const_VectorPtr(const const_VectorPtr<SIZE_DYNAMIC, T> & other);

		/**
		 * Conversion constructor.
		 * @param other other vector. Coordinates pointer will point to the same array as
		 * in other. Since no allocation is done, this array must be accessible during
		 * object lifetime.
		 */
		template <std::size_t ON>
		const_VectorPtr(const const_VectorPtr<ON, T> & other);

	public:
		using Parent::prod;

		/**
		 * Matrix product.
		 * @param matrix multiplier.
		 * @return product of this vector multiplied by matrix.
		 */
		template <std::size_t ON>
		Vector<SIZE_DYNAMIC, T> prod(const Matrix<ON, ON, T> & matrix) const;

		using Parent::operator *;

		/**
		 * Matrix product. Aliast of prod().
		 * @param matrix multiplier.
		 * @return product of this vector multiplied by matrix.
		 */
		template <std::size_t ON>
		Vector<SIZE_DYNAMIC, T> operator *(const Matrix<ON, ON, T> & matrix) const;

		/**
		 * Set coordinates pointer.
		 * @param ptr pointer to array of coordinates.
		 */
		void setPtr(const T * ptr);

		/**
		 * Set coordinates pointer and size.
		 * @param ptr pointer to array of coordinates.
		 * @param size vector size in terms of number of elements.
		 */
		void setPtr(const T * ptr, std::size_t size);

	private:
		/**
		 * Copy assignment. Explicitly forbidden; modeling const pointer, thus can not copy
		 * from other object.
		 */
		const const_VectorPtr<SIZE_DYNAMIC, T> & operator =(const const_VectorPtr<SIZE_DYNAMIC, T> & other);
};

/**
 * Two-dimensional vector on top of const pointer.
 */
template <typename T>
class const_VectorPtr<2, T, true> : public const_VectorPtr<2, T, false>
{
	typedef const_VectorPtr<2, T, false> Parent;

	public:
		//generated copy ctor OK

		/**
		 * Conversion constructor.
		 * @param coords pointer to 2-element array of coordinates. Since no allocation
		 * is done, this array must exist and be accessible during object lifetime.
		 */
		const_VectorPtr(const T * coords);

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
		T det(const const_VectorPtr<2, T> & other) const;

		using Parent::sum;

		/**
		 * Sum.
		 * @param x x coordinate of vector to be added.
		 * @param y y coordinate of vector to be added.
		 * @return sum of this vector and (x, y).
		 */
		Vector<2, T> sum(T x, T y) const;

		using Parent::diff;

		/**
		 * Difference.
		 * @param x x coordinate of vector to be subtracted.
		 * @param y y coordinate of vector to be subtracted.
		 * @return sum of this vector and (x, y).
		 */
		Vector<2, T> diff(T x, T y) const;

		using Parent::prod;

		/**
		 * 4 x 4 matrix product. This irregular function is provided for convenience to
		 * work with 4D homogeneous coordinates. Vector (x, y) is mapped to
		 * (x, y, 0.0, 1.0).
		 * @param matrix matrix multiplier.
		 * @return product of this vector multiplied by matrix.
		 */
		Vector<2, T> prod(const Matrix<4, 4, T> & matrix) const;

		using Parent::operator *;

		/**
		 * 4 x 4 matrix product. Alias of prod().
		 * @param matrix matrix multiplier.
		 * @return product of this vector multiplied by matrix.
		 */
		Vector<2, T> operator *(const Matrix<4, 4, T> & matrix) const;

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

		/**
		 * Obtain vector rotated by given angle around specific point.
		 * @param angle rotation angle in radians. Angle is oriented counterclockwise
		 * according to OpenGL coordinates layout.
		 * @param point point, around which rotation should be performed.
		 * @return rotated vector.
		 */
		Vector<2, T> rotated(T angle, const const_VectorPtr<2, T> & point) const;

	private:
		/**
		 * Copy assignment. Explicitly forbidden; modeling const pointer, thus can not copy
		 * from other object.
		 */
		const const_VectorPtr<2, T> & operator =(const const_VectorPtr<2, T> & other);
};

/**
 * Three-dimensional vector on top of const pointer.
 */
template <typename T>
class const_VectorPtr<3, T, true> : public const_VectorPtr<3, T, false>
{
	typedef const_VectorPtr<3, T, false> Parent;

	public:
		//generated copy ctor OK

		/**
		 * Conversion constructor.
		 * @param coords pointer to 3-element array of coordinates. Since no allocation
		 * is done, this array must exist and be accessible during object lifetime.
		 */
		const_VectorPtr(const T * coords);

	public:
		using Parent::cross;

		/**
		 * Get cross product of this vector and other. Resulting vector is orthogonal
		 * to this vector and other.
		 * @param other other vector.
		 * @return cross product.
		 *
		 * @note resulting vector can also be a zero vector.
		 */
		Vector<3, T> cross(const const_VectorPtr<3, T> & other) const;

		using Parent::ccross;

		/**
		 * Get counter-cross product of this vector and other. Resulting vector is orthogonal
		 * to this vector and other.
		 * @param other other vector.
		 * @return counter-cross product.
		 *
		 * @note resulting vector can also be a zero vector.
		 */
		Vector<3, T> ccross(const const_VectorPtr<3, T> & other) const;

		using Parent::sum;

		/**
		 * Sum.
		 * @param x x coordinate of vector to be added.
		 * @param y y coordinate of vector to be added.
		 * @param z z coordinate of vector to be added.
		 * @return sum of this vector and (x, y, z).
		 */
		Vector<3, T> sum(T x, T y, T z) const;

		using Parent::diff;

		/**
		 * Difference.
		 * @param x x coordinate of vector to be subtracted.
		 * @param y y coordinate of vector to be subtracted.
		 * @param z z coordinate of vector to be subtracted.
		 * @return sum of this vector and (x, y, z).
		 */
		Vector<3, T> diff(T x, T y, T z) const;

		using Parent::prod;

		/**
		 * 4 x 4 matrix product. This irregular function is provided for convenience to
		 * work with 4D homogeneous coordinates. Vector (x, y, z) is mapped to
		 * (x, y, z, 1.0).
		 * @param matrix matrix multiplier.
		 * @return product of this vector multiplied by matrix.
		 */
		Vector<3, T> prod(const Matrix<4, 4, T> & matrix) const;

		using Parent::operator *;

		/**
		 * 4 x 4 matrix product. Alias of prod().
		 * @param matrix matrix multiplier.
		 * @return product of this vector multiplied by matrix.
		 */
		Vector<3, T> operator *(const Matrix<4, 4, T> & matrix) const;

		using Parent::rotated;

		/**
		 * Obtain vector rotated by given values of sine and cosine around specific axis.
		 * @param sin sine.
		 * @param cos cosine.
		 * @param axis axis of rotation. Angle is oriented according to right hand rule
		 * in OpenGL coordinates layout.
		 * @return self-reference to rotated object.
		 */
		Vector<3, T> rotated(T sin, T cos, std::size_t axis) const;

		/**
		 * Obtain vector rotated by given angle around specific axis.
		 * @param angle rotation angle in radians. Angle is oriented according to right
		 * hand rule in OpenGL coordinates layout.
		 * @param c1 first coordinate that describes base-plane.
		 * @param c2 second coordinate that describes base-plane.
		 * @return self-reference to rotated object.
		 */
		Vector<3, T> rotated(T angle, std::size_t axis) const;

	private:
		/**
		 * Copy assignment. Explicitly forbidden; modeling const pointer, thus can not copy
		 * from other object.
		 */
		const const_VectorPtr<3, T> & operator =(const const_VectorPtr<3, T> & other);
};

template <std::size_t N, typename T, bool DIMSPEC>
int const_VectorPtr<N, T, DIMSPEC>::PrintPrecision = std::numeric_limits<T>::digits10 + 2;

//template <std::size_t N, typename T, bool DIMSPEC>
//inline
//const_VectorPtr<N, T, DIMSPEC>::const_VectorPtr(const const_VectorPtr & other):
//	Parent(other)
//{
//}

//template <std::size_t N, typename T, bool DIMSPEC>
//inline
//const_VectorPtr<N, T, DIMSPEC>::operator const T * () const
//{
//	return Parent::operator const T * ();
//}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void const_VectorPtr<N, T, DIMSPEC>::setSize(std::size_t size)
{
	Parent::setSize(size);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
std::size_t const_VectorPtr<N, T, DIMSPEC>::size() const
{
	return Parent::size();
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
const T * const_VectorPtr<N, T, DIMSPEC>::ptr() const
{
	return Parent::ptr();
}

//template <std::size_t N, typename T, bool DIMSPEC>
//inline
//const_VectorPtr<N, T, DIMSPEC>::operator std::size_t () const
//{
//	return Parent::operator size_t();
//}

//template <std::size_t N, typename T, bool DIMSPEC>
//inline
//T const_VectorPtr<N, T, DIMSPEC>::operator [](int i) const
//{
//	return Parent::operator [](i);
//}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::operator [](std::size_t i) const
{
	GPX_ASSERT(i < size(), "index [" << i << "] is out of bounds");
	return Parent::coord(i);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::operator ()(std::size_t i) const
{
	GPX_ASSERT(i < size(), "index (" << i << ") is out of bounds");
	return Parent::coord(i);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::coord(std::size_t i) const
{
	GPX_ASSERT(i < size(), "coord(" << i << ") is out of bounds");
	return Parent::coord(i);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::x() const
{
	GPX_ASSERT(0 < size(), "x() is out of bounds");
	return Parent::coord(0);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::y() const
{
	GPX_ASSERT(1 < size(), "y() is out of bounds");
	return Parent::coord(1);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::z() const
{
	GPX_ASSERT(2 < size(), "z() is out of bounds");
	return Parent::coord(2);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::w() const
{
	GPX_ASSERT(3 < size(), "w() is out of bounds");
	return Parent::coord(3);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
bool const_VectorPtr<N, T, DIMSPEC>::operator ==(const const_VectorPtr<N, T> & other) const
{
	return Parent::operator ==(other);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
bool const_VectorPtr<N, T, DIMSPEC>::operator ==(T val) const
{
	return Parent::operator ==(val);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
bool const_VectorPtr<N, T, DIMSPEC>::operator !=(const const_VectorPtr<N, T> & other) const
{
	return Parent::operator !=(other);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
bool const_VectorPtr<N, T, DIMSPEC>::operator !=(T val) const
{
	return Parent::operator !=(val);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::inverse() const
{
	return Parent::inverse();
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::operator -() const
{
	return Parent::inverse();
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::sum(const const_VectorPtr<N, T> & other) const
{
	return Parent::sum(other);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::operator +(const const_VectorPtr<N, T> & other) const
{
	return Parent::sum(other);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::diff(const const_VectorPtr<N, T> & other) const
{
	return Parent::diff(other);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::operator -(const const_VectorPtr<N, T> & other) const
{
	return Parent::diff(other);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::prod(T scalar) const
{
	return Parent::prod(scalar);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::operator *(T scalar) const
{
	return Parent::prod(scalar);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::prod(const Matrix<N, N, T> & matrix) const
{
	GPX_ASSERT(matrix.rows() == Parent::size(), "number of rows in matrix must be equal to vector size");
	GPX_ASSERT(matrix.cols() == Parent::size(), "number of columns in matrix must be equal to vector size");
	return Parent::prod(matrix);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::operator *(const Matrix<N, N, T> & matrix) const
{
	return prod(matrix);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::quot(T scalar) const
{
	return Parent::quot(scalar);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::operator /(T scalar) const
{
	return Parent::quot(scalar);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::dot(const const_VectorPtr<N, T> & other) const
{
	return Parent::dot(other);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::dot() const
{
	return Parent::dot();
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::length() const
{
	return Parent::length();
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::versor() const
{
	return Parent::versor();
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::det(const const_VectorPtr<N, T> & other, std::size_t c1, std::size_t c2) const
{
	GPX_ASSERT(c1 < size(), "det(other, c1, c2) invalid coordinate c1: " << c1);
	GPX_ASSERT(c2 < size(), "det(other, c1, c2) invalid coordinate c2: " << c2);
	return Parent::det(other, c1, c2);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::cross(const const_VectorPtr<N, T> * others) const
{
	return Parent::cross(others);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::ccross(const const_VectorPtr<N, T> * others) const
{
	return Parent::ccross(others);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
bool const_VectorPtr<N, T, DIMSPEC>::ape(const const_VectorPtr<N, T> & other) const
{
	return Parent::ape(other);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
bool const_VectorPtr<N, T, DIMSPEC>::ape(T val) const
{
	return Parent::ape(val);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
bool const_VectorPtr<N, T, DIMSPEC>::ale(const const_VectorPtr<N, T> & other) const
{
	return Parent::ale(other);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
bool const_VectorPtr<N, T, DIMSPEC>::ale(T val) const
{
	return Parent::ale(val);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::minimal(const const_VectorPtr<N, T> & other) const
{
	return Parent::minimal(other);
}


template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::rotated(T sin, T cos, std::size_t c1, std::size_t c2) const
{
	return Parent::rotated(sin, cos, c1, c2);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::rotated(T angle, std::size_t c1, std::size_t c2) const
{
	return Parent::rotated(angle, c1, c2);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::rotated(T angle, const const_VectorPtr<2, T> & point, std::size_t c1, std::size_t c2) const
{
	return Parent::rotated(angle, point, c1, c2);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
const_VectorPtr<N, T, DIMSPEC>::const_VectorPtr(const const_VectorPtr<N, T, DIMSPEC> & other):
	Parent(other)
{
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
const_VectorPtr<N, T, DIMSPEC>::const_VectorPtr(const T * coords):
	Parent(coords)
{
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
const_VectorPtr<N, T, DIMSPEC>::const_VectorPtr(const T * coords, std::size_t size):
	Parent(coords, size)
{
}

//DIMSPEC = true

template <std::size_t N, typename T>
inline
const_VectorPtr<N, T, true>::const_VectorPtr(const T * coords):
	Parent(coords)
{
};

//DIMSPEC = true, N = SIZE_DYNAMIC

template <typename T>
inline
const_VectorPtr<SIZE_DYNAMIC, T, true>::const_VectorPtr(const T * coords, std::size_t size):
	Parent(coords, size)
{
};

template <typename T>
template <std::size_t ON>
inline
const_VectorPtr<SIZE_DYNAMIC, T, true>::const_VectorPtr(const const_VectorPtr<ON, T> & other):
	Parent(other.ptr(), other.size())
{
}

template <typename T>
template <std::size_t ON>
inline
Vector<SIZE_DYNAMIC, T> const_VectorPtr<SIZE_DYNAMIC, T, true>::prod(const Matrix<ON, ON, T> & matrix) const
{
	GPX_ASSERT(matrix.rows() == Parent::size(), "number of rows in matrix must be equal to vector size");
	GPX_ASSERT(matrix.cols() == Parent::size(), "number of columns in matrix must be equal to vector size");
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<SIZE_DYNAMIC, T>::prod(matrix);
}

template <typename T>
template <std::size_t ON>
inline
Vector<SIZE_DYNAMIC, T> const_VectorPtr<SIZE_DYNAMIC, T, true>::operator *(const Matrix<ON, ON, T> & matrix) const
{
	return prod(matrix);
}

template <typename T>
inline
void const_VectorPtr<SIZE_DYNAMIC, T, true>::setPtr(const T * ptr)
{
	Parent::setPtr(ptr);
}

template <typename T>
inline
void const_VectorPtr<SIZE_DYNAMIC, T, true>::setPtr(const T * ptr, std::size_t size)
{
	Parent::setPtr(ptr, size);
}

//DIMSPEC = true, N = 2

template <typename T>
inline
const_VectorPtr<2, T, true>::const_VectorPtr(const T * coords):
	Parent(coords)
{
}

template <typename T>
inline
Vector<2, T> const_VectorPtr<2, T, true>::cross() const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<2, T>::cross();
}

template <typename T>
inline
Vector<2, T> const_VectorPtr<2, T, true>::orthoCW() const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<2, T>::cross();
}

template <typename T>
inline
Vector<2, T> const_VectorPtr<2, T, true>::ccross() const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<2, T>::ccross();
}

template <typename T>
inline
Vector<2, T> const_VectorPtr<2, T, true>::orthoCCW() const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<2, T>::ccross();
}

template <typename T>
inline
T const_VectorPtr<2, T, true>::det(const const_VectorPtr<2, T> & other) const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<2, T>::det(other);
}

template <typename T>
inline
Vector<2, T> const_VectorPtr<2, T, true>::sum(T x, T y) const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<2, T>::sum(x, y);
}

template <typename T>
inline
Vector<2, T> const_VectorPtr<2, T, true>::diff(T x, T y) const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<2, T>::diff(x, y);
}

template <typename T>
inline
Vector<2, T> const_VectorPtr<2, T, true>::prod(const Matrix<4, 4, T> & matrix) const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<2, T>::prod(matrix);
}

template <typename T>
inline
Vector<2, T> const_VectorPtr<2, T, true>::operator *(const Matrix<4, 4, T> & matrix) const
{
	return prod(matrix);
}

template <typename T>
inline
Vector<2, T> const_VectorPtr<2, T, true>::rotated(T sin, T cos) const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<2, T>::rotated(sin, cos);
}

template <typename T>
inline
Vector<2, T> const_VectorPtr<2, T, true>::rotated(T angle) const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<2, T>::rotated(angle);
}

template <typename T>
inline
Vector<2, T> const_VectorPtr<2, T, true>::rotated(T angle, const const_VectorPtr<2, T> & point) const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<2, T>::rotated(angle, point);
}

//DIMSPEC = true, N = 3

template <typename T>
inline
const_VectorPtr<3, T, true>::const_VectorPtr(const T * coords):
	Parent(coords)
{
}

template <typename T>
inline
Vector<3, T> const_VectorPtr<3, T, true>::cross(const const_VectorPtr<3, T> & other) const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<3, T>::cross(other);
}

template <typename T>
inline
Vector<3, T> const_VectorPtr<3, T, true>::ccross(const const_VectorPtr<3, T> & other) const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<3, T>::ccross(other);
}

template <typename T>
inline
Vector<3, T> const_VectorPtr<3, T, true>::sum(T x, T y, T z) const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<3, T>::sum(x, y, z);
}

template <typename T>
inline
Vector<3, T> const_VectorPtr<3, T, true>::diff(T x, T y, T z) const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<3, T>::diff(x, y, z);
}

template <typename T>
inline
Vector<3, T> const_VectorPtr<3, T, true>::prod(const Matrix<4, 4, T> & matrix) const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<3, T>::prod(matrix);
}

template <typename T>
inline
Vector<3, T> const_VectorPtr<3, T, true>::operator *(const Matrix<4, 4, T> & matrix) const
{
	return prod(matrix);
}

template <typename T>
inline
Vector<3, T> const_VectorPtr<3, T, true>::rotated(T sin, T cos, std::size_t axis) const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<3, T>::rotated(sin, cos, axis);
}

template <typename T>
inline
Vector<3, T> const_VectorPtr<3, T, true>::rotated(T angle, std::size_t axis) const
{
	return GPX_X_MATH_BACKEND_NAMESPACE::const_VectorPtr<3, T>::rotated(angle, axis);
}

}
}

/**
 * Output stream operator for vector types.
 * @param s output stream.
 * @param v vector object.
 */
template <std::size_t N, typename T>
std::ostream & operator <<(std::ostream & s, const gpx::math::const_VectorPtr<N, T> & v)
{
	s.precision(gpx::math::const_VectorPtr<N, T>::PrintPrecision);
	s << "(";
	for (std::size_t i = 0; i < v.size() - 1; i++)
		s << v(i) << ", ";
	s << v(v.size() - 1) << ")" << std::endl;
	return s;
}

#include "VectorPtr.hpp"

#endif /* GPX_X_MATH_CONST_VECTORPTR_HPP_ */

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
