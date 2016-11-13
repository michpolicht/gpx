#ifndef CONST_POINTREF_HPP
#define CONST_POINTREF_HPP

#include "structures.hpp"

namespace gpx {
namespace math {

/**
 * N-dimensional point const reference mimic.
 */
template <std::size_t N, typename T>
class const_PointRef : public const_PointTrait<const_PointRef, N, T, true>
{
	public:
		//const_PointRef(const const_PointRef<N, T> & other) = default;

		/**
		 * Constructor.
		 * @param ptr pointer to N-element array.
		 */
		const_PointRef(const T * ptr);

		//~const_PointRef() = default;

		/**
		 * Individual coordinate access over subscript operator (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T operator [](std::size_t i) const; //if conversion operator to T * is enabled, then default type for subscript access is int, so explicit conversion to std::size_t is required to call this version (provide T operator [](int i) in such case).

		/**
		 * Individual coordinate access over function call operator (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T operator ()(std::size_t i) const;

		/**
		 * Individual coordinate access (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T coord(std::size_t i) const;

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

	private:
		/**
		 * Copy assignment. Forbidden (const reference).
		 */
		void operator =(const_PointRef<N, T> & );

		const T * m_coords;
};

template <std::size_t N, typename T>
const_PointRef<N, T>::const_PointRef(const T * ptr):
	m_coords(ptr)
{
}

template <std::size_t N, typename T>
const T * const_PointRef<N, T>::ptr() const
{
	return m_coords;
}

template <std::size_t N, typename T>
T const_PointRef<N, T>::operator [](std::size_t i) const
{
	return coord(i);
}

template <std::size_t N, typename T>
T const_PointRef<N, T>::operator ()(std::size_t i) const
{
	return coord(i);
}

template <std::size_t N, typename T>
T const_PointRef<N, T>::coord(std::size_t i) const
{
	GPX_ASSERT(i < size(), "coord(" << i << ") is out of bounds");
	return m_coords[i];
}

template <std::size_t N, typename T>
std::size_t const_PointRef<N, T>::size() const
{
	return N;
}

/**
 * Dynamically sized point const reference mimic.
 */
template <typename T>
class const_PointRef<SIZE_DYNAMIC, T> : public const_PointTrait<const_PointRef, SIZE_DYNAMIC, T, true>
{
	public:
		/**
		 * Constructor.
		 * @param vPtr pointer to point object.
		 */
		const_PointRef(const Point<SIZE_DYNAMIC, T> * vPtr);

		//const_PointRef(const const_PointRef<SIZE_DYNAMIC, T> & other) = default;

		//~const_PointRef() = default;

		/**
		 * Individual coordinate access over subscript operator (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T operator [](std::size_t i) const; //if conversion operator to T * is enabled, then default type for subscript access is int, so explicit conversion to std::size_t is required to call this version (provide T operator [](int i) in such case).

		/**
		 * Individual coordinate access over function call operator (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T operator ()(std::size_t i) const;

		/**
		 * Individual coordinate access (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T coord(std::size_t i) const;

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

	private:
		/**
		 * Copy assignment. Forbidden (const reference).
		 */
		void operator =(const_PointRef<SIZE_DYNAMIC, T> & );

		const Point<SIZE_DYNAMIC, T> * m_vPtr;
};

template <typename T>
const_PointRef<SIZE_DYNAMIC, T>::const_PointRef(const Point<SIZE_DYNAMIC, T> * vPtr):
	m_vPtr(vPtr)
{
}

template <typename T>
const T * const_PointRef<SIZE_DYNAMIC, T>::ptr() const
{
	return m_vPtr->ptr();
}

template <typename T>
T const_PointRef<SIZE_DYNAMIC, T>::operator [](std::size_t i) const
{
	return m_vPtr->coord(i);
}

template <typename T>
T const_PointRef<SIZE_DYNAMIC, T>::operator ()(std::size_t i) const
{
	return m_vPtr->coord(i);
}

template <typename T>
T const_PointRef<SIZE_DYNAMIC, T>::coord(std::size_t i) const
{
	return m_vPtr->coord(i);
}

template <typename T>
std::size_t const_PointRef<SIZE_DYNAMIC, T>::size() const
{
	return m_vPtr->size();
}

/**
 * Two-dimensional point const reference mimic.
 */
template <typename T>
class const_PointRef<2, T> : public const_PointTrait<const_PointRef, 2, T, true>
{
	public:
		//const_PointRef(const const_PointRef<2, T> & other) = default;

		/**
		 * Constructor.
		 * @param ptr pointer to 2-element array.
		 */
		const_PointRef(const T * ptr);

		//~const_PointRef() = default;

		/**
		 * Individual coordinate access over subscript operator (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T operator [](std::size_t i) const; //if conversion operator to T * is enabled, then default type for subscript access is int, so explicit conversion to std::size_t is required to call this version (provide T operator [](int i) in such case).

		/**
		 * Individual coordinate access over function call operator (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T operator ()(std::size_t i) const;

		/**
		 * Individual coordinate access (const version).
		 * @param i index.
		 * @return value of i-th coordinate.
		 */
		T coord(std::size_t i) const;

		/**
		 * Get x coordinate. Alias of coord(0) const.
		 * @return value of x coordinate.
		 */
		T x() const;

		/**
		 * Get y coordinate. Alias of coord(0) const.
		 * @return value of y coordinate.
		 */
		T y() const;

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

	private:
		/**
		 * Copy assignment. Forbidden (const reference).
		 */
		void operator =(const const_PointRef<2, T> & );

		const T * m_coords;
};

template <typename T>
const_PointRef<2, T>::const_PointRef(const T * ptr):
	m_coords(ptr)
{
}

template <typename T>
const T * const_PointRef<2, T>::ptr() const
{
	return m_coords;
}

template <typename T>
T const_PointRef<2, T>::operator [](std::size_t i) const
{
	return coord(i);
}

template <typename T>
T const_PointRef<2, T>::operator ()(std::size_t i) const
{
	return coord(i);
}

template <typename T>
T const_PointRef<2, T>::coord(std::size_t i) const
{
	GPX_ASSERT(i < size(), "coord(" << i << ") is out of bounds");
	return m_coords[i];
}

template <typename T>
T const_PointRef<2, T>::x() const
{
	return m_coords[0];
}

template <typename T>
T const_PointRef<2, T>::y() const
{
	return m_coords[1];
}

template <typename T>
std::size_t const_PointRef<2, T>::size() const
{
	return 2;
}

}
}

#endif // CONST_POINTREF_HPP
