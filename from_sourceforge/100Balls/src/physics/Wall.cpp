/**
 * @file
 * @brief .
 */

#include <limits>

#include "../models/WallModel.h"
#include "Wall.h"

Wall::Wall(WallModel * model):
	gpx::phy2d::CMaterialBody(std::numeric_limits<double>::infinity(), 2.0, 1.0),
	model(model)
{
}

Wall::~Wall()
{
}

const gpx::model::VertexData<2> & Wall::cvertices() const
{
	return model->cvertices;
}

bool Wall::test(const gpx::math::const_VectorPtr<2> & cvertex) const
{
	double x = cvertex[0];
	double y = cvertex[1];

	switch (model->type) {
		case WallModel::LEFT:
			if (x < 0.0)
				return true;
			else
				return false;
		case WallModel::RIGHT:
			if (x > 0.0)
				return true;
			else
				return false;
		case WallModel::TOP:
			if (y > 0.0)
				return true;
			else
				return false;
		case WallModel::BOTTOM:
			if (y < 0.0)
				return true;
			else
				return false;
		default:
			return false;
	}
}

gpx::math::Vector<2> Wall::normal(const gpx::phy2d::CollisionPoints & ncPoints) const
{
	switch (model->type) {
		case WallModel::LEFT:
			return gpx::math::Vector<2>(1.0, 0.0);
		case WallModel::RIGHT:
			return gpx::math::Vector<2>(-1.0, 0.0);
		case WallModel::TOP:
			return gpx::math::Vector<2>(0.0, -1.0);
		case WallModel::BOTTOM:
			return gpx::math::Vector<2>(0.0, 1.0);
		default:
			return gpx::math::Vector<2>(0.0, 1.0);
	}
}

gpx::math::Vector<2> Wall::eff(const gpx::math::const_VectorPtr<2> & pre, const gpx::math::const_VectorPtr<2> & post) const
{
	return gpx::math::Vector<2>(pre);
}

gpx::phy2d::ICPolyGroup::element_t Wall::elements() const
{
	return 1;
}

//ICPolyGroup
const gpx::phy2d::ICPoly * Wall::element(gpx::phy2d::ICPolyGroup::element_t i) const
{
	return this;
}

void Wall::update(gpx::real_t dt)
{
//temp code
	recountForces();
	recountImpulses();
//	std::cout << "resultant force: " << resultantForce;

	//recount physical parameters and perform motion

	//write new phase space config to background buffer
	swapBuffers();

	m_a = m_v; //temporary hold old value of v here
	m_p.active()(0) = m_p.background()(0) + m_resultantForce(0) * dt; //add impulse to current momentum
	m_p.active()(1) = m_p.background()(1) + m_resultantForce(1) * dt;
	m_v(0) = m_p.active()(0) / m_mass;
	m_v(1) = m_p.active()(1) / m_mass;
	m_v(1) = 1.5;
	m_a(0) = m_v(0) - m_a(0);
	m_a(1) = m_v(1) - m_a(1);
	m_a /= dt;

	m_pos.active()(0) = m_pos.background()(0) + (m_v(0) * dt);
	m_pos.active()(1) = m_pos.background()(1) + (m_v(1) * dt);

	constructTMatrix(m_tMatrix.active(), m_tMatrixInv.active());

	swapBuffers();

/* normal code (uncomment)

	gpx::phy2d::MaterialObject::recountForces();
	gpx::phy2d::MaterialObject::recountImpulses();
	//Now p consists internal energy.
	//Relaxation here does not cause any cool effect :(
	//Note that this step is important, un-relaxed p may grow out of gpx::real_t bounds
	//and cause inf/inf divisions or other undefined stuff.
	p.active().zero();
	p.background().zero();
	//Now wall with infinite mass may be attached as movable
*/

}
