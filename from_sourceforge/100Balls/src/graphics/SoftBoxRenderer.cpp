/**
 * @file
 * @brief .
 */

#include <gpx/math/functions.hpp>

#include "SoftBoxRenderer.h"
#include "../models/BoxModel.h"
#include "../physics/SoftBox.h"


SoftBoxRenderer::SoftBoxRenderer(SoftBox * box):
	box(box),
	model(box->model)
{
}

SoftBoxRenderer::~SoftBoxRenderer()
{
}

void SoftBoxRenderer::render(gpx::gra2d::RenderContext * context)
{
//	gpx::math::Vector<2> rotationPoint = box->getRotationPoint();
	gpx::glMultMatrix(box->tMatrix());
/*	glTranslated(box->pos(0), box->pos(1), 0.0);*/
//	glRotated(gpx::math::radToDeg(box->getAngle()), 0.0, 0.0, 1.0);
	gpx::glVertexPointer(2, 0, *box->m_cVertices.active().begin());
	glDrawElements(GL_LINE_LOOP, model->VERTEX_NUM, GL_UNSIGNED_INT, & model->verindex[0]);
}
