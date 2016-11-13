/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MODEL_SEGMENT_HPP_
#define GPX_X_MODEL_SEGMENT_HPP_

#include "SegmentTrait.hpp"

namespace gpx {
namespace model {

template <std::size_t DIM, typename T = real_t>
class Segment : public SegmentTrait<Segment, DIM, T>
{
	typedef SegmentTrait<Segment, DIM, T> Parent;
	friend class SegmentTrait<Segment, DIM, T>;
	friend class const_SegmentTrait<Segment, DIM, T>;

	public:
		Segment(math::const_PointRef<DIM, T> first, math::const_PointRef<DIM, T> second);

	protected:
		math::const_PointRef<DIM, T> firstPoint() const;

		math::PointRef<DIM, T> firstPoint();

		math::const_PointRef<DIM, T> secondPoint() const;

		math::PointRef<DIM, T> secondPoint();

	private:
		math::Point<DIM, T> m_first;
		math::Point<DIM, T> m_second;
};

template <std::size_t DIM, typename T>
Segment<DIM, T>::Segment(math::const_PointRef<DIM, T> first, math::const_PointRef<DIM, T> second):
	m_first(first),
	m_second(second)
{
}

template <std::size_t DIM, typename T>
math::const_PointRef<DIM, T> Segment<DIM, T>::firstPoint() const
{
	return m_first;
}

template <std::size_t DIM, typename T>
math::PointRef<DIM, T> Segment<DIM, T>::firstPoint()
{
	return m_first;
}

template <std::size_t DIM, typename T>
math::const_PointRef<DIM, T> Segment<DIM, T>::secondPoint() const
{
	return m_second;
}

template <std::size_t DIM, typename T>
math::PointRef<DIM, T> Segment<DIM, T>::secondPoint()
{
	return m_second;
}

}
}

#endif /* GPX_X_MODEL_SEGMENT_HPP_ */
