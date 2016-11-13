#ifndef POINT_HPP
#define POINT_HPP

#include "structures.hpp"

namespace gpx {
namespace math {

/**
 * N-dimensional point.
 */
template <std::size_t N, typename T>
class Point : public PointTrait<Point, N, T, true>
{
	public:
		/**
		 * Default constructor. Point will be initialized with default constructed values
		 * of type T (0.0 for double for example).
		 * @param num number of coordinates to initialize.
		 */
		explicit Point(std::size_t num = N);

		//Point(const Point<N, T> & other) = default;

		/**
		 * Constructor.
		 * @param val value to initialize point with.
		 * @param num number of coordinates to initialize.
		 */
		explicit Point(T val, std::size_t num = N);

		/**
		 * Constructor.
		 * @param ptr pointer from which data is going to be copied from.
		 * @param num number of coordinates to initialize.
		 */
		explicit Point(const T * ptr, std::size_t num = N);

		/**
		 * Constructor.
		 * @param other other point from which data is going to be copied.
		 */
		Point(const_PointRef<N, T> other);

		//~Point() = default;

		//Point<N, T> & operator =(const Point<N, T> & other) = default;

		/**
		 * Array assignment. Data will be copied from location pointed by ptr.
		 * @param other location from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		Point<N, T> & operator =(const T * other);

		/**
		 * Point assignment. Data will be copied from other point.
		 * @param other other point from which data is going to be copied.
		 * @return self-reference to an object being assigned.
		 */
		Point<N, T> & operator =(const_PointRef<N, T> other);

		/**
		 * Conversion to const_PointRef<N, T>.
		 */
		operator const_PointRef<N, T> () const;

		/**
		 * Conversion to PointRef<N, T>.
		 */
		operator PointRef<N, T> ();

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
		T m_coords[N];
};

template <std::size_t N, typename T>
Point<N, T>::Point(std::size_t num)
{
	GPX_ASSERT(num <= N, "Point(" << num << ") is out of bounds");
	std::fill(m_coords, m_coords + num, T());
}

template <std::size_t N, typename T>
Point<N, T>::Point(T val, std::size_t num)
{
	GPX_ASSERT(num <= N, "Point(T, " << num << ") is out of bounds");
	std::fill(m_coords, m_coords + num, val);
}

template <std::size_t N, typename T>
Point<N, T>::Point(const T * ptr, std::size_t num)
{
	GPX_ASSERT(num <= N, "Point(const T *, " << num << ") is out of bounds");
	std::copy(ptr, ptr + num, m_coords);
}

template <std::size_t N, typename T>
Point<N, T>::Point(const_PointRef<N, T> other)
{
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
}

template <std::size_t N, typename T>
Point<N, T> & Point<N, T>::operator =(const T * other)
{
	std::copy(other, other + size(), m_coords);
	return *this;
}

template <std::size_t N, typename T>
Point<N, T> & Point<N, T>::operator =(const_PointRef<N, T> other)
{
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
	return *this;
}

template <std::size_t N, typename T>
Point<N, T>::operator const_PointRef<N, T> () const
{
	return const_PointRef<N, T>(m_coords);
}

template <std::size_t N, typename T>
Point<N, T>::operator PointRef<N, T> ()
{
	return PointRef<N, T>(m_coords);
}

template <std::size_t N, typename T>
T Point<N, T>::operator [](std::size_t i) const
{
	return coord(i);
}

template <std::size_t N, typename T>
T & Point<N, T>::operator [](std::size_t i)
{
	return coord(i);
}

template <std::size_t N, typename T>
T Point<N, T>::operator ()(std::size_t i) const
{
	return coord(i);
}

template <std::size_t N, typename T>
T & Point<N, T>::operator ()(std::size_t i)
{
	return coord(i);
}

template <std::size_t N, typename T>
T Point<N, T>::coord(std::size_t i) const
{
	GPX_ASSERT(i < size(), "coord(" << i << ") is out of bounds");
	return m_coords[i];
}

template <std::size_t N, typename T>
T & Point<N, T>::coord(std::size_t i)
{
	GPX_ASSERT(i < size(), "index [" << i << "] is out of bounds");
	return m_coords[i];
}

template <std::size_t N, typename T>
std::size_t Point<N, T>::size() const
{
	return N;
}

template <std::size_t N, typename T>
const T * Point<N, T>::ptr() const
{
	return m_coords;
}

template <std::size_t N, typename T>
T * Point<N, T>::ptr()
{
	return m_coords;
}

/**
 * Dynamically sized point.
 *
 * @todo implement reserve.
 */
template <typename T>
class Point<SIZE_DYNAMIC, T> : public PointTrait<Point, SIZE_DYNAMIC, T, true>
{
	public:
		/**
		 * Copy constructor.
		 * @param other other point.
		 */
		Point(const Point<SIZE_DYNAMIC, T> & other);

		/**
		 * Constructor.
		 * @param other other point from which data is going to be copied.
		 */
		Point(const_PointRef<SIZE_DYNAMIC, T> other);

		/**
		 * Constructor. Point will be initialized with default constructed values
		 * of type T (0.0 for double for example).
		 * @param num size of point and number of coordinates to initialize.
		 */
		explicit Point(std::size_t num, std::size_t reserve = 0);

		/**
		 * Constructor.
		 * @param val value to initialize point with.
		 * @param num size of point and number of coordinates to initialize.
		 */
		Point(T val, std::size_t num, std::size_t reserve = 0);

		/**
		 * Constructor.
		 * @param ptr pointer from which data is going to be copied from.
		 * @param num size of point and number of coordinates to initialize.
		 */
		Point(const T * ptr, std::size_t num, std::size_t reserve = 0);

		/**
		 * Destructor.
		 */
		virtual ~Point();

		/**
		 * Copy assignment.
		 * @param other other point from which data is going to be copied.
		 * @return self-reference to an object being assigned.
		 */
		Point<SIZE_DYNAMIC, T> & operator =(const Point<SIZE_DYNAMIC, T> & other);

		/**
		 * Point assignment. Data will be copied from other point.
		 * @param other other point from which data is going to be copied.
		 * @return self-reference to an object being assigned.
		 */
		Point<SIZE_DYNAMIC, T> & operator =(const_PointRef<SIZE_DYNAMIC, T> other);

		/**
		 * Array assignment. Data will be copied from location pointed by ptr.
		 * @param other location from which data is going to be copied from.
		 * Amount of data copied depends on actual point size.
		 * @return self-reference to an object being assigned.
		 */
		Point<SIZE_DYNAMIC, T> & operator =(const T * other);

		/**
		 * Conversion to const_PointRef<SIZE_DYNAMIC, T>.
		 */
		operator const_PointRef<SIZE_DYNAMIC, T> () const;

		/**
		 * Conversion to PointRef<SIZE_DYNAMIC, T>.
		 */
		operator PointRef<SIZE_DYNAMIC, T> ();

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
		 * Get amount of reserved memory.
		 * @return amount of excessively reserved memory as number of coordinates which can be
		 * stored without the need of memory reallocation.
		 */
		std::size_t reserved() const;

		/**
		 * Reserve memory. Request may be scheduled for future realization or even ignored.
		 * Function is required to preserve point data.
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
		std::size_t m_size;
		std::size_t m_reserved;
		T * m_coords;
};

template <typename T>
Point<SIZE_DYNAMIC, T>::Point(const Point<SIZE_DYNAMIC, T> & other):
	m_size(other.size()),
	m_reserved(other.reserved())
{
	m_coords = new T[std::max(size(), reserved())];
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
}

template <typename T>
Point<SIZE_DYNAMIC, T>::Point(const_PointRef<SIZE_DYNAMIC, T> other):
	m_size(other.size()),
	m_reserved(other.reserved())
{
	m_coords = new T[std::max(size(), reserved())];
	std::copy(other.ptr(), other.ptr() + size(), m_coords);

}

template <typename T>
Point<SIZE_DYNAMIC, T>::Point(std::size_t num, std::size_t reserve):
	m_size(num),
	m_reserved(reserve)
{
	m_coords = new T[std::max(size(), reserved())];
	std::fill(m_coords, m_coords + size(), T());
}

template <typename T>
Point<SIZE_DYNAMIC, T>::Point(T val, std::size_t num, std::size_t reserve):
	m_size(num),
	m_reserved(reserve)
{
	m_coords = new T[std::max(size(), reserved())];
	std::fill(m_coords, m_coords + size(), val);
}

template <typename T>
Point<SIZE_DYNAMIC, T>::Point(const T * ptr, std::size_t num, std::size_t reserve):
	m_size(num),
	m_reserved(reserve)
{
	m_coords = new T[std::max(size(), reserved())];
	std::copy(ptr, ptr + size(), m_coords);
}

template <typename T>
Point<SIZE_DYNAMIC, T>::~Point()
{
	delete[] m_coords;
}

template <typename T>
Point<SIZE_DYNAMIC, T> & Point<SIZE_DYNAMIC, T>::operator =(const Point<SIZE_DYNAMIC, T> & other)
{
	//handle self assignment
	if (& other == this)
		return *this;
	resize(other.size());
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
	return *this;
}

template <typename T>
Point<SIZE_DYNAMIC, T> & Point<SIZE_DYNAMIC, T>::operator =(const_PointRef<SIZE_DYNAMIC, T> other)
{
	//handle self assignment (some weird cast may be performed)
	if (other.ptr() == this->ptr())
		return *this;
	resize(other.size());
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
	return *this;
}

template <typename T>
Point<SIZE_DYNAMIC, T> & Point<SIZE_DYNAMIC, T>::operator =(const T * other)
{
	//self assignment branch not required
	std::copy(other, other + size(), m_coords);
	return *this;
}

template <typename T>
Point<SIZE_DYNAMIC, T>::operator const_PointRef<SIZE_DYNAMIC, T> () const
{
	return const_PointRef<SIZE_DYNAMIC, T>(this);
}

template <typename T>
Point<SIZE_DYNAMIC, T>::operator PointRef<SIZE_DYNAMIC, T> ()
{
	return PointRef<SIZE_DYNAMIC, T>(this);
}

template <typename T>
T Point<SIZE_DYNAMIC, T>::operator [](std::size_t i) const
{
	return coord(i);
}

template <typename T>
T & Point<SIZE_DYNAMIC, T>::operator [](std::size_t i)
{
	return coord(i);
}

template <typename T>
T Point<SIZE_DYNAMIC, T>::operator ()(std::size_t i) const
{
	return coord(i);
}

template <typename T>
T & Point<SIZE_DYNAMIC, T>::operator ()(std::size_t i)
{
	return coord(i);
}

template <typename T>
T Point<SIZE_DYNAMIC, T>::coord(std::size_t i) const
{
	GPX_ASSERT(i < size(), "coord(" << i << ") is out of bounds");
	return m_coords[i];
}

template <typename T>
T & Point<SIZE_DYNAMIC, T>::coord(std::size_t i)
{
	GPX_ASSERT(i < size(), "coord(" << i << ") is out of bounds");
	return m_coords[i];
}

template <typename T>
std::size_t Point<SIZE_DYNAMIC, T>::size() const
{
	return m_size;
}

template <typename T>
void Point<SIZE_DYNAMIC, T>::resize(std::size_t p_size)
{
	if (p_size == size())
		return;
	//grow or shrink
	if (std::max(p_size, size()) > reserved()) {
		T * newCoords = new T[std::max(p_size, reserved())];
		delete[] m_coords;
		m_coords = newCoords;
	}
	m_size = p_size;
}

template <typename T>
std::size_t Point<SIZE_DYNAMIC, T>::reserved() const
{
	return m_reserved;
}

template <typename T>
void Point<SIZE_DYNAMIC, T>::reserve(std::size_t p_size)
{
	if (p_size <= size()) {
		//there's already more space allocated than requested
		m_reserved = p_size;
		return;
	}
	T * newCoords = new T[p_size];
	//conserve vector coordinates
	std::copy(m_coords, m_coords + size(), newCoords);
	delete[] m_coords;
	m_coords = newCoords;
	m_reserved = p_size;
}

template <typename T>
const T * Point<SIZE_DYNAMIC, T>::ptr() const
{
	return m_coords;
}

template <typename T>
T * Point<SIZE_DYNAMIC, T>::ptr()
{
	return m_coords;
}

/**
 * Two dimensional point.
 */
template <typename T>
class Point<2, T> : public PointTrait<Point, 2, T, true>
{
	public:
		/**
		 * Default constructor. Point will be initialized with default constructed values
		 * of type T (0.0 for double for example).
		 * @param num number of coordinates to initialize.
		 */
		explicit Point(std::size_t num = 2u);

		//Point(const Point<N, T> & other) = default;

		/**
		 * Constructor.
		 * @param other other point from which data is going to be copied.
		 */
		Point(const_PointRef<2, T> other);

		/**
		 * Constructor.
		 * @param val value to initialize point with.
		 * @param num number of coordinates to initialize.
		 */
		explicit Point(T val, std::size_t num = 2u);

		/**
		 * Constructor.
		 * @param ptr pointer from which data is going to be copied from.
		 * @param num number of coordinates to initialize.
		 */
		explicit Point(const T * ptr, std::size_t num = 2u);

		/**
		 * Constructor.
		 * @param x x coordinate.
		 * @param y y coordinate.
		 */
		Point(T x, T y);

		//~Point() = default;

		//Point<N, T> & operator =(const Point<N, T> & other) = default;

		/**
		 * Point assignment. Data will be copied from other point.
		 * @param other other point from which data is going to be copied.
		 * @return self-reference to an object being assigned.
		 */
		Point<2, T> & operator =(const_PointRef<2, T> other);

		/**
		 * Array assignment. Data will be copied from location pointed by ptr.
		 * @param other location from which data is going to be copied from.
		 * @return self-reference to an object being assigned.
		 */
		Point<2, T> & operator =(const T * other);

		/**
		 * Conversion to const_PointRef<2, T>.
		 */
		operator const_PointRef<2, T> () const;

		/**
		 * Conversion to PointRef<2, T>.
		 */
		operator PointRef<2, T> ();

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
		T m_coords[2];
};

template <typename T>
Point<2, T>::Point(std::size_t num)
{
	GPX_ASSERT(num <= 2, "Point(" << num << ") is out of bounds");
	std::fill(m_coords, m_coords + num, T());
}

template <typename T>
Point<2, T>::Point(const_PointRef<2, T> other)
{
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
}

template <typename T>
Point<2, T>::Point(T val, std::size_t num)
{
	GPX_ASSERT(num <= 2, "Point(T, " << num << ") is out of bounds");
	std::fill(m_coords, m_coords + num, val);
}

template <typename T>
Point<2, T>::Point(const T * ptr, std::size_t num)
{
	GPX_ASSERT(num <= 2, "Point(const T *, " << num << ") is out of bounds");
	std::copy(ptr, ptr + num, m_coords);
}

template <typename T>
Point<2, T>::Point(T x, T y)
{
	m_coords[0] = x;
	m_coords[1] = y;
}

template <typename T>
Point<2, T> & Point<2, T>::operator =(const_PointRef<2, T> other)
{
	std::copy(other.ptr(), other.ptr() + size(), m_coords);
	return *this;
}

template <typename T>
Point<2, T> & Point<2, T>::operator =(const T * other)
{
	std::copy(other, other + size(), m_coords);
	return *this;
}

template <typename T>
Point<2, T>::operator const_PointRef<2, T> () const
{
	return const_PointRef<2, T>(m_coords);
}

template <typename T>
Point<2, T>::operator PointRef<2, T> ()
{
	return PointRef<2, T>(m_coords);
}

template <typename T>
T Point<2, T>::operator [](std::size_t i) const
{
	return coord(i);
}

template <typename T>
T & Point<2, T>::operator [](std::size_t i)
{
	return coord(i);
}

template <typename T>
T Point<2, T>::operator ()(std::size_t i) const
{
	return coord(i);
}

template <typename T>
T & Point<2, T>::operator ()(std::size_t i)
{
	return coord(i);
}

template <typename T>
T Point<2, T>::coord(std::size_t i) const
{
	GPX_ASSERT(i < size(), "coord(" << i << ") is out of bounds");
	return m_coords[i];
}

template <typename T>
T & Point<2, T>::coord(std::size_t i)
{
	GPX_ASSERT(i < size(), "index [" << i << "] is out of bounds");
	return m_coords[i];
}

template <typename T>
T Point<2, T>::x() const
{
	return m_coords[0];
}

template <typename T>
void Point<2, T>::setX(T val)
{
	m_coords[0] = val;
}

template <typename T>
T Point<2, T>::y() const
{
	return m_coords[1];
}

template <typename T>
void Point<2, T>::setY(T val)
{
	m_coords[1] = val;
}

template <typename T>
std::size_t Point<2, T>::size() const
{
	return 2;
}

template <typename T>
const T * Point<2, T>::ptr() const
{
	return m_coords;
}

template <typename T>
T * Point<2, T>::ptr()
{
	return m_coords;
}

}
}

#endif // POINT_HPP
