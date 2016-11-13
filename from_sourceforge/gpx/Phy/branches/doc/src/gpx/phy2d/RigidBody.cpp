/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/phy2d/RigidBody.hpp"

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
	m_L(doubleBufferController(), 0.0),
	m_resultantMoment(0.0),
	m_disloc()
{
	//calculate sinus and cosinus of current angle
	math::sincos(m_angle.active(), & m_angleSin.active(), & m_angleCos.active());
	math::sincos(m_angle.background(), & m_angleSin.background(), & m_angleCos.background());
	updateTMatrix();
}

RigidBody::~RigidBody()
{
}

real_t RigidBody::angle() const
{
	return m_angle.active();
}

void RigidBody::setAngle(real_t angle)
{
	m_angle.active() = angle;
	m_angle.background() = angle;
	math::sincos(angle, & m_angleSin.active(), & m_angleCos.active());
	math::sincos(angle, & m_angleSin.background(), & m_angleCos.background());
	updateTMatrix();
}

void RigidBody::setAngularV(real_t angularV)
{
	m_L.active() = I() * angularV;
	m_L.background() = I() * angularV;
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
	return m_L.active();
}

void RigidBody::setL(real_t L)
{
	m_L.active() = L;
	m_L.background() = L;
}

void RigidBody::setDisloc(const math::const_VectorPtr<2> & disloc)
{
	m_disloc = disloc;
}

const math::Vector<2> & RigidBody::disloc() const
{
	return m_disloc;
}

real_t RigidBody::kineticE() const
{
	return 0.5 * (pA().dot() / m() + LA() * LA() / I());
}

real_t RigidBody::LA() const
{
	return m_L.active();
}

real_t RigidBody::LB() const
{
	return m_L.background();
}

real_t RigidBody::angleA() const
{
	return m_angle.active();
}

real_t RigidBody::angleB() const
{
	return m_angle.background();
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

real_t RigidBody::resultantMoment() const
{
	return m_resultantMoment;
}

void RigidBody::updatePosAngle(real_t dt, math::Vector<2> & posB, real_t & angleB)
{
	real_t angularVdt = LB() / I() * dt;
	angleB = angleA() + angularVdt;
	if (angleB > 2 * math::PI)
		angleB -= 2 * math::PI;
	else if (angleB < -2 * math::PI)
		angleB += 2 * math::PI;

	posB = posA() + pB() / m() * dt + disloc() * std::abs(angularVdt) + disloc() * 0.005; //@todo + oscilation factor (disloc() * oscilationCoeff)
}

void RigidBody::updatePL(real_t dt, math::Vector<2> & pB, real_t & LB)
{
	pB(0) = pA(0) + resultantForce(0) * dt; //add impulse to current momentum
	pB(1) = pA(1) + resultantForce(1) * dt;

	LB = LA() + resultantMoment() * dt;

	for(ImpulsePointsContainer::const_iterator impPoint = impulsePoints().begin(); impPoint != impulsePoints().end(); ++impPoint) {
		pB += impPoint->first;
		math::Vector<2> r(impPoint->second);
		rotateToGlobal(r);
		//r det F
		LB += r.det(impPoint->first);
	}
}

void RigidBody::updateResultantForceMoment(real_t dt, math::Vector<2> & resultantForce, real_t & resultantMoment)
{
	for(ForcePointsContainer::const_iterator forcePoint = forcePoints().begin(); forcePoint != forcePoints().end(); ++forcePoint) {
		Force forceLocal(*(forcePoint->first));
		resultantForce += forceLocal;
		//rotating force by -angle to local coordinates (instead of rotating r to global)
		rotateToLocal(forceLocal);
		//r det F = F det -r
		//r = forcePoint->second - rotation point (0.0)
		resultantMoment += forceLocal.det(-forcePoint->second);
	}
}

void RigidBody::constructTMatrix(phy::TransformationMatrix & tMatrix, phy::TransformationMatrix & tInvMatrix)
{
	tMatrix(0,3) = posB(0);
	tMatrix(1,3) = posB(1);

	//multiply by rotation matrix (effective equivalent of matrix multiplication)
	tMatrix(0,0) = angleCosB();
	tMatrix(1,0) = angleSinB();
	tMatrix(0,1) = -angleSinB();
	tMatrix(1,1) = angleCosB();

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

math::VectorPtr<2> & RigidBody::rotateToGlobal(math::VectorPtr<2> & v) const
{
	return v.rotate(angleSinA(), angleCosA());
}

math::VectorPtr<2> & RigidBody::rotateToLocal(math::VectorPtr<2> & v) const
{
	return v.rotate(-angleSinA(), angleCosA());
}

void RigidBody::updatePos(real_t dt, math::Vector<2> & posB)
{
	updatePosAngle(dt, posB, m_angle.background());
	m_disloc.zero();
//	m_repulse.zero();
	//calculate sine and cosine of current angle
	math::sincos(m_angle.background(), & m_angleSin.background(), & m_angleCos.background());
}

void RigidBody::updateResultantForce(real_t dt, math::Vector<2> & resultantForce)
{
	m_resultantMoment = 0.0;
	updateResultantForceMoment(dt, resultantForce, m_resultantMoment);
}

void RigidBody::updateP(real_t dt, math::Vector<2> & pB)
{
	updatePL(dt, pB, m_L.background());
}

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
