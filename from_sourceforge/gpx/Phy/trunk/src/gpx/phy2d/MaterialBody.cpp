/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/phy2d/MaterialBody.hpp"

#include <gpx/math/functions.hpp>
#include <gpx/log.hpp>

namespace gpx {
namespace phy2d {

MaterialBody::MaterialBody(real_t m):
	m_m(m),
	m_p(doubleBufferController())
{
	m_impulsePoints.reserve(IMPULSE_POINTS_NUM);
}

MaterialBody::~MaterialBody()
{
}

void MaterialBody::setV(const math::const_VectorPtr<2> & v)
{
	m_p.active() = v * m();
	m_p.background() = v * m();
}

real_t MaterialBody::m() const
{
	return m_m;
}

void MaterialBody::setM(real_t m)
{
	m_m = m;
}

const math::Vector<2> & MaterialBody::p() const
{
	return pA();
}

void MaterialBody::setP(const math::const_VectorPtr<2> & p)
{
	m_p.active() = p;
	m_p.background() = p;
}

real_t MaterialBody::kineticE() const
{
	return 0.5 * pA().dot() / m();
}

void MaterialBody::update(real_t dt)
{
	//recount physical parameters and perform motion
	//write new phase-space config to the background buffer
	//forces are probably smaller than impulses, sum them together first
	m_resultantForce.zero();
	updateResultantForce(dt, m_resultantForce);
	updateP(dt, m_p.background());
	m_impulsePoints.clear();
	Parent::update(dt);
}

void MaterialBody::updatePos(real_t dt, math::Vector<2> & posB)
{
	posB = posA() + pB() * dt / m();
}

void MaterialBody::updateResultantForce(real_t dt, math::Vector<2> & resultantForce)
{
	for (ForcePointsContainer::const_iterator forcePoint = forcePoints().begin(); forcePoint != forcePoints().end(); ++forcePoint)
		resultantForce += *(forcePoint->first);
}

void MaterialBody::updateP(real_t dt, math::Vector<2> & pB)
{
	pB = pA() + resultantForce() * dt; //add impulse to current momentum

	for (ImpulsePointsContainer::const_iterator impPoint = impulsePoints().begin(); impPoint != impulsePoints().end(); ++impPoint)
		pB += impPoint->first;
}

void MaterialBody::mountForce(Force * force, const math::const_VectorPtr<2> & point)
{
	m_forcePoints[force] = point;
}

void MaterialBody::unmountForce(Force * force)
{
	m_forcePoints.erase(force);
}

const math::Vector<2> & MaterialBody::forcePoint(Force * force) const
{
	GPX_ASSERT(forcePoints().find(force) != forcePoints().end(), "given force is not mounted");
	return forcePoints().find(force)->second;
}

void MaterialBody::updateForcePoint(const math::Vector<2> & point, const math::const_VectorPtr<2> & val)
{
	const_cast<math::Vector<2> &>(point) = val;
}

const MaterialBody::ForcePointsContainer & MaterialBody::forcePoints() const
{
	return m_forcePoints;
}

void MaterialBody::mountImpulse(const Impulse & impulse, const math::const_VectorPtr<2> & point)
{
	if (m_impulsePoints.capacity() == m_impulsePoints.size()) {
		GPX_DEBUG("impulsePoints exceeds current capacity of: " << m_impulsePoints.capacity() << " records");
		GPX_WARN("impulsePoints needs to be resized");
	}
	m_impulsePoints.push_back(ImpulsePointPair(impulse, math::Vector<2>(point)));
}

const MaterialBody::ImpulsePointsContainer & MaterialBody::impulsePoints() const
{
	return m_impulsePoints;
}

const math::Vector<2> & MaterialBody::pA() const
{
	return m_p.active();
}

real_t MaterialBody::pA(std::size_t i) const
{
	return m_p.active().coord(i);
}

const math::Vector<2> & MaterialBody::pB() const
{
	return m_p.background();
}

real_t MaterialBody::pB(std::size_t i) const
{
	return m_p.background().coord(i);
}

const Force & MaterialBody::resultantForce() const
{
	return m_resultantForce;
}

real_t MaterialBody::resultantForce(std::size_t i) const
{
	return m_resultantForce(i);
}

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
