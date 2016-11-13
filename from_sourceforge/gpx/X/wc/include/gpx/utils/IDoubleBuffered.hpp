/**
 * @file
 * @brief .
 */

#ifndef GPX_X_UTILS_IDOUBLEBUFFERED_HPP_
#define GPX_X_UTILS_IDOUBLEBUFFERED_HPP_

namespace gpx {
namespace utils {

/**
 * Double buffered interface. Whenever object is double buffered it may implement this
 * interface.
 */
class IDoubleBuffered
{
	public:
		/*
		 * Swap buffers. Swap buffers so that active buffer becomes background and background
		 * buffer becomes active.
		 */
		virtual void swapBuffers() = 0;
};

}
}

#endif /* GPX_X_UTILS_IDOUBLEBUFFERED_HPP_ */
