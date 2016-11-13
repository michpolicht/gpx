/*
 * BoxModel.cpp
 *
 *      Author: doc
 */

#include "BoxModel.h"

BoxModel::BoxModel(gpx::real_t width, gpx::real_t height):
	width(width),
	height(height),
	verindex(VERTEX_NUM)
{
	//0-2 bottom cvert 0-1
	//2-4 right  cvert 1-2
	//4-6 top    cvert 2-3
	//6-0 left   cvert 3-0
	vertices[0] = -width / 2.0; vertices[1] = -height / 2.0;
	vertices[2] = width / 2.0; vertices[3] = - height / 2.0;
	vertices[4] = width / 2.0; vertices[5] = height / 2.0;
	vertices[6] = - width / 2.0; vertices[7] = height / 2.0;

	for (int i = 0; i < VERTEX_NUM; i++)
		verindex[i] = i;
	cvertices.setData(vertices, VERTEX_NUM);
}

BoxModel::~BoxModel()
{
}
