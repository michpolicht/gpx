/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_BASE_VECTOR_HPP_
#define GPX_X_MATH_BASE_VECTOR_HPP_

#include "../platform.hpp"

#include GPX_X_MATH_BACKEND_HEADER
#include GPX_X_MATH_BACKEND_BASE_VECTOR_HEADER

namespace gpx {
namespace math {

/**
 * N-dimensional vector on top of N-element pointer.
 */
template <std::size_t N, typename T, bool DIMSPEC>
class base_Vector : public GPX_X_MATH_BACKEND_NAMESPACE::base_Vector<N, T>
{
	typedef _ Parent;

	public:
		//generated copy assignment OK

		/**
		 * Get pointer pointing to coordinates.
		 * @return pointer pointing to coordinates.
		 */
		T * ptr();
		using const_VectorPtr<N, T>::ptr; //to use const version

		/**
		 * Individual coordinate access over subscript operator.
		 * @param i index.
		 * @return reference to i-th coordinate.
		 */
//		T & operator [](int i);	//to prevent ambiguity because of T * conversion operator
		T & operator [](std::size_t i); //default type for subscript access is int, so explicit conversion to size_t is required to call this version
		using const_VectorPtr<N, T>::operator []; //to use const version

		/**
		 * Individual coordinate access over function call operator.
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T & operator ()(std::size_t i);
		using const_VectorPtr<N, T>::operator (); //to use const version

		/**
		 * Individual coordinate access.
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T & coord(std::size_t i);
		using const_VectorPtr<N, T>::coord;	//to use const version

		/**
		 * Set x coordinate of vector.
		 * @param val value to be set.
		 */
		void setX(T val);

		/**
		 * Set y coordinate of vector.
		 * @param val value to be set.
		 */
		void setY(T val);

		/**
		 * Set z coordinate of vector.
		 * @param val value to be set.
		 */
		void setZ(T val);

		/**
		 * Set z coordinate of vector.
		 * @param val value to be set.
		 */
		void setW(T val);

		/**
		 * Addition. Add other vector to this vector.
		 * @param other vector to be added.
		 * @return self-reference to this vector.
		 */
		VectorPtr<N, T> & add(const const_VectorPtr<N, T> & other);

		/**
		 * Addition assignment. Alias of add().
		 * @param other vector to be added.
		 * @return self-reference to an object being assigned.
		 */
		VectorPtr<N, T> & operator +=(const const_VectorPtr<N, T> & other);

		/**
		 * Subtraction. Subtract other vector from this vector.
		 * @param other vector to be subtracted.
		 * @return self-reference to this vector.
		 */
		VectorPtr<N, T> & sub(const const_VectorPtr<N, T> & other);

		/**
		 * Subtraction assignment. Alias of sub().
		 * @param other vector to be subtracted.
		 * @return self-reference to an object being subtracted.
		 */
		VectorPtr<N, T> & operator -=(const const_VectorPtr<N, T> & other);

		/**
		 * Multiplication by scalar. Multiply all vector coordinates by scalar.
		 * @param scalar multiplier.
		 * @return self-reference to an object being multiplied.
		 */
		VectorPtr<N, T> & mul(T scalar);

		/**
		 * Multiplication assignment. Multiply all vector coordinates by scalar. Alias of mul().
		 * @param scalar multiplier.
		 * @return self-reference to an object being multiplied.
		 */
		VectorPtr<N, T> & operator *=(T scalar);

		/**
		 * Multiplication by matrix. Vector is considered to lie horizontally (bra vector).
		 * @param matrix multiplier.
		 * @return self-reference to an object being multiplied.
		 */
		VectorPtr<N, T> & mul(const Matrix<N, N, T> & matrix);

		/**
		 * Multiplication assignment. Vector is considered to lie horizontally (bra vector).
		 * Aliast of mul().
		 * @param matrix multiplier.
		 * @return self-reference to an object being multiplied.
		 */
		VectorPtr<N, T> & operator *=(const Matrix<N, N, T> & matrix);

		/**
		 * Division. Divide all vector coordinates by scalar.
		 * @param scalar divisor.
		 * @return self-reference to an object being divided.
		 */
		VectorPtr<N, T> & div(T scalar);

		/**
		 * Division assignment. Divide all vector coordinates by a scalar. Alias of div().
		 * @param scalar divisor.
		 * @return self-reference to an object being divided.
		 */
		VectorPtr<N, T> & operator /=(T scalar);

		/**
		 * Zero vector coordinates.
		 * @return self-reference to zeroed object.
		 */
		VectorPtr<N, T> & zero();

		/**
		 * Invert this vector.
		 * @return self-reference to inverted object.
		 *
		 * @see inverse().
		 */
		VectorPtr<N, T> & invert();

		/**
		 * Normalize this vector.
		 * @return self-reference to normalized object.
		 *
		 * @see versor().
		 */
		VectorPtr<N, T> & normalize();

		/**
		 * Rotate by given values of sine and cosine on a specific base-plane.
		 * @param sin sine.
		 * @param cos cosine.
		 * @param c1 first coordinate that describes base-plane.
		 * @param c2 second coordinate that describes base-plane.
		 * @return self-reference to rotated object.
		 */
		VectorPtr<N, T> & rotate(T sin, T cos, std::size_t c1, std::size_t c2);

		/**
		 * Rotate vector by given angle on a specific base-plane.
		 * @param angle rotation angle in radians. Angle is oriented according to
		 * right angle formed on base-plane between coordinates @a c1, @a c2.
		 * @param c1 first coordinate that describes base-plane.
		 * @param c2 second coordinate that describes base-plane.
		 * @return self-reference to rotated object.
		 */
		VectorPtr<N, T> & rotate(T angle, std::size_t c1, std::size_t c2);

		/**
		 * Rotate vector by given angle around given point on a specific base-plane.
		 * @param angle rotation angle in radians. Angle is oriented according to
		 * right angle formed on base-plane between coordinates @a c1, @a c2.
		 * @param c1 first coordinate that describes base-plane.
		 * @param c2 second coordinate that describes base-plane.
		 * @param point point on [@a c1, @a c2] base-plane, around which rotation should be
		 * performed.
		 * @return self-reference to rotated object.
		 *
		 * @todo remove (2 dim point incompatible with rotated vector coordinates brings mess).
		 */
		VectorPtr<N, T> & rotate(T angle, const const_VectorPtr<2, T> & point, std::size_t c1, std::size_t c2);

		/**
		 * Minimize this vector against @a other vector.
		 * @param other vector for which minimal vector has to be prepared.
		 * @return parallel vector with exponents of coordinates reduced to smallest
		 * possible values, so that if vector is added to @a other vector it still
		 * affects other vector coordinates (if minimized coordinate is non-zero).
		 * @return self-reference to minimized object.
		 */
		VectorPtr<N, T> & minimize(const const_VectorPtr<N, T> & other);

		/**
		 * Swap elements.
		 * @param c1 coordinate of element to be swapped with @a c2;
		 * @param c2 coordinate of element to be swapped with @a c1;
		 */
		void swap(std::size_t c1, std::size_t c2);

	protected:
		/**
		 * Copy constructor. Sets coordinates pointer as in another vector.
		 * @param other other object. Coordinates pointer will point to the same array as
		 * other. Since no allocation is done, this array must be accessible during object
		 * lifetime.
		 */
		VectorPtr(const VectorPtr<N, T, DIMSPEC> & other);

		/**
		 * Conversion constructor.
		 * @param coords pointer to N-element array of coordinates.
		 */
		VectorPtr(T * coords);

		/**
		 * Constructor.
		 * @param coords pointer to array of coordinates.
		 * @param size array size in terms of number of elements.
		 */
		VectorPtr(T * coords, std::size_t size);

	private:
		/**
		 * Default constructor. Explicitly forbidden; coordinates pointer must be set.
		 */
		VectorPtr();

		/**
		 * Conversion constructor. Direct conversion from const_VectorPtr explicitly
		 * forbidden.
		 * @param other object.
		 */
		VectorPtr(const const_VectorPtr<N, T> & other);
};

/**
 * N-dimensional vector on top of N-element pointer.
 */
template <std::size_t N, typename T>
class VectorPtr<N, T, true> : public VectorPtr<N, T, false>
{
	typedef VectorPtr<N, T, false> Parent;

	public:
		/**
		 * Conversion constructor.
		 * @param coords pointer to N-element array of coordinates.
		 */
		VectorPtr(T * coords);

		//generated copy ctor OK

	public:
		//generated copy assignment OK

		/**
		 * Assignment operator. Data will be copied from other.
		 * @param other source from which data will be copied from.
		 * @return self-reference to object being assigned.
		 */
		VectorPtr<N, T> & operator =(const real_t other[N]);	//assignment operators hidden by generated copy-assignment

		/**
		 * Assignment operator. Data will be copied from other vector.
		 * @param other source from which data will be copied from.
		 * @return self-reference to object being assigned.
		 */
		VectorPtr<N, T> & operator =(const const_VectorPtr<N, T> & other); //assignment operators hidden by generated copy-assignment

		/**
		 * Assignment operator. Coordinates will be set to specific value.
		 * @param val value to be set on all coordinates.
		 * @return self-reference to an object being assigned.
		 */
		VectorPtr<N, T> & operator =(T val); //assignment operators hidden by generated copy-assignment
};

/**
 * Runtime sized vector on top of pointer.
 *
 * @note there is main difference between dynamic and fixed size VectorPtr. Coordinates
 * pointer of fixed size VectorPtr is guaranteed to point to the same location during
 * whole object lifetime. Dynamic VectorPtr provides setPtr() methods, which allow
 * pointer to be modified during runtime.
 */
template <typename T>
class VectorPtr<SIZE_DYNAMIC, T, true> : public VectorPtr<SIZE_DYNAMIC, T, false>
{
	typedef VectorPtr<SIZE_DYNAMIC, T, false> Parent;

	public:
		//generated copy ctor OK

		/**
		 * Constructor.
		 * @param coords pointer to array of coordinates.
		 * @param size size of array in terms of number of elements.
		 */
		VectorPtr(T * coords, std::size_t size = 0);

		/**
		 * Conversion constructor.
		 * @param other other vector. Coordinates pointer will point to the same array as
		 * in other. Since no allocation is done, this array must be accessible during
		 * object lifetime.
		 */
		template <std::size_t ON>
		VectorPtr(VectorPtr<ON, T> & other);

	public:
		//generated copy assignment OK

		/**
		 * Assignment operator. Data will be copied from other.
		 * @param other source from which data will be copied from.
		 * @return self-reference to object being assigned.
		 */
		VectorPtr<SIZE_DYNAMIC, T> & operator =(const real_t * other);	//assignment operators hidden by generated copy-assignment

		/**
		 * Assignment operator. Data will be copied from other vector.
		 * @param other source from which data will be copied from.
		 * @return self-reference to object being assigned.
		 */
		template <std::size_t ON>
		VectorPtr<SIZE_DYNAMIC, T> & operator =(const const_VectorPtr<ON, T> & other); //assignment operators hidden by generated copy-assignment

		/**
		 * Assignment operator. Coordinates will be set to specific value.
		 * @param val value to be set on all coordinates.
		 * @return self-reference to an object being assigned.
		 */
		VectorPtr<SIZE_DYNAMIC, T> & operator =(T val); //assignment operators hidden by generated copy-assignment

		using Parent::mul;

		template <std::size_t ON>
		VectorPtr<SIZE_DYNAMIC, T> & mul(const Matrix<ON, ON, T> & matrix);

		using Parent::operator *=;

		template <std::size_t ON>
		VectorPtr<SIZE_DYNAMIC, T> & operator *=(const Matrix<ON, ON, T> & matrix);

		/**
		 * Set coordinates pointer.
		 * @param ptr pointer to array of coordinates.
		 */
		void setPtr(T * ptr);

		/**
		 * Set coordinates pointer and size.
		 * @param ptr pointer to array of coordinates.
		 * @param size vector size in terms of number of elements.
		 */
		void setPtr(T * ptr, std::size_t size);
};

/**
 * Two-dimensional vector on top of pointer.
 */
template <typename T>
class VectorPtr<2, T, true> : public VectorPtr<2, T, false>
{
	typedef VectorPtr<2, T, false> Parent;

	public:
		//generated copy ctor OK

		/**
		 * Conversion constructor.
		 * @param coords pointer to 3-element array of coordinates.
		 */
		VectorPtr(T * coords);

	public:
		//generated copy assignment OK

		/**
		 * Assignment operator. Data will be copied from other.
		 * @param other source from which data will be copied from.
		 * @return self-reference to object being assigned.
		 */
		VectorPtr<2, T> & operator =(const real_t * other);	//assignment operators hidden by generated copy-assignment

		/**
		 * Assignment operator. Data will be copied from other vector.
		 * @param other source from which data will be copied from.
		 * @return self-reference to object being assigned.
		 */
		VectorPtr<2, T> & operator =(const const_VectorPtr<2, T> & other); //assignment operators hidden by generated copy-assignment

		/**
		 * Assignment operator. Coordinates will be set to specific value.
		 * @param val value to be set on all coordinates.
		 * @return self-reference to an object being assigned.
		 */
		VectorPtr<2, T> & operator =(T val); //assignment operators hidden by generated copy-assignment

		/**
		 * Set coordinates.
		 * @param x x coordinate.
		 * @param y y coordinate.
		 */
		void set(T x, T y);

		using Parent::add;

		/**
		 * Add vector (x, y) to this vector. Provided for convenience.
		 * @param x x coordinate of other vector.
		 * @param y y coordinate of other vector.
		 * @return self-reference to this vector.
		 */
		VectorPtr<2, T> & add(T x, T y);

		using Parent::sub;

		/**
		 * Subtract vector (x, y) from this vector. Provided for convenience.
		 * @param x x coordinate of other vector.
		 * @param y y coordinate of other vector.
		 * @return self-reference to this vector.
		 */
		VectorPtr<2, T> & sub(T x, T y);

		using Parent::mul;

		/**
		 * Multiply vector by 4 x 4 matrix. This irregular function is provided for
		 * convenience to work with 4D homogeneous coordinates. Vector (x, y) is mapped
		 * to (x, y, 0.0, 1.0).
		 * @param matrix matrix.
		 * @return self-reference to this vector.
		 */
		VectorPtr<2, T> & mul(const Matrix<4, 4, T> & matrix);

		using Parent::operator *=;

		/**
		 * Multiply vector by 4 x 4 matrix. Alias of mul().
		 * @param matrix matrix.
		 * @return self-reference to this vector.
		 */
		VectorPtr<2, T> & operator *=(const Matrix<4, 4, T> & matrix);

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
		VectorPtr<2, T> & rotate(T sin, T cos);

		/**
		 * Rotate vector by given angle.
		 * @param angle rotation angle in radians. Angle is oriented counterclockwise
		 * according to OpenGL coordinates layout.
		 * @return self-reference to rotated object.
		 */
		VectorPtr<2, T> & rotate(T angle);

		/**
		 * Rotate vector by given angle around specific point.
		 * @param angle rotation angle in radians. Angle is oriented counterclockwise
		 * according to OpenGL coordinates layout.
		 * @param point point, around which rotation should be performed.
		 * @return self-reference to rotated object.
		 */
		VectorPtr<2, T> & rotate(T angle, const const_VectorPtr<2, T> & point);
};

/**
 * Three-dimensional vector on top of pointer.
 */
template <typename T>
class VectorPtr<3, T, true> : public VectorPtr<3, T, false>
{
	typedef VectorPtr<3, T, false> Parent;

	public:
		//generated copy ctor OK

		/**
		 * Conversion constructor.
		 * @param coords pointer to 3-element array of coordinates.
		 */
		VectorPtr(T * coords);

	public:
		//generated copy assignment OK

		/**
		 * Assignment operator. Data will be copied from other.
		 * @param other source from which data will be copied from.
		 * @return self-reference to object being assigned.
		 */
		VectorPtr<3, T> & operator =(const real_t * other);	//assignment operators hidden by generated copy-assignment

		/**
		 * Assignment operator. Data will be copied from other vector.
		 * @param other source from which data will be copied from.
		 * @return self-reference to object being assigned.
		 */
		VectorPtr<3, T> & operator =(const const_VectorPtr<3, T> & other); //assignment operators hidden by generated copy-assignment

		/**
		 * Assignment operator. Coordinates will be set to specific value.
		 * @param val value to be set on all coordinates.
		 * @return self-reference to an object being assigned.
		 */
		VectorPtr<3, T> & operator =(T val); //assignment operators hidden by generated copy-assignment

		/**
		 * Set coordinates.
		 * @param x x coordinate.
		 * @param y y coordinate.
		 * @param z z coordinate.
		 */
		void set(T x, T y, T z);

		using Parent::add;

		/**
		 * Add vector (x, y, z) to this vector. Provided for convenience.
		 * @param x x coordinate of other vector.
		 * @param y y coordinate of other vector.
		 * @param z z coordinate of other vector.
		 * @return self-reference to this vector.
		 */
		VectorPtr<3, T> & add(T x, T y, T z);

		using Parent::sub;

		/**
		 * Subtract vector (x, y, z) from this vector. Provided for convenience.
		 * @param x x coordinate of other vector.
		 * @param y y coordinate of other vector.
		 * @param z z coordinate of other vector.
		 * @return self-reference to this vector.
		 */
		VectorPtr<3, T> & sub(T x, T y, T z);

		using Parent::mul;

		/**
		 * Multiply vector by 4 x 4 matrix. This irregular function is provided for
		 * convenience to work with 4D homogeneous coordinates. Vector (x, y, z) is mapped
		 * to (x, y, z, 1.0).
		 * @param matrix matrix.
		 * @return self-reference to this vector.
		 */
		VectorPtr<3, T> & mul(const Matrix<4, 4, T> & matrix);

		using Parent::operator *=;

		/**
		 * Multiply vector by 4 x 4 matrix. Alias of mul().
		 * @param matrix matrix.
		 * @return self-reference to this vector.
		 */
		VectorPtr<3, T> & operator *=(const Matrix<4, 4, T> & matrix);

		///////////////////////////////////////////////////////////////////////
		//
		//        ^ y          OpenGL coordinates layout
		//        |
		//        |
		//        .------> x
		//       /
		//      /
        //     * z

		using Parent::rotate;

		/**
		 * Rotate by given values of sine and cosine around specific axis.
		 * @param sin sine.
		 * @param cos cosine.
		 * @param axis axis of rotation. Angle is oriented according to right hand
		 * rule in OpenGL coordinates layout.
		 * @return self-reference to rotated object.
		 */
		VectorPtr<3, T> & rotate(T sin, T cos, std::size_t axis);

		/**
		 * Rotate vector by given angle around specific axis.
		 * @param angle rotation angle in radians. Angle is oriented according to right
		 * hand rule in OpenGL coordinates layout.
		 * @param axis axis of rotation.
		 * @return self-reference to rotated object.
		 */
		VectorPtr<3, T> & rotate(T angle, std::size_t axis);
};

template <std::size_t N, typename T, bool DIMSPEC>
inline
T * VectorPtr<N, T, DIMSPEC>::ptr()
{
	return Parent::ptr();
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T & VectorPtr<N, T, DIMSPEC>::operator [](std::size_t i)
{
	GPX_ASSERT(i < Parent::size(), "index [" << i << "] is out of bounds");
	return Parent::coord(i);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T & VectorPtr<N, T, DIMSPEC>::operator ()(std::size_t i)
{
	GPX_ASSERT(i < Parent::size(), "index (" << i << ") is out of bounds");
	return Parent::coord(i);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T & VectorPtr<N, T, DIMSPEC>::coord(std::size_t i)
{
	GPX_ASSERT(i < Parent::size(), "coord(" << i << ") is out of bounds");
	return Parent::coord(i);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::setX(T val)
{
	GPX_ASSERT(0 < Parent::size(), "setX() is out of bounds");
	Parent::coord(0) = val;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::setY(T val)
{
	GPX_ASSERT(1 < Parent::size(), "setY() is out of bounds");
	Parent::coord(1) = val;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::setZ(T val)
{
	GPX_ASSERT(2 < Parent::size(), "setZ() is out of bounds");
	Parent::coord(2) = val;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::setW(T val)
{
	GPX_ASSERT(3 < Parent::size(), "setW() is out of bounds");
	Parent::coord(3) = val;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::add(const const_VectorPtr<N, T> & other)
{
	Parent::add(other);
	return static_cast<VectorPtr<N, T> & >(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::operator +=(const const_VectorPtr<N, T> & other)
{
	Parent::add(other);
	return static_cast<VectorPtr<N, T> & >(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::sub(const const_VectorPtr<N, T> & other)
{
	Parent::sub(other);
	return static_cast<VectorPtr<N, T> & >(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::operator -=(const const_VectorPtr<N, T> & other)
{
	Parent::sub(other);
	return static_cast<VectorPtr<N, T> & >(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::mul(T scalar)
{
	Parent::mul(scalar);
	return static_cast<VectorPtr<N, T> & >(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::operator *=(T scalar)
{
	Parent::mul(scalar);
	return static_cast<VectorPtr<N, T> & >(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::mul(const Matrix<N, N, T> & matrix)
{
	GPX_ASSERT(matrix.rows() == Parent::size(), "number of rows in matrix must be equal to vector size");
	GPX_ASSERT(matrix.cols() == Parent::size(), "number of columns in matrix must be equal to vector size");
	Parent::mul(matrix);
	return static_cast<VectorPtr<N, T> & >(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::operator *=(const Matrix<N, N, T> & matrix)
{
	return mul(matrix);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::div(T scalar)
{
	Parent::div(scalar);
	return static_cast<VectorPtr<N, T> & >(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::operator /=(T scalar)
{
	Parent::div(scalar);
	return static_cast<VectorPtr<N, T> & >(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::zero()
{
	Parent::zero();
	return static_cast<VectorPtr<N, T> & >(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::invert()
{
	Parent::invert();
	return static_cast<VectorPtr<N, T> & >(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::normalize()
{
	Parent::normalize();
	return static_cast<VectorPtr<N, T> & >(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::rotate(T sin, T cos, std::size_t c1, std::size_t c2)
{
	Parent::rotate(sin, cos, c1, c2);
	return static_cast<VectorPtr<N, T> & >(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::rotate(T angle, std::size_t c1, std::size_t c2)
{
	Parent::rotate(angle, c1, c2);
	return static_cast<VectorPtr<N, T> & >(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::rotate(T angle, const const_VectorPtr<2, T> & point, std::size_t c1, std::size_t c2)
{
	Parent::rotate(angle, point, c1, c2);
	return static_cast<VectorPtr<N, T> & >(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T> & VectorPtr<N, T, DIMSPEC>::minimize(const const_VectorPtr<N, T> & other)
{
	Parent::minimize(other);
	return static_cast<VectorPtr<N, T> & >(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::swap(std::size_t c1, std::size_t c2)
{
	Parent::swap(c1, c2);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T, DIMSPEC>::VectorPtr(const VectorPtr<N, T, DIMSPEC> & other):
	Parent(other)
{
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T, DIMSPEC>::VectorPtr(T * coords):
	Parent(coords)
{
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T, DIMSPEC>::VectorPtr(T * coords, std::size_t size):
	Parent(coords, size)
{
}

// DIMSPEC = true

template <std::size_t N, typename T>
inline
VectorPtr<N, T, true>::VectorPtr(T * coords):
	Parent(coords)
{
}

template <std::size_t N, typename T>
inline
VectorPtr<N, T> & VectorPtr<N, T, true>::operator =(const real_t other[N])
{
	//self assignment branch not required here
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<N, T>::operator =(other);
	return *this;
}

template <std::size_t N, typename T>
inline
VectorPtr<N, T> & VectorPtr<N, T, true>::operator =(const const_VectorPtr<N, T> & other)
{
	//self assignment branch not required here
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<N, T>::operator =(other);
	return *this;
}

template <std::size_t N, typename T>
inline
VectorPtr<N, T> & VectorPtr<N, T, true>::operator =(T val)
{
	//self assignment branch not required here
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<N, T>::operator =(val);
	return *this;
}

// DIMSPEC = true, N = SIZE_DYNAMIC

template <typename T>
inline
VectorPtr<SIZE_DYNAMIC, T, true>::VectorPtr(T * coords, std::size_t size):
	Parent(coords, size)
{
}

template <typename T>
template <std::size_t ON>
inline
VectorPtr<SIZE_DYNAMIC, T, true>::VectorPtr(VectorPtr<ON, T> & other):
	Parent(other.ptr(), other.size())
{
}

template <typename T>
inline
VectorPtr<SIZE_DYNAMIC, T> & VectorPtr<SIZE_DYNAMIC, T, true>::operator =(const real_t * other)
{
	//self assignment branch not required here
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<SIZE_DYNAMIC, T>::operator =(other);
	return *this;
}

template <typename T>
template <std::size_t ON>
inline
VectorPtr<SIZE_DYNAMIC, T> & VectorPtr<SIZE_DYNAMIC, T, true>::operator =(const const_VectorPtr<ON, T> & other)
{
	//self assignment branch not required here
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<SIZE_DYNAMIC, T>::operator =(other);
	return *this;
}

template <typename T>
inline
VectorPtr<SIZE_DYNAMIC, T> & VectorPtr<SIZE_DYNAMIC, T, true>::operator =(T val)
{
	//self assignment branch not required here
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<SIZE_DYNAMIC, T>::operator =(val);
	return *this;
}

template <typename T>
template <std::size_t ON>
inline
VectorPtr<SIZE_DYNAMIC, T> & VectorPtr<SIZE_DYNAMIC, T, true>::mul(const Matrix<ON, ON, T> & matrix)
{
	GPX_ASSERT(matrix.rows() == Parent::size(), "number of rows in matrix must be equal to vector size");
	GPX_ASSERT(matrix.cols() == Parent::size(), "number of columns in matrix must be equal to vector size");
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<SIZE_DYNAMIC, T>::mul(matrix);
	return *this;
}

template <typename T>
template <std::size_t ON>
inline
VectorPtr<SIZE_DYNAMIC, T> & VectorPtr<SIZE_DYNAMIC, T, true>::operator *=(const Matrix<ON, ON, T> & matrix)
{
	return mul(matrix);
}

template <typename T>
inline
void VectorPtr<SIZE_DYNAMIC, T, true>::setPtr(T * ptr)
{
	Parent::setPtr(ptr);
}

template <typename T>
inline
void VectorPtr<SIZE_DYNAMIC, T, true>::setPtr(T * ptr, std::size_t size)
{
	Parent::setPtr(ptr, size);
}

// DIMSPEC = true, N = 2

template <typename T>
inline
VectorPtr<2, T, true>::VectorPtr(T * coords):
	Parent(coords)
{
}

template <typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T, true>::operator =(const real_t * other)
{
	//self assignment branch not required here
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<2, T>::operator =(other);
	return *this;
}

template <typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T, true>::operator =(const const_VectorPtr<2, T> & other)
{
	//self assignment branch not required here
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<2, T>::operator =(other);
	return *this;
}

template <typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T, true>::operator =(T val)
{
	//self assignment branch not required here
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<2, T>::operator =(val);
	return *this;
}

template <typename T>
inline
void VectorPtr<2, T, true>::set(T x, T y)
{
	Parent::setX(x);
	Parent::setY(y);
}

template <typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T, true>::add(T x, T y)
{
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<2, T>::add(x, y);
	return *this;
}

template <typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T, true>::sub(T x, T y)
{
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<2, T>::sub(x, y);
	return *this;
}

template <typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T, true>::mul(const Matrix<4, 4, T> & matrix)
{
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<2, T>::mul(matrix);
	return *this;
}

template <typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T, true>::operator *=(const Matrix<4, 4, T> & matrix)
{
	return mul(matrix);
}

template <typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T, true>::rotate(T sin, T cos)
{
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<2, T>::rotate(sin, cos);
	return *this;
}

template <typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T, true>::rotate(T angle)
{
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<2, T>::rotate(angle);
	return *this;
}

template <typename T>
inline
VectorPtr<2, T> & VectorPtr<2, T, true>::rotate(T angle, const const_VectorPtr<2, T> & point)
{
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<2, T>::rotate(angle, point);
	return *this;
}

// DIMSPEC = true, N = 3

template <typename T>
inline
VectorPtr<3, T, true>::VectorPtr(T * coords):
	Parent(coords)
{
}

template <typename T>
inline
VectorPtr<3, T> & VectorPtr<3, T, true>::operator =(const real_t * other)
{
	//self assignment branch not required here
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<3, T>::operator =(other);
	return *this;
}

template <typename T>
inline
VectorPtr<3, T> & VectorPtr<3, T, true>::operator =(const const_VectorPtr<3, T> & other)
{
	//self assignment branch not required here
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<3, T>::operator =(other);
	return *this;
}

template <typename T>
inline
VectorPtr<3, T> & VectorPtr<3, T, true>::operator =(T val)
{
	//self assignment branch not required here
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<3, T>::operator =(val);
	return *this;
}

template <typename T>
inline
void VectorPtr<3, T, true>::set(T x, T y, T z)
{
	Parent::setX(x);
	Parent::setY(y);
	Parent::setZ(z);
}

template <typename T>
inline
VectorPtr<3, T> & VectorPtr<3, T, true>::add(T x, T y, T z)
{
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<3, T>::add(x, y, z);
	return *this;
}

template <typename T>
inline
VectorPtr<3, T> & VectorPtr<3, T, true>::sub(T x, T y, T z)
{
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<3, T>::sub(x, y, z);
	return *this;
}

template <typename T>
inline
VectorPtr<3, T> & VectorPtr<3, T, true>::mul(const Matrix<4, 4, T> & matrix)
{
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<3, T>::mul(matrix);
	return *this;
}

template <typename T>
inline
VectorPtr<3, T> & VectorPtr<3, T, true>::operator *=(const Matrix<4, 4, T> & matrix)
{
	return mul(matrix);
}

template <typename T>
inline
VectorPtr<3, T> & VectorPtr<3, T, true>::rotate(T sin, T cos, std::size_t axis)
{
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<3, T>::rotate(sin, cos, axis);
	return *this;
}

template <typename T>
inline
VectorPtr<3, T> & VectorPtr<3, T, true>::rotate(T angle, std::size_t axis)
{
	GPX_X_MATH_BACKEND_NAMESPACE::VectorPtr<3, T>::rotate(angle, axis);
	return *this;
}

}
}

#endif
