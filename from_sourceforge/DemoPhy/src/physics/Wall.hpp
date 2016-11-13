/**
 * @file
 * @brief .
 */

#ifndef WALL_HPP_
#define WALL_HPP_

#include <gpx/phy2d/cnewton/pmepp2_s/CMaterialBody.hpp>

class WallModel;

namespace pmepp2_s {

class WallRenderer;

class Wall: public gpx::phy2d::cnewton::pmepp2_s::CMaterialBody,
			public virtual gpx::phy2d::cdetect::interseg::ICPoly
{
	typedef gpx::phy2d::cnewton::pmepp2_s::CMaterialBody CMaterialBody;

	friend class WallRenderer;

	WallModel & m_model;
	gpx::model::VertexData<2> m_emptyCVertices;

	public:
		Wall(WallModel & model);

		virtual ~Wall();

		//gpx::phy2d::ICPolyGroup
		virtual element_t elements() const;

		//gpx::phy2d::ICPolyGroup
		virtual const gpx::phy2d::cdetect::interseg::ICPoly * element(element_t i) const;

		//gpx::phy2d::IPointDetection
		bool test(gpx::math::const_PointRef<2> pre, gpx::math::const_PointRef<2> post) const;

		//gpx::phy2d::ICPoly
		const gpx::model::VertexData<2> & cvertices() const;

		//gpx::phy2d::ICPoly
		gpx::math::Vector<2> normal(gpx::math::const_PointRef<2> pre, gpx::math::const_PointRef<2> post) const;

};

}

#endif /* WALL_HPP_ */
