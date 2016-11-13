/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_CONST_VECTORREF_HPP_
#define GPX_X_MATH_CONST_VECTORREF_HPP_

#include "structures.hpp"

namespace gpx {
namespace math {

/**
 * N-dimensional vector const reference mimic.
 */
template <std::size_t N, typename T>
class const_VectorRef : public const_VectorTrait<const_VectorRef, N, T, true>
{
	public:
		//const_VectorRef(const const_VectorRef<N, T> & other) = default;

		/**
		 * Conversion constructor.
		 * @param ptr pointer to N-element array.
		 */
		const_VectorRef(const T * ptr);

		//~const_VectorRef() = default;

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
		 * Get vector size.
		 * @return vector size in terms of number of coordinates.
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
		void operator =(const const_VectorRef<N, T> & );

		const T * m_coords;
};

template <std::size_t N, typename T>
const_VectorRef<N, T>::const_VectorRef(const T * ptr):
	m_coords(ptr)
{
}

template <std::size_t N, typename T>
T const_VectorRef<N, T>::operator [](std::size_t i) const
{
	return coord(i);
}

template <std::size_t N, typename T>
T const_VectorRef<N, T>::operator ()(std::size_t i) const
{
	return coord(i);
}

template <std::size_t N, typename T>
T const_VectorRef<N, T>::coord(std::size_t i) const
{
	GPX_ASSERT(i < size(), "coord(" << i << ") is out of bounds");
	return m_coords[i];
}

template <std::size_t N, typename T>
std::size_t const_VectorRef<N, T>::size() const
{
	return N;
}

template <std::size_t N, typename T>
const T * const_VectorRef<N, T>::ptr() const
{
	return m_coords;
}

/**
 * Dynamically sized vector const reference mimic.
 */
template <typename T>
class const_VectorRef<SIZE_DYNAMIC, T> : public const_VectorTrait<const_VectorRef, SIZE_DYNAMIC, T, true>
{
	public:
		/**
		 * Constructor.
		 * @param vPtr pointer to vector object.
		 */
		explicit const_VectorRef(const Vector<SIZE_DYNAMIC, T> * vPtr);

		//const_VectorRef(const const_VectorRef<SIZE_DYNAMIC, T> & other) = default;

		//~const_VectorRef() = default;

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
		 * Get vector size.
		 * @return vector size in terms of number of coordinates.
		 */
		std::size_t size() const;

		/**
		 * Get amount of reserved memory.
		 * @return amount of excessively reserved memory as number of coordinates which can be
		 * stored without the need of memory reallocation.
		 */
		std::size_t reserved() const;

		/**
		 * Get const pointer pointing to coordinates.
		 * @return const pointer pointing to coordinates.
		 */
		const T * ptr() const;

	private:
		/**
		 * Copy assignment. Forbidden (const reference).
		 */
		void operator =(const const_VectorRef<SIZE_DYNAMIC, T> & );

		const Vector<SIZE_DYNAMIC, T> * m_vPtr;
};

template <typename T>
const_VectorRef<SIZE_DYNAMIC, T>::const_VectorRef(const Vector<SIZE_DYNAMIC, T> * vPtr):
	m_vPtr(vPtr)
{
}

template <typename T>
T const_VectorRef<SIZE_DYNAMIC, T>::operator [](std::size_t i) const
{
	return m_vPtr->coord(i);
}

template <typename T>
T const_VectorRef<SIZE_DYNAMIC, T>::operator ()(std::size_t i) const
{
	return m_vPtr->coord(i);
}

template <typename T>
T const_VectorRef<SIZE_DYNAMIC, T>::coord(std::size_t i) const
{
	return m_vPtr->coord(i);
}

template <typename T>
std::size_t const_VectorRef<SIZE_DYNAMIC, T>::size() const
{
	return m_vPtr->size();
}

template <typename T>
std::size_t const_VectorRef<SIZE_DYNAMIC, T>::reserved() const
{
	return m_vPtr->reserved();
}

template <typename T>
const T * const_VectorRef<SIZE_DYNAMIC, T>::ptr() const
{
	return m_vPtr->ptr();
}

/**
 * Two-dimensional vector const reference mimic.
 */
template <typename T>
class const_VectorRef<2, T> : public const_VectorTrait<const_VectorRef, 2, T, true>
{
	public:
		//const_VectorRef(const const_VectorRef<2, T> & other) = default;

		/**
		 * Conversion constructor.
		 * @param ptr pointer to 2-element array.
		 */
		const_VectorRef(const T * ptr);

		//~const_VectorRef() = default;

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
		 * Get vector size.
		 * @return vector size in terms of number of coordinates.
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
		void operator =(const const_VectorRef<2, T> & );

		const T * m_coords;
};

template <typename T>
const_VectorRef<2, T>::const_VectorRef(const T * ptr):
	m_coords(ptr)
{
}

template <typename T>
T const_VectorRef<2, T>::operator [](std::size_t i) const
{
	return coord(i);
}

template <typename T>
T const_VectorRef<2, T>::operator ()(std::size_t i) const
{
	return coord(i);
}

template <typename T>
T const_VectorRef<2, T>::coord(std::size_t i) const
{
	GPX_ASSERT(i < size(), "coord(" << i << ") is out of bounds");
	return m_coords[i];
}

template <typename T>
T const_VectorRef<2, T>::x() const
{
	return m_coords[0];
}

template <typename T>
T const_VectorRef<2, T>::y() const
{
	return m_coords[1];
}

template <typename T>
std::size_t const_VectorRef<2, T>::size() const
{
	return 2;
}

template <typename T>
const T * const_VectorRef<2, T>::ptr() const
{
	return m_coords;
}

}
}

#endif
