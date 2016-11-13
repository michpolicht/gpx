/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/Text.hpp"
#include "../../../include/gpx/gui/RenderTarget.hpp"

namespace gpx {
namespace gui {


Text::Properties::Properties(const Widget::Properties & widgetProp, const WidgetRenderer::Properties & rendererProp):
		Widget::Properties(widgetProp),
		WidgetRenderer::Properties(rendererProp)
{
	workareaStyle = INITIAL_WORKAREA_STYLE;
}

Text::Properties::Text::Text():
		heightPolicy(INITIAL_HEIGHT_POLICY)
{
}




Text::Text(const sf::Unicode::Text & string, Font * font, const Properties & defaults):
		Widget(this, defaults),
		WidgetRenderer(this, defaults),
		m_font(font),
		m_stringRenderer(string, font),
		m_textProps(defaults.text)
{
	m_font->addObserver(this);
	real_t width = static_cast<real_t>(m_stringRenderer.GetRect().GetWidth());
	setSize(width, heightForPolicy());
}

Text::~Text()
{
	m_font->removeObserver(this);
}

Text::Properties & Text::Defaults()
{
	static Properties Defaults(Widget::Defaults(), WidgetRenderer::Defaults());
	return Defaults;
}

const sf::Unicode::Text & Text::string() const
{
	return m_stringRenderer.GetText();
}

void Text::setString(const sf::Unicode::Text & string)
{
	m_stringRenderer.SetText(string);
	real_t width = static_cast<real_t>(m_stringRenderer.GetRect().GetWidth());
	setSize(width, heightForPolicy());
}


Font * Text::font() const
{
	return m_font;
}

void Text::setFont(Font * font)
{
	m_font->removeObserver(this);
	m_font = font;
	m_font->addObserver(this);

	m_stringRenderer.setFont(font);
	real_t width = static_cast<real_t>(m_stringRenderer.GetRect().GetWidth());
	setSize(width, heightForPolicy());
}

Text::heightPolicy_t Text::heightPolicy() const
{
	return m_textProps.heightPolicy;
}

void Text::setHeightPolicy(heightPolicy_t heightPolicy)
{
	m_textProps.heightPolicy = heightPolicy;
	setHeight(heightForPolicy());
}

void Text::event(const utils::Observable<Font>::Event & e)
{
	switch (e.type()) {
		case Font::SIZE_CHANGED:
			m_stringRenderer.SetSize(e.observable()->size());
			break;
		case Font::STYLE_CHANGED:
			m_stringRenderer.setFontStyle(e.observable()->style());
			break;
		default:
			GPX_WARN("unrecognized event type: " << e.type());
	}
	real_t width = static_cast<real_t>(m_stringRenderer.GetRect().GetWidth());
	setSize(width, heightForPolicy());
}

void Text::render(gra2d::RenderContext * context)
{
	WidgetRenderer::render(context);
	glScale(1.0, -1.0, 1.0);
	m_stringRenderer.render(context, font()->color());
}

real_t Text::heightForPolicy() const
{
	switch (heightPolicy()) {
		case CHARSET_MAX_HEIGHT:
			return font()->maxCharHeight();
		case STRING_MAX_HEIGHT:
			return static_cast<real_t>(m_stringRenderer.GetRect().GetHeight());
		default:
			GPX_WARN("unknown height policy code: " << heightPolicy());
			return font()->maxCharHeight();
	}
}




Text::StringRenderer::StringRenderer(const sf::Unicode::Text & text, Font * font):
		Parent(text, *(font->family()), static_cast<float>(font->size()))
{
	setFontStyle(font->style());
}

Text::StringRenderer::~StringRenderer()
{
}

void Text::StringRenderer::setFont(Font * font)
{
	SetFont(*(font->family()));
	SetSize(static_cast<float>(font->size()));
	setFontStyle(font->style());
}

void Text::StringRenderer::setFontStyle(Font::style_t style)
{
	SetStyle(Font::MapToSFMLStringStyle(style));
}

void Text::StringRenderer::render(gra2d::RenderContext * context, const gra::Color & color)
{
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_TEXTURE_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		color.glSetRgba();
		RenderTarget target(context);
		Render(target);
	glPopAttrib();
}


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
