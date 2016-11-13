/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_VECTOR_HPP_
#define GPX_X_MATH_VECTOR_HPP_

#include "../platform.hpp"

#include "VectorPtr.hpp"
//#note: "Matrix.hpp" included near eof

#include GPX_X_MATH_BACKEND_HEADER
#include GPX_X_MATH_BACKEND_VECTOR_HEADER

namespace gpx {
namespace math {

/**
 * N-dimensional vector with self-allocated coordinates.
 *
 * @todo C++11 variadic ctors (Vector<N, T>(x, y, z, ..., N)) with variadic templates or maybe initializer lists (currently specializations are required for this).
 */
template <std::size_t N, typename T>
class Vector : public GPX_X_MATH_BACKEND_NAMESPACE::Vector<N, T>
{
	typedef GPX_X_MATH_BACKEND_NAMESPACE::Vector<N, T> Parent;

	public:
		/**
		 * Default constructor. Constructs vector with coordinates initialized
		 * with zeros.
		 */
		Vector();

		/*
		 * Copy constructor. Coordinates are initialized with the same values as
		 * in the other
		 * object.
		 * @param other object from which coordinates will be copied.
		 */
		//generated copy ctor OK

		/**
		 * Constructor.
		 * @param init indicates whenever to initialize vector.
		 * @param size number of coordinates to initialize.
		 * @param val value to initialize vector with.
		 * @param reserve provided for compatibility with dynamically sized vector.
		 */
		explicit Vector(bool init, std::size_t size = N, T val = T(), std::size_t reserve = 0);

		/**
		 * Constructor. This is not a conversion constructor; it should be used
		 * explicitly. It copies coordinates from other object.
		 * @param other object from which coordinates shall be copied.
		 *
		 * @note VectorPtr is a subclass of const_VectorPtr, so this constructor
		 * should handle VectorPtr objects as well.
		 * @param reserve provided for compatibility with dynamically sized vector.
		 */
		explicit Vector(const const_VectorPtr<N, T> & other);

		/**
		 * Constructor. This is not a conversion constructor; it should be used
		 * explicitly. It copies data from coords array.
		 * @param coords array of coordinates.
		 * @param reserve provided for compatibility with dynamically sized vector.
		 */
		explicit Vector(const T coords[N]);

		/**
		 * Constructor. Constructs vector from given two points.
		 * @param init array containing coordinates of initial point.
		 * @param end array containing coordinates of end point.
		 * @param reserve provided for compatibility with dynamically sized vector.
		 */
		Vector(const T init[N], const T end[N]);

		/**
		 * Constructor. Initialized specified number of vector coordinates with
		 * given value.
		 * @param val value to be set on vector coordinates.
		 * @param size vector size in terms of number of elements.
		 * @param reserve provided for compatibility with dynamically sized vector.
		 *
		 * @warning dynamically sized vector provides Vector(std::size_t size) instead.
		 */
		explicit Vector(T val);

	public:
		//generated copy-assignment OK

		/**
		 * Assignment operator. Coordinates will be copied from other object.
		 * @param other object from which data should be copied from.
		 * @return self-reference to an object being assigned.
		 */
//		Vector<N, T> & operator =(const Vector<N, T> & other);

		/**
		 * Assignment operator. Coordinates will be copied from other object.
		 * @param other object from which data should be copied from.
		 * @return self-reference to an object being assigned.
		 *
		 * @note VectorPtr is a subclass of const_VectorPtr, so this operator should
		 * handle VectorPtr objects as well.
		 */
		Vector<N, T> & operator =(const const_VectorPtr<N, T> & other); // It should handle VectorPtr as well as const_VectorPtr.

		/**
		 * Assignment operator. Coordinates will be copied from given array.
		 * @param other array from which data should be copied from.
		 * @return self-reference to an object being assigned.
		 */
		Vector<N, T> & operator =(const real_t other[N]);

		/**
		 * Assignment operator. Coordinates will be set to specific value.
		 * @param val value to be set on all coordinates.
		 * @return self-reference to an object being assigned.
		 */
		Vector<N, T> & operator =(T val);

		/**
		 * Get amount of reserved memory.
		 * @return amount of excessively reserved memory as number of coordinates which can be
		 * stored without the need of memory reallocation. Fixed size vectors return their
		 * size.
		 */
		std::size_t reserve() const;

		/**
		 * Reserve memory. Purpose of this function is to reserve as much space as required
		 * to store given number of coordinates, so that memory reallocation won't be necessary
		 * during further resize operations. This is not imperative. Request may be
		 * scheduled for future realization or even ignored. In any case function is
		 * required to preserve vector data.
		 * @param size amount of memory to reserve in terms of number of coordinates.
		 *
		 * @note function does nothing in case of fixed size vectors, although it is legal
		 * to perform a call.
		 */
		void reserve(std::size_t size);

		/**
		 * Resize vector.
		 * @param size new size in terms of number of coordinates.
		 *
		 * @note fixed size vector can not be resized, however, calling resize() with
		 * current number of coordinates is considered to be valid resize operation.
		 *
		 * @warning resize is destructive operation. Current values of vector coordinates
		 * are lost and replaced by undefined ones.
		 *
		 * @warning resize operation invalidates coordinates pointer.
		 */
		void resize(std::size_t size);
};

template <typename T>
class Vector<SIZE_DYNAMIC, T> : public GPX_X_MATH_BACKEND_NAMESPACE::Vector<SIZE_DYNAMIC, T>
{
	typedef GPX_X_MATH_BACKEND_NAMESPACE::Vector<SIZE_DYNAMIC, T> Parent;

	public:
		/**
		 * Default constructor. Constructs zero sized vector.
		 */
		Vector();	//no reserve to prevent ambiguities

		//generated copy ctor OK

		/**
		 * Constructor. Constructs vector with coordinates initialized with zeros.
		 * @param size vector size in terms of number of coordinates.
		 * @param reserve amount of extra memory to reserve in terms of number of coordinates.
		 *
		 * @warning fixed size vector provides Vector(T val) instead.
		 *
		 * @todo remove reserve, since it will cause ambiguities with Vector(T val, size, reserve)
		 */
		explicit Vector(std::size_t size, std::size_t reserve = 0);

		/**
		 * Constructor.
		 * @param init indicates whenever to initialize vector.
		 * @param size number of coordinates to initialize.
		 * @param val value to initialize vector with.
		 * @param reserve amount of extra memory to reserve in terms of number of coordinates.
		 */
		explicit Vector(bool init, std::size_t size, T val = T(), std::size_t reserve = 0);

		/**
		 * Constructor. This is not a conversion constructor; it should be used explicitly.
		 * It copies coordinates from other object.
		 * @param other object from which coordinates shall be copied.
		 *
		 * @note VectorPtr is a subclass of const_VectorPtr, so this constructor should
		 * handle VectorPtr objects as well.
		 */
		template <std::size_t ON>
		explicit Vector(const const_VectorPtr<ON, T> & other, std::size_t reserve = 0);

		/**
		 * Constructor. This is not a conversion constructor; it should be used explicitly.
		 * It copies data from coords array.
		 * @param coords array of coordinates.
		 * @param size vector size in terms of number of coordinates.
		 * @param reserve amount of extra memory to reserve in terms of number of coordinates.
		 */
		Vector(const T * coords, std::size_t size, std::size_t reserve = 0);

		/**
		 * Constructor. Constructs vector from given two points.
		 * @param init array containing coordinates of initial point.
		 * @param end array containing coordinates of end point.
		 * @param size vector size in terms of number of coordinates. Both points must
		 * also have given dimensionality.
		 * @param reserve amount of extra memory to reserve in terms of number of coordinates.
		 */
		Vector(const T * init, const T * end, std::size_t size, std::size_t reserve = 0);

		/**
		 * Constructor. Initializes all vector coordinates to specific value.
		 * @param val value to be set on all vector coordinates.
		 * @param size vector size in terms of number of coordinates.
		 * @param reserve amount of extra memory to reserve in terms of number of coordinates.
		 */
		Vector(T val, std::size_t size, std::size_t reserve = 0);

	public:
		/**
		 * Assignment operator. Coordinates will be copied from other object.
		 * @param other object from which data should be copied from.
		 * @return self-reference to an object being assigned.
		 */
//		Vector<N, T> & operator =(const Vector<N, T> & other);

		/**
		 * Assignment operator. Coordinates will be copied from other object.
		 * @param other object from which data should be copied from.
		 * @return self-reference to an object being assigned.
		 *
		 * @note VectorPtr is a subclass of const_VectorPtr, so this operator should
		 * handle VectorPtr objects as well.
		 */
		template <std::size_t ON>
		Vector<SIZE_DYNAMIC, T> & operator =(const const_VectorPtr<ON, T> & other); // It should handle VectorPtr as well as const_VectorPtr.

		/**
		 * Assignment operator. Coordinates will be copied from given array.
		 * @param other array from which data should be copied from.
		 * @return self-reference to an object being assigned.
		 */
		Vector<SIZE_DYNAMIC, T> & operator =(const real_t * other);

		/**
		 * Assignment operator. Coordinates will be set to specific value.
		 * @param val value to be set on all coordinates.
		 * @return self-reference to an object being assigned.
		 */
		Vector<SIZE_DYNAMIC, T> & operator =(T val);

		/**
		 * Get amount of reserved memory.
		 * @return amount of excessively reserved memory as number of coordinates which can be
		 * stored without the need of memory reallocation.
		 */
		std::size_t reserve() const;

		/**
		 * Reserve memory. Purpose of this function is to reserve as much space as required
		 * to store given number of coordinates, so that memory reallocation won't be necessary
		 * during further resize operations. This is not imperative. Request may be
		 * scheduled for future realization or even ignored. In any case function is
		 * required to preserve vector data.
		 * @param size amount of memory to reserve in terms of number of coordinates.
		 *
		 * @note function does nothing in case of fixed size vectors, although it is legal
		 * to perform a call.
		 */
		void reserve(std::size_t size);

		/**
		 * Resize vector.
		 * @param size new size in terms of number of coordinates.
		 *
		 * @note fixed size vector can not be resized, however, calling resize() with
		 * current number of coordinates is considered to be valid resize operation.
		 *
		 * @warning resize is destructive operation. Current values of vector coordinates
		 * are lost and replaced by undefined ones.
		 *
		 * @warning resize operation invalidates coordinates pointer.
		 */
		void resize(std::size_t size);
};

template <typename T>
class Vector<2, T> : public GPX_X_MATH_BACKEND_NAMESPACE::Vector<2, T>
{
	typedef GPX_X_MATH_BACKEND_NAMESPACE::Vector<2, T> Parent;

	public:
		/**
		 * Default constructor. Constructs vector with coordinates initialized
		 * with zeros.
		 */
		Vector();

		//generated copy ctor OK

		/**
		 * Constructor.
		 * @param init indicates whenever to initialize vector.
		 * @param size number of coordinates to initialize.
		 * @param val value to initialize vector with.
		 * @param reserve provided for compatibility with dynamically sized vector.
		 */
		explicit Vector(bool init, std::size_t size = 2, T val = T(), std::size_t reserve = 0);

		/**
		 * Constructor. This is not a conversion constructor; it should be used
		 * explicitly. It copies coordinates from other object.
		 * @param other object from which coordinates shall be copied.
		 *
		 * @note VectorPtr is a subclass of const_VectorPtr, so this constructor
		 * should handle VectorPtr objects as well.
		 */
		explicit Vector(const const_VectorPtr<2, T> & other);

		/**
		 * Constructor. This is not a conversion constructor; it should be used
		 * explicitly. It copies data from coords array.
		 * @param coords array of coordinates.
		 */
		explicit Vector(const T coords[2]);

		/**
		 * Constructor. Constructs vector from given three coordinate values.
		 * @param x x coordinate of vector.
		 * @param y y coordinate of vector.
		 */
		Vector(T x, T y);

		/**
		 * Constructor. Constructs vector from given two points.
		 * @param init array containing coordinates of initial point.
		 * @param end array containing coordinates of end point.
		 */
		Vector(const T init[2], const T end[2]);

		/**
		 * Constructor. Initialized specified number of vector coordinates with
		 * given value.
		 * @param val value to be set on vector coordinates.
		 * @param size vector size in terms of number of elements.
		 * @param reserve provided for compatibility with dynamically sized vector.
		 *
		 * @warning dynamically sized vector provides Vector(std::size_t size) instead.
		 */
		explicit Vector(T val); //Vector(size) is not provided to prevent ambiguities between Vector(val)

	public:
		//generated copy-assignment OK

		/**
		 * Assignment operator. Coordinates will be copied from other object.
		 * @param other object from which data should be copied from.
		 * @return self-reference to an object being assigned.
		 *
		 * @note VectorPtr is a subclass of const_VectorPtr, so this operator should
		 * handle VectorPtr objects as well.
		 */
		Vector<2, T> & operator =(const const_VectorPtr<2, T> & other); // It should handle VectorPtr as well as const_VectorPtr.

		/**
		 * Assignment operator. Coordinates will be copied from given array.
		 * @param other array from which data should be copied from.
		 * @return self-reference to an object being assigned.
		 */
		Vector<2, T> & operator =(const real_t other[2]);

		/**
		 * Assignment operator. Coordinates will be set to specific value.
		 * @param val value to be set on all coordinates.
		 * @return self-reference to an object being assigned.
		 */
		Vector<2, T> & operator =(T val);

		/**
		 * Get amount of reserved memory.
		 * @return amount of excessively reserved memory as number of coordinates which can be
		 * stored without the need of memory reallocation. Fixed size vectors return their
		 * size.
		 */
		std::size_t reserve() const;

		/**
		 * Reserve memory. Purpose of this function is to reserve as much space as required
		 * to store given number of coordinates, so that memory reallocation won't be necessary
		 * during further resize operations. This is not imperative. Request may be
		 * scheduled for future realization or even ignored. In any case function is
		 * required to preserve vector data.
		 * @param size amount of memory to reserve in terms of number of coordinates.
		 *
		 * @note function does nothing in case of fixed size vectors, although it is legal
		 * to perform a call.
		 */
		void reserve(std::size_t size);

		/**
		 * Resize vector.
		 * @param size new size in terms of number of coordinates.
		 *
		 * @note fixed size vector can not be resized, however, calling resize() with
		 * current number of coordinates is considered to be valid resize operation.
		 *
		 * @warning resize is destructive operation. Current values of vector coordinates
		 * are lost and replaced by undefined ones.
		 *
		 * @warning resize operation invalidates coordinates pointer.
		 */
		void resize(std::size_t size);
};

template <typename T>
class Vector<3, T> : public GPX_X_MATH_BACKEND_NAMESPACE::Vector<3, T>
{
	typedef GPX_X_MATH_BACKEND_NAMESPACE::Vector<3, T> Parent;

	public:
		/**
		 * Default constructor. Constructs vector with coordinates initialized
		 * with zeros.
		 *
		 * @note to create uninitialized vector use VectorPtr and uninitialized array.
		 */
		Vector();

		//generated copy ctor OK

		/**
		 * Constructor.
		 * @param init indicates whenever to initialize vector.
		 * @param size number of coordinates to initialize.
		 * @param val value to initialize vector with.
		 * @param reserve provided for compatibility with dynamically sized vector.
		 */
		explicit Vector(bool init, std::size_t size = 3, T val = T(), std::size_t reserve = 0);

		/**
		 * Constructor. This is not a conversion constructor; it should be used
		 * explicitly. It copies coordinates from other object.
		 * @param other object from which coordinates shall be copied.
		 *
		 * @note VectorPtr is a subclass of const_VectorPtr, so this constructor
		 * should handle VectorPtr objects as well.
		 */
		explicit Vector(const const_VectorPtr<3, T> & other);

		/**
		 * Constructor. This is not a conversion constructor; it should be used
		 * explicitly. It copies data from coords array.
		 * @param coords array of coordinates.
		 */
		explicit Vector(const T coords[3]);

		/**
		 * Constructor. Constructs vector from given three coordinate values.
		 * @param x x coordinate of vector.
		 * @param y y coordinate of vector.
		 * @param z z coordinate of vector.
		 */
		Vector(T x, T y, T z);

		/**
		 * Constructor. Constructs vector from given two points.
		 * @param init array containing coordinates of initial point.
		 * @param end array containing coordinates of end point.
		 */
		Vector(const T init[3], const T end[3]);

		/**
		 * Constructor. Initialized specified number of vector coordinates with
		 * given value.
		 * @param val value to be set on vector coordinates.
		 * @param size vector size in terms of number of elements.
		 * @param reserve provided for compatibility with dynamically sized vector.
		 *
		 * @warning dynamically sized vector provides Vector(std::size_t size) instead.
		 */
		explicit Vector(T val); //Vector(size) is not provided to prevent ambiguities between Vector(val)

	public:
		//generated copy-assignment OK

		/**
		 * Assignment operator. Coordinates will be copied from other object.
		 * @param other object from which data should be copied from.
		 * @return self-reference to an object being assigned.
		 *
		 * @note VectorPtr is a subclass of const_VectorPtr, so this operator should
		 * handle VectorPtr objects as well.
		 */
		Vector<3, T> & operator =(const const_VectorPtr<3, T> & other); // It should handle VectorPtr as well as const_VectorPtr.

		/**
		 * Assignment operator. Coordinates will be copied from given array.
		 * @param other array from which data should be copied from.
		 * @return self-reference to an object being assigned.
		 */
		Vector<3, T> & operator =(const real_t other[3]);

		/**
		 * Assignment operator. Coordinates will be set to specific value.
		 * @param val value to be set on all coordinates.
		 * @return self-reference to an object being assigned.
		 */
		Vector<3, T> & operator =(T val);

		/**
		 * Get amount of reserved memory.
		 * @return amount of excessively reserved memory as number of coordinates which can be
		 * stored without the need of memory reallocation. Fixed size vectors return their
		 * size.
		 */
		std::size_t reserve() const;

		/**
		 * Reserve memory. Purpose of this function is to reserve as much space as required
		 * to store given number of coordinates, so that memory reallocation won't be necessary
		 * during further resize operations. This is not imperative. Request may be
		 * scheduled for future realization or even ignored. In any case function is
		 * required to preserve vector data.
		 * @param size amount of memory to reserve in terms of number of coordinates.
		 *
		 * @note function does nothing in case of fixed size vectors, although it is legal
		 * to perform a call.
		 */
		void reserve(std::size_t size);

		/**
		 * Resize vector.
		 * @param size new size in terms of number of coordinates.
		 *
		 * @note fixed size vector can not be resized, however, calling resize() with
		 * current number of coordinates is considered to be valid resize operation.
		 *
		 * @warning resize is destructive operation. Current values of vector coordinates
		 * are lost and replaced by undefined ones.
		 *
		 * @warning resize operation invalidates coordinates pointer.
		 */
		void resize(std::size_t size);
};

template <std::size_t N, typename T>
inline
Vector<N, T>::Vector():
	Parent()
{
}

template <std::size_t N, typename T>
inline
Vector<N, T>::Vector(const const_VectorPtr<N, T> & other):
	Parent(other)
{
}

template <std::size_t N, typename T>
inline
Vector<N, T>::Vector(bool init, std::size_t size, T val, std::size_t reserve):
	Parent(init, size, val, reserve)
{
}

template <std::size_t N, typename T>
inline
Vector<N, T>::Vector(const T coords[N]):
	Parent(coords)
{
}

template <std::size_t N, typename T>
inline
Vector<N, T>::Vector(const T init[N], const T end[N]):
	Parent(init, end)
{
}

template <std::size_t N, typename T>
inline
Vector<N, T>::Vector(T val):
	Parent(val)
{
}

//template <std::size_t N, typename T>
//inline
//Vector<N, T> & Vector<N, T>::operator =(const Vector<N, T> & other)
//{
//	//self assignment branch not required here
//	Parent::operator =(other);
//	return *this;
//}

template <std::size_t N, typename T>
inline
Vector<N, T> & Vector<N, T>::operator =(const const_VectorPtr<N, T> & other)
{
	//self assignment branch not required here
	Parent::operator =(other);
	return * this;
}

template <std::size_t N, typename T>
inline
Vector<N, T> & Vector<N, T>::operator =(const real_t other[N])
{
	//self assignment branch not required here
	Parent::operator =(other);
	return * this;
}

template <std::size_t N, typename T>
inline
Vector<N, T> & Vector<N, T>::operator =(T val)
{
	//self assignment branch not required here
	Parent::operator =(val);
	return * this;
}

template <std::size_t N, typename T>
inline
std::size_t Vector<N, T>::reserve() const
{
	return Parent::reserve();
}

template <std::size_t N, typename T>
inline
void Vector<N, T>::reserve(std::size_t size)
{
	Parent::reserve(size);
}

template <std::size_t N, typename T>
inline
void Vector<N, T>::resize(std::size_t size)
{
	Parent::resize(size);
}

//N = SIZE_DYNAMIC

template <typename T>
inline
Vector<SIZE_DYNAMIC, T>::Vector():
	Parent()
{
}

template <typename T>
inline
Vector<SIZE_DYNAMIC, T>::Vector(std::size_t size, std::size_t reserve):
	Parent(size, reserve)
{
}

template <typename T>
inline
Vector<SIZE_DYNAMIC, T>::Vector(bool init, std::size_t size, T val, std::size_t reserve):
	Parent(init, size, val, reserve)
{
}

template <typename T>
template <std::size_t ON>
inline
Vector<SIZE_DYNAMIC, T>::Vector(const const_VectorPtr<ON, T> & other, std::size_t reserve):
	Parent(other, reserve)
{
}

template <typename T>
inline
Vector<SIZE_DYNAMIC, T>::Vector(const T * coords, std::size_t size, std::size_t reserve):
	Parent(coords, size, reserve)
{
}

template <typename T>
inline
Vector<SIZE_DYNAMIC, T>::Vector(const T * init, const T * end, std::size_t size, std::size_t reserve):
	Parent(init, end, size, reserve)
{
}

template <typename T>
inline
Vector<SIZE_DYNAMIC, T>::Vector(T val, std::size_t size, std::size_t reserve):
	Parent(val, size, reserve)
{
}

template <typename T>
template <std::size_t ON>
inline
Vector<SIZE_DYNAMIC, T> & Vector<SIZE_DYNAMIC, T>::operator =(const const_VectorPtr<ON, T> & other)
{
	//self assignment branch not required here
	Parent::operator =(other);
	return *this;
}

template <typename T>
inline
Vector<SIZE_DYNAMIC, T> & Vector<SIZE_DYNAMIC, T>::operator =(const real_t * other)
{
	//self assignment branch not required here
	Parent::operator =(other);
	return *this;
}

template <typename T>
inline
Vector<SIZE_DYNAMIC, T> & Vector<SIZE_DYNAMIC, T>::operator =(T val)
{
	//self assignment branch not required here
	Parent::operator =(val);
	return *this;
}

template <typename T>
inline
std::size_t Vector<SIZE_DYNAMIC, T>::reserve() const
{
	return Parent::reserve();
}

template <typename T>
inline
void Vector<SIZE_DYNAMIC, T>::reserve(std::size_t size)
{
	Parent::reserve(size);
}

template <typename T>
inline
void Vector<SIZE_DYNAMIC, T>::resize(std::size_t size)
{
	Parent::resize(size);
}

//N = 2

template <typename T>
inline
Vector<2, T>::Vector():
	Parent()
{
}

template <typename T>
inline
Vector<2, T>::Vector(bool init, std::size_t size, T val, std::size_t reserve):
	Parent(init, size, val, reserve)
{
}

template <typename T>
inline
Vector<2, T>::Vector(const const_VectorPtr<2, T> & other):
	Parent(other)
{
}

template <typename T>
inline
Vector<2, T>::Vector(const T * coords):
	Parent(coords)
{
}

template <typename T>
inline
Vector<2, T>::Vector(const T init[2], const T end[2]):
	Parent(init, end)
{
}

template <typename T>
inline
Vector<2, T>::Vector(T x, T y):
	Parent(x, y)
{
}

template <typename T>
inline
Vector<2, T>::Vector(T val):
	Parent(val)
{
}

template <typename T>
inline
Vector<2, T> & Vector<2, T>::operator =(const const_VectorPtr<2, T> & other)
{
	//self assignment branch not required here
	Parent::operator =(other);
	return *this;
}

template <typename T>
inline
Vector<2, T> & Vector<2, T>::operator =(const real_t other[2])
{
	//self assignment branch not required here
	Parent::operator =(other);
	return *this;
}

template <typename T>
inline
Vector<2, T> & Vector<2, T>::operator =(T val)
{
	//self assignment branch not required here
	Parent::operator =(val);
	return *this;
}

template <typename T>
inline
std::size_t Vector<2, T>::reserve() const
{
	return Parent::reserve();
}

template <typename T>
inline
void Vector<2, T>::reserve(std::size_t size)
{
	Parent::reserve(size);
}

template <typename T>
inline
void Vector<2, T>::resize(std::size_t size)
{
	Parent::resize(size);
}

//N = 3

template <typename T>
inline
Vector<3, T>::Vector():
	Parent()
{
}

template <typename T>
inline
Vector<3, T>::Vector(bool init, std::size_t size, T val, std::size_t reserve):
	Parent(init, size, val, reserve)
{
}

template <typename T>
inline
Vector<3, T>::Vector(const const_VectorPtr<3, T> & other):
	Parent(other)
{
}

template <typename T>
inline
Vector<3, T>::Vector(const T * coords):
	Parent(coords)
{
}

template <typename T>
inline
Vector<3, T>::Vector(const T init[3], const T end[3]):
	Parent(init, end)
{
}

template <typename T>
inline
Vector<3, T>::Vector(T x, T y, T z):
	Parent(x, y, z)
{
}

template <typename T>
inline
Vector<3, T>::Vector(T val):
	Parent(val)
{
}

template <typename T>
inline
Vector<3, T> & Vector<3, T>::operator =(const const_VectorPtr<3, T> & other)
{
	//self assignment branch not required here
	Parent::operator =(other);
	return *this;
}

template <typename T>
inline
Vector<3, T> & Vector<3, T>::operator =(const real_t other[3])
{
	//self assignment branch not required here
	Parent::operator =(other);
	return *this;
}

template <typename T>
inline
Vector<3, T> & Vector<3, T>::operator =(T val)
{
	//self assignment branch not required here
	Parent::operator =(val);
	return *this;
}

template <typename T>
inline
std::size_t Vector<3, T>::reserve() const
{
	return Parent::reserve();
}

template <typename T>
inline
void Vector<3, T>::reserve(std::size_t size)
{
	Parent::reserve(size);
}

template <typename T>
inline
void Vector<3, T>::resize(std::size_t size)
{
	Parent::resize(size);
}

}
}

#include "Matrix.hpp"

#endif /* GPX_X_MATH_VECTOR_HPP_ */

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
