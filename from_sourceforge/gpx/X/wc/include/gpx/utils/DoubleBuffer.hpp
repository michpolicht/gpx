/**
 * @file
 * @brief .
 */

#ifndef GPX_X_UTILS_DOUBLEBUFFER_HPP_
#define GPX_X_UTILS_DOUBLEBUFFER_HPP_

#include "DoubleBufferController.hpp"

namespace gpx {
namespace utils {

/**
 * Double buffer. Double buffer encapsulates two entities of certain data type. The idea
 * is to mark one of them as active and the second one as background. While background
 * data is being overwritten, the active one should remain unchanged. They may be swapped
 * to apply results or, to abandon changes, same entity may be used again for overwrite.
 * Many DoubleBuffer objects may have one controller, thus synchronized swapping can be
 * easily achieved.
 *
 * @see DoubleBufferController.
 */
template <typename T>
class DoubleBuffer
{
	public:
		/**
		 * Constructor. This version of constructor does not explicitly initialize entities.
		 * C++ rules of array initialization are applied. This means initialization depends
		 * on underlying type (builtin types ain't initialized, custom types are initialized
		 * with default constructed value).
		 * @param controller double buffer controller.
		 */
		explicit DoubleBuffer(const DoubleBufferController & controller);

		/**
		 * Constructor.
		 * @param controller double buffer controller.
		 * @param initVal value to initialize active and background entities with.
		 */
		DoubleBuffer(const DoubleBufferController & controller, const T & initVal);

		/**
		 * Constructor.
		 * @param controller double buffer controller.
		 * @param actVal value to initialize active entity with.
		 * @param bgVal value to initialize background entity with.
		 */
		DoubleBuffer(const DoubleBufferController & controller, const T & actVal, const T & bgVal);

		T & active();	//same as operator T &

		const T & active() const; //same as operator const T &

		T & background();

		const T & background() const;

	protected:
		/**
		 * Default constructor.
		 */
		DoubleBuffer() {}

	private:
		T m_buff[2];
		const DoubleBufferController & m_controller;

};

template <typename T>
DoubleBuffer<T>::DoubleBuffer(const DoubleBufferController & controller):
	m_controller(controller)
{
}

template <typename T>
DoubleBuffer<T>::DoubleBuffer(const DoubleBufferController & controller, const T & initVal):
	m_controller(controller)
{
	m_buff[0] = initVal;
	m_buff[1] = initVal;
}

template <typename T>
DoubleBuffer<T>::DoubleBuffer(const DoubleBufferController & controller, const T & actVal, const T & bgVal):
	m_controller(controller)
{
	m_buff[controller.activeBuff()] = actVal;
	m_buff[controller.backgroundBuff()] = bgVal;
}

template <typename T>
inline
T & DoubleBuffer<T>::active()
{
	return m_buff[m_controller.activeBuff()];
}

template <typename T>
inline
const T & DoubleBuffer<T>::active() const
{
	return m_buff[m_controller.activeBuff()];
}

template <typename T>
inline
T & DoubleBuffer<T>::background()
{
	return m_buff[m_controller.backgroundBuff()];
}

template <typename T>
inline
const T & DoubleBuffer<T>::background() const
{
	return m_buff[m_controller.backgroundBuff()];
}


}
}

#endif /* GPX_X_UTILS_DOUBLEBUFFER_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
