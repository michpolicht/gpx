#ifndef SEGMENTPRINT_HPP
#define SEGMENTPRINT_HPP

#include "Segment.hpp"
#include "SegmentPtr.hpp"
#include "const_SegmentPtr.hpp"

#include <limits>

namespace gpx {
namespace model {

template <std::size_t DIM, typename T = real_t>
struct SegmentPrint
{
	static int Precision;
};

template<std::size_t DIM, typename T>
int SegmentPrint<DIM, T>::Precision = std::numeric_limits<T>::digits10 + 2;

}
}

/**
 * Output stream operator for segment types.
 * @param s output stream.
 * @param seg segment object.
 */
template <std::size_t DIM, typename T>
std::ostream & operator <<(std::ostream & s, gpx::model::const_SegmentPtr<DIM, T> seg)
{
	s.precision(gpx::model::SegmentPrint<DIM, T>::Precision);
	s << "(";
	for (std::size_t i = 0; i < DIM - 1; i++)
		s << seg->first(i) << ", ";
	s << seg->first(DIM - 1) << ") -> (";
	for (std::size_t i = 0; i < DIM - 1; i++)
		s << seg->second(i) << ", ";
	s << seg->second(DIM - 1) << ")" << std::endl;
	return s;
}

template <std::size_t DIM, typename T>
std::ostream & operator <<(std::ostream & s, const gpx::model::SegmentPtr<DIM, T> & seg)
{
	return operator <<(s, gpx::model::const_SegmentPtr<DIM, T>(seg));
}

template <std::size_t DIM, typename T>
std::ostream & operator <<(std::ostream & s, const gpx::model::Segment<DIM, T> & seg)
{
	return operator <<(s, gpx::model::const_SegmentPtr<DIM, T>(& seg));
}

#endif // SEGMENTPRINT_HPP
