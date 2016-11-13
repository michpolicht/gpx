#ifndef CONST_POINTTRAIT_HPP
#define CONST_POINTTRAIT_HPP

#include "structures.hpp"
#include "functions.hpp"

namespace gpx {
namespace math {

/**
 * Const methods for N-dimensional DERIVED point of type T.
 */
template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
class const_PointTrait
{
	typedef const_PointTrait<DERIVED, N, T, DIMSPEC> Self;

	public:
		/**
		 * Equality operator.
		 * @param other other point.
		 * @return @p true if all coordinates of this point are equal to the corresponding
		 * coordinates of other point, @p false otherwise.
		 */
		bool operator ==(const_PointRef<N, T> other) const;

		/**
		 * Inequality operator.
		 * @param other other point.
		 * @return @p true if all coordinates of this point are equal to the corresponding
		 * coordinates of other point, @p false otherwise.
		 */
		bool operator !=(const_PointRef<N, T> other) const;

		/**
		 * Almost equal.
		 * @return @p true if all coordinates are almost equal to coordinates
		 * of other point, @p false otherwise.
		 *
		 * @note ale() is stronger than ape().
		 */
		bool ale(const_PointRef<N, T> other) const;

		/**
		 * Approximately equal.
		 * @return @p true if all coordinates are approximately equal to coordinates
		 * of other point, @p false otherwise.
		 *
		 * @note ale() is stronger than ape().
		 */
		bool ape(const_PointRef<N, T> other) const;

		/**
		 * Distance from zero point. Provided for convenience. Result is the
		 * same as calling diff(Point<N, T>()).
		 * @return difference between this point and point with zero coordinates.
		 */
		Vector<N, T> diff() const;

		/**
		 * Difference.
		 * @param other point which coordinates should be subtracted.
		 * @return difference between this and other point coordinates.
		 */
		Vector<N, T> diff(const_PointRef<N, T> other) const;

		/**
		 * Difference. Alias of diff().
		 * @param other point which coordinates should be subtracted.
		 * @return difference between this and other point coordinates.
		 */
		Vector<N, T> operator -(const_PointRef<N, T> other) const;

		/**
		 * Translation.
		 * @param vec vector by which point should be translated.
		 * @return point, which is a translation of this point.
		 */
		Point<N, T> translation(const_VectorRef<N, T> vec) const;

		/**
		 * Translation. Alias of translation().
		 * @param vec vector by which point should be translated.
		 * @return point, which is a translation of this point.
		 */
		Point<N, T> operator +(const_VectorRef<N, T> vec) const;

	private:
		const DERIVED<N, T> & derived() const;
};

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_PointTrait<DERIVED, N, T, DIMSPEC>::operator ==(const_PointRef<N, T> other) const
{
	return std::equal(derived().ptr(), derived().ptr() + derived().size(), other.ptr());
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_PointTrait<DERIVED, N, T, DIMSPEC>::operator !=(const_PointRef<N, T> other) const
{
	return !std::equal(derived().ptr(), derived().ptr() + derived().size(), other.ptr());
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_PointTrait<DERIVED, N, T, DIMSPEC>::ale(const_PointRef<N, T> other) const
{
	for (std::size_t i = 0; i < derived().size(); i++)
		if (!gpx::math::ale(derived().coord(i), other.coord(i)))
			return false;
	return true;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_PointTrait<DERIVED, N, T, DIMSPEC>::ape(const_PointRef<N, T> other) const
{
	for (std::size_t i = 0; i < derived().size(); i++)
		if (!gpx::math::ape(derived().coord(i), other.coord(i)))
			return false;
	return true;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_PointTrait<DERIVED, N, T, DIMSPEC>::diff() const
{
	return gpx::math::Vector<N, T>(derived().ptr(), derived().size());
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_PointTrait<DERIVED, N, T, DIMSPEC>::diff(const_PointRef<N, T> other) const
{
	gpx::math::Vector<N, T> result(derived().ptr(), derived().size());
	for (std::size_t i = 0; i < derived().size(); i++)
		result(i) -= other(i);
	return result;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Vector<N, T> const_PointTrait<DERIVED, N, T, DIMSPEC>::operator -(const_PointRef<N, T> other) const
{
	return Self::diff(other);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Point<N, T> const_PointTrait<DERIVED, N, T, DIMSPEC>::translation(const_VectorRef<N, T> vec) const
{
	Point<N, T> result(derived());
	result += vec;
	return result;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
Point<N, T> const_PointTrait<DERIVED, N, T, DIMSPEC>::operator +(const_VectorRef<N, T> vec) const
{
	return Self::translation(vec);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
const DERIVED<N, T> & const_PointTrait<DERIVED, N, T, DIMSPEC>::derived() const
{
	return static_cast<const DERIVED<N, T> & >(*this);
}

}
}

#endif // CONST_POINTTRAIT_HPP
