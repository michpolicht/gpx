/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GUI_LAYOUT_HPP_
#define GPX_Gra_GUI_LAYOUT_HPP_

#include <gpx/utils/IObserver.hpp>

#include "Container.hpp"
#include "BoxOffset.hpp"
#include "LayoutRenderer.hpp"

namespace gpx {
namespace gui {

/**
 * Layout.
 */
class GPX_API Layout : public Container,
					   public virtual utils::IObserver<BoxOffset>
{
	typedef Container Parent;

	public:
		typedef LayoutRenderer Renderer;

		enum halign_t {
				HALIGN_LEFT,
				HALIGN_RIGHT,
				HALIGN_CENTER
		};

		enum valign_t {
				VALIGN_TOP,
				VALIGN_BOTTOM,
				VALIGN_CENTER
		};

		struct Properties : public Parent::Properties
		{
			static const sizePolicy_t INITIAL_WIDTH_POLICY = CHILD_SIZE;
			static const sizePolicy_t INITIAL_HEIGHT_POLICY = CHILD_SIZE;

			struct Layout
			{
				static const real_t INITIAL_SPACING = 5.0;
				static const real_t INITIAL_PADDING = 2.5;
				static const halign_t INITIAL_HALIGN = HALIGN_LEFT;
				static const valign_t INITIAL_VALIGN = VALIGN_TOP;

				BoxOffset spacing;
				BoxOffset padding;
				halign_t halign;
				valign_t valign;

				Layout();
			} layout;

			Properties(const Parent::Properties & prop);
		};

	public:
		Layout(WidgetRenderer * renderer, const Properties & defaults = Defaults());

		virtual ~Layout();

	public:
		static Properties & Defaults();

	public:
		BoxOffset & spacing();

		const BoxOffset & spacing() const;

		BoxOffset & padding();

		const BoxOffset & padding() const;

		halign_t halign() const;

		void setHalign(halign_t halign);

		valign_t valign() const;

		void setValign(valign_t valign);

		//Parent
		virtual void add(Widget * widget);

		//Parent
		virtual void remove(Widget * widget);

		//utils::IObserver<BoxOffset>
		virtual void event(const utils::Observable<BoxOffset>::Event & e);

		virtual void event(const Widget::Event<StateEvent> & e);

		virtual void event(const Widget::Event<ChildEvent> & e);

	protected:
		/**
		 * Repack widgets. Function should traverses whole list of widgets and set up
		 * position, width and height for each widget and layout.
		 */
		virtual void repack() = 0;

	private:
		Properties::Layout m_props;
		bool m_repacking;
};

}
}

#endif /* GPX_Gra_GUI_LAYOUT_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
