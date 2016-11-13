#ifndef POINTREF_HPP
#define POINTREF_HPP

#include "structures.hpp"

namespace gpx {
namespace math {

/**
 * N-dimensional point reference mimic.
 */
template <std::size_t N, typename T>
class PointRef : public PointTrait<PointRef, N, T, true>
{
	public:
		//PointRef(const PointRef & other) = default;

		explicit PointRef(T * ptr);

		operator const_PointRef<N, T> () const;

		//~PointRef() = default;

		/**
		 * Copy assignment. Data will be copied from other point.
		 * @param other point from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		PointRef<N, T> & operator =(const PointRef<N, T> & other);

		/**
		 * Point assignment. Data will be copied from other point.
		 * @param other point from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		PointRef<N, T> & operator =(const const_PointRef<N, T> & other);

		/**
		 * Point assignment. Data will be copied from other point.
		 * @param other point from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		PointRef<N, T> & operator =(const Point<N, T> & other);

		/**
		 * Array assignment. Data will be copied from location pointed by ptr.
		 * @param other location from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		PointRef<N, T> & operator =(const T * other);

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
		 * Get point size.
		 * @return point size in terms of number of coordinates.
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
PointRef<N, T>::PointRef(T * ptr):
	m_coords(ptr)
{
}

template <std::size_t N, typename T>
PointRef<N, T>::operator const_PointRef<N, T> () const
{
	return const_PointRef<N, T>(m_coords);
}

template <std::size_t N, typename T>
PointRef<N, T> & PointRef<N, T>::operator =(const PointRef<N, T> & other)
{
	//Do not move this to PointTrait!
	//Point may rely purely on compiler provided copy assignment.
	//If PointTrait had copy assignment, it would be called for Point
	//as well, since PointTrait is also its parent class.
	//Rather replace T * coords with composite backend::PointRef member and then this
	//operator can be delegated.

	//self assignment branch not required here
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
	return *this;
}

template <std::size_t N, typename T>
PointRef<N, T> & PointRef<N, T>::operator =(const const_PointRef<N, T> & other)
{
	//Need to provide separate operator = for const_PointRef and Point,
	//because copy assignment introduces ambiguity for Point,
	//which can be converted to either PointRef or const_PointRef.
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
	return *this;
}

template <std::size_t N, typename T>
PointRef<N, T> & PointRef<N, T>::operator =(const Point<N, T> & other)
{
	//Need to provide separate operator = for const_PointRef and Point,
	//because copy assignment signature introduces ambiguity for Point,
	//which can be converted to either PointRef or const_PointRef.
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
	return *this;
}

template <std::size_t N, typename T>
PointRef<N, T> & PointRef<N, T>::operator =(const T * other)
{
	std::copy(other, other + size(), m_coords);
	return *this;
}

template <std::size_t N, typename T>
T PointRef<N, T>::operator [](std::size_t i) const
{
	return coord(i);
}

template <std::size_t N, typename T>
T & PointRef<N, T>::operator [](std::size_t i)
{
	return coord(i);
}

template <std::size_t N, typename T>
T PointRef<N, T>::operator ()(std::size_t i) const
{
	return coord(i);
}

template <std::size_t N, typename T>
T & PointRef<N, T>::operator ()(std::size_t i)
{
	return coord(i);
}

template <std::size_t N, typename T>
T PointRef<N, T>::coord(std::size_t i) const
{
	GPX_ASSERT(i < size(), "index [" << i << "] is out of bounds");
	return m_coords[i];
}

template <std::size_t N, typename T>
T & PointRef<N, T>::coord(std::size_t i)
{
	GPX_ASSERT(i < size(), "index [" << i << "] is out of bounds");
	return m_coords[i];
}

template <std::size_t N, typename T>
std::size_t PointRef<N, T>::size() const
{
	return N;
}

template <std::size_t N, typename T>
const T * PointRef<N, T>::ptr() const
{
	return m_coords;
}

template <std::size_t N, typename T>
T * PointRef<N, T>::ptr()
{
	return m_coords;
}

/**
 * Dynamically sized point reference mimic.
 */
template <typename T>
class PointRef<SIZE_DYNAMIC, T> : public PointTrait<PointRef, SIZE_DYNAMIC, T, true>
{
	public:
		//PointRef(const PointRef & other) = default;

		PointRef(Point<SIZE_DYNAMIC, T> * vPtr);

		operator const_PointRef<SIZE_DYNAMIC, T> () const;

		//~PointRef() = default;

		/**
		 * Copy assignment. Data will be copied from other point.
		 * @param other point from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		PointRef<SIZE_DYNAMIC, T> & operator =(const PointRef<SIZE_DYNAMIC, T> & other);

		/**
		 * Point assignment. Data will be copied from other point.
		 * @param other point from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		PointRef<SIZE_DYNAMIC, T> & operator =(const const_PointRef<SIZE_DYNAMIC, T> & other);

		/**
		 * Point assignment. Data will be copied from other point.
		 * @param other point from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		PointRef<SIZE_DYNAMIC, T> & operator =(const Point<SIZE_DYNAMIC, T> & other);

		/**
		 * Array assignment. Data will be copied from location pointed by ptr.
		 * @param other location from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		PointRef<SIZE_DYNAMIC, T> & operator =(const T * other);

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
		 * Get point size.
		 * @return point size in terms of number of coordinates.
		 */
		std::size_t size() const;

		/**
		 * Resize point.
		 * @param size new size in terms of number of coordinates.
		 *
		 * @warning resize is destructive operation. Current values of point coordinates
		 * are lost and replaced by undefined ones.
		 *
		 * @warning resize operation invalidates coordinates pointer.
		 */
		void resize(std::size_t size);

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
		Point<SIZE_DYNAMIC, T> * m_vPtr;
};

template <typename T>
PointRef<SIZE_DYNAMIC, T>::PointRef(Point<SIZE_DYNAMIC, T> * vPtr):
	m_vPtr(vPtr)
{
}

template <typename T>
PointRef<SIZE_DYNAMIC, T>::operator const_PointRef<SIZE_DYNAMIC, T> () const
{
	return const_PointRef<SIZE_DYNAMIC, T>(m_vPtr);
}

template <typename T>
PointRef<SIZE_DYNAMIC, T> & PointRef<SIZE_DYNAMIC, T>::operator =(const PointRef<SIZE_DYNAMIC, T> & other)
{
	//self assignment branch not required here
	*m_vPtr = other;
	return *this;
}

template <typename T>
PointRef<SIZE_DYNAMIC, T> & PointRef<SIZE_DYNAMIC, T>::operator =(const const_PointRef<SIZE_DYNAMIC, T> & other)
{
	*m_vPtr = other;
	return *this;
}

template <typename T>
PointRef<SIZE_DYNAMIC, T> & PointRef<SIZE_DYNAMIC, T>::operator =(const Point<SIZE_DYNAMIC, T> & other)
{
	*m_vPtr = other;
	return *this;
}

template <typename T>
PointRef<SIZE_DYNAMIC, T> & PointRef<SIZE_DYNAMIC, T>::operator =(const T * other)
{
	*m_vPtr = other;
	return *this;
}

template <typename T>
T PointRef<SIZE_DYNAMIC, T>::operator [](std::size_t i) const
{
	return m_vPtr->operator [](i);
}

template <typename T>
T & PointRef<SIZE_DYNAMIC, T>::operator [](std::size_t i)
{
	return m_vPtr->operator [](i);
}

template <typename T>
T PointRef<SIZE_DYNAMIC, T>::operator ()(std::size_t i) const
{
	return m_vPtr->operator ()(i);
}

template <typename T>
T & PointRef<SIZE_DYNAMIC, T>::operator ()(std::size_t i)
{
	return m_vPtr->operator ()(i);
}

template <typename T>
T PointRef<SIZE_DYNAMIC, T>::coord(std::size_t i) const
{
	return m_vPtr->coord(i);
}

template <typename T>
T & PointRef<SIZE_DYNAMIC, T>::coord(std::size_t i)
{
	return m_vPtr->coord(i);
}

template <typename T>
std::size_t PointRef<SIZE_DYNAMIC, T>::size() const
{
	return m_vPtr->size();
}

template <typename T>
void PointRef<SIZE_DYNAMIC, T>::resize(std::size_t size)
{
	return m_vPtr->size(size);
}

template <typename T>
const T * PointRef<SIZE_DYNAMIC, T>::ptr() const
{
	return m_vPtr->ptr();
}

template <typename T>
T * PointRef<SIZE_DYNAMIC, T>::ptr()
{
	return m_vPtr->ptr();
}

/**
 * Two-dimensional point const reference mimic.
 */
template <typename T>
class PointRef<2, T> : public PointTrait<PointRef, 2, T, true>
{
	public:
		//PointRef(const PointRef & other) = default;

		PointRef(T * ptr);

		operator const_PointRef<2, T> () const;

		//~PointRef() = default;

		/**
		 * Copy assignment. Data will be copied from other point.
		 * @param other point from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		PointRef<2, T> & operator =(const PointRef<2, T> & other);

		/**
		 * Point assignment. Data will be copied from other point.
		 * @param other point from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		PointRef<2, T> & operator =(const const_PointRef<2, T> & other);

		/**
		 * Point assignment. Data will be copied from other point.
		 * @param other point from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		PointRef<2, T> & operator =(const Point<2, T> & other);

		/**
		 * Array assignment. Data will be copied from location pointed by ptr.
		 * @param other location from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		PointRef<2, T> & operator =(const T * other);

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
		 * Get point size.
		 * @return point size in terms of number of coordinates.
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
PointRef<2, T>::PointRef(T * ptr):
	m_coords(ptr)
{
}

template <typename T>
PointRef<2, T>::operator const_PointRef<2, T> () const
{
	return const_PointRef<2, T>(m_coords);
}

template <typename T>
PointRef<2, T> & PointRef<2, T>::operator =(const PointRef<2, T> & other)
{
	//self assignment branch not required here
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
	return *this;
}

template <typename T>
PointRef<2, T> & PointRef<2, T>::operator =(const const_PointRef<2, T> & other)
{
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
	return *this;
}

template <typename T>
PointRef<2, T> & PointRef<2, T>::operator =(const Point<2, T> & other)
{
	//Need to provide separate operator = for const_PointRef and Point,
	//because copy assignment introduces ambiguity for Point,
	//which can be converted to either PointRef or const_PointRef.
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
	return *this;
}

template <typename T>
PointRef<2, T> & PointRef<2, T>::operator =(const T * other)
{
	std::copy(other, other + size(), m_coords);
	return *this;
}

template <typename T>
T PointRef<2, T>::operator [](std::size_t i) const
{
	return coord(i);
}

template <typename T>
T & PointRef<2, T>::operator [](std::size_t i)
{
	return coord(i);
}

template <typename T>
T PointRef<2, T>::operator ()(std::size_t i) const
{
	return coord(i);
}

template <typename T>
T & PointRef<2, T>::operator ()(std::size_t i)
{
	return coord(i);
}

template <typename T>
T PointRef<2, T>::coord(std::size_t i) const
{
	GPX_ASSERT(i < size(), "index [" << i << "] is out of bounds");
	return m_coords[i];
}

template <typename T>
T & PointRef<2, T>::coord(std::size_t i)
{
	GPX_ASSERT(i < size(), "index [" << i << "] is out of bounds");
	return m_coords[i];
}

template <typename T>
T PointRef<2, T>::x() const
{
	return m_coords[0];
}

template <typename T>
void PointRef<2, T>::setX(T val)
{
	m_coords[0] = val;
}

template <typename T>
T PointRef<2, T>::y() const
{
	return m_coords[1];
}

template <typename T>
void PointRef<2, T>::setY(T val)
{
	m_coords[1] = val;
}

template <typename T>
std::size_t PointRef<2, T>::size() const
{
	return 2;
}

template <typename T>
const T * PointRef<2, T>::ptr() const
{
	return m_coords;
}

template <typename T>
T * PointRef<2, T>::ptr()
{
	return m_coords;
}

}
}

#endif // POINTREF_HPP
