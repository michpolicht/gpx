#ifndef FastBall_BOXMODEL_H_
#define FastBall_BOXMODEL_H_

#include <vector>

#include <gpx/model/VertexData.hpp>

class BoxModel
{
	public:
		static const int VERTEX_NUM = 4;

		gpx::real_t width;
		gpx::real_t height;
		gpx::real_t vertices[VERTEX_NUM * 2];	//std::vector<gpx::real_t *> vertices?
		gpx::model::VertexData<2> cvertices;
		std::vector<int> verindex;

		BoxModel(gpx::real_t width, gpx::real_t height);
		virtual ~BoxModel();
};

#endif /* FastBall_BOXMODEL_H_ */
