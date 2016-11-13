/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_FPSWIDGET_HPP_
#define GPX_Gra_FPSWIDGET_HPP_

#include "Text.hpp"

#include <sstream>

namespace gpx {
namespace gui {

class GPX_API FpsWidget : public Text
{
	typedef Text Parent;

	public:
		typedef FpsWidget Renderer;

	public:
		static const char * INITIAL_STRING;
		static const gra2d::RenderContext::time_t INITIAL_RECORD_SHOWTIME = 30.0;	//seconds
		static const int INITIAL_FPS_WIDTH = 10;

	public:
		FpsWidget(Font * font = Font::Default());

		virtual ~FpsWidget();

		virtual void render(gra2d::RenderContext * context);

		gra2d::RenderContext::time_t fps() const;

		gra2d::RenderContext::time_t fpsAvg() const;

		gra2d::RenderContext::time_t fpsMin() const;

		gra2d::RenderContext::time_t fpsMax() const;

		gra2d::RenderContext::time_t recordShowtime() const;

		void setRecordShowtime(gra2d::RenderContext::time_t recordShowtime);

	private:
		std::ostringstream m_stream;
		gra2d::RenderContext::time_t m_fps;
		gra2d::RenderContext::time_t m_fpsAvg;
		gra2d::RenderContext::time_t m_fpsMin;
		gra2d::RenderContext::time_t m_fpsMax;
		gra2d::RenderContext::time_t m_fpsMinTime;
		gra2d::RenderContext::time_t m_fpsMaxTime;
		gra2d::RenderContext::time_t m_recordShowTime;
};

}
}

#endif /* GPX_Gra_FPSWIDGET_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
