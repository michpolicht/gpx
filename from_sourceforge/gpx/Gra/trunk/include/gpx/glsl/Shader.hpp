/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GLSL_SHADER_HPP_
#define GPX_Gra_GLSL_SHADER_HPP_

#include <gpx/platform.hpp>

#include "../gl_wrap.hpp"
#include "../gra/Requirements.hpp"

namespace gpx {
namespace glsl {

/**
 * GLSL shader program.
 */
class GPX_API Shader
{
	public:
		/**
		 * Constructor.
		 * @param type shader type. According to OpenGL standard, might be either
		 * GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
		 * @param source valid source code for the shader. Shader code is immediately copied
		 * into shader object, thus @a source string can be safely deleted after constructor
		 * returns.
		 * @param compile compile shader instantly.
		 */
		Shader(GLenum type, const GLchar * source, bool compile = true);

		/**
		 * Constructor. Creates instance for already existing shader.
		 * @param id shader id. Results are undefined if shader with given id doesn't exist.
		 */
		Shader(GLuint id);

		/**
		 * Destructor.
		 */
		virtual ~Shader();

	public:
		GLenum type() const;

		GLuint id() const;

		/**
		 * Check whenever shader was compiled.
		 * @return @p true when shader was compiled, @p false otherwise.
		 */
		bool compiled() const;

		/**
		 * Compile shader. May cause abnormal termination on failure.
		 */
		void compile();

	protected:
		/**
		 * Log shader info log.
		 * @param logEmpty logs output even if log is empty.
		 */
		void logShaderInfoLog(bool logEmpty = false) const;

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

#endif /* GPX_Gra_GLSL_SHADER_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
