/**
 * @file
 * @brief .
 */

#ifndef Balls_WALLMODEL_HPP_
#define Balls_WALLMODEL_HPP_

#include <gpx/model/VertexData.hpp>

class WallModel
{
	public:
		static const int VERTEX_NUM = 2;

		enum Type {LEFT, RIGHT, TOP, BOTTOM};

		gpx::real_t width;
		gpx::real_t vertices[VERTEX_NUM * 2];
		gpx::model::VertexData<2> cvertices;
		Type type;

		WallModel(gpx::real_t width, Type type);

		virtual ~WallModel();
};

#endif /* Balls_WALLMODEL_HPP_ */
