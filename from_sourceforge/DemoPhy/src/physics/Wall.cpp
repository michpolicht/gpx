/**
 * @file
 * @brief .
 */

#include "Wall.hpp"
#include "../model/WallModel.hpp"

#include <limits>

namespace pmepp2_s
{

Wall::Wall(WallModel & model):
	CMaterialBody(std::numeric_limits<double>::infinity()),
	m_model(model)
{
}

Wall::~Wall()
{
}

gpx::phy2d::cdetect::interseg::ICPolyGroup::element_t Wall::elements() const
{
	return 1;
}

const gpx::phy2d::cdetect::interseg::ICPoly * Wall::element(element_t ) const
{
	return this;
}

const gpx::model::VertexData<2> & Wall::cvertices() const
{
	return m_emptyCVertices;
//	return m_model.cvertices;
}

bool Wall::test(gpx::math::const_PointRef<2> pre, gpx::math::const_PointRef<2> post) const
{
	GPX_UNUSED(post);

	//bumper.pre = wedge.post!
	double x = pre[0];
	double y = pre[1];

	switch (m_model.type) {
		case WallModel::LEFT:
			if (x < 0.0)
				return true;
			else
				return false;
		case WallModel::RIGHT:
			if (x > 0.0)
				return true;
			else
				return false;
		case WallModel::TOP:
			if (y > 0.0)
				return true;
			else
				return false;
		case WallModel::BOTTOM:
			if (y < 0.0)
				return true;
			else
				return false;
		default:
			return false;
	}
}

gpx::math::Vector<2> Wall::normal(gpx::math::const_PointRef<2> pre, gpx::math::const_PointRef<2> post) const
{
	GPX_UNUSED(pre);
	GPX_UNUSED(post);

	switch (m_model.type) {
		case WallModel::LEFT:
			return gpx::math::Vector<2>(1.0, 0.0);
		case WallModel::RIGHT:
			return gpx::math::Vector<2>(-1.0, 0.0);
		case WallModel::TOP:
			return gpx::math::Vector<2>(0.0, -1.0);
		case WallModel::BOTTOM:
			return gpx::math::Vector<2>(0.0, 1.0);
		default:
			return gpx::math::Vector<2>(0.0, 1.0);
	}
}

}
