/**
 * @file
 * @brief .
 */

#ifndef GPX_X_LOG_LOGBUF_HPP_
#define GPX_X_LOG_LOGBUF_HPP_

#include "../platform.hpp"

#include <cstdlib>
#include <iostream>
#include <list>

namespace gpx {
namespace log {

/**
 * Log buffer.
 */
class LogBuf: public std::streambuf
{
	public:
		/**
		 * Attach buffer.
		 * @param buf pointer to std::streambuf object.
		 */
		void attachBuffer(std::streambuf * buf);

		/**
		 * Detach buffer.
		 * @param buf pointer to std::streambuf object.
		 */
		void detachBuffer(std::streambuf * buf);

		/**
		 * Attach stream 's buffer. Defined for convenience.
		 * @param buf pointer to std::streambuf object.
		 */
		void attachStream(std::ostream & stream);

		/**
		 * Detach stream 's buffer.
		 * @param buf pointer to std::streambuf object.
		 */
		void detachStream(std::ostream & stream);

	protected:
		typedef std::list<std::streambuf *> BufsContainer;

	protected:
		/**
		 * Get buffers container.
		 * @return container containing attached buffers.
		 */
		BufsContainer & bufs();

		/**
		 * Get buffers container (const version).
		 * @return container containing attached buffers.
		 */
		const BufsContainer & bufs() const;

		//std::streambuf
		virtual int sync();

		//std::streambuf
		virtual int_type overflow(int_type c);

		//std::streambuf
		virtual std::streamsize xsputn(const char_type * s, std::streamsize n);

	private:
		BufsContainer m_bufs;

};


inline
void LogBuf::attachBuffer(std::streambuf * buf)
{
	if (buf != this)
		m_bufs.push_back(buf);
}

inline
void LogBuf::detachBuffer(std::streambuf * buf)
{
	m_bufs.remove(buf);
}

inline
void LogBuf::attachStream(std::ostream & stream)
{
	attachBuffer(stream.rdbuf());
}

inline
void LogBuf::detachStream(std::ostream & stream)
{
	detachBuffer(stream.rdbuf());
}

inline
LogBuf::BufsContainer & LogBuf::bufs()
{
	return m_bufs;
}

inline
const LogBuf::BufsContainer & LogBuf::bufs() const
{
	return m_bufs;
}

inline
int LogBuf::sync()
{
	int result = 0;

	//just like before (im writing this comments from the bottom)
	//it is responsibility of each buffer to sync(), we just force syncing.
	for (BufsContainer::iterator i = m_bufs.begin(); i != m_bufs.end(); ++i)
		if ((*i)->pubsync() == -1)
			result = -1;
	return result;
}

inline
LogBuf::int_type LogBuf::overflow(int_type c)
{
	int_type result = c; //according to docs overflow() should return c in case of everything is fine and eof in case of something is very not fine

	//note: sputc() of each buffer will call overflow if necessary.
	for (BufsContainer::iterator i = m_bufs.begin(); i != m_bufs.end(); ++i)
		if (traits_type::eq_int_type((*i)->sputc(traits_type::to_char_type(c)), traits_type::eof()))
			result = traits_type::eof(); //really, eof shouldn't happen in output stream ~:|
	return result;
}

inline
std::streamsize LogBuf::xsputn(const char_type * s, std::streamsize n)
{
	//TODO: it is up to buffers to put those characters, but possibly kind of error
	//should be generated if sputn fails :/.
	for (BufsContainer::iterator i = m_bufs.begin(); i != m_bufs.end(); ++i)
		(*i)->sputn(s, n);

	//always return n, even if there is no buffer attached - characters must be lost and
	//not turned away somewhere into space-time of iostreams.
	return n;
}

}
}

#endif /* GPX_X_LOG_LOGBUF_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
