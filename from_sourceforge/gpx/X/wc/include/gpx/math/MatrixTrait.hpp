#ifndef MATRIXTRAIT_HPP
#define MATRIXTRAIT_HPP

#include "structures.hpp"

#include GPX_X_MATH_BACKEND_HEADER
#include GPX_X_MATH_BACKEND_MATRIXTRAIT_HEADER

namespace gpx {
namespace math {

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
class MatrixTrait : public const_MatrixTrait<DERIVED, M, N, T, true>,
					private GPX_X_MATH_BACKEND_NAMESPACE::MatrixTrait<DERIVED, M, N, T, true>
{
	typedef const_MatrixTrait<DERIVED, M, N, T, true> Parent;
	typedef GPX_X_MATH_BACKEND_NAMESPACE::MatrixTrait<DERIVED, M, N, T, true> Impl;
	friend class GPX_X_MATH_BACKEND_NAMESPACE::MatrixTrait<DERIVED, M, N, T, true>;
	friend class GPX_X_MATH_BACKEND_NAMESPACE::MatrixTrait<DERIVED, M, N, T, false>;
	friend class MatrixTrait<DERIVED, N, N, T, true>;

	public:
		/**
		 * Addition. Add other matrix to this matrix.
		 * @param other matrix to be added.
		 * @return self-reference to matrix performing operation.
		 */
		DERIVED<M, N, T> & add(const_MatrixRef<M, N, T> other);

		/**
		 * Addition assignment. Alias of add().
		 * @param other matrix to be added.
		 * @return self-reference to matrix performing operation.
		 */
		DERIVED<M, N, T> & operator +=(const_MatrixRef<M, N, T> other);

		/**
		 * Subtraction. Subtract other matrix from this matrix.
		 * @param other matrix to be subtracted.
		 * @return self-reference to matrix performing operation.
		 */
		DERIVED<M, N, T> & sub(const_MatrixRef<M, N, T> other);

		/**
		 * Subtraction assignment. Alias of sub().
		 * @param other matrix to be subtracted.
		 * @return self-reference to matrix performing operation.
		 */
		DERIVED<M, N, T> & operator -=(const_MatrixRef<M, N, T> other);

		/**
		 * Multiplication. Multiply matrix by another matrix.
		 * @param other matrix multiplier.
		 * @return self-reference to matrix performing operation.
		 */
		DERIVED<M, N, T> & mul(const_MatrixRef<N, N, T> other);

		/**
		 * Scalar multiplication. Multiply all matrix elements by scalar value.
		 * @param val scalar multiplier.
		 * @return self-reference to matrix performing operation.
		 */
		DERIVED<M, N, T> & mul(T val);

		/**
		 * Multiplication assignment. Alias of mul().
		 * @param other matrix multiplier.
		 * @return self-reference to matrix performing operation.
		 */
		DERIVED<M, N, T> & operator *=(const_MatrixRef<N, N, T> other);

		/**
		 * Scalar multiplication assignment. Alias of mul().
		 * @param val scalar multiplier.
		 * @return self-reference to matrix performing operation.
		 */
		DERIVED<M, N, T> & operator *=(T val);

		/**
		 * Zero matrix elements.
		 * @return self-reference to zeroed matrix.
		 */
		DERIVED<M, N, T> & zero();

		/**
		 * Set identity matrix. Set elements so that matrix becomes an identity matrix.
		 * @return self-reference to matrix being set.
		 */
		DERIVED<M, N, T> & identity();

		/**
		 * Swap rows.
		 * @param r1 row to be swapped with @a r2.
		 * @param r2 row to be swapped with @a r1.
		 */
		void swapRows(std::size_t r1, std::size_t r2);

		/**
		 * Swap columns.
		 * @param c1 column to be swapped with @a c2.
		 * @param c2 column to be swapped with @a c1.
		 */
		void swapCols(std::size_t c1, std::size_t c2);
};

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
DERIVED<M, N, T> & MatrixTrait<DERIVED, M, N, T, DIMSPEC>::add(const_MatrixRef<M, N, T> other)
{
	Impl::add(other);
	return Impl::derived();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
DERIVED<M, N, T> & MatrixTrait<DERIVED, M, N, T, DIMSPEC>::operator +=(const_MatrixRef<M, N, T> other)
{
	Impl::add(other);
	return Impl::derived();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
DERIVED<M, N, T> & MatrixTrait<DERIVED, M, N, T, DIMSPEC>::sub(const_MatrixRef<M, N, T> other)
{
	Impl::sub(other);
	return Impl::derived();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
DERIVED<M, N, T> & MatrixTrait<DERIVED, M, N, T, DIMSPEC>::operator -=(const_MatrixRef<M, N, T> other)
{
	Impl::sub(other);
	return Impl::derived();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
DERIVED<M, N, T> & MatrixTrait<DERIVED, M, N, T, DIMSPEC>::mul(const_MatrixRef<N, N, T> other)
{
	Impl::mul(other);
	return Impl::derived();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
DERIVED<M, N, T> & MatrixTrait<DERIVED, M, N, T, DIMSPEC>::mul(T val)
{
	Impl::mul(val);
	return Impl::derived();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
DERIVED<M, N, T> & MatrixTrait<DERIVED, M, N, T, DIMSPEC>::operator *=(const_MatrixRef<N, N, T> other)
{
	Impl::mul(other);
	return Impl::derived();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
DERIVED<M, N, T> & MatrixTrait<DERIVED, M, N, T, DIMSPEC>::operator *=(T val)
{
	Impl::mul(val);
	return Impl::derived();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
DERIVED<M, N, T> & MatrixTrait<DERIVED, M, N, T, DIMSPEC>::zero()
{
	Impl::zero();
	return Impl::derived();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
DERIVED<M, N, T> & MatrixTrait<DERIVED, M, N, T, DIMSPEC>::identity()
{
	Impl::identity();
	return Impl::derived();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
void MatrixTrait<DERIVED, M, N, T, DIMSPEC>::swapRows(std::size_t r1, std::size_t r2)
{
	GPX_ASSERT(r1 < Impl::derived().rows(), "swapRows(" << r1 << ", " << r2 << ") is out of bounds");
	GPX_ASSERT(r2 < Impl::derived().rows(), "swapRows(" << r1 << ", " << r2 << ") is out of bounds");

	Impl::swapRows(r1, r2);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
void MatrixTrait<DERIVED, M, N, T, DIMSPEC>::swapCols(std::size_t c1, std::size_t c2)
{
	GPX_ASSERT(c1 < Impl::derived().cols(), "swapCols(" << c1 << ", " << c2 << ") is out of bounds");
	GPX_ASSERT(c2 < Impl::derived().cols(), "swapCols(" << c1 << ", " << c2 << ") is out of bounds");

	Impl::swapCols(c1, c2);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t N, typename T>
class MatrixTrait<DERIVED, N, N, T, true> : public MatrixTrait<DERIVED, N, N, T, false>
{
	typedef MatrixTrait<DERIVED, N, N, T, false> Parent;
	typedef GPX_X_MATH_BACKEND_NAMESPACE::MatrixTrait<DERIVED, N, N, T, true> Impl;

	public:
		/**
		 * Transpose matrix.
		 * @return self-reference to matrix being transposed.
		 */
		DERIVED<N, N, T> & transpose();

		/**
		 * Invert matrix.
		 * @param self-reference to inverted matrix.
		 *
		 * @warning matrix should be non-singular.
		 */
		DERIVED<N, N, T> & invert();
};

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t N, typename T>
DERIVED<N, N, T> & MatrixTrait<DERIVED, N, N, T, true>::transpose()
{
	Impl::transpose();
	return Impl::derived();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t N, typename T>
DERIVED<N, N, T> & MatrixTrait<DERIVED, N, N, T, true>::invert()
{
	Impl::invert();
	return Impl::derived();
}

}
}

#endif // MATRIXTRAIT_HPP
