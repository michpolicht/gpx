/**
 * @file
 * @brief .
 */

#ifndef RIGIDPOLY_HPP_
#define RIGIDPOLY_HPP_

#include <gpx/phy2d/cdetect/interseg/CPoly.hpp>
#include <gpx/phy2d/cnewton/pmepp2_s/CRigidBody.hpp>

namespace pmepp2_s {

class RigidPoly : public gpx::phy2d::cnewton::pmepp2_s::CRigidBody,
				  public gpx::phy2d::cdetect::interseg::CPoly<gpx::model::NONE>
{
	typedef gpx::phy2d::cnewton::pmepp2_s::CRigidBody CRigidBody;
	typedef gpx::phy2d::cdetect::interseg::CPoly<gpx::model::NONE> CPoly;

	public:
		RigidPoly(const gpx::model::VertexData<2> & vdata, gpx::real_t mass, gpx::phy::material_t material = 0);

		virtual ~RigidPoly();

	public:
		virtual gpx::math::Vector<2> normal(gpx::math::const_PointRef<2> pre, gpx::math::const_PointRef<2> post) const;
};

}

#endif /* RIGIDPOLY_HPP_ */
