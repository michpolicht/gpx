/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/glsl/Program.hpp"

namespace gpx {
namespace glsl {

Program::Program()
{
	Requirements::CheckOnce();

	m_id = glCreateProgram();
}

Program::Program(GLuint id):
		m_id(id)
{
	Requirements::CheckOnce();

	assert(glIsProgram(m_id) == GL_TRUE);
}

Program::~Program()
{
	glDeleteProgram(m_id);
}

void Program::UseFixed()
{
	glUseProgram(0);
}

GLuint Program::id() const
{
	return m_id;
}

bool Program::linked() const
{
	GLint linked;
	glGetProgramiv(m_id, GL_LINK_STATUS, & linked);
	return linked == GL_TRUE ? true : false;
}

GLint Program::activeUniforms() const
{
	GLint result;
	glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, & result);
	return result;
}

GLint Program::activeUniformMaxLength() const
{
	GLint result;
	glGetProgramiv(m_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, & result);
	return result;
}

void Program::activeUniformInfo(GLint index, UniformInfo & out) const
{
	out.index = index;
	glGetActiveUniform(m_id, index,	out.bufSize, & out.nameLength, & out.size, & out.type, out.name);
}

GLint Program::activeAttribs() const
{
	GLint result;
	glGetProgramiv(m_id, GL_ACTIVE_ATTRIBUTES, & result);
	return result;
}

GLint Program::uniformLocation(const GLchar * name) const
{
	return glGetUniformLocation(m_id, name);
}

void Program::activeAttribInfo(GLint index, AttribInfo & out) const
{
	out.index = index;
	glGetActiveAttrib(m_id, index, out.bufSize, & out.nameLength, & out.size,  & out.type, out.name);
}

GLint Program::activeAttribMaxLength() const
{
	GLint result;
	glGetProgramiv(m_id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, & result);
	return result;
}

GLint Program::attribLocation(const GLchar * name) const
{
	return glGetAttribLocation(m_id, name);
}

void Program::attachShader(const Shader & shader)
{
	glAttachShader(m_id, shader.id());
}

void Program::detachShader(const Shader & shader)
{
	glDetachShader(m_id, shader.id());
}

void Program::link()
{
	if (!linked()) {
		glLinkProgram(m_id);
		if (linked()) {
			logProgramInfoLog();
			GPX_NOTE("program (id: " << m_id << ") linked successfully");
		} else {
			logProgramInfoLog();
			GPX_FATAL("program (id: " << m_id << ") can not be linked");
		}
	} else
		GPX_WARN("program (id: " << m_id << ") already linked");
}

void Program::use()
{
	assert(linked() == true);

	glUseProgram(m_id);
}

void Program::logProgramInfoLog(bool logEmpty) const
{
	GLint length;
	glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, & length);
	if ((length > 1) || (logEmpty)) {
		GLchar log[length];
		glGetProgramInfoLog(m_id, length, NULL, log);
		GPX_DEBUG("program info log:" << std::endl << log);
	}
}


void Program::Requirements::CheckOnce()
{
	static bool checked = false;
	if (checked)
		return;

	RequireFunc("glCreateProgram", glCreateProgram == NULL);
	RequireFunc("glAttachShader", glAttachShader == NULL);
	RequireFunc("glDetachShader", glDetachShader == NULL);
	RequireFunc("glGetProgramiv", glGetProgramiv == NULL);
	RequireFunc("glGetProgramInfoLog", glGetProgramInfoLog == NULL);
	RequireFunc("glIsProgram", glIsProgram == NULL);

	checked = true;
}

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
