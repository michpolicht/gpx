#ifndef INTROSPECTOR_HPP
#define INTROSPECTOR_HPP

#include "graphics/Renderer.hpp"

#include <gpx/phy2d/cnewton/pmepp2_s/Introspector.hpp>
#include <gpx/phy_config.hpp>
#include <gpx/ext/UnorderedMap.hpp>

namespace pmepp2_s {

class Introspector : public gpx::phy2d::cnewton::pmepp2_s::Introspector
{
	typedef gpx::phy2d::cnewton::pmepp2_s::Introspector Parent;
	typedef gpx::phy2d::cnewton::pmepp2_s::ICFixed ICFixed;
	typedef gpx::phy2d::cnewton::pmepp2_s::Cluster Cluster;
	typedef gpx::phy2d::cnewton::pmepp2_s::DetectionDataContainer DetectionDataContainer;

	public:
		Introspector(gpx::gra::RenderWindow & win, gpx::gra2d::View & view);

		void associate(const ICFixed * const fixed, Renderer * const renderer);

		void toggleSkipBreakpoints();

		virtual void setSkipBreakpoints(bool skip);

		virtual void breakpoint();

		virtual void light(const ICFixed & fixed);

		virtual void off(const ICFixed & fixed);

		virtual void highlight(const ICFixed & fixed);

		virtual void playdown(const ICFixed & fixed);

	private:
		void refreshDisplay();

		void waitForUser();

		typedef gpx::ext::UnorderedMap<const ICFixed *, Renderer *> AssocContainer;
		AssocContainer m_assoc;
		gpx::gra::RenderWindow & m_win;
		gpx::gra2d::View & m_view;
		bool m_skipBreakpoints;
};

}

#endif // INTROSPECTOR_HPP
