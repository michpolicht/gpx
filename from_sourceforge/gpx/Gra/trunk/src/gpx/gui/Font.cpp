/**
 * @file
 * @brief .
 */

#include <gpx/log.hpp>

#include "../../../include/gpx/gui/Font.hpp"

namespace gpx {
namespace gui {

const gra::Color Font::INITIAL_COLOR(0.0, 0.0, 0.0, 1.0);

Font * Font::M_Default = 0;

Font::Font(const FontFamily * family, size_t size):
		m_family(family),
		m_size(size),
		m_style(INITIAL_STYLE),
		m_color(INITIAL_COLOR),
		m_charsetString(family->charset(), *family, size)
{
}

Font::~Font()
{
}

void Font::SetDefault(Font * font)
{
	M_Default = font;
}

Font * Font::Default()
{
	if (M_Default == 0)
		M_Default = DefaultAlloc();
	return M_Default;
}

unsigned long Font::MapToSFMLStringStyle(style_t style)
{
	unsigned long rStyle = sf::String::Regular;
	if (style & Font::BOLD) {
		rStyle |= sf::String::Bold;
		style ^= Font::BOLD;	//toggle bit
	}
	if (style & Font::ITALIC) {
		rStyle |= sf::String::Italic;
		style ^= Font::ITALIC;
	}
	if (style & Font::UNDERLINED) {
		rStyle |= sf::String::Underlined;
		style ^= Font::UNDERLINED;
	}
	if (style != 0)
		GPX_WARN("unrecognized bit(s) in font style mask: " << std::hex << style);
	return rStyle;
}

const FontFamily * Font::family() const
{
	return m_family;
}

Font::size_t Font::size() const
{
	return m_size;
}

void Font::setSize(size_t size)
{
	m_size = size;
	m_charsetString.SetSize(static_cast<float>(size));
	notifyObservers(SIZE_CHANGED);
}

int Font::style() const
{
	return m_style;
}

void Font::setStyle(style_t style)
{
	m_style = style;
	m_charsetString.SetStyle(MapToSFMLStringStyle(style));
	notifyObservers(STYLE_CHANGED);
}

const gra::Color & Font::color() const
{
	return m_color;
}

void Font::setColor(const gra::Color & color)
{
	m_color = color;
	notifyObservers(COLOR_CHANGED);
}

real_t Font::maxCharHeight() const
{
	return static_cast<real_t>(m_charsetString.GetRect().GetHeight());
}

Font * Font::DefaultAlloc()
{
	static FontFamily fontFamily;
	static Font font(& fontFamily, 13.0);
	return & font;
}



}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
