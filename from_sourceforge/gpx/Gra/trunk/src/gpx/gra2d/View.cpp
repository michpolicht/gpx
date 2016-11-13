/**
 * @file
 * @brief .
 */


#include <gpx/math/structures.hpp>

#include "../../../include/gpx/gra2d/View.hpp"



namespace gpx {
namespace gra2d {


View::View(gra::RenderWindow & renderWindow, Scene & scene):
		m_scene(scene),
		m_renderWindow(renderWindow),
		m_viewport(renderWindow.viewport()),
		m_clip(scene.clip()),
		m_doSetup(false)
{
	init();
	setup();
}

View::View(gra::RenderWindow & renderWindow, Scene & scene, Clip & clip):
		m_scene(scene),
		m_renderWindow(renderWindow),
		m_viewport(renderWindow.viewport()),
		m_clip(clip),
		m_doSetup(false)
{
	init();
	setup();
}

View::View(gra::RenderWindow & renderWindow, Scene & scene, gra::Viewport & viewport):
		m_scene(scene),
		m_renderWindow(renderWindow),
		m_viewport(viewport),
		m_clip(scene.clip()),
		m_doSetup(false)
{
	init();
	setup();
}

View::View(gra::RenderWindow & renderWindow, Scene & scene, Clip & clip, gra::Viewport & viewport):
		m_scene(scene),
		m_renderWindow(renderWindow),
		m_viewport(viewport),
		m_clip(clip),
		m_doSetup(false)
{
	init();
	setup();
}

View::~View()
{
	m_clip.removeObserver(this);
	m_viewport.removeObserver(this);
}



Scene & View::scene()
{
	return m_scene;
}

gra::Viewport & View::viewport()
{
	return m_viewport;
}

const gra::Viewport & View::viewport() const
{
	return m_viewport;
}

gra::RenderWindow & View::renderWindow()
{
	return m_renderWindow;
}

const gra::RenderWindow & View::renderWindow() const
{
	return m_renderWindow;
}


//void View::setZoom(real_t zoom)
//{
//	this->zoom = zoom;
//}
//
//real_t View::getZoom() const
//{
//	return zoom;
//}

math::Vector<2> View::svRatio() const
{
	return math::Vector<2>(svWidthRatio(), svHeightRatio());
}

real_t View::svWidthRatio() const
{
	return (m_clip[Clip::RIGHT] - m_clip[Clip::LEFT]) / static_cast<real_t>(m_viewport[gra::Viewport::WIDTH] - m_viewport[gra::Viewport::X]);
}

real_t View::svHeightRatio() const
{
	return (m_clip[Clip::TOP] - m_clip[Clip::BOTTOM]) / static_cast<real_t>(m_viewport[gra::Viewport::HEIGHT] - m_viewport[gra::Viewport::Y]);
}

math::Point<2> View::mapToScene(real_t x, real_t y) const
{
	GLdouble MVMatrix[16];
	GLdouble resultX;
	GLdouble resultY;
	GLdouble resultZ;	//redundant

	glGetv(GL_MODELVIEW_MATRIX, MVMatrix);
	gluUnProject(static_cast<GLdouble>(x), static_cast<GLdouble>(y), 0.0,
			MVMatrix, m_projectionMatrix, m_viewport.params(),
			& resultX, & resultY, & resultZ);
	return math::Point<2>(static_cast<real_t>(resultX), static_cast<real_t>(resultY));
}

math::Point<2> View::mapToScene(math::const_PointRef<2> point) const
{
	return mapToScene(point[0], point[1]);
}

math::Point<2> View::mapToScene(int x, int y) const
{
	return mapToScene(static_cast<real_t>(x), static_cast<real_t>(y));
}

math::Point<2> View::mapToScene(math::const_PointRef<2, int> point) const
{
	return mapToScene(static_cast<real_t>(point[0]), static_cast<real_t>(point[1]));
}

math::Point<2> View::mapToViewport(real_t x, real_t y) const
{
	GLdouble MVMatrix[16];
	GLdouble resultX;
	GLdouble resultY;
	GLdouble resultZ;	//redundant

	glGetv(GL_MODELVIEW_MATRIX, MVMatrix);
	gluProject(static_cast<GLdouble>(x), static_cast<GLdouble>(y), 0.0,
			MVMatrix, m_projectionMatrix, m_viewport.params(),
			& resultX, & resultY, & resultZ);
	return math::Point<2>(static_cast<real_t>(resultX), static_cast<real_t>(resultY));
}

math::Point<2> View::mapToViewport(math::const_PointRef<2> point) const
{
	return mapToViewport(point[0], point[1]);
}

//void View::resize(GLint viewportW, GLint viewportH)
//{
//	setViewport(viewportW, viewportH);
//	setup();
//}
//
//void View::resize(GLint viewportX, GLint viewportY, GLint viewportW, GLint viewportH)
//{
//	setViewport(viewportX, viewportY, viewportW, viewportH);
//	setup();
//}

void View::event(const utils::Observable<Clip>::Event & )
{
	setup();
}

void View::event(const utils::Observable<gra::Viewport>::Event & )
{
	setup();
}

void View::update()
{
	glMatrixMode(GL_PROJECTION);
	gpx::glLoadMatrix(m_projectionMatrix);
	glMatrixMode(GL_MODELVIEW);
	//todo transformations
	m_scene.update(this);
}

void View::setup()
{
	glViewport(m_viewport.x(), m_viewport.y(), m_viewport.width(), m_viewport.height());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(static_cast<GLdouble>(m_clip.left()), static_cast<GLdouble>(m_clip.right()),
			   static_cast<GLdouble>(m_clip.bottom()), static_cast<GLdouble>(m_clip.top()));
	//flip
//	gluOrtho2D(static_cast<GLdouble>(m_clip.left()), static_cast<GLdouble>(m_clip.right()),
//			   static_cast<GLdouble>(m_clip.top()), static_cast<GLdouble>(m_clip.bottom()));
	//glu sets near and far to -1.0 and 1.0 respectively
	gpx::glGetv(GL_PROJECTION_MATRIX, m_projectionMatrix);
	glMatrixMode(GL_MODELVIEW);
}

void View::init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor4(0.0, 0.0, 0.0, 0.0);
	glEnableClientState(GL_VERTEX_ARRAY); //to use gl*v functions
	glShadeModel(GL_FLAT);
	m_viewport.addObserver(this);
	m_clip.addObserver(this);
}

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
