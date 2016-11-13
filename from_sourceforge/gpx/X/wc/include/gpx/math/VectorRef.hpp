/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_VECTORREF_HPP_
#define GPX_X_MATH_VECTORREF_HPP_

#include "structures.hpp"

namespace gpx {
namespace math {

/**
 * N-dimensional vector reference mimic.
 */
template <std::size_t N, typename T>
class VectorRef : public VectorTrait<VectorRef, N, T, true>
{
	public:
		//VectorRef(const VectorRef & other) = default;

		explicit VectorRef(T * ptr);

		operator const_VectorRef<N, T> () const;

		//~VectorRef() = default;

		/**
		 * Copy assignment. Data will be copied from other vector.
		 * @param other vector from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		VectorRef<N, T> & operator =(const VectorRef<N, T> & other);

		/**
		 * Vector assignment. Data will be copied from other vector.
		 * @param other vector from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		VectorRef<N, T> & operator =(const const_VectorRef<N, T> & other);

		/**
		 * Vector assignment. Data will be copied from other vector.
		 * @param other vector from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		VectorRef<N, T> & operator =(const Vector<N, T> & other);

		/**
		 * Array assignment. Data will be copied from location pointed by ptr.
		 * @param other location from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		VectorRef<N, T> & operator =(const T * other);

		/**
		 * Individual coordinate access over subscript operator (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T operator [](std::size_t i) const; //if conversion operator to T * is enabled, then default type for subscript access is int, so explicit conversion to std::size_t is required to call this version (provide T operator [](int i) in such case).

		/**
		 * Individual coordinate access over subscript operator.
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T & operator [](std::size_t i); //if conversion operator to T * is enabled, then default type for subscript access is int, so explicit conversion to std::size_t is required to call this version (provide T operator [](int i) in such case).

		/**
		 * Individual coordinate access over function call operator (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T operator ()(std::size_t i) const;

		/**
		 * Individual coordinate access over function call operator.
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T & operator ()(std::size_t i);

		/**
		 * Individual coordinate access.
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T coord(std::size_t i) const;

		/**
		 * Individual coordinate access (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T & coord(std::size_t i);

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
		 * Get pointer pointing to coordinates.
		 * @return pointer pointing to coordinates.
		 */
		T * ptr();

	private:
		T * m_coords;
};

template <std::size_t N, typename T>
VectorRef<N, T>::VectorRef(T * ptr):
	m_coords(ptr)
{
}

template <std::size_t N, typename T>
VectorRef<N, T>::operator const_VectorRef<N, T> () const
{
	return const_VectorRef<N, T>(m_coords);
}

template <std::size_t N, typename T>
VectorRef<N, T> & VectorRef<N, T>::operator =(const VectorRef<N, T> & other)
{
	//Do not move this to VectorTrait!
	//Vector may rely purely on compiler provided copy assignment.
	//If VectorTrait had copy assignment, it would be called for Vector
	//as well, since VectorTrait is also its parent class.
	//Rather replace T * coords with composite backend::VectorRef member and then this
	//operator can be delegated.

	//self assignment branch not required here
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
	return *this;
}

template <std::size_t N, typename T>
VectorRef<N, T> & VectorRef<N, T>::operator =(const const_VectorRef<N, T> & other)
{
	//Need to provide separate operator = for const_VectorRef and Vector,
	//because copy assignment introduces ambiguity for Vector,
	//which can be converted to either VectorRef or const_VectorRef.
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
	return *this;
}

template <std::size_t N, typename T>
VectorRef<N, T> & VectorRef<N, T>::operator =(const Vector<N, T> & other)
{
	//Need to provide separate operator = for const_VectorRef and Vector,
	//because copy assignment signature introduces ambiguity for Vector,
	//which can be converted to either VectorRef or const_VectorRef.
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
	return *this;
}

template <std::size_t N, typename T>
VectorRef<N, T> & VectorRef<N, T>::operator =(const T * other)
{
	std::copy(other, other + size(), m_coords);
	return *this;
}

template <std::size_t N, typename T>
T VectorRef<N, T>::operator [](std::size_t i) const
{
	return coord(i);
}

template <std::size_t N, typename T>
T & VectorRef<N, T>::operator [](std::size_t i)
{
	return coord(i);
}

template <std::size_t N, typename T>
T VectorRef<N, T>::operator ()(std::size_t i) const
{
	return coord(i);
}

template <std::size_t N, typename T>
T & VectorRef<N, T>::operator ()(std::size_t i)
{
	return coord(i);
}

template <std::size_t N, typename T>
T VectorRef<N, T>::coord(std::size_t i) const
{
	GPX_ASSERT(i < size(), "index [" << i << "] is out of bounds");
	return m_coords[i];
}

template <std::size_t N, typename T>
T & VectorRef<N, T>::coord(std::size_t i)
{
	GPX_ASSERT(i < size(), "index [" << i << "] is out of bounds");
	return m_coords[i];
}

template <std::size_t N, typename T>
std::size_t VectorRef<N, T>::size() const
{
	return N;
}

template <std::size_t N, typename T>
const T * VectorRef<N, T>::ptr() const
{
	return m_coords;
}

template <std::size_t N, typename T>
T * VectorRef<N, T>::ptr()
{
	return m_coords;
}

/**
 * Dynamically sized vector reference mimic.
 */
template <typename T>
class VectorRef<SIZE_DYNAMIC, T> : public VectorTrait<VectorRef, SIZE_DYNAMIC, T, true>
{
	public:
		//VectorRef(const VectorRef<SIZE_DYNAMIC, T> & other) = default;

		explicit VectorRef(Vector<SIZE_DYNAMIC, T> * vPtr);

		operator const_VectorRef<SIZE_DYNAMIC, T> () const;

		//~VectorRef() = default;

		/**
		 * Copy assignment. Data will be copied from other vector.
		 * @param other vector from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		VectorRef<SIZE_DYNAMIC, T> & operator =(const VectorRef<SIZE_DYNAMIC, T> & other);

		/**
		 * Vector assignment. Data will be copied from other vector.
		 * @param other vector from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		VectorRef<SIZE_DYNAMIC, T> & operator =(const_VectorRef<SIZE_DYNAMIC, T> other);

		/**
		 * Vector assignment. Data will be copied from other vector.
		 * @param other vector from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		VectorRef<SIZE_DYNAMIC, T> & operator =(const Vector<SIZE_DYNAMIC, T> & other);

		/**
		 * Array assignment. Data will be copied from location pointed by ptr.
		 * @param other location from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		VectorRef<SIZE_DYNAMIC, T> & operator =(const T * other);

		/**
		 * Individual coordinate access over subscript operator (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T operator [](std::size_t i) const; //if conversion operator to T * is enabled, then default type for subscript access is int, so explicit conversion to std::size_t is required to call this version (provide T operator [](int i) in such case).

		/**
		 * Individual coordinate access over subscript operator.
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T & operator [](std::size_t i); //if conversion operator to T * is enabled, then default type for subscript access is int, so explicit conversion to std::size_t is required to call this version (provide T operator [](int i) in such case).

		/**
		 * Individual coordinate access over function call operator (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T operator ()(std::size_t i) const;

		/**
		 * Individual coordinate access over function call operator.
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T & operator ()(std::size_t i);

		/**
		 * Individual coordinate access.
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T coord(std::size_t i) const;

		/**
		 * Individual coordinate access (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T & coord(std::size_t i);

		/**
		 * Get vector size.
		 * @return vector size in terms of number of coordinates.
		 */
		std::size_t size() const;

		/**
		 * Resize vector.
		 * @param size new size in terms of number of coordinates.
		 *
		 * @warning resize is destructive operation. Current values of vector coordinates
		 * are lost and replaced by undefined ones.
		 *
		 * @warning resize operation invalidates coordinates pointer.
		 */
		void resize(std::size_t size);

		/**
		 * Get amount of reserved memory.
		 * @return amount of excessively reserved memory as number of coordinates which can be
		 * stored without the need of memory reallocation.
		 */
		std::size_t reserved() const;

		/**
		 * Reserve memory. Request may be scheduled for future realization or even ignored.
		 * Function is required to preserve vector data.
		 * @param size amount of memory to reserve in terms of number of coordinates.
		 */
		void reserve(std::size_t size);

		/**
		 * Get const pointer pointing to coordinates.
		 * @return const pointer pointing to coordinates.
		 */
		const T * ptr() const;

		/**
		 * Get pointer pointing to coordinates.
		 * @return pointer pointing to coordinates.
		 */
		T * ptr();

	private:
		Vector<SIZE_DYNAMIC, T> * m_vPtr;
};

template <typename T>
VectorRef<SIZE_DYNAMIC, T>::VectorRef(Vector<SIZE_DYNAMIC, T> * vPtr):
	m_vPtr(vPtr)
{
}

template <typename T>
VectorRef<SIZE_DYNAMIC, T>::operator const_VectorRef<SIZE_DYNAMIC, T> () const
{
	return const_VectorRef<SIZE_DYNAMIC, T>(m_vPtr);
}

template <typename T>
VectorRef<SIZE_DYNAMIC, T> & VectorRef<SIZE_DYNAMIC, T>::operator =(const VectorRef<SIZE_DYNAMIC, T> & other)
{
	//self assignment branch not required here
	*m_vPtr = other;
	return *this;
}

template <typename T>
VectorRef<SIZE_DYNAMIC, T> & VectorRef<SIZE_DYNAMIC, T>::operator =(const_VectorRef<SIZE_DYNAMIC, T> other)
{
	*m_vPtr = other;
	return *this;
}

template <typename T>
VectorRef<SIZE_DYNAMIC, T> & VectorRef<SIZE_DYNAMIC, T>::operator =(const Vector<SIZE_DYNAMIC, T> & other)
{
	*m_vPtr = other;
	return *this;
}

template <typename T>
VectorRef<SIZE_DYNAMIC, T> & VectorRef<SIZE_DYNAMIC, T>::operator =(const T * other)
{
	*m_vPtr = other;
	return *this;
}

template <typename T>
T VectorRef<SIZE_DYNAMIC, T>::operator [](std::size_t i) const
{
	return m_vPtr->operator [](i);
}

template <typename T>
T & VectorRef<SIZE_DYNAMIC, T>::operator [](std::size_t i)
{
	return m_vPtr->operator [](i);
}

template <typename T>
T VectorRef<SIZE_DYNAMIC, T>::operator ()(std::size_t i) const
{
	return m_vPtr->operator ()(i);
}

template <typename T>
T & VectorRef<SIZE_DYNAMIC, T>::operator ()(std::size_t i)
{
	return m_vPtr->operator ()(i);
}

template <typename T>
T VectorRef<SIZE_DYNAMIC, T>::coord(std::size_t i) const
{
	return m_vPtr->coord(i);
}

template <typename T>
T & VectorRef<SIZE_DYNAMIC, T>::coord(std::size_t i)
{
	return m_vPtr->coord(i);
}

template <typename T>
std::size_t VectorRef<SIZE_DYNAMIC, T>::size() const
{
	return m_vPtr->size();
}

template <typename T>
void VectorRef<SIZE_DYNAMIC, T>::resize(std::size_t size)
{
	return m_vPtr->resize(size);
}

template <typename T>
std::size_t VectorRef<SIZE_DYNAMIC, T>::reserved() const
{
	return m_vPtr->reserved();
}

template <typename T>
void VectorRef<SIZE_DYNAMIC, T>::reserve(std::size_t size)
{
	return m_vPtr->reserve(size);
}

template <typename T>
const T * VectorRef<SIZE_DYNAMIC, T>::ptr() const
{
	return m_vPtr->ptr();
}

template <typename T>
T * VectorRef<SIZE_DYNAMIC, T>::ptr()
{
	return m_vPtr->ptr();
}

/**
 * Two-dimensional vector const reference mimic.
 */
template <typename T>
class VectorRef<2, T> : public VectorTrait<VectorRef, 2, T, true>
{
	public:
		//VectorRef(const VectorRef & other) = default;

		explicit VectorRef(T * ptr);

		operator const_VectorRef<2, T> () const;

		//~VectorRef() = default;

		/**
		 * Copy assignment. Data will be copied from other vector.
		 * @param other vector from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		VectorRef<2, T> & operator =(const VectorRef<2, T> & other);

		/**
		 * Vector assignment. Data will be copied from other vector.
		 * @param other vector from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		VectorRef<2, T> & operator =(const const_VectorRef<2, T> & other);

		/**
		 * Vector assignment. Data will be copied from other vector.
		 * @param other vector from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		VectorRef<2, T> & operator =(const Vector<2, T> & other);

		/**
		 * Array assignment. Data will be copied from location pointed by ptr.
		 * @param other location from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		VectorRef<2, T> & operator =(const T * other);

		/**
		 * Individual coordinate access over subscript operator (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T operator [](std::size_t i) const; //if conversion operator to T * is enabled, then default type for subscript access is int, so explicit conversion to std::size_t is required to call this version (provide T operator [](int i) in such case).

		/**
		 * Individual coordinate access over subscript operator.
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T & operator [](std::size_t i); //if conversion operator to T * is enabled, then default type for subscript access is int, so explicit conversion to std::size_t is required to call this version (provide T operator [](int i) in such case).

		/**
		 * Individual coordinate access over function call operator (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T operator ()(std::size_t i) const;

		/**
		 * Individual coordinate access over function call operator.
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T & operator ()(std::size_t i);

		/**
		 * Individual coordinate access.
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T coord(std::size_t i) const;

		/**
		 * Individual coordinate access (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T & coord(std::size_t i);

		/**
		 * Get x coordinate. Alias of coord(0) const.
		 * @return value of x coordinate.
		 */
		T x() const;

		/**
		 * Set x coordinate.
		 * @param val value to be set.
		 */
		void setX(T val);

		/**
		 * Get y coordinate. Alias of coord(0) const.
		 * @return value of y coordinate.
		 */
		T y() const;

		/**
		 * Set y coordinate.
		 * @param val value to be set.
		 */
		void setY(T val);

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
		 * Get pointer pointing to coordinates.
		 * @return pointer pointing to coordinates.
		 */
		T * ptr();

	private:
		T * m_coords;
};

template <typename T>
VectorRef<2, T>::VectorRef(T * ptr):
	m_coords(ptr)
{
}

template <typename T>
VectorRef<2, T>::operator const_VectorRef<2, T> () const
{
	return const_VectorRef<2, T>(m_coords);
}

template <typename T>
VectorRef<2, T> & VectorRef<2, T>::operator =(const VectorRef<2, T> & other)
{
	//self assignment branch not required here
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
	return *this;
}

template <typename T>
VectorRef<2, T> & VectorRef<2, T>::operator =(const const_VectorRef<2, T> & other)
{
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
	return *this;
}

template <typename T>
VectorRef<2, T> & VectorRef<2, T>::operator =(const Vector<2, T> & other)
{
	//Need to provide separate operator = for const_VectorRef and Vector,
	//because copy assignment introduces ambiguity for Vector,
	//which can be converted to either VectorRef or const_VectorRef.
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
	return *this;
}

template <typename T>
VectorRef<2, T> & VectorRef<2, T>::operator =(const T * other)
{
	std::copy(other, other + size(), m_coords);
	return *this;
}

template <typename T>
T VectorRef<2, T>::operator [](std::size_t i) const
{
	return coord(i);
}

template <typename T>
T & VectorRef<2, T>::operator [](std::size_t i)
{
	return coord(i);
}

template <typename T>
T VectorRef<2, T>::operator ()(std::size_t i) const
{
	return coord(i);
}

template <typename T>
T & VectorRef<2, T>::operator ()(std::size_t i)
{
	return coord(i);
}

template <typename T>
T VectorRef<2, T>::coord(std::size_t i) const
{
	GPX_ASSERT(i < size(), "index [" << i << "] is out of bounds");
	return m_coords[i];
}

template <typename T>
T & VectorRef<2, T>::coord(std::size_t i)
{
	GPX_ASSERT(i < size(), "index [" << i << "] is out of bounds");
	return m_coords[i];
}

template <typename T>
T VectorRef<2, T>::x() const
{
	return m_coords[0];
}

template <typename T>
void VectorRef<2, T>::setX(T val)
{
	m_coords[0] = val;
}

template <typename T>
T VectorRef<2, T>::y() const
{
	return m_coords[1];
}

template <typename T>
void VectorRef<2, T>::setY(T val)
{
	m_coords[1] = val;
}

template <typename T>
std::size_t VectorRef<2, T>::size() const
{
	return 2;
}

template <typename T>
const T * VectorRef<2, T>::ptr() const
{
	return m_coords;
}

template <typename T>
T * VectorRef<2, T>::ptr()
{
	return m_coords;
}


}
}

#endif
