/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/phy2d/CRigidBody.hpp"
#include "../../../include/gpx/phy2d/DragnDropCollider.hpp"

#include <gpx/log.hpp>

namespace gpx {
namespace phy2d {


CRigidBody::CRigidBody(real_t mass, real_t I, phy::material_t material, real_t boundR):
	RigidBody(mass, I),
	m_material(material),
	m_boundR(boundR),
	m_dislocMultiplier(INITIAL_DISLOC_MULTIPLIER)
{
}

CRigidBody::~CRigidBody()
{
}

real_t CRigidBody::FindBoundR(const model::VertexData<2> & cvertices)
{
	real_t boundR = 0.0;
	for (model::VertexData<2>::const_iterator vertIt = cvertices.begin(); vertIt != cvertices.end(); ++vertIt) {
		math::const_VectorPtr<2> r(*vertIt);
		boundR = std::max(boundR, r.dot());
	}
	return std::sqrt(boundR);
}

phy::material_t CRigidBody::material() const
{
	return m_material;
}

void CRigidBody::setMaterial(phy::material_t material)
{
	m_material = material;
}

real_t CRigidBody::findBoundR()
{
	real_t r = FindBoundR(element(0)->cvertices());
	for (ICNewton::element_t i = 1; i < elements(); i++)
		r = std::max(r, FindBoundR(element(i)->cvertices()));
	return r;
}

void CRigidBody::setBoundR(real_t boundR)
{
	this->m_boundR = boundR;
}

real_t CRigidBody::boundR() const
{
	return m_boundR;
}

real_t CRigidBody::obtainBoundR()
{
	return boundR() != -1.0 ? boundR() : findBoundR();
}

real_t CRigidBody::dislocMultiplier() const
{
	return m_dislocMultiplier;
}

void CRigidBody::setDislocMultiplier(real_t dislocMultiplier)
{
	m_dislocMultiplier = dislocMultiplier;
}

void CRigidBody::performDragnDrop(DragnDropCollider * collider)
{
	real_t dt = collider->dt();
	setV(math::Vector<2>(collider->dx()/dt, collider->dy()/dt));
	//	setPos(getX() + collider->getDx(), getY() + collider->getDy());
}

void CRigidBody::mountImpulse(const Impulse & impulse, const math::const_VectorPtr<2> & point)
{
	RigidBody::mountImpulse(impulse, point);
}

void CRigidBody::roundAwayImpulse(Impulse & impulse, const NewtonCollisionData & data, bool normal)
{
	if (normal) {
		real_t boundR = obtainBoundR();
		math::Vector<2> disloc(data.bData.normal);
		disloc.invert();
//		disloc *= std::abs(m_L.active() * boundR * data.bData.dData.dt); //it would be better to use L after recount...
		disloc *= boundR * m_dislocMultiplier;
		setDisloc(disloc);
	}
//	if (normal) {
//		math::Vector<2> disloc(impulse);
////		disloc *= std::abs(m_L.active() * boundR * data.bData.dData.dt); //it would be better to use L after recount...
//		setDisloc(disloc);
////		math::Vector<2> repulse(data.bData.normal);
////		repulse.invert();
////		m_repulse = repulse;
//	} else {
//		real_t boundR = obtainBoundR();
//		math::Vector<2> disl(impulse + disloc());
//		disl.normalize();
////		disloc *= std::abs(m_L.active() * boundR * data.bData.dData.dt); //it would be better to use L after recount...
//		disl *= boundR * m_dislocMultiplier;
//		setDisloc(disl);
//
////		math::Vector<2> repulse(m_repulse + impulse);
////		repulse.normalize();
////		repulse.invert();
////		m_repulse = repulse;
//	}
//	if (normal) {
////		real_t boundR = obtainBoundR();
//		math::Vector<2> repulse(resultantForce());
//		repulse.normalize();
//		repulse.invert();
////		repulse *= boundR * m_dislocMultiplier;
//		m_repulse = repulse;
//	}
//	if (normal) {
//		math::Vector<2> disl(impulse);
//		setDisloc(disl);
//	} else {
//		real_t boundR = obtainBoundR();
//		math::Vector<2> disl(disloc() + impulse);
//		disl.normalize();
////		disloc *= std::abs(m_L.active() * boundR * data.bData.dData.dt); //it would be better to use L after recount...
//		disl *= boundR * m_dislocMultiplier;
//		setDisloc(disl);
//		GPX_DEBUG("disl: " << disl);
//		GPX_DEBUG("dislNormal: " << data.bData.normal * boundR * m_dislocMultiplier);
//	}
}

math::Vector<2> CRigidBody::aCoef(const NewtonCollisionBase & bData) const
{
	math::Vector<2> r(bData.points.eff);
	rotateToGlobal(r);
//	return math::Vector<2>(1.0 / m() + (r(1) * r(1) / I()), 1.0 / m() + (r(0) * r(0) / I()));
	real_t ax = 1.0 / m() + (((std::abs(r(0)) + std::abs(r(1))) / std::abs(r(1))) * r(1) * r(1) / I());
	real_t ay = 1.0 / m() + (((std::abs(r(0)) + std::abs(r(1))) / std::abs(r(0))) * r(0) * r(0) / I());
	return math::Vector<2>(ax, ay);
}

math::Vector<2> CRigidBody::bCoef(real_t p, const NewtonCollisionBase & bData) const
{
	const real_t & dt = bData.dData.dt;

	math::Vector<2> r(bData.points.eff);
	rotateToGlobal(r);

//	real_t ax = 1.0 / m() + (r(1) * r(1) / I());
//	real_t ay = 1.0 / m() + (r(0) * r(0) / I());

	real_t ax = 1.0 / m() + (((r(0) + r(1)) / r(1)) * r(1) * r(1) / I());
	real_t ay = 1.0 / m() + (((r(0) + r(1)) / r(0)) * r(0) * r(0) / I());

	//compensate permanent forces
	//reaction to permanent force
	real_t bx = std::min(p, 1.0) * resultantForce(0) * dt * ax;
	real_t by = std::min(p, 1.0) * resultantForce(1) * dt * ay;
	//reaction to permanent moment
	real_t resultantMomentx_add = 0.0;
	real_t resultantMomenty_add = 0.0;
	if (r(1) != 0.0)
		resultantMomentx_add = std::min(p, 1.0) * resultantMoment() * dt * ax / r(1);
	if (r(0) != 0.0)
		resultantMomenty_add = std::min(p, 1.0) * resultantMoment() * dt * ay / r(0);
	bx += resultantMomentx_add;
	by -= resultantMomenty_add;

	//momentum addition
	bx += p * pA(0) / m();
	by += p * pA(1) / m();

	//angular momentum addition
	bx += p * LA() * -r(1) / I();
	by += p * LA() * r(0) / I();

//	//L translates into force proportional to (rx, ry)
//	real_t Lx_coef = std::abs(r(1)) / (std::abs(r(1)) + std::abs(r(0)));
//	real_t Ly_coef = std::abs(r(0)) / (std::abs(r(1)) + std::abs(r(0)));
//	real_t Lx_add = std::abs(LA() * r(1) / I() + resultantMomentx_add);
//	real_t Ly_add = std::abs(LA() * r(0) / I() - resultantMomenty_add);
//	real_t px_add = std::abs(pA(0) / m() + resultantForce(0) * dt * ax);
//	real_t py_add = std::abs(pA(1) / m() + resultantForce(1) * dt * ay);
//
//	//multiply bx by bx_coef
//	if ((Lx_add + px_add) != 0.0)	//do not divide by 0.0 (note: px_add and Lx_add are absolute values)
//		bx *= (Lx_coef * Lx_add + px_add) / (Lx_add + px_add);
//	//multiply by by by_coef
//	if ((Ly_add + py_add) != 0.0)	//do not divide by 0.0 (note: py_add and Ly_add are absolute values)
//		by *= (Ly_coef * Ly_add + py_add) / (Ly_add + py_add);

	return math::Vector<2>(bx, by);
}

phy::material_t CRigidBody::material(element_t element) const
{
	return m_material;
}

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
