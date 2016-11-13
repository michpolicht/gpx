#ifndef RECORDABLEFLOAT_HPP
#define RECORDABLEFLOAT_HPP

#include "RecordableInt.hpp"

#include <cstddef>
#include <limits>
#include <cmath>

namespace gpx {
namespace phy {

/**
 * IRecordable interface helper for floating point types.
 * @param F floating point type (float, double, long double).
 */
template <typename F>
struct RecordableFloat
{
	static const int BYTE_BITS = 8; ///< Canonical byte size in bits.
	static const int BYTE_MASK = 0xFF; ///< 8-bit byte mask.
	//char may be != 8 bits (sizeof() = 1 is not necessary 8 bits)
	static const int CHAR_BYTES = std::numeric_limits<unsigned char>::digits / BYTE_BITS;	///< Size of char type in 8-bit bytes.
	static const int MANTISSA_REMAINDER_BITS = std::numeric_limits<F>::digits % BYTE_BITS;	///< Mantissa reminder bits.
	//counting remainder bits as whole byte (1...8 digits = 1 byte, 9...16 = 2 bytes, and so on).
	static const int MANTISSA_BYTES = std::numeric_limits<F>::digits / BYTE_BITS + (MANTISSA_REMAINDER_BITS > 0);	///< Size of F type in 8-bit bytes, counting manitissa remainder bits as whole byte.

	static const int FLAG_SIGN = 0x1;	///< Flag indicates that stored value has negative sign.
	static const int FLAG_QNAN = 0x2;	///< Flag indicates that stored value is quiet NaN.
	static const int FLAG_INF = 0x4;	///< Flag indicates that stored value is infinity.

	/**
	 * Get snapshot size.
	 * @return amount of 8 bit bytes required to store floating point number of type F in byte array.
	 */
	static std::size_t SnapshotSize();

	/**
	 * Store floating point number in byte array. Function will store number in endian
	 * independent fashion.
	 * @param snapshot pointer to an array into which results should be written. Array
	 * must have SnapshotSize() characters allocated to store a number.
	 * @param num number.
	 *
	 * @note function does not pack snapshot array data if @p char has more than 8 bits.
	 * It will use no more than first 8 bits of each array element.
	 */
	static void Store(char * snapshot, F num);

	/**
	 * Restore floating point number from byte array.
	 * @param snapshot pointer to an array in which number is stored.
	 * @param num vaiable into which restored value should be written.
	 *
	 * @note function is not unpacking snapshot array data if @p char has more than 8 bits.
	 * It always uses first 8 bits.
	 */
	static void Restore(char * snapshot, F & num);
};

template <typename F>
std::size_t RecordableFloat<F>::SnapshotSize()
{
	//1 byte for flags + exponent bytes + mantissa bytes
	return 1 + RecordableInt<int>::SnapshotSize() + MANTISSA_BYTES;
}

template <typename F>
void RecordableFloat<F>::Store(char * snapshot, F num)
{
	//write flags and advance pointer
	char flags = 0;
	if (std::signbit(num))
		flags |= FLAG_SIGN;
#if __cplusplus >= 201103L
	if (std::isnan(num))
		flags |= FLAG_QNAN;
	if (std::isinf(num))
		flags |= FLAG_INF;
#else
	#pragma message("C++11 functions not available.")
	if (num != num)
		flags |= FLAG_QNAN;
	if (std::abs(num) == std::numeric_limits<F>::infinity())
		flags |= FLAG_INF;
#endif
	*snapshot = flags;
	snapshot++;

	//write exponent and advance pointer
	F mant;
	int exp;
	mant = std::frexp(num, & exp);
	RecordableInt<int>::Store(snapshot, exp);
	snapshot += RecordableInt<int>::SnapshotSize();

	//write mantissa
	F fract, integral;
	fract = std::fabs(mant);
	for (int i = 0; i < MANTISSA_BYTES; i++) {
		fract = std::modf(std::ldexp(fract, BYTE_BITS), & integral);
		snapshot[i] = static_cast<unsigned char>(integral) & BYTE_MASK;
	}

}

template <typename F>
void RecordableFloat<F>::Restore(char * snapshot, F & num)
{
	//read flags and advance pointer or quit
	char flags = *snapshot;
	bool sign = flags & FLAG_SIGN;
	if (flags & FLAG_INF) {
		num = sign ? -std::numeric_limits<F>::infinity() : std::numeric_limits<F>::infinity();
		return;
	}
	if (flags & FLAG_QNAN) {
		num = std::numeric_limits<F>::quiet_NaN();
		return;
	}
	snapshot++;

	//read exponent
	int exp;
	RecordableInt<int>::Restore(snapshot, exp);
	snapshot += RecordableInt<int>::SnapshotSize();

	//read mantissa
	unsigned char integral;
	num = F();
	for (int i = MANTISSA_BYTES - 1; i >= 0; i--) {
		integral = snapshot[i] & BYTE_MASK;
		num = std::ldexp(num + static_cast<F>(integral), -8);
	}

	//add sign and exponent
	num = sign ? std::ldexp(-num, exp) : std::ldexp(num, exp);
}

}
}

#endif // RECORDABLEFLOAT_HPP
