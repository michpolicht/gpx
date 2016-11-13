/**
 * @file
 * @brief .
 */

#ifndef BOXMODEL_HPP_
#define BOXMODEL_HPP_

#include <gpx/model/VertexData.hpp>

class BoxModel
{
	public:
		static const int VERTEX_NUM = 4;

		gpx::real_t width;
		gpx::real_t height;
		gpx::real_t vertices[VERTEX_NUM * 2];
		gpx::model::VertexData<2> cvertices;

		BoxModel(gpx::real_t width, gpx::real_t height);

		virtual ~BoxModel();
};

#endif /* BOXMODEL_HPP_ */
