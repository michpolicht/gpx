/*
 * @file
 * @brief .
 */

#include <gpx/log/Log.hpp>

#include "../../../include/gpx/gra/RenderWindow.hpp"


namespace gpx {
namespace gra {

RenderWindow::RenderWindow():
		m_viewport(static_cast<GLint>(this->GetWidth()), static_cast<GLint>(this->GetHeight()))
{
	init();
}

RenderWindow::RenderWindow(sf::VideoMode mode, const std::string & title, unsigned long windowStyle, const sf::WindowSettings & params):
		::sf::RenderWindow(mode, title, windowStyle, params),
		 m_viewport(static_cast<GLint>(mode.Width), static_cast<GLint>(mode.Height))
{
	init();
}


RenderWindow::RenderWindow(sf::WindowHandle handle, const sf::WindowSettings & params):
		::sf::RenderWindow(handle, params),
		 m_viewport(static_cast<GLint>(this->GetWidth()), static_cast<GLint>(this->GetHeight()))
{
	init();
}


RenderWindow::~RenderWindow()
{
	if (IsOpened())
		Close();
}

Viewport & RenderWindow::viewport()
{
	return m_viewport;
}

bool RenderWindow::fetchEvent(sf::Event & e)
{
	bool result = Parent::GetEvent(e);
	if (result && (e.Type == sf::Event::Resized))
		m_viewport.setSize(e.Size.Width, e.Size.Height);
	return result;
}

void RenderWindow::postEvent(sf::Event & e)
{
	static_cast<WindowListener &>(*this).OnEvent(e);
}

void RenderWindow::logGlInfo(int level) const
{
	//info level 0
	GPX_INFO("using OpenGL " << glGetString(GL_VERSION));
	GPX_INFO("vendor: " << glGetString(GL_VENDOR));
	GPX_INFO("renderer: " << glGetString(GL_RENDERER));
	GPX_INFO("extensions: " << glGetString(GL_EXTENSIONS));
	if (level < 1)
		return;

	//info level 1
	int param;
	glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, & param);
	GPX_INFO("modelview matrix stack: " << param);
	glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, & param);
	GPX_INFO("projection matrix stack: " << param);
	if (level < 2)
		return;

	//info level 2
	float paramf[2]; // __attribute__((unused)); //is this portable?
	paramf[0] = 0.0;	//this is for sure portable way to suppress unused warning
	#ifdef GL_ALIASED_POINT_SIZE_RANGE
		glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, paramf);
		GPX_INFO("aliased point size range: (" << *paramf << ", " << *(paramf + 1) << ")");
	#else
		GPX_INFO("aliased point size range: info N/A");
	#endif /* GL_ALIASED_POINT_SIZE_RANGE */
	#ifdef GL_SMOOTH_POINT_SIZE_RANGE
		glGetFloatv(GL_SMOOTH_POINT_SIZE_RANGE, paramf);
		GPX_INFO("smooth point size range: (" << *paramf << ", " << *(paramf + 1) << ")");
	#else
		GPX_INFO("smooth point size range: info N/A");
	#endif /* GL_SMOOTH_POINT_SIZE_RANGE */
	#ifdef GL_SMOOTH_POINT_SIZE_GRANULARITY
		glGetFloatv(GL_SMOOTH_POINT_SIZE_GRANULARITY, paramf);
		GPX_INFO("smooth point size granularity: " << *paramf);
	#else
		GPX_INFO("smooth point size granularity: info N/A");
	#endif /* GL_SMOOTH_POINT_SIZE_GRANULARITY */
}

void RenderWindow::display()
{
	Parent::Display();

    GLenum glErr = glGetError();
	if (glErr != GL_NO_ERROR)
		GPX_WARN("OpenGL error: " << gluErrorString(glErr));
}

bool RenderWindow::GetEvent(sf::Event & e)
{
	return Parent::GetEvent(e);
}

void RenderWindow::init()
{
	GPX_INFO("GPX "GPX_VERSION);

	GLenum err;
	if ((err = glewInit()) != GLEW_OK)
		GPX_FATAL("GLEW initialization failed" << std::endl << "GLEW error: " << glewGetErrorString(err));
	else
		GPX_INFO("using GLEW " << glewGetString(GLEW_VERSION));
}

void RenderWindow::Display()
{
	Parent::Display();
}

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
