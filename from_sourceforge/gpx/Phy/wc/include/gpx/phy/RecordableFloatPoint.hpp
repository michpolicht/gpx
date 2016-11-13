#ifndef RECORDABLEFLOATPOINT_HPP
#define RECORDABLEFLOATPOINT_HPP

#include "RecordableFloat.hpp"

#include <gpx/math/structures.hpp>

namespace gpx {
namespace phy {

/**
 * IRecordable interface helper for gpx::math points with fixed size and floating point
 * types of coordinates.
 * @param N fixed number of coordinates.
 * @param F type of coordinates (must be floating point type).
 */
template <std::size_t N, typename F = real_t>
struct RecordableFloatPoint
{
		/**
		 * Get snapshot size.
		 * @return amount of 8 bit bytes required to store point in byte array.
		 */
		static std::size_t SnapshotSize();

		/**
		 * Store point in byte array.
		 * @param snapshot pointer to an array into which results should be written. Array
		 * must have SnapshotSize() characters allocated to store a point.
		 * @param num number.
		 *
		 * @note function does not pack snapshot array data if @p char has more than 8 bits.
		 * It will use no more than first 8 bits of each array element.
		 */
		static void Store(char * snapshot, math::const_PointRef<N, F> point);

		/**
		 * Restore point from byte array.
		 * @param snapshot pointer to an array in which point is stored.
		 * @param num point into which restored values should be written.
		 *
		 * @note function is not unpacking snapshot array data if @p char has more than 8 bits.
		 * It always uses first 8 bits.
		 */
		static void Restore(char * snapshot, math::PointRef<N, F> point);

};

template <std::size_t N, typename F>
std::size_t RecordableFloatPoint<N, F>::SnapshotSize()
{
	return N * RecordableFloat<F>::SnapshotSize();
}

template <std::size_t N, typename F>
void RecordableFloatPoint<N, F>::Store(char * snapshot, math::const_PointRef<N, F> point)
{
	//prevent inconsistency between SnapshotSize() and point.size()
	GPX_ASSERT(point.size() == N, "size mismatch (" << point.size() << " == " << N << ")");

	for (std::size_t n = 0; n < point.size(); n++) {
		RecordableFloat<F>::Store(snapshot, point.coord(n));
		snapshot += RecordableFloat<F>::SnapshotSize();
	}
}

template <std::size_t N, typename F>
void RecordableFloatPoint<N, F>::Restore(char * snapshot, math::PointRef<N, F> point)
{
	//prevent inconsistency between SnapshotSize() and point.size()
	GPX_ASSERT(point.size() == N, "size mismatch (" << point.size() << " == " << N << ")");

	for (std::size_t n = 0; n < point.size(); n++) {
		RecordableFloat<F>::Restore(snapshot, point.coord(n));
		snapshot += RecordableFloat<F>::SnapshotSize();
	}
}

/**
 * Disabled IRecordable interface helper for dynamically sized gpx::math points.
 */
template <typename F>
struct RecordableFloatPoint<math::SIZE_DYNAMIC, F>
{
};

}
}

#endif // RECORDABLEFLOATPOINT_HPP
