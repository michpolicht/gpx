/**
 * @file
 * @brief .
 */

#include "RigidPoly.hpp"

namespace pmepp2_s {

RigidPoly::RigidPoly(const gpx::model::VertexData<2> & vdata, gpx::real_t mass, gpx::phy::material_t material):
	CRigidBody(
		mass,
		0.5 * mass * gpx::model::sqboundr(vdata),
		material
	),
	CPoly(vdata)
{
}

RigidPoly::~RigidPoly()
{
}

gpx::math::Vector<2> RigidPoly::normal(gpx::math::const_PointRef<2> pre, gpx::math::const_PointRef<2> post) const
{
	gpx::math::Vector<2> result(CPoly::normal(pre, post));
//	GPX_DEBUG("RigidPoly normal: " << result);
	rotateToGlobal(result);
	return result;
}

}
