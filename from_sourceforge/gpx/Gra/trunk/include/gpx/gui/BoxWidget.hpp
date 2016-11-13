/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GUI_BOXWIDGET_HPP_
#define GPX_Gra_GUI_BOXWIDGET_HPP_

#include "Widget.hpp"
#include "BoxOffset.hpp"

namespace gpx {
namespace gui {

/**
 * Box widget.
 *
 * @todo whole class is under construction.
 */
class GPX_API BoxWidget : public Widget,
						  public virtual utils::IObserver<BoxOffset>
{
	typedef Widget Parent;

	public:
		enum areaNames_t {
			PADDING_AREA = Widget::WORK_AREA,
			BORDER_AREA
		};

	public:
		static const BoxOffset INITIAL_BORDER;
		static const BoxOffset INITIAL_PADDING;

	public:
		BoxWidget(WidgetRenderer * renderer);

		virtual ~BoxWidget();

	public:
		static const BoxOffset & DefaultBorder();

		static void SetDefaultBorder(const BoxOffset & border);

		static const BoxOffset & DefaultPadding();

		static void SetDefaultPadding(const BoxOffset & padding);

	public:
		const BoxOffset & border() const;

		BoxOffset & border();

		const BoxOffset & padding() const;

		BoxOffset & padding();

		const BoxOffset & offset() const;

		//IObserver<BoxOffset>
		virtual void event(const utils::Observable<BoxOffset>::Event & e);

	private:
		static BoxOffset M_DefaultBorder;
		static BoxOffset M_DefaultPadding;

	private:
		BoxOffset m_border;
		BoxOffset m_padding;
		BoxOffset m_offset;  //offset including border and padding
};

}
}

#endif /* GPX_Gra_GUI_BOXWIDGET_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
