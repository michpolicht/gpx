#ifndef GPX_PHY2D_CNEWTON_PMEPP2_S_INTROSPECTOR_HPP
#define GPX_PHY2D_CNEWTON_PMEPP2_S_INTROSPECTOR_HPP

#include "ICFixed.hpp"
#include "Cluster.hpp"

#include <gpx/utils/Array.hpp>

namespace gpx {
namespace phy2d {
namespace cnewton {
namespace pmepp2_s {

/**
 * Introspector. Debugging tool, which provides a way for objects to introspect themselves.
 */
class GPX_API Introspector
{
	public:
		Introspector();

		void triggerError(const char * msg);

		void resetError();

		bool error() const;

		const char * errorMsg() const;

		virtual void setSkipBreakpoints(bool skip);

		virtual void breakpoint();

		virtual void off(const ICFixed & fixed);

		virtual void light(const ICFixed & fixed);

		virtual void highlight(const ICFixed & fixed);

		virtual void playdown(const ICFixed & fixed);

	private:
		static const char * DEFAULT_ERROR_MSG;

		bool m_error;
		const char * m_errorMsg;
};

}
}
}
}

#endif /* GPX_PHY2D_CNEWTON_PMEPP2_S_INTROSPECTOR_HPP */
