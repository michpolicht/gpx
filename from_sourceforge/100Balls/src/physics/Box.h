/*
 * Box.h
 *
 *      Author: doc
 */

#ifndef FastBall_BOX_H_
#define FastBall_BOX_H_

#include <gpx/phy2d/CRigidBody.hpp>

class BoxModel;


class Box : public gpx::phy2d::CRigidBody,
			public virtual gpx::phy2d::ICPoly
{
	friend class BoxRenderer; //for convenience give renderer direct access

//	gpx::math::Vector<2> centerOfMass;

	protected:
		BoxModel * model;

		struct Segment {
			const gpx::math::VectorPtr<2> & start;
			const gpx::math::VectorPtr<2> & end;

			Segment(const gpx::math::VectorPtr<2> & start, const gpx::math::VectorPtr<2> & end):
				start(start),
				end(end)
			{}
		};

		/**
		 * Check orientation of triangle ABC.
		 * @return if curve is positively (or counterclockwise) oriented 1, if curve is
		 * negatively (or clockwise) oriented -1. When curve is non-orientable
		 * (points are collinear) function returns 0.
		 */
		int ccw(const gpx::math::VectorPtr<2> & A, const gpx::math::VectorPtr<2> & B, const gpx::math::VectorPtr<2> & C) const;

		/**
		 * Check if two segments intersect.
		 * @param seg1 first segment.
		 * @param seg2 second segment.
		 * @return @p true when segments intersect, @p false otherwise.
		 */
		bool doesIntersect(const Segment & seg1, const Segment & seg2) const;

	public:
		Box(BoxModel * model, double mass);

		virtual ~Box();

		virtual bool test(const gpx::math::const_VectorPtr<2> & cvertex) const;

		virtual const gpx::model::VertexData<2> & cvertices() const;

		//ICPoly
		gpx::math::Vector<2> normal(const gpx::phy2d::CollisionPoints & ncPoints) const;

		//ICPoly
		gpx::math::Vector<2> eff(const gpx::math::const_VectorPtr<2> & pre, const gpx::math::const_VectorPtr<2> & post) const;

		//ICPoly
		gpx::phy2d::ICPolyGroup::element_t elements() const;

		//ICPoly
		const gpx::phy2d::ICPoly * element(gpx::phy2d::ICPolyGroup::element_t i) const;
};

inline
bool Box::doesIntersect(const Segment & AB, const Segment & CD) const
{
	return ccw(AB.start, CD.start , CD.end) != ccw(AB.end, CD.start, CD.end)
		&& ccw(AB.start, AB.end, CD.start) != ccw(AB.start, AB.end, CD.end);
}


#endif /* FastBall_BOX_H_ */
