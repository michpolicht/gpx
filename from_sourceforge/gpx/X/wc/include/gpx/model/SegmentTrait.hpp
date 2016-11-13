#ifndef SEGMENTTRAIT_HPP
#define SEGMENTTRAIT_HPP

#include "const_SegmentTrait.hpp"

namespace gpx {
namespace model {

template <template <std::size_t, typename> class DERIVED, std::size_t DIM, typename T>
class SegmentTrait : public const_SegmentTrait<DERIVED, DIM, T>
{
	typedef const_SegmentTrait<DERIVED, DIM, T> Parent;

	public:
		using Parent::first;

		math::PointRef<DIM, T> first();

		using Parent::second;

		math::PointRef<DIM, T> second();

		T & first(std::size_t i);

		T & second(std::size_t i);

	private:
		DERIVED<DIM, T> & derived();
};

template <template <std::size_t, typename> class DERIVED, std::size_t DIM, typename T>
math::PointRef<DIM, T> SegmentTrait<DERIVED, DIM, T>::first()
{
	return derived().firstPoint();
}

template <template <std::size_t, typename> class DERIVED, std::size_t DIM, typename T>
math::PointRef<DIM, T> SegmentTrait<DERIVED, DIM, T>::second()
{
	return derived().secondPoint();
}

template <template <std::size_t, typename> class DERIVED, std::size_t DIM, typename T>
T & SegmentTrait<DERIVED, DIM, T>::first(std::size_t i)
{
	return derived().firstPoint().coord(i);
}

template <template <std::size_t, typename> class DERIVED, std::size_t DIM, typename T>
T & SegmentTrait<DERIVED, DIM, T>::second(std::size_t i)
{
	return derived().secondPoint().coord(i);
}

template <template <std::size_t, typename> class DERIVED, std::size_t DIM, typename T>
DERIVED<DIM, T> & SegmentTrait<DERIVED, DIM, T>::derived()
{
	return static_cast<DERIVED<DIM, T> &>(*this);
}

}
}

#endif // SEGMENTTRAIT_HPP
