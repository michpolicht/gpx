/**
 * @file
 * @brief .
 */

#ifndef GPX_100Balls_CPOLYGON_H_
#define GPX_100Balls_CPOLYGON_H_

//#include <gpx/phy2d/CollidingMaterialObject.hpp>
#include <gpx/phy2d/CRigidBody.hpp>
#include <gpx/phy2d/CPoly.hpp>


class CPolygon : public gpx::phy2d::CRigidBody,
				 public gpx::phy2d::CPoly<gpx::model::NONE>
{
	private:
		typedef gpx::phy2d::CPoly<gpx::model::NONE> CPoly;

	public:
		CPolygon(const gpx::model::VertexData<2> & vdata, gpx::real_t mass);

		virtual ~CPolygon();

	public:
		gpx::math::Vector<2> normal(const gpx::phy2d::CollisionPoints & ncPoints) const;
};

#endif /* GPX_100Balls_CPOLYGON_H_ */
