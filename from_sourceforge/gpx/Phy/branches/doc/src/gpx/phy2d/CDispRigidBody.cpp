/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/phy2d/CDispRigidBody.hpp"
#include "../../../include/gpx/phy2d/DragnDropCollider.hpp"

#include <gpx/log.hpp>

namespace gpx {
namespace phy2d {

CDispRigidBody::CDispRigidBody(real_t mass, real_t I, const math::const_VectorPtr<2> & cm, phy::material_t material, real_t boundR):
	DispRigidBody(mass, I, cm),
	m_material(material),
	m_boundR(boundR),
	m_dislocMultiplier(INITIAL_DISLOC_MULTIPLIER)
{
}

CDispRigidBody::~CDispRigidBody()
{
}

phy::material_t CDispRigidBody::material() const
{
	return m_material;
}

void CDispRigidBody::setMaterial(phy::material_t material)
{
	m_material = material;
}

real_t CDispRigidBody::findBoundR()
{
	real_t r = FindBoundR(element(0)->cvertices(), rotationPoint());
	for (ICNewton::element_t i = 1; i < elements(); i++)
		r = std::max(r, FindBoundR(element(i)->cvertices(), rotationPoint()));
	return r;
}

void CDispRigidBody::setBoundR(real_t boundR)
{
	this->m_boundR = boundR;
}

real_t CDispRigidBody::boundR() const
{
	return m_boundR;
}

real_t CDispRigidBody::obtainBoundR()
{
	return boundR() != -1.0 ? boundR() : findBoundR();
}

real_t CDispRigidBody::dislocMultiplier() const
{
	return m_dislocMultiplier;
}

void CDispRigidBody::setDislocMultiplier(real_t dislocMultiplier)
{
	m_dislocMultiplier = dislocMultiplier;
}

void CDispRigidBody::performDragnDrop(DragnDropCollider * collider)
{
	real_t dt = collider->dt();
	setV(math::Vector<2>(collider->dx()/dt, collider->dy()/dt));
	//	setPos(getX() + collider->getDx(), getY() + collider->getDy());
}

void CDispRigidBody::mountImpulse(const Impulse & impulse, const math::const_VectorPtr<2> & point)
{
	DispRigidBody::mountImpulse(impulse, point);
}

void CDispRigidBody::roundAwayImpulse(Impulse & impulse, const NewtonCollisionData & data, bool normal)
{
	if (normal) {
		real_t boundR = obtainBoundR();
		math::Vector<2> disloc(data.bData.normal);
		disloc.invert();
//		disloc *= std::abs(m_L.active() * boundR * data.bData.dData.dt); //it would be better to use L after recount...
		disloc *= boundR * m_dislocMultiplier;
		setDisloc(disloc);
	}
}

math::Vector<2> CDispRigidBody::aCoef(const NewtonCollisionBase & bData) const
{
	math::Vector<2> r(bData.points.eff - rotationPoint());
	rotateToGlobal(r);
	return math::Vector<2>(1.0 / m() + (r(1) * r(1) / Idisp()), 1.0 / m() + (r(0) * r(0) / Idisp()));
}

math::Vector<2> CDispRigidBody::bCoef(real_t e, const NewtonCollisionBase & bData) const
{
	const real_t & dt = bData.dData.dt;

	math::Vector<2> r(bData.points.eff - rotationPoint());
	rotateToGlobal(r);

	real_t ax = 1.0 / m() + (r(1) * r(1) / Idisp());
	real_t ay = 1.0 / m() + (r(0) * r(0) / Idisp());

	//compensate permanent forces
	//reaction to permanent force
	real_t bx = resultantForce(0) * dt * ax;
	real_t by = resultantForce(1) * dt * ay;
	//reaction to permanent moment
	real_t resultantMomentx_add = 0.0;
	real_t resultantMomenty_add = 0.0;
	if (r(1) != 0.0)
		resultantMomentx_add = resultantMoment() * dt * ax / r(1);
	if (r(0) != 0.0)
		resultantMomenty_add = resultantMoment() * dt * ay / r(0);
	bx += resultantMomentx_add;
	by -= resultantMomenty_add;

	//momentum addition
	bx += e * pA(0) / m();
	by += e * pA(1) / m();

	//angular momentum addition
	bx += e * LA() * -r(1) / Idisp();
	by += e * LA() * r(0) / Idisp();

	//L translates into force proportional to (rx, ry)
	real_t Lx_coef = std::abs(r(1)) / (std::abs(r(1)) + std::abs(r(0)));
	real_t Ly_coef = std::abs(r(0)) / (std::abs(r(1)) + std::abs(r(0)));
	real_t Lx_add = std::abs(LA() * r(1) / Idisp() + resultantMomentx_add);
	real_t Ly_add = std::abs(LA() * r(0) / Idisp() - resultantMomenty_add);
	real_t px_add = std::abs(pA(0) / m() + resultantForce(0) * dt * ax);
	real_t py_add = std::abs(pA(1) / m() + resultantForce(1) * dt * ay);

	//multiply bx by bx_coef
	if ((Lx_add + px_add) != 0.0)	//do not divide by 0.0 (note: px_add and Lx_add are absolute values)
		bx *= (Lx_coef * Lx_add + px_add) / (Lx_add + px_add);
	//multiply by by by_coef
	if ((Ly_add + py_add) != 0.0)	//do not divide by 0.0 (note: py_add and Ly_add are absolute values)
		by *= (Ly_coef * Ly_add + py_add) / (Ly_add + py_add);

	return math::Vector<2>(bx, by);
}

phy::material_t CDispRigidBody::material(element_t element) const
{
	return m_material;
}

real_t CDispRigidBody::FindBoundR(const model::VertexData<2> & cvertices, const math::const_VectorPtr<2> & rotationPoint)
{
	real_t boundR = 0.0;
	for (model::VertexData<2>::const_iterator vertIt = cvertices.begin(); vertIt != cvertices.end(); ++vertIt) {
		math::const_VectorPtr<2> r(*vertIt);
		boundR = std::max(boundR, (r - rotationPoint).dot());
	}
	return std::sqrt(boundR);
}

}
}

//(c)MP: Copyright © 2011, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
