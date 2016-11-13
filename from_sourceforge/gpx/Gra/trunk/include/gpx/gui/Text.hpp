/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GUI_TEXT_HPP_
#define GPX_Gra_GUI_TEXT_HPP_

#include <SFML/System/Unicode.hpp>
#include <SFML/Graphics/String.hpp>

#include "WidgetRenderer.hpp"
#include "Widget.hpp"
#include "Font.hpp"

namespace gpx {
namespace gui {

class GPX_API Text : public Widget,
					 public WidgetRenderer,
					 public virtual utils::IObserver<Font>
{
	public:
		typedef Text Renderer;

		enum heightPolicy_t {
				CHARSET_MAX_HEIGHT,
				STRING_MAX_HEIGHT
		};

		struct Properties : public Widget::Properties,
						    public WidgetRenderer::Properties
		{
			static const workareaStyle_t INITIAL_WORKAREA_STYLE = WORKAREA_NONE;

			struct Text
			{
				static const heightPolicy_t INITIAL_HEIGHT_POLICY = CHARSET_MAX_HEIGHT;

				heightPolicy_t heightPolicy;

				Text();
			} text;

			Properties(const Widget::Properties & widgetProp, const WidgetRenderer::Properties & rendererProp);
		};

	public:
		explicit Text(const sf::Unicode::Text & string, Font * font = Font::Default(), const Properties & defaults = Defaults());

		virtual ~Text();

	public:
		static Properties & Defaults();

	public:
		const sf::Unicode::Text & string() const;

		void setString(const sf::Unicode::Text & string);

		Font * font() const;

		void setFont(Font * font);

		heightPolicy_t heightPolicy() const;

		void setHeightPolicy(heightPolicy_t heightPolicy);

		//utils::IObserver<Font>
		virtual void event(const utils::Observable<Font>::Event & e);

		//Widget
		virtual void render(gra2d::RenderContext * context);

	protected:
		class StringRenderer : public sf::String
		{
			typedef sf::String Parent;

			public:
				StringRenderer(const sf::Unicode::Text & text, Font * font);

				virtual ~StringRenderer();

				void setFont(Font * font);

				void setFontStyle(Font::style_t style);

				virtual void render(gra2d::RenderContext * context, const gra::Color & color);
		};

	private:
		real_t heightForPolicy() const;

	private:
		Font * m_font;
		StringRenderer m_stringRenderer;
		Properties::Text m_textProps;
};

}
}

#endif /* GPX_Gra_GUI_TEXT_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
