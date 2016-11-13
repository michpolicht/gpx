#ifndef SEGMENTPTR_HPP
#define SEGMENTPTR_HPP

#include "SegmentTrait.hpp"

namespace gpx {
namespace model {

/**
 * Segment pointer mimic. Segment holds two points of arbitrary dimension and type.
 * @param DIM point dimension.
 * @param T point coordinates type.
 */
template <std::size_t DIM, typename T = real_t>
class SegmentPtr : private SegmentTrait<SegmentPtr, DIM, T>
{
	typedef SegmentTrait<SegmentPtr, DIM, T> Parent;
	friend class SegmentTrait<SegmentPtr, DIM, T>;
	friend class const_SegmentTrait<SegmentPtr, DIM, T>;

	public:
		/**
		 * Default constructor.
		 */
		SegmentPtr();

		/**
		 * Conversion constructor.
		 * @param seg segment.
		 */
		SegmentPtr(Segment<DIM, T> * seg);

		/**
		 * Constructor.
		 * @param first coordinates of first point.
		 * @param second coordinates of second point.
		 */
		SegmentPtr(T * firstPtr, T * secondPtr);

		void setFirstPtr(T * firstPtr);

		void setSecondPtr(T * secondPtr);

		/**
		 * Check if null.
		 * @return @p true if any of pointers: first or second is null (0), @p false
		 * otherwise.
		 */
		bool isNull() const;

		const SegmentTrait<SegmentPtr, DIM, T> * operator ->() const;

		SegmentTrait<SegmentPtr, DIM, T> * operator ->();

		const SegmentTrait<SegmentPtr, DIM, T> & operator *() const;

		SegmentTrait<SegmentPtr, DIM, T> & operator *();

	protected:
		math::const_PointRef<DIM, T> firstPoint() const;

		math::PointRef<DIM, T> firstPoint();

		math::const_PointRef<DIM, T> secondPoint() const;

		math::PointRef<DIM, T> secondPoint();

	private:
		T * m_first;
		T * m_second;
};

template <std::size_t DIM, typename T>
SegmentPtr<DIM, T>::SegmentPtr()
{
}

template <std::size_t DIM, typename T>
SegmentPtr<DIM, T>::SegmentPtr(Segment<DIM, T> * seg):
	m_first(seg->first().ptr()),
	m_second(seg->second().ptr())
{
}

template <std::size_t DIM, typename T>
SegmentPtr<DIM, T>::SegmentPtr(T * first, T * second):
	Parent(first, second)
{
}

template <std::size_t DIM, typename T>
void SegmentPtr<DIM, T>::setFirstPtr(T * first)
{
	m_first = first;
}

template <std::size_t DIM, typename T>
void SegmentPtr<DIM, T>::setSecondPtr(T * second)
{
	m_second = second;
}

template <std::size_t DIM, typename T>
bool SegmentPtr<DIM, T>::isNull() const
{
	return (m_first == 0) || (m_second == 0);
}

template <std::size_t DIM, typename T>
const SegmentTrait<SegmentPtr, DIM, T> * SegmentPtr<DIM, T>::operator ->() const
{
	return this;
}

template <std::size_t DIM, typename T>
SegmentTrait<SegmentPtr, DIM, T> * SegmentPtr<DIM, T>::operator ->()
{
	return this;
}

template <std::size_t DIM, typename T>
const SegmentTrait<SegmentPtr, DIM, T> & SegmentPtr<DIM, T>::operator *() const
{
	return *this;
}

template <std::size_t DIM, typename T>
SegmentTrait<SegmentPtr, DIM, T> & SegmentPtr<DIM, T>::operator *()
{
	return *this;
}

template <std::size_t DIM, typename T>
math::const_PointRef<DIM, T> SegmentPtr<DIM, T>::firstPoint() const
{
	return m_first;
}

template <std::size_t DIM, typename T>
math::PointRef<DIM, T> SegmentPtr<DIM, T>::firstPoint()
{
	return m_first;
}

template <std::size_t DIM, typename T>
math::const_PointRef<DIM, T> SegmentPtr<DIM, T>::secondPoint() const
{
	return m_second;
}

template <std::size_t DIM, typename T>
math::PointRef<DIM, T> SegmentPtr<DIM, T>::secondPoint()
{
	return m_second;
}

}
}

#endif // SEGMENTPTR_HPP
