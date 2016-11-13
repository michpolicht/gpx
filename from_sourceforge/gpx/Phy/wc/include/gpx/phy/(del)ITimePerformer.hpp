/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy_ITIMEPERFORMER_HPP_
#define GPX_Phy_ITIMEPERFORMER_HPP_

#include <gpx/platform.hpp>

namespace gpx {
namespace phy {

/**
 * Time performer. Represents abstract object, which state depends on time.
 */
class ITimePerformer
{
	public:
		/**
		 * Update.
		 * @param dt time elapsed from last update. Value 0.0 and positives should be
		 * handled by implementing classes. Result of calling this method with negative
		 * value is undefined.
		 */
		virtual void update(real_t dt) = 0;
};

}
}


#endif /* GPX_Phy_ITIMEPERFORMER_HPP_ */
