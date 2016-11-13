/**
 * @file
 * @brief .
 */

#ifndef GPX_X_LOG_LOGSTREAM_HPP_
#define GPX_X_LOG_LOGSTREAM_HPP_

#include "LogBuf.hpp"

namespace gpx {
namespace log {

/**
 * Log stream.
 */
class LogStream: public std::ostream
{
	public:
		/**
		 * Default constructor.
		 */
		LogStream();

		/**
		 * Destructor.
		 */
		virtual ~LogStream();

	public:
		/**
		 * Get internal buffer.
		 * @return pointer to LogBuf object.
		 *
		 * @note this is overloaded member of std::ostream class.
		 */
		LogBuf * rdbuf();

		/**
		 * Attach stream buffer. Attaches buffer pointed by @a buf to LogStream's
		 * internal LogBuf buffer.
		 * @param buf pointer to std::streambuf object.
		 *
		 * @see rdbuf(), detachBuffer(), attachStream().
		 */
		void attachBuffer(std::streambuf * buf);

		/**
		 * Detach stream buffer.
		 * @param buf pointer to std::streambuf object.
		 *
		 * @see attachBuffer(), detachStream().
		 */
		void detachBuffer(std::streambuf * buf);

		/**
		 * Attach stream's buffer. This function is defined for convenience,
		 * it attaches @a stream 's internal buffer to LogStream's internal
		 * LogBuf buffer.
		 * @param stream reference to std::ostream object.
		 *
		 * @see attachBuffer(), detachStream().
		 */
		void attachStream(std::ostream & stream);

		/**
		 * Detach stream's buffer.
		 * @param stream reference to std::ostream object.
		 *
		 * @see detachBuffer(), attachStream().
		 */
		void detachStream(std::ostream & stream);

	private:
		LogBuf m_logBuf;
};


inline
LogStream::LogStream():
	std::ostream(& m_logBuf)
{
};

inline
LogStream::~LogStream()
{
};

inline
LogBuf * LogStream::rdbuf()
{
	return & m_logBuf;
}

inline
void LogStream::attachBuffer(std::streambuf * buf)
{
	m_logBuf.attachBuffer(buf);
}

inline
void LogStream::detachBuffer(std::streambuf * buf)
{
	m_logBuf.detachBuffer(buf);
}

inline
void LogStream::attachStream(std::ostream & stream)
{
	m_logBuf.attachStream(stream);
}

inline
void LogStream::detachStream(std::ostream & stream)
{
	m_logBuf.detachStream(stream);
}

}
}

#endif /* GPX_X_LOG_LOGSTREAM_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
