/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/phy2d/MaterialBody.hpp"
#include "../../../include/gpx/phy/RecordableFloatVector.hpp"

#include <gpx/math/functions.hpp>
#include <gpx/log.hpp>

namespace gpx {
namespace phy2d {

MaterialBody::MaterialBody(real_t m):
	m_m(m),
	m_p(doubleBufferController())
{
}

MaterialBody::~MaterialBody()
{
}

void MaterialBody::setV(math::const_VectorRef<2> v)
{
	setP(v * m());
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

void MaterialBody::setP(math::const_VectorRef<2> p)
{
	setPB(p);
	swapBuffers();
	setPB(p);
	swapBuffers();
}

real_t MaterialBody::kineticE() const
{
	return 0.5 * pA().dot() / m();
}

void MaterialBody::mountForce(const Force * force, math::const_PointRef<2> point)
{
	m_forcePoints[force] = point;
}

void MaterialBody::unmountForce(const Force * force)
{
	m_forcePoints.erase(force);
}

math::Point<2> MaterialBody::forcePoint(const Force & force) const
{
	GPX_ASSERT(forcePoints().find(& force) != forcePoints().end(), "given force is not mounted");
	return forcePoints().find(& force)->second;
}

void MaterialBody::updateForcePoint(const Force & force, math::const_PointRef<2> pos)
{
	GPX_ASSERT(forcePoints().find(& force) != forcePoints().end(), "given force is not mounted");
	m_forcePoints.find(& force)->second = pos;
}

const MaterialBody::ForcePointsContainer & MaterialBody::forcePoints() const
{
	return m_forcePoints;
}

MaterialBody::ForcePointsContainer & MaterialBody::forcePoints()
{
	return m_forcePoints;
}

void MaterialBody::applyImpulse(const Impulse & impulse, math::const_PointRef<2> point)
{
	GPX_UNUSED(point);

	swapBuffers();
	m_p.background() += impulse;
	swapBuffers();
}

void MaterialBody::update(real_t dt)
{
	//recount physical parameters and perform motion
	//write new phase-space config to the background buffer

	//update momentum
	setPB(pA() + resultantForce() * dt);
	//update position
	setPosB(posA() + pB() * dt / m());
}

std::size_t MaterialBody::snapshotSize() const
{
	//Parent + p A + p B
	return Parent::snapshotSize() + 2 * phy::RecordableFloatVector<2>::SnapshotSize();
}

void MaterialBody::store(char * snapshot) const
{
	//store p
	phy::RecordableFloatVector<2>::Store(snapshot, pA());
	snapshot += phy::RecordableFloatVector<2>::SnapshotSize();
	phy::RecordableFloatVector<2>::Store(snapshot, pB());
	snapshot += phy::RecordableFloatVector<2>::SnapshotSize();
	//store Parent
	Parent::store(snapshot);
}

void MaterialBody::restore(char * snapshot)
{
	//restore p
	phy::RecordableFloatVector<2>::Restore(snapshot, m_p.active());
	snapshot += phy::RecordableFloatVector<2>::SnapshotSize();
	phy::RecordableFloatVector<2>::Restore(snapshot, m_p.background());
	snapshot += phy::RecordableFloatVector<2>::SnapshotSize();
	//restore Parent
	Parent::restore(snapshot);
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

void MaterialBody::setPB(math::const_VectorRef<2> p)
{
	m_p.background() = p;
}

Force MaterialBody::resultantForce() const
{
	Force resForce;
	for (ForcePointsContainer::const_iterator forcePoint = forcePoints().begin(); forcePoint != forcePoints().end(); ++forcePoint)
		resForce += *(forcePoint->first);
	return resForce;
}

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
