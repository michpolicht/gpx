/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GUI_FONT_HPP_
#define GPX_Gra_GUI_FONT_HPP_

#include <SFML/Graphics/String.hpp>

#include <gpx/utils/Observable.hpp>

#include "../gra/Color.hpp"
#include "FontFamily.hpp"

namespace gpx {
namespace gui {

/**
 * Font. Holds standard font properties like font family, size or color.
 */
class GPX_API Font : public utils::Observable<Font>
{
	public:
		typedef float size_t;
		typedef int style_t;

		enum eventType_t {
				SIZE_CHANGED,
				COLOR_CHANGED,
				STYLE_CHANGED
		};

		enum styleNames_t {
				REGULAR = 0,
				BOLD = 1,
				ITALIC = 2,
				UNDERLINED = 4
		};

	public:
		static const gra::Color INITIAL_COLOR;
		static const style_t INITIAL_STYLE = REGULAR;

	public:
		Font(const FontFamily * family, size_t size);

		virtual ~Font();

	public:
		static void SetDefault(Font * font);

		static Font * Default();

		static unsigned long MapToSFMLStringStyle(style_t style);

	public:
		const FontFamily * family() const;

		size_t size() const;

		void setSize(size_t size);

		int style() const;

		void setStyle(style_t style);

		const gra::Color & color() const;

		void setColor(const gra::Color & color);

		/**
		 * Get maximal character height for current encoding.
		 * @return height of tallest character in the current character set.
		 */
		real_t maxCharHeight() const;

	private:
		static Font * DefaultAlloc(); //allocation is done as static function variable to avoid SFML crash, every time default font is initialized (due to SFML bug)

	private:
		static Font * M_Default;

	private:
		const FontFamily * m_family;
		size_t m_size;
		int m_style;
		gra::Color m_color;
		sf::String m_charsetString;
};



}
}

#endif /* GPX_Gra_GUI_FONT_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
