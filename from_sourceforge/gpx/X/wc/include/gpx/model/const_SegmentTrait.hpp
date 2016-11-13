#ifndef CONST_SEGMENTTRAIT_HPP
#define CONST_SEGMENTTRAIT_HPP

#include "../math/structures.hpp"

namespace gpx {
namespace model {

template <template <std::size_t, typename> class DERIVED, std::size_t DIM, typename T>
class const_SegmentTrait
{
	public:
		math::const_PointRef<DIM, T> first() const;

		math::const_PointRef<DIM, T> second() const;

		T first(std::size_t i) const;

		T second(std::size_t i) const;

	private:
		const DERIVED<DIM, T> & derived() const;
};

template <template <std::size_t, typename> class DERIVED, std::size_t DIM, typename T>
math::const_PointRef<DIM, T> const_SegmentTrait<DERIVED, DIM, T>::first() const
{
	return derived().firstPoint();
}

template <template <std::size_t, typename> class DERIVED, std::size_t DIM, typename T>
math::const_PointRef<DIM, T> const_SegmentTrait<DERIVED, DIM, T>::second() const
{
	return derived().secondPoint();
}

template <template <std::size_t, typename> class DERIVED, std::size_t DIM, typename T>
T const_SegmentTrait<DERIVED, DIM, T>::first(std::size_t i) const
{
	return derived().firstPoint().coord(i);
}

template <template <std::size_t, typename> class DERIVED, std::size_t DIM, typename T>
T const_SegmentTrait<DERIVED, DIM, T>::second(std::size_t i) const
{
	return derived().secondPoint().coord(i);
}

template <template <std::size_t, typename> class DERIVED, std::size_t DIM, typename T>
const DERIVED<DIM, T> & const_SegmentTrait<DERIVED, DIM, T>::derived() const
{
	return static_cast<const DERIVED<DIM, T> &>(*this);
}

}
}

#endif // CONST_SEGMENTTRAIT_HPP
