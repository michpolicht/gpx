/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GUI_BUTTON_HPP_
#define GPX_Gra_GUI_BUTTON_HPP_

#include <gpx/platform.hpp>
#include <gpx/utils/Observable.hpp>

#include "Widget.hpp"

namespace gpx {
namespace gui {

/**
 * Button.
 */
class GPX_API Button : public Widget,
					   public utils::Observable<Button>
{
	typedef Widget Parent;

	public:
		enum eventType_t {
			EXCITED,
			UNEXCITED,
			PRESSED,
			RELEASED,
			ACTIVATED,
			DEACTIVATED
		};

		struct Properties : public Parent::Properties
		{
			struct Button
			{
				static const bool INITIAL_REBOUND = true;

				bool rebound;

				Button();
			} button;

			Properties(const Parent::Properties & prop);
		};

	public:
		static const bool INITIAL_EXCITED = false;
		static const bool INITIAL_PRESSED = false;
		static const bool INITIAL_ACTIVE = false;

	public:
		Button(WidgetRenderer * renderer, const Properties & defaults = Defaults());

		virtual ~Button();

	public:
		static Properties & Defaults();

	public:
		bool excited() const;

		void setExcited(bool excited);

		bool pressed() const;

		void setPressed(bool pressed);

		bool active() const;

		void setActive(bool active);

		bool rebound() const;

		void setRebound(bool rebound);

		void toggle();

	protected:
		virtual void event(const Widget::Event<StateEvent> & e);

		virtual void event(const Widget::Event<TriggerEvent> & e);

	private:
		Properties::Button m_buttonProps;
		bool m_excited;
		bool m_pressed;
		bool m_active;
};

}
}

#endif /* GPX_Gra_GUI_BUTTON_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
