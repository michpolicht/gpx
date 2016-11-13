/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_BASIC_CONST_VECTORTRAIT_HPP_
#define GPX_X_MATH_BASIC_CONST_VECTORTRAIT_HPP_

#include "traits.hpp"

#include "../functions.hpp"

#include <cmath>
#include <algorithm>

namespace gpx {
namespace math {
namespace basic {

/**
 * Backend implementation of gpx::math::const_VectorTrait<DERIVED, N, T, DIMSPEC>.
 */
template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
class const_VectorTrait
{
	protected:
		bool operator ==(gpx::math::const_VectorRef<N, T> other) const;

//		bool operator ==(T val) const;

		bool operator !=(gpx::math::const_VectorRef<N, T> other) const;

//		bool operator !=(T val) const;

		gpx::math::Vector<N, T> inverse() const;

		gpx::math::Vector<N, T> sum(gpx::math::const_VectorRef<N, T> other) const;

		gpx::math::Vector<N, T> diff(gpx::math::const_VectorRef<N, T> other) const;

		gpx::math::Vector<N, T> prod(T scalar) const;

		gpx::math::Vector<N, T> prod(gpx::math::const_MatrixRef<N, N, T> matrix) const;

		gpx::math::Vector<N, T> quot(T scalar) const;

		T dot(gpx::math::const_VectorRef<N, T> other) const;

		T dot() const;

		T length() const;

		gpx::math::Vector<N, T> versor() const;

		T det(gpx::math::const_VectorRef<N, T> other, std::size_t c1, std::size_t c2) const;

		gpx::math::Vector<N, T> cross(gpx::math::const_VectorRef<N, T> * others) const;

		gpx::math::Vector<N, T> ccross(gpx::math::const_VectorRef<N, T> * others) const;

		bool ape(gpx::math::const_VectorRef<N, T> other) const;

//		bool ape(T val) const;

		bool ale(gpx::math::const_VectorRef<N, T> other) const;

//		bool ale(T val) const;

		bool isZero() const;

		bool apeZero() const;

		bool aleZero() const;

		gpx::math::Vector<N, T> minimal(gpx::math::const_VectorRef<N, T> other) const;

		gpx::math::Vector<N, T> rotated(T sin, T cos, std::size_t c1, std::size_t c2) const;

		gpx::math::Vector<N, T> rotated(T angle, std::size_t c1, std::size_t c2) const;

		const DERIVED<N, T> & derived() const;
};

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_VectorTrait<DERIVED, N, T, DIMSPEC>::operator ==(gpx::math::const_VectorRef<N, T> other) const
{
	return std::equal(derived().ptr(), derived().ptr() + derived().size(), other.ptr());
}

//template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
//inline
//bool const_VectorMethods<DERIVED, N, T, DIMSPEC>::operator ==(T val) const
//{
//	for (std::size_t i = 0; i < size(); i++)
//		if (Parent::coord(i) != val)
//			return false;
//	return true;
//}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_VectorTrait<DERIVED, N, T, DIMSPEC>::operator !=(gpx::math::const_VectorRef<N, T> other) const
{
	return !std::equal(derived().ptr(), derived().ptr() + derived().size(), other.ptr());
}

//template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
//inline
//bool const_VectorMethods<DERIVED, N, T, DIMSPEC>::operator !=(T val) const
//{
//	for (std::size_t i = 0; i < size(); i++)
//		if (Parent::coord(i) != val)
//			return true;
//	return false;
//}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::inverse() const
{
	gpx::math::Vector<N, T> result(derived());
	result.invert();
	return result;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::sum(gpx::math::const_VectorRef<N, T> other) const
{
	gpx::math::Vector<N, T> result(derived());
	result += other;
	return result;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::diff(gpx::math::const_VectorRef<N, T> other) const
{
	gpx::math::Vector<N, T> result(derived());
	result -= other;
	return result;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::prod(T scalar) const
{
	gpx::math::Vector<N, T> result(derived());
	result *= scalar;
	return result;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::prod(gpx::math::const_MatrixRef<N, N, T> matrix) const
{
	gpx::math::Vector<N, T> result(derived());
	result *= matrix;
	return result;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::quot(T scalar) const
{
	gpx::math::Vector<N, T> result(derived());
	result /= scalar;
	return result;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
T const_VectorTrait<DERIVED, N, T, DIMSPEC>::dot(gpx::math::const_VectorRef<N, T> other) const
{
	T result = T();
	for (std::size_t i = 0; i < derived().size(); i++)
		result += derived().coord(i) * other.coord(i);
	return result;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
T const_VectorTrait<DERIVED, N, T, DIMSPEC>::dot() const
{
	return dot(derived());
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
T const_VectorTrait<DERIVED, N, T, DIMSPEC>::length() const
{
	return std::sqrt(dot());
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::versor() const
{
	gpx::math::Vector<N, T> result(derived());
	result.div(length());
	return result;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
T const_VectorTrait<DERIVED, N, T, DIMSPEC>::det(gpx::math::const_VectorRef<N, T> other, std::size_t c1, std::size_t c2) const
{
	return (derived().coord(c1) * other.coord(c2)) - (derived().coord(c2) * other.coord(c1));
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::cross(gpx::math::const_VectorRef<N, T> * others) const
{
	//c0  a0 b0 ... z0
	//c1  a1 b1 ... z1
	//c2  a2 b2 ... z2
	//.   .  .  ... .
	//cN  aN bN ... zN
	//resulting vector is [+1 * det(minor(c0)), -1 * det(minor(c1)), +1 * det(minor(c2)), ..., +/-1 * det(minor(cN))]

	gpx::math::Vector<N, T> result = VectorTraits<N, T>::MakeUninitializedVector(derived().size());
	typename MatrixTraits<N, N, T>::MatrixMinor m(derived().size() - 1, derived().size() - 1);

	//fill matrix for minor c0
	for (std::size_t c = 0; c < derived().size() - 1; c++) {
		m(c, 0) = derived().coord(c + 1);
		for (std::size_t n = 0; n < derived().size() - 2; n++)
			m(c, n + 1) = others[n].coord(c + 1);
	}
	result[0] = m.det();

	//considering minor c + 1 (c1 for c = 0)
	for (std::size_t c = 0; c < derived().size() - 1; c++) {
		//overwrite row c
		m(c, 0) = derived().coord(c);
		for (std::size_t n = 0; n < derived().size() - 2; n++)
			m(c, n + 1) = others[n].coord(c);
		if (c % 2)	//minor(c1) for c = 0, minor(c2) for c = 2, ..., % 2 = 0 -> else block
			result[c + 1] = m.det();	//minor(c2), minor(c4), ...
		else
			result[c + 1] = -m.det();	//minor(c1), minor(c3), ...
	}

	return result;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::ccross(gpx::math::const_VectorRef<N, T> * others) const
{
	gpx::math::Vector<N, T> result = cross(others);
	result.invert();
	return result;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_VectorTrait<DERIVED, N, T, DIMSPEC>::ape(gpx::math::const_VectorRef<N, T> other) const
{
	for (std::size_t i = 0; i < derived().size(); i++)
		if (!gpx::math::ape(derived().coord(i), other.coord(i)))
			return false;
	return true;
}

//template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
//inline
//bool const_VectorMethods<DERIVED, N, T, DIMSPEC>::ape(T val) const
//{
//	for (std::size_t i = 0; i < size(); i++)
//		if (!gpx::math::ape(coord(i), val))
//			return false;
//	return true;
//}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_VectorTrait<DERIVED, N, T, DIMSPEC>::ale(gpx::math::const_VectorRef<N, T> other) const
{
	for (std::size_t i = 0; i < derived().size(); i++)
		if (!gpx::math::ale(derived().coord(i), other.coord(i)))
			return false;
	return true;
}

//template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
//inline
//bool const_VectorMethods<DERIVED, N, T, DIMSPEC>::ale(T val) const
//{
//	for (std::size_t i = 0; i < size(); i++)
//		if (!gpx::math::ale(coord(i), val))
//			return false;
//	return true;
//}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_VectorTrait<DERIVED, N, T, DIMSPEC>::isZero() const
{	
	for (std::size_t i = 0; i < derived().size(); i++)
		if (derived().coord(i) != T())
			return false;
	return true;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_VectorTrait<DERIVED, N, T, DIMSPEC>::apeZero() const
{
	for (std::size_t i = 0; i < derived().size(); i++)
		if (!gpx::math::ape(derived().coord(i), T()))
			return false;
	return true;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
bool const_VectorTrait<DERIVED, N, T, DIMSPEC>::aleZero() const
{
	for (std::size_t i = 0; i < derived().size(); i++)
		if (!gpx::math::ale(derived().coord(i), T()))
			return false;
	return true;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::minimal(gpx::math::const_VectorRef<N, T> other) const
{
	gpx::math::Vector<N, T> result(derived());
	result.minimize(other);
	return result;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::rotated(T sin, T cos, std::size_t c1, std::size_t c2) const
{
	gpx::math::Vector<N, T> result(derived());
	result.rotate(sin, cos, c1, c2);
	return result;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Vector<N, T> const_VectorTrait<DERIVED, N, T, DIMSPEC>::rotated(T angle, std::size_t c1, std::size_t c2) const
{
	gpx::math::Vector<N, T> result(derived());
	result.rotate(angle, c1, c2);
	return result;
}

template <template <std::size_t, typename> class DERIVED, std::size_t N, typename T, bool DIMSPEC>
const DERIVED<N, T> & const_VectorTrait<DERIVED, N, T, DIMSPEC>::derived() const
{
	return static_cast<const DERIVED<N, T> & >(*this);
}


//template <typename T>
//class const_VectorPtr<gpx::math::SIZE_DYNAMIC, T, true> : public const_VectorPtr<gpx::math::SIZE_DYNAMIC, T, false>
//{
//	typedef const_VectorPtr<gpx::math::SIZE_DYNAMIC, T, false> Parent;

//	public:
//		//generated copy ctor OK

//	protected:
//		const_VectorPtr(const T * coords, std::size_t size);

//	protected:
//		void setPtr(const T * ptr);

//		void setPtr(const T * ptr, std::size_t size);

//		using Parent::prod;

//		template <std::size_t ON>
//		gpx::math::Vector<gpx::math::SIZE_DYNAMIC, T> prod(const gpx::math::Matrix<ON, ON, T> & matrix) const;

//	private:
//		//forbidden
//		const_VectorPtr<gpx::math::SIZE_DYNAMIC, T> & operator =(const const_VectorPtr<gpx::math::SIZE_DYNAMIC, T> & other);
//};

/**
 * Backend implementation of gpx::math::const_VectorTrait<DERIVED, 2, T, true>.
 *
 * @todo override length() to use std::hypot with C++11.
 */
template <template <std::size_t, typename> class DERIVED, typename T>
class const_VectorTrait<DERIVED, 2, T, true> : public const_VectorTrait<DERIVED, 2, T, false>
{
	typedef const_VectorTrait<DERIVED, 2, T, false> Parent;

	protected:
//		T length() const; //override

		using Parent::cross;

		gpx::math::Vector<2, T> cross() const;

		using Parent::ccross;

		gpx::math::Vector<2, T> ccross() const;

		using Parent::det;

		T det(gpx::math::const_VectorRef<2, T> other) const;

		using Parent::rotated;

		gpx::math::Vector<2, T> rotated(T sin, T cos) const;

		gpx::math::Vector<2, T> rotated(T angle) const;
};

//template <template <std::size_t, typename> class DERIVED, typename T>
//gpx::math::Vector<2, T> const_VectorTrait<DERIVED, 2, T, true>::cross() const
//{
//	return std::hypot(Parent::derived().coord(0), Parent::derived().coord(1));
//}

template <template <std::size_t, typename> class DERIVED, typename T>
gpx::math::Vector<2, T> const_VectorTrait<DERIVED, 2, T, true>::cross() const
{
	return gpx::math::Vector<2, T>(Parent::derived().coord(1), -Parent::derived().coord(0));
}

template <template <std::size_t, typename> class DERIVED, typename T>
gpx::math::Vector<2, T> const_VectorTrait<DERIVED, 2, T, true>::ccross() const
{
	return gpx::math::Vector<2, T>(-Parent::derived().coord(1), Parent::derived().coord(0));
}

template <template <std::size_t, typename> class DERIVED, typename T>
T const_VectorTrait<DERIVED, 2, T, true>::det(gpx::math::const_VectorRef<2, T> other) const
{
	return (Parent::derived().coord(0) * other(1)) - (Parent::derived().coord(1) * other(0));
}

template <template <std::size_t, typename> class DERIVED, typename T>
gpx::math::Vector<2, T> const_VectorTrait<DERIVED, 2, T, true>::rotated(T sin, T cos) const
{
	gpx::math::Vector<2, T> result(Parent::derived());
	result.rotate(sin, cos);
	return result;
}

template <template <std::size_t, typename> class DERIVED, typename T>
gpx::math::Vector<2, T> const_VectorTrait<DERIVED, 2, T, true>::rotated(T angle) const
{
	gpx::math::Vector<2, T> result(Parent::derived());
	result.rotate(angle);
	return result;
}

//template <typename T>
//class const_VectorPtr<3, T, true> : public const_VectorPtr<3, T, false>
//{
//	typedef const_VectorPtr<3, T, false> Parent;

//	public:
//		//generated copy ctor OK

//	protected:
//		const_VectorPtr(const T * coords);

//		using Parent::cross;

//		gpx::math::Vector<3, T> cross(const gpx::math::const_VectorPtr<3, T> & other) const;

//		using Parent::ccross;

//		gpx::math::Vector<3, T> ccross(const gpx::math::const_VectorPtr<3, T> & other) const;

//		using Parent::sum;

//		gpx::math::Vector<3, T> sum(T x, T y, T z) const;

//		using Parent::diff;

//		gpx::math::Vector<3, T> diff(T x, T y, T z) const;

//		using Parent::prod;

//		gpx::math::Vector<3, T> prod(const gpx::math::Matrix<4, 4, T> & matrix) const;

//		using Parent::rotated;

//		gpx::math::Vector<3, T> rotated(T sin, T cos, std::size_t axis) const;

//		gpx::math::Vector<3, T> rotated(T angle, std::size_t axis) const;

//	private:
//		//forbidden
//		const_VectorPtr<3, T> & operator =(const const_VectorPtr<3, T> & other);
//};


////DIMSPEC = true, N = SIZE_DYNAMIC

//template <typename T>
//inline
//const_VectorPtr<gpx::math::SIZE_DYNAMIC, T, true>::const_VectorPtr(const T * coords, std::size_t size):
//	Parent(coords, size)
//{
//}

//template <typename T>
//inline
//void const_VectorPtr<gpx::math::SIZE_DYNAMIC, T, true>::setPtr(const T * ptr)
//{
//	Parent::setPtr(const_cast<T *>(ptr));
//}

//template <typename T>
//inline
//void const_VectorPtr<gpx::math::SIZE_DYNAMIC, T, true>::setPtr(const T * ptr, std::size_t size)
//{
//	Parent::setPtr(const_cast<T *>(ptr), size);
//}

//template <typename T>
//template <std::size_t ON>
//inline
//gpx::math::Vector<gpx::math::SIZE_DYNAMIC, T> const_VectorPtr<gpx::math::SIZE_DYNAMIC, T, true>::prod(const gpx::math::Matrix<ON, ON, T> & matrix) const
//{
//	gpx::math::Vector<gpx::math::SIZE_DYNAMIC, T> result(static_cast<const gpx::math::const_VectorPtr<gpx::math::SIZE_DYNAMIC, T> &>(*this));
//	result *= matrix;
//	return result;
//}

////DIMSPEC = true, N = 3

//template <typename T>
//inline
//const_VectorPtr<3, T, true>::const_VectorPtr(const T * coords):
//	Parent(coords)
//{
//}

//template <typename T>
//inline
//gpx::math::Vector<3, T> const_VectorPtr<3, T, true>::cross(const gpx::math::const_VectorPtr<3, T> & other) const
//{
//	return gpx::math::Vector<3, T>(
//			Parent::coord(1) * other(2) - Parent::coord(2) * other(1),
//			Parent::coord(2) * other(0) - Parent::coord(0) * other(2),
//			Parent::coord(0) * other(1) - Parent::coord(1) * other(0)
//		);
//}

//template <typename T>
//inline
//gpx::math::Vector<3, T> const_VectorPtr<3, T, true>::ccross(const gpx::math::const_VectorPtr<3, T> & other) const
//{
//	return gpx::math::Vector<3, T>(
//			Parent::coord(2) * other(1) - Parent::coord(1) * other(2),
//			Parent::coord(0) * other(2) - Parent::coord(2) * other(0),
//			Parent::coord(1) * other(0) - Parent::coord(0) * other(1)
//		);
//}

//template <typename T>
//inline
//gpx::math::Vector<3, T> const_VectorPtr<3, T, true>::sum(T x, T y, T z) const
//{
//	gpx::math::Vector<3, T> result(static_cast<const gpx::math::const_VectorPtr<3, T> &>(*this));
//	result.add(x, y, z);
//	return result;
//}

//template <typename T>
//inline
//gpx::math::Vector<3, T> const_VectorPtr<3, T, true>::diff(T x, T y, T z) const
//{
//	gpx::math::Vector<3, T> result(static_cast<const gpx::math::const_VectorPtr<3, T> &>(*this));
//	result.sub(x, y, z);
//	return result;
//}

//template <typename T>
//inline
//gpx::math::Vector<3, T> const_VectorPtr<3, T, true>::prod(const gpx::math::Matrix<4, 4, T> & matrix) const
//{
//	gpx::math::Vector<3, T> result(static_cast<const gpx::math::const_VectorPtr<3, T> &>(*this));
//	result.mul(matrix);
//	return result;
//}

//template <typename T>
//inline
//gpx::math::Vector<3, T> const_VectorPtr<3, T, true>::rotated(T sin, T cos, std::size_t axis) const
//{
//	gpx::math::Vector<3, T> result(static_cast<const gpx::math::const_VectorPtr<3, T> & >(*this));
//	result.rotate(sin, cos, axis);
//	return result;
//}

//template <typename T>
//inline
//gpx::math::Vector<3, T> const_VectorPtr<3, T, true>::rotated(T angle, std::size_t axis) const
//{
//	gpx::math::Vector<3, T> result(static_cast<const gpx::math::const_VectorPtr<3, T> & >(*this));
//	result.rotate(angle, axis);
//	return result;
//}

}
}
}

#endif /* GPX_X_MATH_BASIC_CONST_VECTORPTR_HPP_ */
