/**
 * @file /100Balls/src/models/BallModel.h
 * @brief .
 */

#ifndef Balls_BALLMODEL_H_
#define Balls_BALLMODEL_H_

#include <vector>
#include <gpx/model/VertexData.hpp>

class BallModel
{
	public:
		static const int VERTEX_NUM = 12;

		double r;
		double vertices[VERTEX_NUM * 2];
		std::vector<int> verindex;
		gpx::model::VertexData<2> cvertices;

		/**
		 * Constructor.
		 * @param r radius.
		 */
		BallModel(double r);

		virtual ~BallModel();
};

#endif /* Balls_BALLMODEL_H_ */
