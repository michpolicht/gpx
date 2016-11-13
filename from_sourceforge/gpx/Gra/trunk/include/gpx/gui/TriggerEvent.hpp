/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GUI_TRIGGEREVENT_HPP_
#define GPX_Gra_GUI_TRIGGEREVENT_HPP_

#include <gpx/math/structures.hpp>

namespace gpx {
namespace gui {

class TriggerEvent
{
	public:
		typedef unsigned int type_t;

		enum typeNames_t {
			PRIMARY,
			SECONDARY,
			TERTIARY,
			QUATERNARY,
			QUINARY,
			SENARY,
			SEPTENARY,
			OCTONARY,
			NONARY,
			DENARY
		};

		enum action_t {
			PRESS,
			RELEASE
//			DOUBLE_RELEASE
		};

	public:
		TriggerEvent(action_t action, type_t type, real_t x, real_t y);

		TriggerEvent(action_t action, type_t type, int x, int y);

		TriggerEvent(action_t action, type_t type, math::const_PointRef<2> pos);

		action_t action() const;

		type_t type() const;

		real_t x() const;

		real_t y() const;

	private:
		action_t m_action;
		type_t m_type;
		real_t m_x;
		real_t m_y;
};

inline
TriggerEvent::TriggerEvent(action_t action, type_t type, real_t x, real_t y):
		m_action(action),
		m_type(type),
		m_x(x),
		m_y(y)
{
}

inline
TriggerEvent::TriggerEvent(action_t action, type_t type, int x, int y):
		m_action(action),
		m_type(type),
		m_x(static_cast<real_t>(x)),
		m_y(static_cast<real_t>(y))
{
}

inline
TriggerEvent::TriggerEvent(action_t action, type_t type, math::const_PointRef<2> pos):
		m_action(action),
		m_type(type),
		m_x(pos[0]),
		m_y(pos[1])
{
}

inline
TriggerEvent::action_t TriggerEvent::action() const
{
	return m_action;
}

inline
TriggerEvent::type_t TriggerEvent::type() const
{
	return m_type;
}

inline
real_t TriggerEvent::x() const
{
	return m_x;
}

inline
real_t TriggerEvent::y() const
{
	return m_y;
}


}
}


#endif /* GPX_Gra_GUI_TRIGGEREVENT_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
