/*
 * Box.cpp
 *
 *      Author: doc
 */

#include <gpx/log.hpp>
#include <gpx/phy2d/DragnDropCollider.hpp>

#include "Box.h"
#include "../models/BoxModel.h"

Box::Box(BoxModel * model, double mass):
	gpx::phy2d::CRigidBody(
		mass,
		mass * ((model->width * model->width) + (model->height * model->height)) / 12.0,
		2.0,
		1.0,
		FindBoundR(model->cvertices)
	),
	model(model)
{
}

Box::~Box()
{
}

int Box::ccw(const gpx::math::VectorPtr<2> & A, const gpx::math::VectorPtr<2> & B, const gpx::math::VectorPtr<2> & C) const
{
	gpx::real_t ccw = ((C(1) - A(1)) * (B(0) - A(0))) - ((B(1) - A(1)) * (C(0) - A(0)));
	return ccw > 0.0 ? 1 : ccw < 0.0 ? -1 : 0;
}

const gpx::model::VertexData<2> & Box::cvertices() const
{
	return model->cvertices;
}

bool Box::test(const gpx::math::const_VectorPtr<2> & cvertex) const
{
	double x = cvertex[0];
	double y = cvertex[1];

	if ((x < model->width / 2.0) && (x > -model->width / 2.0) && (y < model->height / 2.0) && (y > -model->height / 2.0))
		return true;
	return false;
}

//
//gpx::math::Vector<2> Box::mapToLocal(const gpx::math::VectorPtr<2> & point) const
//{
//	return gpx::phy::NewtonObject::mapToLocal(point);
//}
//
//
//gpx::math::Vector<2> Box::mapToGlobal(const gpx::math::VectorPtr<2> & point) const
//{
//	return gpx::phy::NewtonObject::mapToGlobal(point);
//}

gpx::math::Vector<2> Box::normal(const gpx::phy2d::CollisionPoints & ncPoints) const
{
//	std::cout << "pre: " << ncPoints.pre << "post: " << ncPoints.post;

	const Segment seg(ncPoints.pre, ncPoints.post);
	for (std::size_t i = 0; i < model->cvertices.num(); i++) {
		const gpx::math::VectorPtr<2> edgeStart(model->cvertices[i]);
		const gpx::math::VectorPtr<2> edgeEnd(model->cvertices[(i+1) % model->cvertices.num()]);
		const Segment edge(edgeStart, edgeEnd);
		if (doesIntersect(seg, edge)) {
			gpx::math::Vector<2> normal((edgeEnd - edgeStart).cross());
			normal.normalize();
			normal.rotate(m_angleSin.active(), m_angleCos.active());
//			std::cout << "normal: " << normal;
			return normal;
		}
	}
	GPX_FATAL("could not find valid normal vector");
	return gpx::math::Vector<2>();
}

gpx::math::Vector<2> Box::eff(const gpx::math::const_VectorPtr<2> & pre, const gpx::math::const_VectorPtr<2> & post) const
{
	return gpx::math::Vector<2>(pre);
}

gpx::phy2d::ICPolyGroup::element_t Box::elements() const
{
	return 1;
}

const gpx::phy2d::ICPoly * Box::element(gpx::phy2d::ICPolyGroup::element_t i) const
{
	return this;
}


