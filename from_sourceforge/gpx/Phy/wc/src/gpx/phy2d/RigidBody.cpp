/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/phy2d/RigidBody.hpp"
#include "../../../include/gpx/phy/RecordableFloat.hpp"

#include <gpx/math/functions.hpp>
#include <gpx/log.hpp>

namespace gpx {
namespace phy2d {


RigidBody::RigidBody(real_t m, real_t I):
	MaterialBody(m),
	m_angleSin(doubleBufferController()),
	m_angleCos(doubleBufferController()),
	m_angle(doubleBufferController(), 0.0),
	m_I(I),
	m_L(doubleBufferController(), 0.0)
{
	//calculate sine and cosine of current angle
	math::sincos(m_angle.background(), m_angleSin.background(), m_angleCos.background());
	updateTMatricesB();
	//do the same for second buffer
	swapBuffers();
	math::sincos(m_angle.background(), m_angleSin.background(), m_angleCos.background());
	updateTMatricesB();
	swapBuffers();	//leave buffer in initial state (just in case)
}

RigidBody::~RigidBody()
{
}

real_t RigidBody::angle() const
{
	return angleA();
}

void RigidBody::setAngle(real_t angle)
{
	setAngleB(angle);
	swapBuffers();
	setAngleB(angle);
	swapBuffers();
}

void RigidBody::setAngularV(real_t angularV)
{
	setL(I() * angularV);
}

real_t RigidBody::I() const
{
	return m_I;
}

void RigidBody::setI(real_t I)
{
	m_I = I;
}

real_t RigidBody::L() const
{
	return LA();
}

void RigidBody::setL(real_t L)
{
	setLB(L);
	swapBuffers();
	setLB(L);
	swapBuffers();
}

real_t RigidBody::kineticE() const
{
	return 0.5 * (pA().dot() / m() + LA() * LA() / I());
}

void RigidBody::applyImpulse(const Impulse & impulse, math::const_PointRef<2> point)
{
	Parent::applyImpulse(impulse, point);

	math::Vector<2> r = point.diff();
	rotateToGlobal(r);
	swapBuffers();
	//r det Fdt
	m_L.background() += r.det(impulse);
	swapBuffers();
}

void RigidBody::update(real_t dt)
{
	//momentum and position is updated in the same way as in MaterialBody
	Parent::update(dt);

	//update angular momentum
	setLB(LA() + resultantMoment() * dt);
	//update angle
	real_t angleB = angleA() + LB() / I() * dt;
	if (angleB > 2 * math::PI)
		angleB -= 2 * math::PI;
	else if (angleB < -2 * math::PI)
		angleB += 2 * math::PI;
	setAngleB(angleB);
}

std::size_t RigidBody::snapshotSize() const
{
	//Parent
	std::size_t result = Parent::snapshotSize();
	//angleSin A + angleSin B
	result += 2 * phy::RecordableFloat<real_t>::SnapshotSize();
	//angleCos A + angleCos B
	result += 2 * phy::RecordableFloat<real_t>::SnapshotSize();
	//angle A + angle B
	result += 2 * phy::RecordableFloat<real_t>::SnapshotSize();
	//L A + L B
	result += 2 * phy::RecordableFloat<real_t>::SnapshotSize();
	return result;
}

void RigidBody::store(char * snapshot) const
{
	//store angleSin
	phy::RecordableFloat<real_t>::Store(snapshot, m_angleSin.active());
	snapshot += phy::RecordableFloat<real_t>::SnapshotSize();
	phy::RecordableFloat<real_t>::Store(snapshot, m_angleSin.background());
	snapshot += phy::RecordableFloat<real_t>::SnapshotSize();
	//store angleCos
	phy::RecordableFloat<real_t>::Store(snapshot, m_angleCos.active());
	snapshot += phy::RecordableFloat<real_t>::SnapshotSize();
	phy::RecordableFloat<real_t>::Store(snapshot, m_angleCos.background());
	snapshot += phy::RecordableFloat<real_t>::SnapshotSize();
	//store angle
	phy::RecordableFloat<real_t>::Store(snapshot, m_angle.active());
	snapshot += phy::RecordableFloat<real_t>::SnapshotSize();
	phy::RecordableFloat<real_t>::Store(snapshot, m_angle.background());
	snapshot += phy::RecordableFloat<real_t>::SnapshotSize();
	//store L
	phy::RecordableFloat<real_t>::Store(snapshot, m_L.active());
	snapshot += phy::RecordableFloat<real_t>::SnapshotSize();
	phy::RecordableFloat<real_t>::Store(snapshot, m_L.background());
	snapshot += phy::RecordableFloat<real_t>::SnapshotSize();
	//store Parent
	Parent::store(snapshot);
}

void RigidBody::restore(char * snapshot)
{
	//restore angleSin
	phy::RecordableFloat<real_t>::Restore(snapshot, m_angleSin.active());
	snapshot += phy::RecordableFloat<real_t>::SnapshotSize();
	phy::RecordableFloat<real_t>::Restore(snapshot, m_angleSin.background());
	snapshot += phy::RecordableFloat<real_t>::SnapshotSize();
	//restore angleCos
	phy::RecordableFloat<real_t>::Restore(snapshot, m_angleCos.active());
	snapshot += phy::RecordableFloat<real_t>::SnapshotSize();
	phy::RecordableFloat<real_t>::Restore(snapshot, m_angleCos.background());
	snapshot += phy::RecordableFloat<real_t>::SnapshotSize();
	//restore angle
	phy::RecordableFloat<real_t>::Restore(snapshot, m_angle.active());
	snapshot += phy::RecordableFloat<real_t>::SnapshotSize();
	phy::RecordableFloat<real_t>::Restore(snapshot, m_angle.background());
	snapshot += phy::RecordableFloat<real_t>::SnapshotSize();
	//restore L
	phy::RecordableFloat<real_t>::Restore(snapshot, m_L.active());
	snapshot += phy::RecordableFloat<real_t>::SnapshotSize();
	phy::RecordableFloat<real_t>::Restore(snapshot, m_L.background());
	snapshot += phy::RecordableFloat<real_t>::SnapshotSize();
	//restore Parent
	Parent::restore(snapshot);
}

real_t RigidBody::LA() const
{
	return m_L.active();
}

real_t RigidBody::LB() const
{
	return m_L.background();
}

void RigidBody::setLB(real_t L)
{
	m_L.background() = L;
}

real_t RigidBody::angleA() const
{
	return m_angle.active();
}

real_t RigidBody::angleB() const
{
	return m_angle.background();
}

void RigidBody::setAngleB(real_t angle)
{
	m_angle.background() = angle;
	math::sincos(angle, m_angleSin.background(), m_angleCos.background());
	updateTMatricesB();
}

real_t RigidBody::angleSinA() const
{
	return m_angleSin.active();
}

real_t RigidBody::angleSinB() const
{
	return m_angleSin.background();
}

real_t RigidBody::angleCosA() const
{
	return m_angleCos.active();
}

real_t RigidBody::angleCosB() const
{
	return m_angleCos.background();
}

void RigidBody::rotateToGlobal(math::VectorRef<2> v) const
{
	v.rotate(angleSinA(), angleCosA());
}

void RigidBody::rotateToLocal(math::VectorRef<2> v) const
{
	v.rotate(-angleSinA(), angleCosA());
}

real_t RigidBody::resultantMoment() const
{
	real_t resMoment = 0;
	for(ForcePointsContainer::const_iterator forcePoint = forcePoints().begin(); forcePoint != forcePoints().end(); ++forcePoint) {
		math::Vector<2> r = forcePoint->second.diff();
		//rotate to global
		rotateToGlobal(r);
		//r det F
		resMoment += r.det(*(forcePoint->first));
	}
	return resMoment;
}

void RigidBody::constructTMatrix(phy::TransformationMatrix & tMatrix)
{
	tMatrix(0,3) = posB(0);
	tMatrix(1,3) = posB(1);

	//multiply by rotation matrix (effective equivalent of matrix multiplication)
	tMatrix(0,0) = angleCosB();
	tMatrix(1,0) = angleSinB();
	tMatrix(0,1) = -angleSinB();
	tMatrix(1,1) = angleCosB();
}

void RigidBody::constructTMatrixInv(phy::TransformationMatrix & tInvMatrix)
{
	//inverted rotation matrix
	tInvMatrix(0,0) = angleCosB();
	tInvMatrix(1,0) = -angleSinB();
	tInvMatrix(0,1) = angleSinB();
	tInvMatrix(1,1) = angleCosB();

	//multiply inverted translation matrix by inverted rotation matrix to obtain inverted
	//transformation matrix (inv translation matrix has negated tMatrix(0,3) and tMatrix(1,3))
	tInvMatrix(0,3) = (-posB(0) * angleCosB()) - (posB(1) * angleSinB());
	tInvMatrix(1,3) = ( posB(0) * angleSinB()) - (posB(1) * angleCosB());
}

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
