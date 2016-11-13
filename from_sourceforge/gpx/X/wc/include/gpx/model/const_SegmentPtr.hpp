#ifndef CONST_SEGMENTPTR_HPP
#define CONST_SEGMENTPTR_HPP

#include "const_SegmentTrait.hpp"
#include "Segment.hpp"
#include "SegmentPtr.hpp"

namespace gpx {
namespace model {

/**
 * Segment const pointer mimic. Segment consists of two points of arbitrary dimension and type.
 * @param DIM point dimension.
 * @param T point coordinates type.
 */
template <std::size_t DIM, typename T = real_t>
class const_SegmentPtr : private const_SegmentTrait<const_SegmentPtr, DIM, T>
{
	typedef const_SegmentTrait<const_SegmentPtr, DIM, T> Parent;
	friend class const_SegmentTrait<const_SegmentPtr, DIM, T>;

	public:
		/**
		 * Default constructor.
		 */
		const_SegmentPtr();

		/**
		 * Conversion constructor.
		 * @param seg segment pointer mimic.
		 */
		const_SegmentPtr(const SegmentPtr<DIM, T> & seg);

		/**
		 * Conversion constructor.
		 * @param seg segment.
		 */
		const_SegmentPtr(const Segment<DIM, T> * seg);

		/**
		 * Constructor.
		 * @param first coordinates of first point.
		 * @param second coordinates of second point.
		 */
		const_SegmentPtr(const T * firstPtr, const T * secondPtr);

		void setFirstPtr(const T * firstPtr);	//ok does not modify data, like const_iterator has ++ operator

		void setSecondPtr(const T * secondPtr);

		/**
		 * Check if null.
		 * @return @p true if any of pointers: first or second is null (0), @p false
		 * otherwise.
		 */
		bool isNull() const;

		const const_SegmentTrait<const_SegmentPtr, DIM, T> * operator ->() const;

		const const_SegmentTrait<const_SegmentPtr, DIM, T> & operator *() const;

	protected:
		math::const_PointRef<DIM, T> firstPoint() const;

		math::const_PointRef<DIM, T> secondPoint() const;

	private:
		const T * m_first;
		const T * m_second;
};

template <std::size_t DIM, typename T>
const_SegmentPtr<DIM, T>::const_SegmentPtr():
	m_first(0),
	m_second(0)
{
}

template <std::size_t DIM, typename T>
const_SegmentPtr<DIM, T>::const_SegmentPtr(const SegmentPtr<DIM, T> & seg):
	m_first(seg->first().ptr()),
	m_second(seg->second().ptr())
{
}

template <std::size_t DIM, typename T>
const_SegmentPtr<DIM, T>::const_SegmentPtr(const Segment<DIM, T> * seg):
	m_first(seg->first().ptr()),
	m_second(seg->second().ptr())
{
}

template <std::size_t DIM, typename T>
const_SegmentPtr<DIM, T>::const_SegmentPtr(const T * first, const T * second):
	m_first(first),
	m_second(second)
{
}

template <std::size_t DIM, typename T>
void const_SegmentPtr<DIM, T>::setFirstPtr(const T * first)
{
	m_first = first;
}

template <std::size_t DIM, typename T>
void const_SegmentPtr<DIM, T>::setSecondPtr(const T * second)
{
	m_second = second;
}

template <std::size_t DIM, typename T>
bool const_SegmentPtr<DIM, T>::isNull() const
{
	return (m_first == 0) || (m_second == 0);
}

template <std::size_t DIM, typename T>
const const_SegmentTrait<const_SegmentPtr, DIM, T> * const_SegmentPtr<DIM, T>::operator ->() const
{
	return this;
}

template <std::size_t DIM, typename T>
const const_SegmentTrait<const_SegmentPtr, DIM, T> & const_SegmentPtr<DIM, T>::operator *() const
{
	return *this;
}

template <std::size_t DIM, typename T>
math::const_PointRef<DIM, T> const_SegmentPtr<DIM, T>::firstPoint() const
{
	return m_first;
}

template <std::size_t DIM, typename T>
math::const_PointRef<DIM, T> const_SegmentPtr<DIM, T>::secondPoint() const
{
	return m_second;
}

}
}

#endif // CONST_SEGMENTPTR_HPP
