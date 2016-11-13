/*
 * BoxRenderer.cpp
 *
 *      Author: doc
 */


//#include <math/Structures.h>
#include <gpx/math/functions.hpp>

#include "BoxRenderer.h"

#include "../models/BoxModel.h"
#include "../physics/Box.h"


BoxRenderer::BoxRenderer(Box * box)
{
	this->box = box;
	this->model = box->model;
}

void BoxRenderer::render(gpx::gra2d::RenderContext * context)
{
//	gpx::math::Vector<2> rotationPoint = box->getRotationPoint();
	glMultMatrixd(box->tMatrix());
//	glLoadMatrixd(box->getTransformationMatrix());
/*	glTranslated(box->pos(0), box->pos(1), 0.0);*/
//	glRotated(gpx::math::radToDeg(box->getAngle()), 0.0, 0.0, 1.0);
	glVertexPointer(2, GL_DOUBLE, 0, model->vertices);
	glDrawElements(GL_LINE_LOOP, model->VERTEX_NUM, GL_UNSIGNED_INT, & model->verindex[0]);
}
