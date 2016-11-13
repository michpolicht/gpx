/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/ContentButton.hpp"

namespace gpx {
namespace gui {

ContentButton::Properties::Properties(const Parent::Properties & prop):
		Parent::Properties(prop)
{
	widthPolicy = INITIAL_WIDTH_POLICY;
	heightPolicy = INITIAL_HEIGHT_POLICY;
}




ContentButton::ContentButton(Widget * content, const Properties & defaults):
		Parent(& m_renderer, defaults),
		m_renderer(this)
{
	init(content);
}

ContentButton::ContentButton(const Properties & defaults):
		Parent(& m_renderer, defaults),
		m_renderer(this)
{
}

void ContentButton::init(Widget * content)
{
	m_content = content;
	if (content) {
		content->setParent(this);
		setMinSize(content->totalSize());
	}
}


ContentButton::~ContentButton()
{
	if (content())
		content()->setParent(0);
}

ContentButton::Properties & ContentButton::Defaults()
{
	static Properties Defaults(Parent::Defaults());
	return Defaults;
}

Widget * ContentButton::content() const
{
	return m_content;
}

void ContentButton::setContent(Widget * content)
{
	m_content->setParent(0);
	m_content = content;
	if (content) {
		m_content->setParent(this);
		setMinSize(m_content->totalSize());
	}
}

void ContentButton::event(const Widget::Event<ChildEvent> & e)
{
	if (e.state() == StateEvent::TOTAL_SIZE_CHANGED)
		setMinSize(e.child()->totalSize());
}


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
