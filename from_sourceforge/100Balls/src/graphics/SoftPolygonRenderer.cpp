/**
 * @file
 * @brief .
 */

#include "SoftPolygonRenderer.h"
#include "../physics/SoftPolygon.h"


SoftPolygonRenderer::SoftPolygonRenderer(SoftPolygon * spoly):
	m_spoly(spoly)
{
}

SoftPolygonRenderer::~SoftPolygonRenderer()
{
}

void SoftPolygonRenderer::render(gpx::gra2d::RenderContext * context)
{
	gpx::glMultMatrix(m_spoly->tMatrix());
	glVertexPointer(2, GL_DOUBLE, 0, m_spoly->m_cVertices.active().data());
	glDrawArrays(GL_LINE_LOOP, 0, m_spoly->m_cVertices.active().num());
//	glDrawElements(GL_LINE_LOOP, model->VERTEX_NUM, GL_UNSIGNED_INT, & model->verindex[0]);
}
