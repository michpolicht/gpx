/**
 * @file
 * @brief .
 */

#ifndef GPX_X_LOG_MACROS_HPP_
#define GPX_X_LOG_MACROS_HPP_

#include "Log.hpp"


#ifdef GPX_NO_LOG			///< Turns off all logging macros except GPX_FATAL and GPX_INFO.
	#define GPX_NO_DEBUG	///< Turns off GPX_DEBUG macro.
	#define GPX_NO_NOTE		///< Turns off GPX_NOTE macro.
	#define GPX_NO_WARN		///< Turns off GPX_WARN macro.
#endif /*GPX_NO_LOG*/


/** @TODO this is rather temporary macro. Shall be replaced by manipulators */
#define GPX_LOG_FLF " (file: " << __FILE__ << " line: " << __LINE__ << " function: " << __FUNCTION__ << ")"

/**
 * Debug message. This kind of messages are intended to be utilized during development.
 * This macro should be turned off for releases.
 * @param EXPR expression containing debug message. Expression is injected into LogStream
 * object thus standard ostream syntax may be used.
 * @return reference to LogStream object.
 */
#ifndef GPX_NO_DEBUG
	#define GPX_DEBUG(EXPR) ::gpx::log::Log::Instance().debugStream() << "Debug message: " << EXPR << GPX_LOG_FLF << std::endl
#else
	#define GPX_DEBUG(EXPR) (void)0
#endif /*GPX_NO_DEBUG*/

/**
 * Notice. Indicate notable events, etc.
 * @param EXPR expression containing notice. Expression is injected into LogStream
 * object thus standard ostream syntax may be used.
 * @return reference to LogStream object.
 */
#ifndef GPX_NO_NOTE
	#define GPX_NOTE(EXPR) ::gpx::log::Log::Instance().noteStream() << "Note: " << EXPR << GPX_LOG_FLF << std::endl
#else
	#define GPX_NOTE(EXPR) (void)0
#endif /*GPX_NO_NOTICE*/

/**
 * Warning. Indicate something serious that shouldn't be omitted. It is good idea not to
 * turn off GPX_WARN macro completely and at least collect the data in the log file.
 * @param EXPR expression containing warning message. Expression is injected into LogStream
 * object thus standard ostream syntax may be used.
 * @return reference to LogStream object.
 */
#ifndef GPX_NO_WARN
	#define GPX_WARN(EXPR) ::gpx::log::Log::Instance().warnStream() << "Warning: " << EXPR << GPX_LOG_FLF << std::endl
#else
	#define GPX_WARN(EXPR) (void)0
#endif /*GPX_NO_WARN*/

/**
 * Fatal error. Sends fatal error message to LogStream and exits with EXIT_FAILURE code.
 * This macro should never be turned off.
 * @param EXPR expression containing fatal error message. Expression is injected into LogStream
 * object thus standard ostream syntax may be used.
 */
#ifndef GPX_NO_FATAL
	#define GPX_FATAL(EXPR) ::gpx::log::Log::Instance().fatalStream() << "Fatal error: " << EXPR << GPX_LOG_FLF << std::endl, std::exit(EXIT_FAILURE)
#else
	#define GPX_FATAL(EXPR) (void)0
#endif /*GPX_NO_FATAL*/

/**
 * Information. Indicate informational data. Intended to operate on the same level of
 * importance as notice. In opposite to notice the output is clean, without prefix, file,
 * line or function name in it.
 * @param EXPR expression containing information. Expression is injected into LogStream
 * object thus standard ostream syntax may be used.
 * @return reference to LogStream object.
 */
#ifndef GPX_NO_INFO
	#define GPX_INFO(EXPR) ::gpx::log::Log::Instance().infoStream() << EXPR << std::endl
#else
	#define GPX_INFO(EXPR) (void)0
#endif /*GPX_NO_INFO*/



#endif /* GPX_X_LOG_MACROS_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
