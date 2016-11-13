/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy_IMOVABLE_HPP_
#define GPX_Phy_IMOVABLE_HPP_

#include <gpx/utils/IDoubleBuffered.hpp>

namespace gpx {
namespace phy {


/**
 * Movable object interface.
 */
class IMovable
{
	public:
		/**
		 * Update.
		 * @param dt time elapsed from last update. Value 0.0 and positives should be
		 * handled by implementing classes. Result of calling this method with negative
		 * value is undefined.
		 */
		virtual void update(real_t dt) = 0;

		/**
		 * Swap buffers. Swap buffers so that active buffer becomes background and background
		 * buffer becomes active.
		 */
		virtual void swapBuffers() = 0;

	protected:
		~IMovable() {}
};


}
}

#endif /* GPX_Phy_IMOVABLE_HPP_ */
