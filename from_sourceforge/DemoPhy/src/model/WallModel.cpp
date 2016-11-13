/**
 * @file
 * @brief .
 */

#include "WallModel.hpp"

WallModel::WallModel(gpx::real_t width, Type type):
	width(width),
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
	cvertices.setData(vertices, VERTEX_NUM);
}

WallModel::~WallModel()
{
}

