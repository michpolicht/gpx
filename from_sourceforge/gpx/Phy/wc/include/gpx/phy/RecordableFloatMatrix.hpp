#ifndef RECORDABLEFLOATMATRIX_HPP
#define RECORDABLEFLOATMATRIX_HPP

#include "RecordableFloat.hpp"

#include <gpx/math/structures.hpp>

namespace gpx {
namespace phy {

/**
 * IRecordable interface helper for gpx::math matrices with fixed size and floating point
 * types of elements.
 * @param M fixed number of rows.
 * @param N fixed number of columns.
 * @param F floating point type of elements.
 */
template <std::size_t M, std::size_t N, typename F = real_t>
struct RecordableFloatMatrix
{
		/**
		 * Get snapshot size.
		 * @return amount of 8 bit bytes required to store matrix in byte array.
		 */
		static std::size_t SnapshotSize();

		/**
		 * Store matrix in byte array.
		 * @param snapshot pointer to an array into which results should be written. Array
		 * must have SnapshotSize() characters allocated to store a matrix.
		 * @param num number.
		 *
		 * @note function does not pack snapshot array data if @p char has more than 8 bits.
		 * It will use no more than first 8 bits of each array element.
		 */
		static void Store(char * snapshot, math::const_MatrixRef<M, N, F> matrix);

		/**
		 * Restore matrix from byte array.
		 * @param snapshot pointer to an array in which matrix is stored.
		 * @param num matrix into which restored values should be written.
		 *
		 * @note function is not unpacking snapshot array data if @p char has more than 8 bits.
		 * It always uses first 8 bits.
		 */
		static void Restore(char * snapshot, math::MatrixRef<M, N, F> matrix);

};

template <std::size_t M, std::size_t N, typename F>
std::size_t RecordableFloatMatrix<M, N, F>::SnapshotSize()
{
	return M * N * RecordableFloat<F>::SnapshotSize();
}

template <std::size_t M, std::size_t N, typename F>
void RecordableFloatMatrix<M, N, F>::Store(char * snapshot, math::const_MatrixRef<M, N, F> matrix)
{
	//prevent inconsistency between SnapshotSize() and matrix.size()
	GPX_ASSERT(matrix.size() == M * N, "size mismatch (" << matrix.size() << " == " << M * N << ")");

	for (std::size_t n = 0; n < matrix.size(); n++) {
		RecordableFloat<F>::Store(snapshot, matrix.element(n));
		snapshot += RecordableFloat<F>::SnapshotSize();
	}
}

template <std::size_t M, std::size_t N, typename F>
void RecordableFloatMatrix<M, N, F>::Restore(char * snapshot, math::MatrixRef<M, N, F> matrix)
{
	//prevent inconsistency between SnapshotSize() and matrix.size()
	GPX_ASSERT(matrix.size() == M * N, "size mismatch (" << matrix.size() << " == " << M * N << ")");

	for (std::size_t n = 0; n < matrix.size(); n++) {
		RecordableFloat<F>::Restore(snapshot, matrix.element(n));
		snapshot += RecordableFloat<F>::SnapshotSize();
	}
}

/**
 * Disabled IRecordable interface helper for dynamically sized gpx::math matrices.
 */
template <typename F>
struct RecordableFloatMatrix<math::SIZE_DYNAMIC, math::SIZE_DYNAMIC, F>
{
};

}
}

#endif // RECORDABLEFLOATMATRIX_HPP
