/**
 * @file
 * @brief .
 */

#ifndef GPX_X_UTILS_CONDITIONAL_HPP_
#define GPX_X_UTILS_CONDITIONAL_HPP_

namespace gpx {
namespace utils {

/**
 * Conditional variable.
 */
template <typename T, typename S = bool>
class Conditional
{
	public:
		Conditional();

		Conditional(T val);

		Conditional(S state, T val = T());

		operator S() const;

		T operator *() const;

		S state() const;

		const T & val() const;

	private:
		S m_state;
		T m_val;
};



template <typename T, typename S>
inline
Conditional<T, S>::Conditional():
		m_state(false)
{
}

template <typename T, typename S>
inline
Conditional<T, S>::Conditional(T val):
		m_state(true),
		m_val(val)
{
}

template <typename T, typename S>
inline
Conditional<T, S>::Conditional(S state, T val):
		m_state(state),
		m_val(val)
{
}

template <typename T, typename S>
inline
Conditional<T, S>::operator S() const
{
	return state();
}

template <typename T, typename S>
inline
T Conditional<T, S>::operator *() const
{
	return m_val;
}

template <typename T, typename S>
inline
S Conditional<T, S>::state() const
{
	return m_state;
}

template <typename T, typename S>
inline
const T & Conditional<T, S>::val() const
{
	return m_val;
}


}
}

#endif /* GPX_X_UTILS_CONDITIONAL_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
