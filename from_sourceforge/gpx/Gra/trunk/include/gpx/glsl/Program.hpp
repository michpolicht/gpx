/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GLSL_PROGRAM_HPP_
#define GPX_Gra_GLSL_PROGRAM_HPP_

#include <vector>

#include <gpx/platform.hpp>

#include "../gl_wrap.hpp"
#include "Shader.hpp"
#include "UniformInfo.hpp"
#include "AttribInfo.hpp"

namespace gpx {
namespace glsl {

/**
 * GLSL program.
 */
class GPX_API Program
{
	public:
		/**
		 * Default constructor.
		 */
		Program();

		/**
		 * Constructor. Creates instance for already existing program.
		 * @param id program id. Results are undefined if program with given id doesn't exist.
		 */
		Program(GLuint id);

		virtual ~Program();

	public:
		/**
		 * Use fixed OpenGL functionality. Quits currently used program and falls back to
		 * OpenGL fixed functionality.
		 */
		static void UseFixed();

	public:
		GLuint id() const;

		/**
		 * Check whenever program was linked.
		 * @return @p true when program was linked, @p false otherwise.
		 */
		bool linked() const;

		/**
		 * Get number of active uniform variables.
		 * @return number of active uniform variables.
		 */
		GLint activeUniforms() const;

		GLint activeUniformMaxLength() const;

		void activeUniformInfo(GLint index, UniformInfo & out) const;

		GLint uniformLocation(const GLchar * name) const;

		GLint activeAttribs() const;

		GLint activeAttribMaxLength() const;

		void activeAttribInfo(GLint index, AttribInfo & out) const;

		GLint attribLocation(const GLchar * name) const;

		void attachShader(const Shader & shader);

		void detachShader(const Shader & shader);

		/**
		 * Link program. May cause abnormal termination on failure.
		 */
		void link();

		/**
		 * Use program. Before using a program it must be @ref link() "linked" first.
		 * If other program is already in use it replaces it, as well as OpenGL fixed
		 * functionality.
		 */
		void use();

	protected:
		void logProgramInfoLog(bool logEmpty = false) const;

	private:
		struct Requirements : public gra::Requirements
		{
			static void CheckOnce();
		};

	private:
		GLuint m_id;
};

}
}

#endif /* GPX_Gra_GLSL_PROGRAM_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
