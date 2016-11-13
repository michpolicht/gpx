/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/phy2d/CMaterialBody.hpp"
#include "../../../include/gpx/phy2d/DragnDropCollider.hpp"

namespace gpx {
namespace phy2d {


CMaterialBody::CMaterialBody(real_t m, phy::material_t material):
	MaterialBody(m),
	m_material(material)
{
}

CMaterialBody::~CMaterialBody()
{
}

phy::material_t CMaterialBody::material() const
{
	return m_material;
}

void CMaterialBody::setMaterial(phy::material_t material)
{
	m_material = material;
}


void CMaterialBody::performDragnDrop(gpx::phy2d::DragnDropCollider * collider)
{
	real_t dt = collider->dt();
	setV(math::Vector<2>(collider->dx()/dt, collider->dy()/dt));
//	setPos(getX() + collider->getDx(), getY() + collider->getDy());
}

void CMaterialBody::mountImpulse(const Impulse & impulse, const math::const_VectorPtr<2> & point)
{
	MaterialBody::mountImpulse(impulse, point);
}

void CMaterialBody::roundAwayImpulse(Impulse & impulse, const NewtonCollisionData & data, bool normal)
{
}

math::Vector<2> CMaterialBody::aCoef(const gpx::phy2d::NewtonCollisionBase & bData) const
{
	return math::Vector<2>(1.0 / m(), 1.0 / m());
}

math::Vector<2> CMaterialBody::bCoef(real_t p, const gpx::phy2d::NewtonCollisionBase & bData) const
{
	const real_t & dt = bData.dData.dt;

	//reaction force addition
	real_t bx = std::min(p, 1.0) * resultantForce(0) * dt / m();
	real_t by = std::min(p, 1.0) * resultantForce(1) * dt / m();
	//momentum
	bx += p * pA(0) / m();
	by += p * pA(1) / m();

	return math::Vector<2>(bx, by);
}

phy::material_t CMaterialBody::material(element_t element) const
{
	return m_material;
}



}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
