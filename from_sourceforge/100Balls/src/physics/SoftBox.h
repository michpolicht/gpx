/**
 * @file
 * @brief .
 */

#ifndef GPX_100Balls_SOFTBOX_H_
#define GPX_100Balls_SOFTBOX_H_

#include <vector>

#include <gpx/utils/DoubleBuffer.hpp>
#include <gpx/phy2d/AbstractField.hpp>

#include "Box.h"


class SoftBoxVertex;


class SoftBox : public Box
{
	friend class SoftBoxRenderer; //for convenience give renderer direct access
	friend class SoftBoxVertex;

	protected:
		std::vector<SoftBoxVertex> m_parts;
		gpx::utils::DoubleBuffer<gpx::model::VertexData<2> > m_cVertices;
		gpx::real_t * m_vertexBuff[2];

	public:
		SoftBox(BoxModel * model, double mass);

		virtual ~SoftBox();

		std::vector<SoftBoxVertex> & getParts();

		//Box
		bool test(const gpx::math::const_VectorPtr<2> & cvertex) const;

		//Box
		const gpx::model::VertexData<2> & cvertices() const;

		//gpx::phy2d::RigidBody
		void update(gpx::real_t dt);
};


class SoftBoxField: public gpx::phy2d::AbstractField
{
	public:
		gpx::math::Vector<2> operator()(const point_t & ref, const point_t & r);
};


class SoftBoxVertex: public virtual gpx::phy2d::ICNewtonMovable,
					 public virtual gpx::phy2d::ICPoly
{
	friend class SoftBox;

	protected:
		static SoftBoxField m_reactField;
		SoftBox * m_parent;
		std::size_t m_index;
		gpx::utils::DoubleBuffer<gpx::model::VertexData<2> > m_cVertices;
		bool m_virtualSwap;
		bool m_relax;

	public:
		SoftBoxVertex(SoftBox * parent);

		virtual ~SoftBoxVertex();

		void setParent(SoftBox * parent);

		void setIndex(std::size_t);

		//gpx::phy::ITimePerformer
		virtual void update(gpx::real_t dt);

		virtual void swapBuffers();

		//gpx::phy2d::IColliding
		virtual gpx::math::Vector<2> mapToGlobal(const gpx::math::const_VectorPtr<2> & point) const;

		//gpx::phy2d::IColliding
		virtual gpx::math::Vector<2> mapToLocal(const gpx::math::const_VectorPtr<2> & point) const;

		//gpx::phy2d::IColliding
		bool test(const gpx::math::const_VectorPtr<2> & cvertex) const;

		virtual const gpx::model::VertexData<2> & cvertices() const;

		virtual gpx::math::Vector<2> eff(const gpx::math::const_VectorPtr<2> & pre, const gpx::math::const_VectorPtr<2> & post) const;

		virtual gpx::math::Vector<2> normal(const gpx::phy2d::CollisionPoints & ncPoints) const;

		//ICPolyGroup
		virtual gpx::phy2d::ICPolyGroup::element_t elements() const;

		//ICPolyGroup
		virtual const gpx::phy2d::ICPoly * element(gpx::phy2d::ICPolyGroup::element_t i) const;

		virtual gpx::math::Vector<2> aCoef(const gpx::phy2d::NewtonCollisionBase & bData) const;

		virtual gpx::math::Vector<2> bCoef(gpx::real_t e, const gpx::phy2d::NewtonCollisionBase & bData) const;

		virtual gpx::phy::material_t material(gpx::phy2d::ICPolyGroup::element_t element) const;

		virtual void roundAwayImpulse(gpx::phy2d::Impulse & impulse, const gpx::phy2d::NewtonCollisionData & data, bool normal);

		virtual void mountImpulse(const gpx::phy2d::Impulse & impulse, const gpx::math::const_VectorPtr<2> & point);
};

#endif /* GPX_100Balls_SOFTBOX_H_ */
