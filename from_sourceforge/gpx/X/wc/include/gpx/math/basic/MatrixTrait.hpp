#ifndef GPX_X_MATH_BASIC_MATRIXTRAIT_HPP
#define GPX_X_MATH_BASIC_MATRIXTRAIT_HPP

#include <algorithm>

namespace gpx {
namespace math {
namespace basic {

/**
 * Backend implementation of gpx::math::MatrixTrait<DERIVED, M, N, T, DIMSPEC>.
 */
template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
class MatrixTrait
{
	friend class MatrixTrait<DERIVED, N, N, T, true>;

	protected:
		void add(gpx::math::const_MatrixRef<M, N, T> other);

		void sub(gpx::math::const_MatrixRef<M, N, T> other);

		void mul(gpx::math::const_MatrixRef<N, N, T> other);

		void mul(T val);

		void zero();

		void identity();

		void swapRows(std::size_t r1, std::size_t r2);

		void swapCols(std::size_t c1, std::size_t c2);

		DERIVED<M, N, T> & derived();

	private:
		/**
		 * Invert matrix. Helper method for MatrixTrait<N, N, T> specializations.
		 * @param derived matrix to be inverted.
		 */
		static void Invert(DERIVED<N, N, T> & derived);
};

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
void MatrixTrait<DERIVED, M, N, T, DIMSPEC>::Invert(DERIVED<N, N, T> & derived)
{
	gpx::math::Matrix<N, N, T> I(static_cast<T>(1.0), derived.rows(), derived.cols()); //identity matrix
	std::size_t index[derived.cols()]; //index holds columns order

	for (std::size_t j = 0; j < derived.cols(); j++)
		index[j] = j;

	//perform operations on col j (leading element(j,j))
	for (std::size_t j = 0; j < derived.cols(); j++) {
		//find max pivot
		for (std::size_t jj = j + 1; jj < derived.cols(); jj++)
			if (std::abs(derived.element(index[jj] * derived.cols() + j)) > std::abs(derived.element(index[j] * derived.cols() + j)))
				std::swap(index[j], index[jj]); //swap cols
		//divisor may be 0, then matrix is singular and function will fail
		T divisor = derived.element(index[j] * derived.cols() + j);
		for (std::size_t i = 0; i < derived.cols(); i++) {
			I.element(index[j] * derived.cols() + i) /= divisor;
			derived.element(index[j] * derived.cols() + i) /= divisor;
		}
		for (std::size_t ii = 0; ii < derived.cols(); ii++)
			if (ii != j) {
				T multiplier = derived.element(index[ii] * derived.cols() + j);
				for (std::size_t i = 0; i < derived.cols(); i++) {
					I.element(index[ii] * derived.cols() + i) -= multiplier * I.element(index[j] * derived.cols() + i);
					derived.element(index[ii] * derived.cols() + i) -= multiplier * derived.element(index[j] * derived.cols() + i);
				}
			}
	}
	//copy column by column
	for (std::size_t j = 0; j < derived.cols(); j++)
		std::copy(I.ptr(0, index[j]), I.ptr(0, index[j]) + derived.rows(), derived.ptr(0, j));
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
void MatrixTrait<DERIVED, M, N, T, DIMSPEC>::add(gpx::math::const_MatrixRef<M, N, T> other)
{
	for (std::size_t i = 0; i < derived().size(); i++)
		derived().element(i) += other.element(i);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
void MatrixTrait<DERIVED, M, N, T, DIMSPEC>::sub(gpx::math::const_MatrixRef<M, N, T> other)
{
	for (std::size_t i = 0; i < derived().size(); i++)
		derived().element(i) -= other.element(i);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
void MatrixTrait<DERIVED, M, N, T, DIMSPEC>::mul(gpx::math::const_MatrixRef<N, N, T> other)
{
	Matrix<M, N, T> tmp(derived());	//temporal copy
	for (std::size_t r = 0; r < derived().rows(); r++) {
		for (std::size_t c = 0; c < derived().cols(); c++) {
			derived().element(r, c) = T();
			for (std::size_t cr = 0; cr < derived().cols(); cr++)
				derived().element(r, c) += tmp(r, cr) * other(cr, c);
		}
	}
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
void MatrixTrait<DERIVED, M, N, T, DIMSPEC>::mul(T val)
{
	for (std::size_t i = 0; i < derived().size(); i++)
		derived().element(i) *= val;
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
void MatrixTrait<DERIVED, M, N, T, DIMSPEC>::zero()
{
	std::fill(derived().ptr(), derived().ptr() + derived().size(), T());
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
void MatrixTrait<DERIVED, M, N, T, DIMSPEC>::identity()
{
	std::fill(derived().ptr(), derived().ptr() + derived().size(), T());
	for (std::size_t i = 0; i < std::min(derived().rows(), derived().cols()); i++)
		derived().element(derived().rows() * i + i) = static_cast<T>(1.0);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
void MatrixTrait<DERIVED, M, N, T, DIMSPEC>::swapRows(std::size_t r1, std::size_t r2)
{
	for (std::size_t c = 0; c < derived().cols(); c++)
		std::swap(derived().element(c * derived().rows() + r1), derived().element(c * derived().rows() + r2));
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
void MatrixTrait<DERIVED, M, N, T, DIMSPEC>::swapCols(std::size_t c1, std::size_t c2)
{
	for (std::size_t r = 0; r < derived().rows(); r++)
		std::swap(derived().element(c1 * derived().rows() + r), derived().element(c2 * derived().rows() + r));
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t M, std::size_t N, typename T, bool DIMSPEC>
DERIVED<M, N, T> & MatrixTrait<DERIVED, M, N, T, DIMSPEC>::derived()
{
	return static_cast<DERIVED<M, N, T> & >(*this);
}

/**
 * Backend implementation of gpx::math::MatrixTrait<DERIVED, N, N, T, true>.
 */
template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t N, typename T>
class MatrixTrait<DERIVED, N, N, T, true> : public MatrixTrait<DERIVED, N, N, T, false>
{
	typedef MatrixTrait<DERIVED, N, N, T, false> Parent;

	protected:
		void transpose();

		/*
		 * Basic implementation which uses Gauss-Jordan transformations with pivoting.
		 * @warning if matrix is singular method will fail.
		 */
		void invert();
};

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t N, typename T>
void MatrixTrait<DERIVED, N, N, T, true>::transpose()
{
	for (std::size_t i = 0; i < Parent::derived().rows(); i++)
		for(std::size_t j = i + 1; j < Parent::derived().cols(); j++)
			std::swap(Parent::derived().element(i, j), Parent::derived().element(j, i));
}

template <template <std::size_t, std::size_t, typename> class DERIVED, std::size_t N, typename T>
void MatrixTrait<DERIVED, N, N, T, true>::invert()
{
	Parent::Invert(Parent::derived());
}

/**
 * Backend implementation of gpx::math::MatrixTrait<DERIVED, gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>.
 */
template <template <std::size_t, std::size_t, typename> class DERIVED, typename T>
class MatrixTrait<DERIVED, gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true> : public MatrixTrait<DERIVED, gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, false>
{
	typedef MatrixTrait<DERIVED, gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, false> Parent;

	protected:
		void transpose();

		/*
		 * Basic implementation which uses Gauss-Jordan transformations with pivoting.
		 * @warning if matrix is singular method will fail.
		 */
		void invert();
};

template <template <std::size_t, std::size_t, typename> class DERIVED, typename T>
void MatrixTrait<DERIVED, gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::transpose()
{
	gpx::math::Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> copy(Parent::derived());
	Parent::derived().resize(Parent::derived().cols(), Parent::derived().rows());
	for (std::size_t i = 0; i < Parent::derived().rows(); i++)
		for(std::size_t j = 0; j < Parent::derived().cols(); j++)
			Parent::derived().element(i, j) = copy(j, i);
}

template <template <std::size_t, std::size_t, typename> class DERIVED, typename T>
void MatrixTrait<DERIVED, gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::invert()
{
	GPX_ASSERT(Parent::derived().rows() == Parent::derived().cols(), "number of rows and columns must be equal");

	Parent::Invert(Parent::derived());
}

}
}
}

#endif // MATRIXTRAIT_HPP
