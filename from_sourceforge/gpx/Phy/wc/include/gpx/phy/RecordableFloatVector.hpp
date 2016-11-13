#ifndef RECORDABLEFLOATVECTOR_HPP
#define RECORDABLEFLOATVECTOR_HPP

#include "RecordableFloat.hpp"

#include <gpx/math/structures.hpp>

namespace gpx {
namespace phy {

/**
 * IRecordable interface helper for gpx::math vectors with fixed size and floating point
 * types of coordinates.
 * @param N fixed number of coordinates.
 * @param F type of coordinates (must be floating point type).
 */
template <std::size_t N, typename F = real_t>
struct RecordableFloatVector
{
		/**
		 * Get snapshot size.
		 * @return amount of 8 bit bytes required to store vector in byte array.
		 */
		static std::size_t SnapshotSize();

		/**
		 * Store vector in byte array.
		 * @param snapshot pointer to an array into which results should be written. Array
		 * must have SnapshotSize() characters allocated to store a vector.
		 * @param num number.
		 *
		 * @note function does not pack snapshot array data if @p char has more than 8 bits.
		 * It will use no more than first 8 bits of each array element.
		 */
		static void Store(char * snapshot, math::const_VectorRef<N, F> vector);

		/**
		 * Restore vector from byte array.
		 * @param snapshot pointer to an array in which point is stored.
		 * @param num vector into which restored values should be written.
		 *
		 * @note function is not unpacking snapshot array data if @p char has more than 8 bits.
		 * It always uses first 8 bits.
		 */
		static void Restore(char * snapshot, math::VectorRef<N, F> vector);

};

template <std::size_t N, typename F>
std::size_t RecordableFloatVector<N, F>::SnapshotSize()
{
	return N * RecordableFloat<F>::SnapshotSize();
}

template <std::size_t N, typename F>
void RecordableFloatVector<N, F>::Store(char * snapshot, math::const_VectorRef<N, F> vector)
{
	//prevent inconsistency between SnapshotSize() and vector.size()
	GPX_ASSERT(vector.size() == N, "size mismatch (" << vector.size() << " == " << N << ")");

	for (std::size_t n = 0; n < vector.size(); n++) {
		RecordableFloat<F>::Store(snapshot, vector.coord(n));
		snapshot += RecordableFloat<F>::SnapshotSize();
	}
}

template <std::size_t N, typename F>
void RecordableFloatVector<N, F>::Restore(char * snapshot, math::VectorRef<N, F> vector)
{
	//prevent inconsistency between SnapshotSize() and vector.size()
	GPX_ASSERT(vector.size() == N, "size mismatch (" << vector.size() << " == " << N << ")");

	for (std::size_t n = 0; n < vector.size(); n++) {
		RecordableFloat<F>::Restore(snapshot, vector.coord(n));
		snapshot += RecordableFloat<F>::SnapshotSize();
	}
}

/**
 * Disabled IRecordable interface helper for dynamically sized gpx::math vectors.
 */
template <typename F>
struct RecordableFloatVector<math::SIZE_DYNAMIC, F>
{
};

}
}

#endif // RECORDABLEFLOATVECTOR_HPP
