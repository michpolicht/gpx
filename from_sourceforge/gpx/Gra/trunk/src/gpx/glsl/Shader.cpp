/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/glsl/Shader.hpp"

namespace gpx {
namespace glsl {

Shader::Shader(GLenum type, const GLchar * source, bool compileNow)
{
	Requirements::CheckOnce();

	m_id = glCreateShader(type);

	//notes on glShaderSource()
	//"If length is NULL, each string is assumed to be null terminated" -- OpenGL spec
	//"The source code strings are not scanned or parsed at this time;
	//they are simply copied into the specified shader object." -- OpenGL spec
	//"An application can modify or free its copy of the source code strings
	//immediately after the function returns" -- Randi J. Rost - OpenGL Shading Language 2ed
	glShaderSource(m_id, 1, & source, NULL);
	if (compileNow)
		compile();
}

Shader::Shader(GLuint id):
		m_id(id)
{
	Requirements::CheckOnce();

	assert(glIsShader(id) == GL_TRUE);
}


Shader::~Shader()
{
	glDeleteShader(m_id);
}

GLenum Shader::type() const
{
	GLint type;
	glGetShaderiv(m_id, GL_SHADER_TYPE, & type);
	return type;
}

GLuint Shader::id() const
{
	return m_id;
}


bool Shader::compiled() const
{
	GLint compiled;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, & compiled);
	return compiled == GL_TRUE ? true : false;
}

void Shader::compile()
{
	if (!compiled()) {
		glCompileShader(m_id);
		if (compiled()) {
			logShaderInfoLog();
			GPX_NOTE("shader (id: " << m_id << ") compiled successfully");
		} else {
			logShaderInfoLog();
			GPX_FATAL("shader (id: " << m_id << ") can not be compiled");
		}
	} else
		GPX_WARN("shader (id: " << m_id << ") already compiled");
}

void Shader::logShaderInfoLog(bool logEmpty) const
{
	GLint length;
	glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, & length);
	if ((length > 1) || (logEmpty)) {
		GLchar log[length];
		glGetShaderInfoLog(m_id, length, NULL, log);
		GPX_DEBUG("shader info log:" << std::endl << log);
	}
}


void Shader::Requirements::CheckOnce()
{
	static bool checked = false;
	if (checked)
		return;

	RequireFunc("glCreateShader", glCreateShader == NULL);
	RequireFunc("glShaderSource", glShaderSource == NULL);
	RequireFunc("glCompileShader", glCompileShader == NULL);
	RequireFunc("glGetShaderiv", glGetShaderiv == NULL);
	RequireFunc("glGetShaderInfoLog", glGetShaderInfoLog == NULL);
	RequireFunc("glIsShader", glIsShader == NULL);

	checked = true;
}


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
