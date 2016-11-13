/**
 * @file
 * @brief .
 */

#ifndef Balls_WALLMODEL_H_
#define Balls_WALLMODEL_H_


#include <vector>

#include <gpx/model/VertexData.hpp>

class WallModel
{
	public:
		static const int VERTEX_NUM = 2;

		enum Type {LEFT, RIGHT, TOP, BOTTOM};

		double width;
		double vertices[VERTEX_NUM * 2];
		gpx::model::VertexData<2> cvertices;
		std::vector<int> verindex;
		Type type;

		WallModel(double width, Type type);
		virtual ~WallModel();
};

#endif /* Balls_WALLMODEL_H_ */
