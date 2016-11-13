/**
 * @file /100Balls/src/graphics/BallRenderer.cpp
 * @brief .
 */


#include "../physics/Ball.h"
#include "../models/BallModel.h"

#include "BallRenderer.h"

BallRenderer::BallRenderer(Ball * ball):
	ball(ball),
	model(ball->model)
{
}

BallRenderer::~BallRenderer()
{
}

void BallRenderer::render(gpx::gra2d::RenderContext * context)
{
	glMultMatrixd(ball->tMatrix());
	glVertexPointer(2, GL_DOUBLE, 0, model->vertices);
	glDrawElements(GL_LINE_LOOP, model->VERTEX_NUM, GL_UNSIGNED_INT, & model->verindex[0]);
}

