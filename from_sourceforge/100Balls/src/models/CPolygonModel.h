/**
 * @file
 * @brief .
 */

#ifndef GPX_100Balls_CPOLYGONMODEL_H_
#define GPX_100Balls_CPOLYGONMODEL_H_

#include <gpx/model/VertexData.hpp>


class CPolygonModel
{
	public:
		gpx::model::VertexData<2> & cvertices;

		CPolygonModel(gpx::model::VertexData<2> & cvertices);

		virtual ~CPolygonModel();
};

#endif /* GPX_100Balls_CPOLYGONMODEL_H_ */
