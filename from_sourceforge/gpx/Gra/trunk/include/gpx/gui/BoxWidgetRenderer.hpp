/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GUI_BOXWIDGETRENDERER_HPP_
#define GPX_Gra_GUI_BOXWIDGETRENDERER_HPP_

#include "WidgetRenderer.hpp"

namespace gpx {
namespace gui {

class BoxWidget;

/**
 * Box widget renderer.
 *
 * @todo whole class is under construction.
 */
class GPX_API BoxWidgetRenderer : public WidgetRenderer
{
	typedef WidgetRenderer Parent;

	public:
		enum borderStyle_t {
			BORDER_NONE,
			BORDER_SOLID
		}; //BORDER_RIDGE, BORDER_OUTSET..... (via CSS naming)

		static const gra::Color INITIAL_BORDER_COLOR;
		static const borderStyle_t INITIAL_BORDER_STYLE = BORDER_SOLID;

	public:
		BoxWidgetRenderer(BoxWidget * widget);

		virtual ~BoxWidgetRenderer();

	public:
		const gra::Color & borderColor() const;

		gra::Color & borderColor();

		borderStyle_t borderStyle() const;

		void setBorderStyle(borderStyle_t borderStyle);

		virtual void render(gra2d::RenderContext * context);

	private:
		class IBorderPainter
		{
			public:
				virtual void render(BoxWidget * widget, gra2d::RenderContext * context) = 0;
		};

		/**
		 * Fake border painter. Widget renderer's dummy class.
		 */
		class NoneBorderPainter : public IBorderPainter
		{
			public:
				void render(BoxWidget * widget, gra2d::RenderContext * context);
		};

		/**
		 * Solid border painter. Widget renderer's helper class.
		 */
		class SolidBorderPainter : public IBorderPainter
		{
			public:
				void render(BoxWidget * widget, gra2d::RenderContext * context);

			private:
				Rect m_box;
		};

	private:
		static SolidBorderPainter M_SolidBorderPainter;
		static NoneBorderPainter M_NoneBorderPainter;

	private:
		BoxWidget * m_widget;
		gra::Color m_borderColor;
		borderStyle_t m_borderStyle;
		IBorderPainter * m_borderPainter;
};

}
}

#endif /* GPX_Gra_GUI_BOXWIDGETRENDERER_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
