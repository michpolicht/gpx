/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GUI_SCROLLEVENT_HPP_
#define GPX_Gra_GUI_SCROLLEVENT_HPP_

namespace gpx {
namespace gui {

struct ScrollEvent
{
	public:
		enum axis_t {
			VERTICAL,
			HORIZONTAL,
			DEPTH
		};

	public:
		ScrollEvent(axis_t axis, int delta);

		axis_t axis() const;

		int delta() const;

	private:
		axis_t m_axis;
		int m_delta;
};

inline
ScrollEvent::ScrollEvent(axis_t axis, int delta):
		m_axis(axis),
		m_delta(delta)
{
}

inline
ScrollEvent::axis_t ScrollEvent::axis() const
{
	return m_axis;
}

inline
int ScrollEvent::delta() const
{
	return m_delta;
}


}
}

#endif /* GPX_Gra_GUI_SCROLLEVENT_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
