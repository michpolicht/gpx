#ifndef POINTTRAIT_HPP
#define POINTTRAIT_HPP

#include "const_PointTrait.hpp"

namespace gpx {
namespace math {

/**
 * Methods for N-dimensional DERIVED point of type T.
 */
template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
class PointTrait : public const_PointTrait<DERIVED, N, T, true>
{
	typedef PointTrait<DERIVED, N, T, DIMSPEC> Self;

	public:
		/**
		 * Translation. Translate point by given vector.
		 * @param vec vector to be added.
		 * @return self-reference to an object being translated.
		 */
		DERIVED<N, T> & translate(const_VectorRef<N, T> vec);

		/**
		 * Addition assignment. Alias of translate().
		 * @param vec vector to be added.
		 * @return self-reference to an object being assigned.
		 */
		DERIVED<N, T> & operator +=(const_VectorRef<N, T> vec);

	private:
		DERIVED<N, T> & derived();
};

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & PointTrait<DERIVED, N, T, DIMSPEC>::translate(const_VectorRef<N, T> vec)
{
	for (std::size_t i = 0; i < derived().size(); i++)
		derived().coord(i) += vec(i);
	return derived();
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & PointTrait<DERIVED, N, T, DIMSPEC>::operator +=(const_VectorRef<N, T> vec)
{
	return Self::translate(vec);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & PointTrait<DERIVED, N, T, DIMSPEC>::derived()
{
	return static_cast<DERIVED<N, T> & >(*this);
}

}
}

#endif // POINTTRAIT_HPP
