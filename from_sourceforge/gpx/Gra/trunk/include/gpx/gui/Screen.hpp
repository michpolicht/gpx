/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GUI_SCREEN_HPP_
#define GPX_Gra_GUI_SCREEN_HPP_

#include "ViewDispatcher.hpp"
#include "../gra/Viewport.hpp"

namespace gpx {
namespace gui {

/**
 * Private screen allocator. Allocates scene and view objects according to base-from-member
 * idiom.
 *
 * @see http://www.boost.org/doc/libs/1_44_0/libs/utility/base_from_member.html.
 */
class private_ScreenAllocator
{
	public:
		gra2d::Scene m_scene;
		gra2d::View m_view;

	protected:
		private_ScreenAllocator(Dispatcher & dispatcher);
};

/**
 * Screen. It is convenient class when widgets are added to a dedicated view and scene.
 * It provides its own scene and view and takes care about dispatching events.
 * One has to call update() in order to update the view.
 */
class GPX_API Screen : private private_ScreenAllocator,
					   public ViewDispatcher,
					   public utils::IObserver<gra::Viewport>
{
	typedef ViewDispatcher Parent;

	public:
		Screen(Dispatcher & dispatcher);

		/**
		 * Destructor. Widgets will be removed from scene during destruction.
		 */
		virtual ~Screen();

	public:
		/**
		 * Add widget. Widget will be added to the scene, positioned at upper left corner
		 * of the scene (0.0, scene height) and resized to the scene size if it uses
		 * gui::Widget::PARENT_SIZE policy. Widgets are removed from scene during
		 * destruction.
		 * @param widget widget to be added.
		 */
		void add(Widget * widget);

		/**
		 * Remove widget.
		 * @param widget widget to remove.
		 */
		void remove(Widget * widget);

		/**
		 * Updates the view.
		 */
		void update();

		virtual void event(const utils::Observable<gra::Viewport>::Event & e);

	protected:
		//note: const view getter in the parent
		gra2d::View & view();

		gra2d::Scene & scene();

		const gra2d::Scene & scene() const;
};


}
}

#endif /* GPX_Gra_GUI_SCREEN_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
