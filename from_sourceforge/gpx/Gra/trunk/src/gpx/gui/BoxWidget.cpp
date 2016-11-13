/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/BoxWidget.hpp"

namespace gpx {
namespace gui {

const BoxOffset BoxWidget::INITIAL_BORDER(5.0);
const BoxOffset BoxWidget::INITIAL_PADDING(5.0);


BoxWidget::BoxWidget(WidgetRenderer * renderer):
		Parent(renderer),
		m_border(BoxWidget::DefaultBorder()),
		m_padding(BoxWidget::DefaultPadding()),
		m_offset(m_border + m_padding)
{
}

BoxWidget::~BoxWidget()
{
}

const BoxOffset & BoxWidget::DefaultBorder()
{
	return M_DefaultBorder;
}

void BoxWidget::SetDefaultBorder(const BoxOffset & border)
{
	M_DefaultBorder = border;
}

const BoxOffset & BoxWidget::DefaultPadding()
{
	return M_DefaultPadding;
}

void BoxWidget::SetDefaultPadding(const BoxOffset & padding)
{
	M_DefaultPadding = padding;
}

BoxOffset & BoxWidget::border()
{
	return m_border;
}

const BoxOffset & BoxWidget::border() const
{
	return m_border;
}

BoxOffset & BoxWidget::padding()
{
	return m_padding;
}

const BoxOffset & BoxWidget::padding() const
{
	return m_padding;
}

const BoxOffset & BoxWidget::offset() const
{
	return m_offset;
}

void BoxWidget::event(const utils::Observable<BoxOffset>::Event & )
{
	//TODO
//	if (e.observable() == & border()) {
//		m_offset = border() + padding();
//		//child event border changed
//	} else if (e.observable() == & padding()) {
//		m_offset = border() + padding();
////		m_box.setX(-padding().left());
////		m_box.setY(-padding().bottom());
//		m_box.setWidth(width() + padding().horizontal());
//		m_box.setHeight(height() + padding().vertical());
//	}
//	//TODO
////	if (e.observable() == & m_border) {
////		//child event border changed
////	}
}


BoxOffset BoxWidget::M_DefaultBorder(INITIAL_BORDER);
BoxOffset BoxWidget::M_DefaultPadding(INITIAL_PADDING);


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
