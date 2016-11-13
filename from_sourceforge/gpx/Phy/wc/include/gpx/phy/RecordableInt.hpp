#ifndef RECORDABLEINT_HPP
#define RECORDABLEINT_HPP

#include <cstddef>
#include <limits>
#include <cmath>

namespace gpx {
namespace phy {

/**
 * IRecordable interface helper for integral types.
 * @param I integral type (signed or unsigned: char, short, int, long, long long).
 * Type must satisfy requirement: sizeof(I) <= sizeof(unsigned long long)
 */
template <typename I>
struct RecordableInt
{
	static const int BYTE_BITS = 8; ///< Canonical byte size in bits.
	static const int BYTE_MASK = 0xFF; ///< 8-bit byte mask.
	//char may be != 8 bits (sizeof() = 1 is not necessary 8 bits)
	static const int CHAR_BYTES = std::numeric_limits<unsigned char>::digits / BYTE_BITS;	///< Size of char type in 8-bit bytes.

	/**
	 * Get snapshot size.
	 * @return amount of 8 bit bytes required to store integral of type T in byte array.
	 */
	static std::size_t SnapshotSize();

	/**
	 * Store integral in byte array. Function will store number in endian independent fashion,
	 * although currently it doesn't care about other things (like byte format, e.g. BCD).
	 * @param snapshot pointer to an array into which results should be written. Array
	 * must have SnapshotSize() characters allocated to store a number.
	 * @param num number.
	 *
	 * @note function does not pack snapshot array data if @p char has more than 8 bits.
	 * It will use no more than first 8 bits of each array element.
	 */
	static void Store(char * snapshot, I num);

	/**
	 * Restore integral from byte array.
	 * @param snapshot pointer to an array in which number is stored.
	 * @param num vaiable into which restored value should be written.
	 *
	 * @note function is not unpacking snapshot array data if @p char has more than 8 bits.
	 * It always uses first 8 bits.
	 */
	static void Restore(char * snapshot, I & num);
};

template <typename I>
std::size_t RecordableInt<I>::SnapshotSize()
{
	//sizeof returns size in compiler bytes (not necessary 8 bit) + 1 byte for a sign
	return sizeof(I) * CHAR_BYTES + 1;
}

template <typename I>
void RecordableInt<I>::Store(char * snapshot, I num)
{
	typedef unsigned long long cast_t;
	GPX_ASSERT(sizeof(I) <= sizeof(cast_t), "type of number to store exceeds size limit: sizeof(" << sizeof(I) << ") <= sizeof(" << sizeof(cast_t) << ")");

	char sign = num < 0 ? 1 : 0;
	cast_t castval;
	castval = sign ? static_cast<cast_t>(-num) : static_cast<cast_t>(num);
	snapshot[0] = sign;
	for (std::size_t byte = 1; byte < SnapshotSize(); byte++) {
		snapshot[byte] = castval & BYTE_MASK;
		castval >>= BYTE_BITS;
	}
}

template <typename I>
void RecordableInt<I>::Restore(char * snapshot, I & num)
{
	typedef unsigned long long cast_t;
	GPX_ASSERT(sizeof(I) <= sizeof(cast_t), "type of number to store exceeds size limit: sizeof(" << sizeof(I) << ") <= sizeof(" << sizeof(cast_t) << ")");

	char sign = snapshot[0];
	cast_t castval = 0;
	for (std::size_t byte = SnapshotSize() - 1; byte > 0; byte--) {
		castval <<= BYTE_BITS;
		castval |= snapshot[byte] & BYTE_MASK;
	}
	num = sign ? -static_cast<I>(castval) : static_cast<I>(castval);
}

}
}

#endif // RECORDABLEINT_HPP
