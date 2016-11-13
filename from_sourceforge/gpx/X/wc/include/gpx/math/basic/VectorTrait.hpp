/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_BASIC_VECTORTRAIT_HPP_
#define GPX_X_MATH_BASIC_VECTORTRAIT_HPP_

#include "../functions.hpp"

#include <cmath>
#include <algorithm>

namespace gpx {
namespace math {
namespace basic {

/**
 * Backend implementation of gpx::math::VectorTrait<DERIVED, N, T, DIMSPEC>.
 */
template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
class VectorTrait
{
	protected:
		void add(gpx::math::const_VectorRef<N, T> other);

		void sub(gpx::math::const_VectorRef<N, T> other);

		void mul(T scalar);

		void mul(gpx::math::const_MatrixRef<N, N, T> matrix);

		void div(T scalar);

		void zero();

		void invert();

		void normalize();

		void rotate(T sin, T cos, std::size_t c1, std::size_t c2);

		void rotate(T angle, std::size_t c1, std::size_t c2);

		void minimize(const gpx::math::const_VectorRef<N, T> other);

		void swap(std::size_t c1, std::size_t c2);

		DERIVED<N, T> & derived();
};

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
void VectorTrait<DERIVED, N, T, DIMSPEC>::add(gpx::math::const_VectorRef<N, T> other)
{
	//decent compiler should unroll this loop
	for (std::size_t i = 0; i < derived().size(); i++)
		derived().coord(i) += other(i);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
void VectorTrait<DERIVED, N, T, DIMSPEC>::sub(gpx::math::const_VectorRef<N, T> other)
{
	//decent compiler should unroll this loop
	for (std::size_t i = 0; i < derived().size(); i++)
		derived().coord(i) -= other(i);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
void VectorTrait<DERIVED, N, T, DIMSPEC>::mul(T scalar)
{
	//decent compiler should unroll this loop
	for (std::size_t i = 0; i < derived().size(); i++)
		derived().coord(i) *= scalar;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
void VectorTrait<DERIVED, N, T, DIMSPEC>::mul(gpx::math::const_MatrixRef<N, N, T> matrix)
{
	gpx::math::Vector<N, T> copy(derived());
	for (std::size_t i = 0; i < derived().size(); i++) {
		derived().coord(i) = T();
		for (std::size_t j = 0; j < derived().size(); j++)
			derived().coord(i) += copy(j) * matrix(j, i);
	}
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
void VectorTrait<DERIVED, N, T, DIMSPEC>::div(T scalar)
{
	//decent compiler should unroll this loop
	for (std::size_t i = 0; i < derived().size(); i++)
		derived().coord(i) /= scalar;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
void VectorTrait<DERIVED, N, T, DIMSPEC>::zero()
{
	std::fill(derived().ptr(), derived().ptr() + derived().size(), T());
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
void VectorTrait<DERIVED, N, T, DIMSPEC>::invert()
{
	//decent compiler should unroll this loop
	for (std::size_t i = 0; i < derived().size(); i++)
		derived().coord(i) = -derived().coord(i);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
void VectorTrait<DERIVED, N, T, DIMSPEC>::normalize()
{
	div(derived().length());
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
void VectorTrait<DERIVED, N, T, DIMSPEC>::rotate(T sin, T cos, std::size_t c1, std::size_t c2)
{
	T v1, v2;

	v1 = derived().coord(c1);
	v2 = derived().coord(c2);

	derived().coord(c1) = (v1 * cos) - (v2 * sin);
	derived().coord(c2) = (v2 * cos) + (v1 * sin);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
void VectorTrait<DERIVED, N, T, DIMSPEC>::rotate(T angle, std::size_t c1, std::size_t c2)
{
	real_t sin, cos;
	gpx::math::sincos(angle, sin, cos);
	rotate(static_cast<T>(sin), static_cast<T>(cos), c1, c2);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
void VectorTrait<DERIVED, N, T, DIMSPEC>::minimize(gpx::math::const_VectorRef<N, T> other)
{
	int epsExp;
	int ptrExp[derived().size()];
	int dExp;
	T ptrSig[derived().size()];
	T epsilon = gpx::math::eps(other(0));
	for (std::size_t i = 1; i < derived().size(); i++)
		epsilon = std::max(epsilon, gpx::math::eps(other(i)));
	std::frexp(epsilon, & epsExp);
	for (std::size_t i = 0; i < derived().size(); i++)
		ptrSig[i] = std::frexp(derived().coord(i), & ptrExp[i]);
	int minExp = ptrExp[0];
	for (std::size_t i = 1; i < derived().size(); i++)
		minExp = std::min(minExp, ptrExp[i]);
	dExp = -epsExp + minExp;
	for (std::size_t i = 0; i < derived().size(); i++)
		derived().coord(i) = std::ldexp(ptrSig[i], ptrExp[i] - dExp);
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
void VectorTrait<DERIVED, N, T, DIMSPEC>::swap(std::size_t c1, std::size_t c2)
{
	std::swap(derived().coord(c1), derived().coord(c2));
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
DERIVED<N, T> & VectorTrait<DERIVED, N, T, DIMSPEC>::derived()
{
	return static_cast<DERIVED<N, T> & >(*this);
}

/**
 * Backend implementation of gpx::math::VectorTrait<DERIVED, 2, T, true>.
 */
template <template <std::size_t, typename> class DERIVED, typename T>
class VectorTrait<DERIVED, 2, T, true> : public VectorTrait<DERIVED, 2, T, false>
{
	typedef VectorTrait<DERIVED, 2, T, false> Parent;

	protected:
		using Parent::rotate;

		void rotate(T sin, T cos);

		void rotate(T angle);
};

template <template <std::size_t, typename> class DERIVED, typename T>
void VectorTrait<DERIVED, 2, T, true>::rotate(T sin, T cos)
{
	T v1 = Parent::derived().coord(0);
	T v2 = Parent::derived().coord(1);

	Parent::derived().coord(0) = (v1 * cos) - (v2 * sin);
	Parent::derived().coord(1) = (v2 * cos) + (v1 * sin);
}

template <template <std::size_t, typename> class DERIVED, typename T>
void VectorTrait<DERIVED, 2, T, true>::rotate(T angle)
{
	real_t sin, cos;
	gpx::math::sincos(angle, sin, cos);
	rotate(static_cast<T>(sin), static_cast<T>(cos));
}

}
}
}

#endif /* GPX_X_MATH_BASIC_CONST_VECTORPTR_HPP_ */
