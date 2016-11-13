/**
 * @file
 * @brief .
 */

#include "MaterialPolyRenderer.hpp"

namespace pmepp2_s
{

MaterialPolyRenderer::MaterialPolyRenderer(const MaterialPoly & poly):
		m_poly(poly)
{
}

MaterialPolyRenderer::~MaterialPolyRenderer()
{
}

void MaterialPolyRenderer::render(gpx::gra2d::RenderContext * )
{
	gpx::glColor3v(color().ptr());
	gpx::glMultMatrix(m_poly.tMatrix().ptr());
	gpx::glVertexPointer(m_poly.cvertices().dim(), 0, m_poly.cvertices().data());
	glDrawArrays(GL_LINE_LOOP, 0, m_poly.cvertices().num());
}

}
