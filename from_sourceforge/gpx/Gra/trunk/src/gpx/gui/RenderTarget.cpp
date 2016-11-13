/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/RenderTarget.hpp"
#include "../../../include/gpx/gra2d/RenderContext.hpp"
#include "../../../include/gpx/gra2d/View.hpp"

namespace gpx {
namespace gui {

RenderTarget::RenderTarget(gra2d::RenderContext * context):
		m_context(context)
{
}

RenderTarget::~RenderTarget()
{
}

unsigned int RenderTarget::GetWidth() const
{
	return static_cast<unsigned int>(m_context->currentView()->viewport().width());
}

unsigned int RenderTarget::GetHeight() const
{
	return static_cast<unsigned int>(m_context->currentView()->viewport().height());
}

void RenderTarget::draw(const sf::Drawable & drawable)
{
	Parent::Draw(drawable);
}

bool RenderTarget::Activate(bool Active)
{
	return Active;
}



}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
