/**
 * @file
 * @brief .
 */

#ifndef Balls_WALL_H_
#define Balls_WALL_H_

#include <gpx/phy2d/CMaterialBody.hpp>

class WallModel;


class Wall: public gpx::phy2d::CMaterialBody,
			public virtual gpx::phy2d::ICPoly
{
	friend class WallRenderer;

	WallModel * model;

	public:
		Wall(WallModel * model);

		virtual ~Wall();

		//overriden gpx::phy::IColliding
		bool test(const gpx::math::const_VectorPtr<2> & cvertex) const;

		//overriden gpx::phy:INewtonColliding
		const gpx::model::VertexData<2> & cvertices() const;

		//overriden gpx::phy::INewtonColliding
		gpx::math::Vector<2> normal(const gpx::phy2d::CollisionPoints & ncPoints) const;

		//overriden gpx::phy::INewtonColliding
		gpx::math::Vector<2> eff(const gpx::math::const_VectorPtr<2> & pre, const gpx::math::const_VectorPtr<2> & post) const;

		//ICPolyGroup
		virtual gpx::phy2d::ICPolyGroup::element_t elements() const;

		//ICPolyGroup
		const gpx::phy2d::ICPoly * element(gpx::phy2d::ICPolyGroup::element_t i) const;

		//@Override gpx::phy::MaterialObject
		void update(gpx::real_t dt);
};

#endif /* Balls_WALL_H_ */
