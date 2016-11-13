/**
 * @file
 * @brief .
 */

#include "CPolygonRenderer.h"
#include "../physics/CPolygon.h"


CPolygonRenderer::CPolygonRenderer(CPolygon * cpoly):
	cpoly(cpoly)
{
}

CPolygonRenderer::~CPolygonRenderer()
{
}

void CPolygonRenderer::render(gpx::gra2d::RenderContext * context)
{
	gpx::glMultMatrix(cpoly->tMatrix());
	glVertexPointer(2, GL_DOUBLE, 0, cpoly->cvertices().data());
	glDrawArrays(GL_LINE_LOOP, 0, cpoly->cvertices().num());
//	glDrawElements(GL_LINE_LOOP, model->VERTEX_NUM, GL_UNSIGNED_INT, & model->verindex[0]);
}
