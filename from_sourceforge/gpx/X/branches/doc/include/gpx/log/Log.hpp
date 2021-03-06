/**
 * @file
 * @brief .
 */

#ifndef GPX_X_LOG_LOG_HPP_
#define GPX_X_LOG_LOG_HPP_

#include "../utils/NonCopyable.hpp"
#include "LogStream.hpp"

namespace gpx {
namespace log {

/**
 * Log. Main class of GPX log facility.
 *
 * This class is a singleton and can not be instantiated directly. To obtain instance
 * use Instance() function. For convenient usage of this class five macros are defined,
 * in separate header, for logging purposes (GPX_DEBUG, GPX_NOTE, GPX_WARN, GPX_FATAL,
 * GPX_INFO).
 *
 * Log class defines five streams which are instances of LogStream class. Each of them
 * may be attached to any number of other streams. For example, to bring debug output
 * to std::cout, attach std::cout to debug stream. Five basic streams are:
 * 	- debug stream - used by GPX_DEBUG macro. Obtain it by calling debugStream().
 * 	- note stream - used by GPX_NOTE macro. Obtain it by calling noteStream().
 * 	- warn stream - used by GPX_WARN macro. Obtain it by calling warnStream().
 * 	- fatal stream - used by GPX_FATAL macro. Obtain it by calling fatalStream().
 * 	- info stream - used by GPX_INFO macro. Obtain it by calling infoStream().
 *  .
 * There is also special sixth stream which is not used directly by any macro:
 * 	- combined stream - obtain it by calling combinedStream().
 *  .
 * Combined stream is already attached to five previously described streams. By attaching
 * std::cout to combined stream, all five streams will put the output, through combined
 * stream, to std::cout.
 */
class Log : utils::NonCopyable
{
	public:
		/**
		 * Get Log singleton instance.
		 * @return Log instance.
		 */
		static Log & Instance();

	public:
		/**
		 * Get debug stream.
		 * @return debug stream.
		 *
		 * @see GPX_DEBUG.
		 */
		LogStream & debugStream();

		/**
		 * Get notice stream.
		 * @return notice stream.
		 *
		 * @see GPX_NOTE.
		 */
		LogStream & noteStream();

		/**
		 * Get warn stream.
		 * @return warn stream.
		 *
		 * @see GPX_WARN.
		 */
		LogStream & warnStream();

		/**
		 * Get fatal stream.
		 * @return fatal stream.
		 *
		 * @see GPX_FATAL.
		 */
		LogStream & fatalStream();

		/**
		 * Get info stream.
		 * @return info stream.
		 *
		 * @see GPX_INFO.
		 */
		LogStream & infoStream();

		/**
		 * Get combined stream.
		 * @return combined stream.
		 */
		LogStream & combinedStream();

		/**
		 * Attach log. Attaches respectively five streams (without combined) of other log to
		 * streams of this log.
		 * @param other other log.
		 *
		 * @note this function is useful when working with libraries.
		 *
		 * @see detachLog().
		 */
		void attachLog(Log & other);

		/**
		 * Detach log. Detaches respectively five streams (without combined) of other log
		 * from streams of this log.
		 * @param other other log.
		 *
		 * @see attachLog().
		 */
		void detachLog(Log & other);

	private:
		/**
		 * Default constructor. This class is a singleton and can not be instantiated
		 * directly. Use Instance() method instead.
		 */
		Log();

	private:
		LogStream m_combinedStream;
		LogStream m_debugStream;
		LogStream m_noteStream;
		LogStream m_warnStream;
		LogStream m_fatalStream;
		LogStream m_infoStream;
};

inline
Log & Log::Instance()
{
	static Log instance;
	return instance;
}

inline
LogStream & Log::debugStream()
{
	return m_debugStream;
}

inline
LogStream & Log::noteStream()
{
	return m_noteStream;
}

inline
LogStream & Log::warnStream()
{
	return m_warnStream;
}

inline
LogStream & Log::fatalStream()
{
	return m_fatalStream;
}

inline
LogStream & Log::infoStream()
{
	return m_infoStream;
}

inline
LogStream & Log::combinedStream()
{
	return m_combinedStream;
}

inline
void Log::attachLog(Log & other)
{
	m_debugStream.attachStream(other.debugStream());
	m_noteStream.attachStream(other.noteStream());
	m_warnStream.attachStream(other.warnStream());
	m_fatalStream.attachStream(other.fatalStream());
	m_infoStream.attachStream(other.infoStream());
}

inline
void Log::detachLog(Log & other)
{
	m_debugStream.detachStream(other.debugStream());
	m_noteStream.detachStream(other.noteStream());
	m_warnStream.detachStream(other.warnStream());
	m_fatalStream.detachStream(other.fatalStream());
	m_infoStream.detachStream(other.infoStream());
}

inline
Log::Log()
{
	m_debugStream.attachStream(m_combinedStream);
	m_noteStream.attachStream(m_combinedStream);
	m_warnStream.attachStream(m_combinedStream);
	m_fatalStream.attachStream(m_combinedStream);
	m_infoStream.attachStream(m_combinedStream);
}

}
}

#endif /* GPX_X_LOG_LOG_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
