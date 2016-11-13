/**
 * @file
 * @brief .
 */

#include "WallRenderer.hpp"

namespace pmepp2_s
{

WallRenderer::WallRenderer(Wall & wall):
		m_wall(wall),
		m_model(wall.m_model)
{
}

WallRenderer::~WallRenderer()
{
}

void WallRenderer::render(gpx::gra2d::RenderContext * )
{
	gpx::glColor3v(color().ptr());
//	glColor3f(0.0, 0.0, 0.0);
	gpx::glMultMatrix(m_wall.tMatrix().ptr());
	gpx::glVertexPointer(m_model.cvertices.dim(), 0, m_model.cvertices.data());
	glDrawArrays(GL_LINES, 0, m_model.cvertices.num());
}

}
