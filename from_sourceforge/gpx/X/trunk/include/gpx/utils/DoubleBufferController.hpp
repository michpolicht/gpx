/**
 * @file
 * @brief .
 */

#ifndef GPX_X_UTILS_DOUBLEBUFFERCONTROLLER_HPP_
#define GPX_X_UTILS_DOUBLEBUFFERCONTROLLER_HPP_

namespace gpx {
namespace utils {

/**
 * Double buffer controller. Double buffer controller performs swap operation on related
 * double buffers.
 *
 * @see DoubleBuffer.
 *
 * @todo make swapBuffers() truly atomic.
 */
class DoubleBufferController
{
	public:
		typedef bool buff_t;

	public:
		/**
		 * Default constructor. Initializes with active buffer 0.
		 */
		DoubleBufferController(): m_activeBuff(0) {};

		/**
		 * Destructor.
		 */
		virtual ~DoubleBufferController() {};

		/**
		 * Get active buffer.
		 * @return number of buffer which is active (0|1).
		 */
		buff_t activeBuff() const;

		/**
		 * Get background buffer.
		 * @return number of buffer which is background (0|1).
		 */
		buff_t backgroundBuff() const;

		/**
		 * Swap buffers.
		 */
		void swapBuffers();

	protected:
		buff_t m_activeBuff;
};

inline
DoubleBufferController::buff_t DoubleBufferController::activeBuff() const
{
	return m_activeBuff;
}

inline
DoubleBufferController::buff_t DoubleBufferController::backgroundBuff() const
{
	return m_activeBuff ^ 0x1;
}

inline
void DoubleBufferController::swapBuffers()
{
	m_activeBuff ^= 0x1;	//this should
}


}
}

#endif /* GPX_X_UTILS_DOUBLEBUFFERCONTROLLER_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
