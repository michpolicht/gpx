/**
 * @file
 * @brief .
 */

#ifndef GPX_X_UTILS_FUNCTIONS_HPP_
#define GPX_X_UTILS_FUNCTIONS_HPP_

#include <cstddef>

namespace gpx {
namespace utils {

/**
 * Hash function template. For use with types easily convertible to std::size_t (like pointers).
 */
template<typename T>
struct hash
{
	std::size_t operator()(const T & i) const
	{
		//reinterpret_cast would trigger error if size_t is smaller than referenced type.
		//Explicit cast will overflow and this is eligible for hash function.
		return (std::size_t)i;
	}
};

}
}

#endif /* GPX_X_UTILS_FUNCTIONS_HPP_ */
