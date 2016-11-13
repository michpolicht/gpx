/**
 * @file /100Balls/src/physics/Ball.cpp
 * @brief .
 */

#include "../models/BallModel.h"

#include "Ball.h"

Ball::Ball(BallModel * model, double mass):
	gpx::phy2d::CMaterialBody(mass, 2.0, 1.0),
	model(model)
{
}

Ball::~Ball()
{
}

const gpx::model::VertexData<2> & Ball::cvertices() const
{
	return model->cvertices;
}

//gpx::math::Vector<2> NBall::mapToGlobal(const gpx::math::VectorPtr<2> & point) const
//{
//	return gpx::phy::NewtonObject::mapToGlobal(point);
//}
//
//gpx::math::Vector<2> NBall::mapToLocal(const gpx::math::VectorPtr<2> & point) const
//{
//	return gpx::phy::NewtonObject::mapToLocal(point);
//}

bool Ball::test(const gpx::math::const_VectorPtr<2> & cvertex) const
{
	double x = cvertex[0];
	double y = cvertex[1];

	if (std::sqrt((x*x) + (y*y)) < model->r)
		return true;
	return false;
}

gpx::math::Vector<2> Ball::normal(const gpx::phy2d::CollisionPoints & ncPoints) const
{
	//for the circle it is OK to simplify and consider only post collision point
	double r = std::sqrt((ncPoints.post(0)*ncPoints.post(0)) + (ncPoints.post(1)*ncPoints.post(1)));
	return gpx::math::Vector<2>(ncPoints.post(0)/r, ncPoints.post(1)/r);

	//another simplification: assume that post.x^2 + post.y^2 = model->r^2
//	return gpx::math::Vector<2>(ncPoints.post(0)/model->r, ncPoints.post(1)/model->r);
}

gpx::math::Vector<2> Ball::eff(const gpx::math::const_VectorPtr<2> & pre, const gpx::math::const_VectorPtr<2> & post) const
{
	return gpx::math::Vector<2>(pre);
}

gpx::phy2d::ICPolyGroup::element_t Ball::elements() const
{
	return 1;
}

const gpx::phy2d::ICPoly * Ball::element(gpx::phy2d::ICPolyGroup::element_t i) const
{
	return this;
}

