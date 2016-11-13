/**
 * @file
 * @brief .
 */

#include <iomanip>

#include "../../../include/gpx/gui/FpsWidget.hpp"

namespace gpx {
namespace gui {

const char * FpsWidget::INITIAL_STRING = "fps info N/A";

FpsWidget::FpsWidget(Font * font):
		Parent(INITIAL_STRING, font),
		m_stream(INITIAL_STRING),
		m_fps(0.0),
		m_fpsAvg(0.0),
		m_fpsMin(std::numeric_limits<double>::infinity()),
		m_fpsMax(0.0),
		m_fpsMinTime(0.0),
		m_fpsMaxTime(0.0),
		m_recordShowTime(INITIAL_RECORD_SHOWTIME)
{
	m_stream.setf(std::ios::showpoint | std::ios::fixed | std::ios::left);
	m_stream.precision(1);
}

FpsWidget::~FpsWidget()
{
}

gra2d::RenderContext::time_t FpsWidget::fps() const
{
	return m_fps;
}

gra2d::RenderContext::time_t FpsWidget::fpsAvg() const
{
	return m_fpsAvg;
}

gra2d::RenderContext::time_t FpsWidget::fpsMin() const
{
	return m_fpsMin;
}

gra2d::RenderContext::time_t FpsWidget::fpsMax() const
{
	return m_fpsMax;
}

gra2d::RenderContext::time_t FpsWidget::recordShowtime() const
{
	return m_recordShowTime;
}

void FpsWidget::setRecordShowtime(gra2d::RenderContext::time_t recordShowtime)
{
	m_recordShowTime = recordShowtime;
}

void FpsWidget::render(gra2d::RenderContext * context)
{
	gra2d::RenderContext::time_t frameTime = context->frameTime();
	if (frameTime != 0.0) {
		m_fps = 1.0 / frameTime;
		if (m_fpsMinTime > recordShowtime()) {
			m_fpsMin = std::numeric_limits<gra2d::RenderContext::time_t>::infinity();
			m_fpsMinTime = 0.0;
		}
		m_fps < m_fpsMin ? m_fpsMin = m_fps : m_fpsMinTime += frameTime;
		if (m_fpsMaxTime > recordShowtime())
			m_fpsMax = m_fpsMaxTime = 0.0;
		m_fps > m_fpsMax ? m_fpsMax = m_fps : m_fpsMaxTime += frameTime;
		m_fpsAvg = (m_fpsAvg * 0.995) + (m_fps * 0.005);

		m_stream.clear();
		m_stream.str("");
		m_stream << "fps: " << std::setw(INITIAL_FPS_WIDTH) << m_fps
				 << " avg: " << std::setw(INITIAL_FPS_WIDTH) << m_fpsAvg
				 << " min: " << std::setw(INITIAL_FPS_WIDTH) << m_fpsMin
				 << " max: " << std::setw(INITIAL_FPS_WIDTH) << m_fpsMax;
	}
	setString(m_stream.str());
	setMinWidth(std::max(width(), minWidth()));
	setMinHeight(std::max(height(), minHeight()));
	Parent::render(context);
}


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
