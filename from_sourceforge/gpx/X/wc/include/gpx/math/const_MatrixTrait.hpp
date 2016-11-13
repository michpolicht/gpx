#ifndef CONST_MATRIXTRAIT_HPP
#define CONST_MATRIXTRAIT_HPP

#include "structures.hpp"

#include GPX_X_MATH_BACKEND_HEADER
#include GPX_X_MATH_BACKEND_CONST_MATRIXTRAIT_HEADER

namespace gpx {
namespace math {

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
class const_MatrixTrait : private GPX_X_MATH_BACKEND_NAMESPACE::const_MatrixTrait<DERIVED, M, N, T, true>
{
	typedef GPX_X_MATH_BACKEND_NAMESPACE::const_MatrixTrait<DERIVED, M, N, T, true> Impl;
	friend class GPX_X_MATH_BACKEND_NAMESPACE::const_MatrixTrait<DERIVED, M, N, T, true>;
	friend class GPX_X_MATH_BACKEND_NAMESPACE::const_MatrixTrait<DERIVED, M, N, T, false>;
	friend class const_MatrixTrait<DERIVED, N, N, T, true>;

	public:
		/**
		 * Equality operator.
		 * @param other other matrix.
		 * @return @p true if all elements of this matrix are equal to the corresponding
		 * elements of the other matrix; @p false otherwise.
		 */
		bool operator ==(const_MatrixRef<M, N, T> other) const;

		/**
		 * Approximately equal.
		 * @param other other matrix.
		 * @return @p true if all elements of this matrix are approximately equal to the
		 * corresponding elements of the other matrix; @p false otherwise.
		 */
		bool ape(const_MatrixRef<M, N, T> other) const;

		/**
		 * Almost equal.
		 * @param other other matrix.
		 * @return @p true if all elements of this matrix are almost equal to the
		 * corresponding elements of the other matrix; @p false otherwise.
		 *
		 * @note ale() is stronger than ape().
		 */
		bool ale(const_MatrixRef<M, N, T> other) const;

		/**
		 * Inequality operator.
		 * @param other other matrix.
		 * @return @p true if at least one element is not equal to the corresponding element
		 * of the other matrix; @p false otherwise.
		 */
		bool operator !=(const_MatrixRef<M, N, T> other) const;

		/**
		 * Check if matrix is an identity matrix.
		 * @return @p true when all elements on diagonal are equal 1 and all elements outside
		 * diagonal are equal 0. Otherwise function returns @p false.
		 */
		bool isIdentity() const;

		/**
		 * Check if matrix is almost an identity matrix.
		 * @return @p true when all elements on diagonal are almost equal 1 and all
		 * elements outside diagonal are almost equal 0. Otherwise function returns @p false.
		 *
		 * @note ale() is stronger than ape().
		 *
		 * @note because ale() is critically sensitive around zero it's probably better to use
		 * apeIdentity() variant.
		 */
		bool aleIdentity() const;

		/**
		 * Check if matrix is approximately an identity matrix.
		 * @return @p true when all elements on diagonal are appriximately equal 1 and all
		 * elements outside diagonal are approximately equal 0. Otherwise function
		 * returns @p false.
		 *
		 * @note ale() is stronger than ape().
		 */
		bool apeIdentity() const;

		/**
		 * Check if matrix is a zero matrix.
		 * @return @p true when all elements are equal 0, @p false otherwise.
		 */
		bool isZero() const;

		/**
		 * Check if matrix is almost a zero matrix.
		 * @return @p true when all elements are almost equal 0, @p false otherwise.
		 *
		 * @note ale() is stronger than ape().
		 *
		 * @note because ale() is critically sensitive around zero it's probably better to use
		 * apeZero() variant.
		 */
		bool aleZero() const;

		/**
		 * Check if matrix is approximately a zero matrix.
		 * @return @p true when all elements are approximately equal 0, @p false otherwise.
		 *
		 * @note ale() is stronger than ape().
		 */
		bool apeZero() const;

		/**
		 * Sum.
		 * @param other matrix to be added.
		 * @return sum of this matrix and the other.
		 */
		Matrix<M, N, T> sum(const_MatrixRef<M, N, T> other) const;

		/**
		 * Sum. Alias of sum().
		 * @param other matrix to be added.
		 * @return sum of this matrix and the other.
		 */
		Matrix<M, N, T> operator +(const_MatrixRef<M, N, T> other) const;

		/**
		 * Difference.
		 * @param other matrix to be subtracted.
		 * @return difference of this matrix and the other.
		 */
		Matrix<M, N, T> diff(const_MatrixRef<M, N, T> other) const;

		/**
		 * Difference. Alias of diff().
		 * @param other matrix to be subtracted.
		 * @return difference of this matrix and the other.
		 */
		Matrix<M, N, T> operator -(const_MatrixRef<M, N, T> other) const;

		/**
		 * Product.
		 * @param other matrix multiplier. Other matrix may have arbitrary number of
		 * @a ON columns.
		 * @return product of this matrix multiplied by other.
		 */
		template <std::size_t ON>
		Matrix<M, ON, T> prod(const_MatrixRef<N, ON, T> other) const;

		template <std::size_t ON>
		Matrix<M, ON, T> prod(MatrixRef<N, ON, T> other) const;

		template <std::size_t ON>
		Matrix<M, ON, T> prod(const Matrix<N, ON, T> & other) const;

		/**
		 * Vector product.
		 * @param vec vector multiplier.
		 * @return product of matrix multiplied by vector.
		 */
		Vector<M, T> prod(const_VectorRef<N, T> vec) const;

		/**
		 * Scalar product.
		 * @param val scalar multiplier.
		 * @return product of this matrix multiplied by scalar.
		 */
		Matrix<M, N, T> prod(T val) const;

		/**
		 * Product. Alias of prod().
		 * @param other matrix multiplier. Other matrix may have arbitrary number of
		 * @a ON columns.
		 * @return product of this matrix multiplied by other.
		 */
		template <std::size_t ON>
		Matrix<M, ON, T> operator *(const_MatrixRef<N, ON, T> other) const;

		template <std::size_t ON>
		Matrix<M, ON, T> operator *(MatrixRef<N, ON, T> other) const;

		template <std::size_t ON>
		Matrix<M, ON, T> operator *(const Matrix<N, ON, T> & other) const;

		/**
		 * Vector product. Alias of prod().
		 * @param val scalar multiplier.
		 * @return product of this matrix multiplied by scalar.
		 */
		Vector<M, T> operator *(const_VectorRef<N, T> vec) const;

		/**
		 * Scalar product. Alias of prod().
		 * @param val scalar multiplier.
		 * @return product of this matrix multiplied by scalar.
		 */
		Matrix<M, N, T> operator *(T val) const;

		/**
		 * Transposed matrix.
		 * @return transposed matrix.
		 */
		Matrix<N, M, T> transposed() const;
};

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::operator ==(const_MatrixRef<M, N, T> other) const
{
	return Impl::operator ==(other);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::ape(const_MatrixRef<M, N, T> other) const
{
	return Impl::ape(other);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::ale(const_MatrixRef<M, N, T> other) const
{
	return Impl::ale(other);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::operator !=(const_MatrixRef<M, N, T> other) const
{
	return Impl::operator !=(other);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::isIdentity() const
{
	return Impl::isIdentity();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::aleIdentity() const
{
	return Impl::aleIdentity();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::apeIdentity() const
{
	return Impl::apeIdentity();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::isZero() const
{
	return Impl::isZero();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::aleZero() const
{
	return Impl::aleZero();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
bool const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::apeZero() const
{
	return Impl::apeZero();
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
Matrix<M, N, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::sum(const_MatrixRef<M, N, T> other) const
{
	return Impl::sum(other);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
Matrix<M, N, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::operator +(const_MatrixRef<M, N, T> other) const
{
	return Impl::sum(other);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
Matrix<M, N, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::diff(const_MatrixRef<M, N, T> other) const
{
	return Impl::diff(other);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
Matrix<M, N, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::operator -(const_MatrixRef<M, N, T> other) const
{
	return Impl::diff(other);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
template <std::size_t ON>
Matrix<M, ON, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::prod(const_MatrixRef<N, ON, T> other) const
{
	return Impl::prod(other);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
template <std::size_t ON>
Matrix<M, ON, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::prod(MatrixRef<N, ON, T> other) const
{
	return Impl::prod(static_cast<const_MatrixRef<N, ON, T> >(other));
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
template <std::size_t ON>
Matrix<M, ON, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::prod(const Matrix<N, ON, T> & other) const
{
	return Impl::prod(static_cast<const_MatrixRef<N, ON, T> >(other));
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
Vector<M, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::prod(const_VectorRef<N, T> vec) const
{
	return Impl::prod(vec);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
Matrix<M, N, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::prod(T val) const
{
	return Impl::prod(val);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
template <std::size_t ON>
Matrix<M, ON, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::operator *(const_MatrixRef<N, ON, T> other) const
{
	return Impl::prod(other);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
template <std::size_t ON>
Matrix<M, ON, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::operator *(MatrixRef<N, ON, T> other) const
{
	return Impl::prod(static_cast<const_MatrixRef<N, ON, T> >(other));
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
template <std::size_t ON>
Matrix<M, ON, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::operator *(const Matrix<N, ON, T> & other) const
{
	return Impl::prod(static_cast<const_MatrixRef<N, ON, T> >(other));
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
Vector<M, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::operator *(const_VectorRef<N, T> vec) const
{
	return Impl::prod(vec);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
Matrix<M, N, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::operator *(T val) const
{
	return Impl::prod(val);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
Matrix<N, M, T> const_MatrixTrait<DERIVED, M, N, T, DIMSPEC>::transposed() const
{
	return Impl::transposed();
}


template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t N, typename T>
class const_MatrixTrait<DERIVED, N, N, T, true> : public const_MatrixTrait<DERIVED, N, N, T, false>
{
	typedef const_MatrixTrait<DERIVED, N, N, T, false> Parent;
	typedef GPX_X_MATH_BACKEND_NAMESPACE::const_MatrixTrait<DERIVED, N, N, T, true> Impl;

	public:
		/**
		 * Determinant.
		 * @return matrix determinant.
		 */
		T det() const;
};

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t N, typename T>
T const_MatrixTrait<DERIVED, N, N, T, true>::det() const
{
	return Impl::det();
}

}
}

#endif // CONST_MATRIXTRAIT_HPP
