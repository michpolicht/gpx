/**
 * @file
 * @brief .
 */


#include "../models/WallModel.h"
#include "../physics/Wall.h"
#include "WallRenderer.h"

WallRenderer::WallRenderer(Wall * wall):
	wall(wall),
	model(wall->model)
{
}

WallRenderer::~WallRenderer()
{
}

void WallRenderer::render(gpx::gra2d::RenderContext * context)
{
	glMultMatrixd(wall->tMatrix());
	glVertexPointer(2, GL_DOUBLE, 0, model->vertices);
	glDrawElements(GL_LINE_LOOP, model->VERTEX_NUM, GL_UNSIGNED_INT, & model->verindex[0]);
}
