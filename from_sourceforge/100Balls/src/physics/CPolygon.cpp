/**
 * @file
 * @brief .
 */

#include "CPolygon.h"

CPolygon::CPolygon(const gpx::model::VertexData<2> & vdata, gpx::real_t mass):
	gpx::phy2d::CRigidBody(
		mass,
		0.5 * mass * gpx::phy2d::CRigidBody::FindBoundR(vdata) * gpx::phy2d::CRigidBody::FindBoundR(vdata),
		1.5,
		1.0,
		gpx::phy2d::CRigidBody::FindBoundR(vdata)
	),
	CPoly(vdata)
{
//	setEffMultiplier(1.0 / 128.0);
//	setDislocMultiplier(0.0);		//for perfect ball 0.0 is justified
}

CPolygon::~CPolygon()
{
}

gpx::math::Vector<2> CPolygon::normal(const gpx::phy2d::CollisionPoints & ncPoints) const
{
	gpx::math::Vector<2> result(CPoly::normal(ncPoints));
	rotateToGlobal(result);
	return result;
}
