/**
 * @file
 * @brief .
 */

#include "RigidPolyRenderer.hpp"

namespace pmepp2_s
{

RigidPolyRenderer::RigidPolyRenderer(const RigidPoly & poly):
	m_poly(poly)
{
}

RigidPolyRenderer::~RigidPolyRenderer()
{
}

void RigidPolyRenderer::render(gpx::gra2d::RenderContext * )
{
	gpx::glColor3v(color().ptr());
	gpx::glMultMatrix(m_poly.tMatrix().ptr());
	gpx::glVertexPointer(m_poly.cvertices().dim(), 0, m_poly.cvertices().data());
	glDrawArrays(GL_LINE_LOOP, 0, m_poly.cvertices().num());
}

}
