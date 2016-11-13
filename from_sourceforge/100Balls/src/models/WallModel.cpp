/**
 * @file
 * @brief .
 */

#include "WallModel.h"

WallModel::WallModel(double width, Type type):
	width(width),
	verindex(VERTEX_NUM),
	type(type)
{
	switch (type) {
		case LEFT:
			vertices[0] = 0.0; vertices[1] = 0.0;
			vertices[2] = 0.0; vertices[3] = width;
			break;
		case RIGHT:
			vertices[0] = 0.0; vertices[1] = width;
			vertices[2] = 0.0; vertices[3] = 0.0;
			break;
		case TOP:
			vertices[0] = 0.0; vertices[1] = 0.0;
			vertices[2] = width; vertices[3] = 0.0;
			break;
		case BOTTOM:
			vertices[0] = width; vertices[1] = 0.0;
			vertices[2] = 0.0; vertices[3] = 0.0;
			break;
	}

	for (int i = 0; i < VERTEX_NUM; i++)
		verindex[i] = i;
	cvertices.setData(vertices, VERTEX_NUM);
}

WallModel::~WallModel()
{
}

