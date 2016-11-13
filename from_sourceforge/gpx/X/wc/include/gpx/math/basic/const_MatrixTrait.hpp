#ifndef GPX_X_MATH_BASIC_CONST_MATRIXTRAIT_HPP
#define GPX_X_MATH_BASIC_CONST_MATRIXTRAIT_HPP

#include "traits.hpp"

#include <algorithm>

namespace gpx {
namespace math {
namespace basic {

/**
 * Backend implementation of gpx::math::const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>.
 */
template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
class const_MatrixTrait
{
	friend class const_MatrixTrait<DERIVED, N, N, T, true>;

	protected:
		bool operator ==(gpx::math::const_MatrixRef<M, N, T> other) const;

		bool operator !=(gpx::math::const_MatrixRef<M, N, T> other) const;

		bool ape(gpx::math::const_MatrixRef<M, N, T> other) const;

		bool ale(gpx::math::const_MatrixRef<M, N, T> other) const;

		bool isIdentity() const;

		bool apeIdentity() const;

		bool aleIdentity() const;

		bool isZero() const;

		bool apeZero() const;

		bool aleZero() const;

		gpx::math::Matrix<M, N, T> sum(gpx::math::const_MatrixRef<M, N, T> other) const;

		gpx::math::Matrix<M, N, T> diff(gpx::math::const_MatrixRef<M, N, T> other) const;

		template <std::size_t ON>
		gpx::math::Matrix<M, ON, T> prod(gpx::math::const_MatrixRef<N, ON, T> other) const;

		gpx::math::Vector<M, T> prod(gpx::math::const_VectorRef<N, T> other) const;

		gpx::math::Matrix<M, N, T> prod(T val) const;

		gpx::math::Matrix<N, M, T> transposed() const;

		const DERIVED<M, N, T> & derived() const;

	private:
		/**
		 * Determinant helper. Helper method for const_MatrixTrait<N, N, T> specializations.
		 * @param elements matrix elements (column-major order).
		 * @param size number of rows or columns, thus matrix size is @a size * @a size.
		 * @return determinant of matrix defined by @a elements and @a size.
		 *
		 * @todo better implementation if det() needed.
		 */
		static T Det(const T * elements, std::size_t size);
};

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::operator ==(gpx::math::const_MatrixRef<M, N, T> other) const
{
	return std::equal(derived().ptr(), derived().ptr() + derived().size(), other.ptr());
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::operator !=(gpx::math::const_MatrixRef<M, N, T> other) const
{
	return !std::equal(derived().ptr(), derived().ptr() + derived().size(), other.ptr());
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::ape(gpx::math::const_MatrixRef<M, N, T> other) const
{
	for (std::size_t i = 0; i < derived().size(); i++)
		if (!gpx::math::ape(derived().element(i), other.element(i)))
			return false;
	return true;
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::ale(gpx::math::const_MatrixRef<M, N, T> other) const
{
	for (std::size_t i = 0; i < derived().size(); i++)
		if (!gpx::math::ale(derived().element(i), other.element(i)))
			return false;
	return true;
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::isIdentity() const
{
	//diagonal
	for (std::size_t i = 0; i < std::min(derived().rows(), derived().cols()); i++)
		if (derived().element(derived().rows() * i + i) != static_cast<T>(1.0))
			return false;
	//lower triangle
	for (std::size_t i = 1; i < derived().rows(); i++)
		for (std::size_t j = 0; j < std::min(i, derived().cols()); j++)
			if (derived().element(derived().rows() * j + i) != T())
				return false;
	//upper triangle
	for (std::size_t j = 1; j < derived().cols(); j++)
		for (std::size_t i = 0; i < std::min(j, derived().rows()); i++)
			if (derived().element(derived().rows() * j + i) != T())
				return false;
	return true;
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::apeIdentity() const
{
	//diagonal
	for (std::size_t i = 0; i < std::min(derived().rows(), derived().cols()); i++)
		if (!gpx::math::ape(derived().element(derived().rows() * i + i), static_cast<T>(1.0)))
			return false;
	//lower triangle
	for (std::size_t i = 1; i < derived().rows(); i++)
		for (std::size_t j = 0; j < std::min(i, derived().cols()); j++)
			if (!gpx::math::ape(derived().element(derived().rows() * j + i), T()))
				return false;
	//upper triangle
	for (std::size_t j = 1; j < derived().cols(); j++)
		for (std::size_t i = 0; i < std::min(j, derived().rows()); i++)
			if (!gpx::math::ape(derived().element(derived().rows() * j + i), T()))
				return false;
	return true;
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::aleIdentity() const
{
	//diagonal
	for (std::size_t i = 0; i < std::min(derived().rows(), derived().cols()); i++)
		if (!gpx::math::ale(derived().element(derived().rows() * i + i), static_cast<T>(1.0)))
			return false;
	//lower triangle
	for (std::size_t i = 1; i < derived().rows(); i++)
		for (std::size_t j = 0; j < std::min(i, derived().cols()); j++)
			if (!gpx::math::ale(derived().element(derived().rows() * j + i), T()))
				return false;
	//upper triangle
	for (std::size_t j = 1; j < derived().cols(); j++)
		for (std::size_t i = 0; i < std::min(j, derived().rows()); i++)
			if (!gpx::math::ale(derived().element(derived().rows() * j + i), T()))
				return false;
	return true;
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::isZero() const
{
	for (std::size_t i = 0; i < derived().size(); i++)
		if (derived().element(i) != T())
			return false;
	return true;
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::aleZero() const
{
	for (std::size_t i = 0; i < derived().size(); i++)
		if (!gpx::math::ale(derived().element(i), T()))
			return false;
	return true;
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::apeZero() const
{
	for (std::size_t i = 0; i < derived().size(); i++)
		if (!gpx::math::ape(derived().element(i), T()))
			return false;
	return true;
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Matrix<M, N, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::sum(gpx::math::const_MatrixRef<M, N, T> other) const
{
	gpx::math::Matrix<M, N, T> result(derived());
	result += other;
	return result;
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Matrix<M, N, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::diff(gpx::math::const_MatrixRef<M, N, T> other) const
{
	gpx::math::Matrix<M, N, T> result(derived());
	result -= other;
	return result;
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
template <std::size_t ON>
gpx::math::Matrix<M, ON, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::prod(gpx::math::const_MatrixRef<N, ON, T> other) const
{
	gpx::math::Matrix<M, ON, T> result(T(), derived().rows(), other.cols());
	for (std::size_t r = 0; r < derived().rows(); r++) {
		for (std::size_t c = 0; c < other.cols(); c++) {
			for (std::size_t cr = 0; cr < derived().cols(); cr++)
				result(r, c) += derived().element(r, cr) * other(cr, c);
		}
	}
	return result;
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Vector<M, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::prod(gpx::math::const_VectorRef<N, T> vec) const
{
	gpx::math::Vector<M, T> result(derived().rows());
	const T * colPtr = derived().ptr();
	for (std::size_t c = 0; c < derived().cols(); c++) {
		for (std::size_t r = 0; r < derived().rows(); r++)
			result(r) += colPtr[r] * vec(c);
		colPtr += derived().rows();
	}
	return result;
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Matrix<M, N, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::prod(T val) const
{
	gpx::math::Matrix<M, N, T> result(derived());
	result *= val;
	return result;
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
gpx::math::Matrix<N, M, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::transposed() const
{
	gpx::math::Matrix<N, M, T> result = MatrixTraits<N, M, T>::MakeUninitializedMatrix(derived().cols(), derived().rows());
	for (std::size_t i = 0; i < derived().rows(); i++)
		for(std::size_t j = 0; j < derived().cols(); j++)
			result(j, i) = derived().element(i, j);
	return result;
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
const DERIVED<M, N, T> & const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::derived() const
{
	return static_cast<const DERIVED<M, N, T> & >(*this);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
T const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::Det(const T * elements, std::size_t size)
{
	T result = T();
	T tmp[--size * size++];

	if (size == 2)
		return elements[0] * elements[3] - (elements[1] * elements[2]);
	for (std::size_t j = 0; j < size; j++) {
		for(std::size_t k = size, ctr = 0; k < size * size; k++)
			if (k % size != j)
				tmp[ctr++] = elements[k];
		result += elements[j] * ((j % 2) ? -1.0 : 1.0) * Det(tmp, size - 1);
	}
	return result;
}

/**
 * Backend implementation of gpx::math::const_MatrixTrait<DERIVED, N, N, T, true>.
 */
template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t N, typename T>
class const_MatrixTrait<DERIVED, N, N, T, true> : public const_MatrixTrait<DERIVED, N, N, T, false>
{
	typedef const_MatrixTrait<DERIVED, N, N, T, false> Parent;

	protected:
		/**
		 * Calculate determinant.
		 * @return matrix determinant.
		 */
		T det() const;
};

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t N, typename T>
T const_MatrixTrait<DERIVED, N, N, T, true>::det() const
{
	if (Parent::derived().size() == 1)
		return Parent::derived().element(0);
	return Parent::Det(Parent::derived().ptr(), Parent::derived().cols());
}

/**
 * Backend implementation of gpx::math::const_MatrixTrait<DERIVED, gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>.
 */
template <template <std::size_t, std::size_t, typename> class DERIVED, typename T>
class const_MatrixTrait<DERIVED, gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true> : public const_MatrixTrait<DERIVED, gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, false>
{
	typedef const_MatrixTrait<DERIVED, gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, false> Parent;

	protected:
		/**
		 * Calculate determinant.
		 * @return matrix determinant.
		 */
		T det() const;
};

template <template <std::size_t, std::size_t, typename> class DERIVED, typename T>
T const_MatrixTrait<DERIVED, gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::det() const
{
	GPX_ASSERT(Parent::derived().rows() == Parent::derived().cols(), "number of rows and columns must be equal (" << Parent::derived().rows() << " != " << Parent::derived().cols() << ")");

	if (Parent::derived().size() == 1)
		return Parent::derived().element(0);
	return Parent::Det(Parent::derived().ptr(), Parent::derived().cols());
}

}
}
}

#endif // CONST_MATRIXTRAIT_HPP
