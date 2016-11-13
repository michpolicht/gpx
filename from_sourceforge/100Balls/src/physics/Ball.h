/**
 * @file /100Balls/src/physics/Ball.h
 * @brief .
 */

#ifndef Balls_BALL_H_
#define Balls_BALL_H_

#include <gpx/phy2d/CMaterialBody.hpp>


class BallModel;

class Ball: public gpx::phy2d::CMaterialBody,
			public virtual gpx::phy2d::ICPoly
{
	friend class BallRenderer;

	BallModel * model;

	public:
		Ball(BallModel * model, double mass);

		virtual ~Ball();

		//IPointDetection
		bool test(const gpx::math::const_VectorPtr<2> & cvertex) const;

		//ICPoly
		const gpx::model::VertexData<2> & cvertices() const;

		//ICPoly
		gpx::math::Vector<2> normal(const gpx::phy2d::CollisionPoints & ncPoints) const;

		//ICPoly
		gpx::math::Vector<2> eff(const gpx::math::const_VectorPtr<2> & pre, const gpx::math::const_VectorPtr<2> & post) const;

		//ICPoly
		gpx::phy2d::ICPolyGroup::element_t elements() const;

		//ICPoly
		const gpx::phy2d::ICPoly * element(gpx::phy2d::ICPolyGroup::element_t i) const;

};

#endif /* Balls_BALL_H_ */
