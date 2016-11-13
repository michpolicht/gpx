#ifndef BALLMODEL_HPP_
#define BALLMODEL_HPP_

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

#endif /* BALLMODEL_HPP_ */
