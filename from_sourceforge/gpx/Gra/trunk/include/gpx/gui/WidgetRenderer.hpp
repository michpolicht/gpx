/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GUI_WIDGETRENDERER_HPP_
#define GPX_Gra_GUI_WIDGETRENDERER_HPP_

#include "Rect.hpp"
#include "../gra/Color.hpp"
#include "../gra2d/GraphicsObjectRenderer.hpp"

namespace gpx {
namespace gui {

class Widget;

/**
 * Widget renderer.
 */
class GPX_API WidgetRenderer : public gra2d::GraphicsObjectRenderer
{
	typedef gra2d::GraphicsObjectRenderer Parent;

	public:
		//Prefixes are crucial because wingdi.h "cleverly" polluted global namespace
		enum workareaStyle_t {
			WORKAREA_NONE,
			WORKAREA_OPAQUE,
			WORKAREA_FRAME
		};	//WORKAREA_TEXTURE...

		struct Properties
		{
			static const workareaStyle_t INITIAL_WORKAREA_STYLE = WORKAREA_OPAQUE;
			static const gra::Color INITIAL_WORKAREA_COLOR; //SIOF!

			workareaStyle_t workareaStyle;
			gra::Color workareaColor;

			Properties();
		};

	public:
		WidgetRenderer(const Widget * widget, const Properties & defaults = Defaults());

		virtual ~WidgetRenderer();

	public:
		/**
		 * Widget renderer defaults.
		 * @return default values used to construct object.
		 */
		static Properties & Defaults();

	public:
		const Widget * widget() const;

		workareaStyle_t workareaStyle() const;

		void setWorkareaStyle(workareaStyle_t workareaStyle);

		const gra::Color & workareaColor() const;

		gra::Color & workareaColor();

		virtual void render(gra2d::RenderContext * context);

	private:
		const Widget * m_widget;
		Properties m_props;
};


}
}

#endif /* GPX_Gra_GUI_WIDGETRENDERER_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
