/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_ILOCALFRAME_HPP_
#define GPX_Phy2d_ILOCALFRAME_HPP_

#include <gpx/math/structures.hpp>

namespace gpx {
namespace phy2d {

/**
 * Local frame of reference.
 */
class ILocalFrame
{
	public:
		/**
		 * Map point to global coordinates.
		 * @param point point to be transformed.
		 */
		virtual math::Point<2> mapToGlobal(math::const_PointRef<2> point) const = 0;

		/**
		 * Map point to local coordinates.
		 * @param point point to be transformed.
		 */
		virtual math::Point<2> mapToLocal(math::const_PointRef<2> point) const = 0;

	protected:
		~ILocalFrame() {}
};

}
}

#endif /* GPX_Phy2d_ILOCALFRAME_HPP_ */
