/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/HFlowLayout.hpp"

namespace gpx {
namespace gui {

HFlowLayout::HFlowLayout()
{
}

HFlowLayout::~HFlowLayout()
{
}

void HFlowLayout::repack()
{
	GPX_DEBUG(this << ": repack called");
	setSize(componentsTotalWidth() + padding().horizontal(),
	        componentsMaxHeight() + spacing().vertical() + padding().vertical(), CHILD_SIZE);
	for (WidgetsContainer::iterator wi = widgets().begin(); wi != widgets().end(); ++wi)
		(*wi)->setHeight(height() - padding().vertical() - spacing().vertical(), PARENT_SIZE);
	real_t hoffset = padding().left();
	if (widthPolicy() != CHILD_SIZE) {
		if (halign() == HALIGN_CENTER)
			hoffset += 0.5 * (width() - padding().horizontal() - componentsTotalWidth());
		else if (halign() == HALIGN_RIGHT)
			hoffset += width() - padding().horizontal() - componentsTotalWidth();
		//nothing to do on HALIGN_LEFT
	}
	for (WidgetsContainer::iterator wi = widgets().begin(); wi != widgets().end(); ++wi) {
		hoffset += spacing().left();
		real_t voffset = spacing().top() + padding().top();
		if (valign() == VALIGN_CENTER)
			voffset += 0.5 * (height() - padding().vertical() - spacing().vertical() - (*wi)->totalHeight());
		else if (valign() == VALIGN_BOTTOM)
			voffset += height() - padding().vertical() - spacing().vertical() - (*wi)->totalHeight();
		//nothing to do on VALIGN_TOP
		(*wi)->setPos(hoffset, -voffset);
		hoffset += spacing().right() + (*wi)->totalWidth();
	}
	hoffset += padding().right();
//	childWidth(hoffset);
}

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
