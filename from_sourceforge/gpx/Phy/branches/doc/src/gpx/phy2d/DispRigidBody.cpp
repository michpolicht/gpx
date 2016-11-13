/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/phy2d/DispRigidBody.hpp"

namespace gpx {
namespace phy2d {

DispRigidBody::DispRigidBody(real_t m, real_t I, const math::const_VectorPtr<2> & cm):
		Parent(m, I),
		m_centerOfMass(cm),
		m_rp(m_centerOfMass)
{
	updateIdisp();
}

DispRigidBody::~DispRigidBody()
{
}

real_t DispRigidBody::Steiner(real_t m, real_t I, const math::const_VectorPtr<2> & displacement)
{
	//Idisp = Icenter + m * R^2
	return I + (m * displacement.dot());
}

real_t DispRigidBody::Idisp() const
{
	return m_Idisp;
}

void DispRigidBody::setM(real_t m)
{
	Parent::setM(m);
	updateIdisp();
}

void DispRigidBody::setAngularV(real_t angularV)
{
	setL(Idisp() * angularV);
}

void DispRigidBody::setI(real_t I)
{
	Parent::setI(I);
	updateIdisp();
}

const math::Vector<2> & DispRigidBody::rotationPoint() const
{
	return m_rp.pos;
}

void DispRigidBody::setRotationPoint(const math::const_VectorPtr<2> & rpPos)
{
	m_rp.pos = rpPos;
	m_rp.displacement = rpPos - m_centerOfMass;
	updateIdisp();
}

const math::Vector<2> & DispRigidBody::centerOfMass() const
{
	return m_centerOfMass;
}

void DispRigidBody::setCenterOfMass(const math::const_VectorPtr<2> & centerOfMass)
{
	m_centerOfMass = centerOfMass;
	m_rp.displacement = m_rp.pos - m_centerOfMass;
	updateIdisp();
}

real_t DispRigidBody::kineticE() const
{
	return 0.5 * (pA().dot() / m() + LA() * LA() / Idisp());
}

DispRigidBody::RotationPoint::RotationPoint(const math::const_VectorPtr<2> & pos, const math::const_VectorPtr<2> & displacement):
		pos(pos),
		displacement(displacement)
{
}

void DispRigidBody::updatePosAngle(real_t dt, math::Vector<2> & posB, real_t & angleB)
{
	real_t angularVdt = LB() / Idisp() * dt;
	angleB = angleA() + angularVdt;
	if (angleB > 2 * math::PI)
		angleB -= 2 * math::PI;
	else if (angleB < -2 * math::PI)
		angleB += 2 * math::PI;

	posB = posA() + pB() / m() * dt + disloc() * std::abs(angularVdt);
}

void DispRigidBody::updatePL(real_t dt, math::Vector<2> & pB, real_t & LB)
{
	pB(0) = pA(0) + resultantForce(0) * dt; //add impulse to current momentum
	pB(1) = pA(1) + resultantForce(1) * dt;

	LB = LA() + resultantMoment() * dt;

	for(ImpulsePointsContainer::const_iterator impPoint = impulsePoints().begin(); impPoint != impulsePoints().end(); ++impPoint) {
		pB += impPoint->first;
		math::Vector<2> r(impPoint->second - m_rp.pos);
		rotateToGlobal(r);
		LB += r.det(impPoint->first);
	}
}

void DispRigidBody::updateResultantForceMoment(real_t dt, math::Vector<2> & resultantForce, real_t & resultantMoment)
{
	for(ForcePointsContainer::const_iterator forcePoint = forcePoints().begin(); forcePoint != forcePoints().end(); ++forcePoint) {
		Force forceLocal(*(forcePoint->first));
		resultantForce += forceLocal;
		//rotating force by -angle to local coordinates (instead of rotating r to global)
		rotateToLocal(forceLocal);
		//r det F = F det -r
		//r = forcePoint->second - m_rp.pos
		resultantMoment += forceLocal.det(m_rp.pos - forcePoint->second);
	}
}

void DispRigidBody::constructTMatrix(phy::TransformationMatrix & tMatrix, phy::TransformationMatrix & tInvMatrix)
{
	//translate to rotation point (effective equivalent of matrix multiplication)
	tMatrix(0,3) = posB(0) + m_rp.pos(0);   //base position + relative rotation point position
	tMatrix(1,3) = posB(1) + m_rp.pos(1);

	//multiply by rotation matrix (effective equivalent of matrix multiplication)
	tMatrix(0,0) = angleCosB();
	tMatrix(1,0) = angleSinB();
	tMatrix(0,1) = -angleSinB();
	tMatrix(1,1) = angleCosB();

	//translate back to origin (effective equivalent of matrix multiplication)
	tMatrix(0,3) += (-m_rp.pos(0) * angleCosB()) + (m_rp.pos(1) * angleSinB());
	tMatrix(1,3) += (-m_rp.pos(0) * angleSinB()) - (m_rp.pos(1) * angleCosB());

	//inverted rotation matrix
	tInvMatrix(0,0) = angleCosB();
	tInvMatrix(1,0) = -angleSinB();
	tInvMatrix(0,1) = angleSinB();
	tInvMatrix(1,1) = angleCosB();

	//multiply inverted translation matrix by inverted rotation matrix to obtain inverted
	//transformation matrix (inv translation matrix has negated tMatrix(0,3) and tMatrix(1,3))
	tInvMatrix(0,3) = (-tMatrix(0,3) * angleCosB()) - (tMatrix(1,3) * angleSinB());
	tInvMatrix(1,3) = ( tMatrix(0,3) * angleSinB()) - (tMatrix(1,3) * angleCosB());
}

void DispRigidBody::findExtAngularARotationPoints(RotationPoint & rpA, RotationPoint & rpB)
{
	real_t Fx, Fy, RdetF;

	rotationPointPrecalc(Fx, Fy, RdetF);
	real_t Fx2Fy2 = (Fx * Fx) + (Fy * Fy); //dot product...

	if (Fx2Fy2 == 0.0) {
		//possible only if Fx = 0.0 and Fy = 0.0
		//thus rrx and rry must be 0, since rrx = (0.5 * Fy * I / m) / FdetR, rry = (0.5 * Fx * I / m) / FdetR
		rpA.displacement.zero();
		rpB.displacement.zero();
		rpA.pos = rpB.pos = m_centerOfMass;
		return;
	}

	real_t sqrt = std::sqrt((RdetF * RdetF) + (Fx2Fy2 * I() / m()));

	rpA.displacement(0) = Fy * (RdetF + sqrt) / Fx2Fy2;
	rpB.displacement(0) = Fy * (RdetF - sqrt) / Fx2Fy2;
	rpA.displacement(1) = -Fx * (RdetF + sqrt) / Fx2Fy2;
	rpB.displacement(1) = -Fx * (RdetF - sqrt) / Fx2Fy2;
	rpA.pos = m_centerOfMass + rpA.displacement;
	rpB.pos = m_centerOfMass + rpB.displacement;
}

void DispRigidBody::findMaxERotationPoint(RotationPoint & rp)
{
	real_t Fx, Fy, mRdetF;

	rotationPointPrecalc(Fx, Fy, mRdetF);
	mRdetF *= m();
	if (math::ale(mRdetF, 0.0))
		rp.displacement.zero();
	else {
		rp.displacement(0) = -Fy * I() / mRdetF;
		rp.displacement(1) = Fx * I() / mRdetF;
	}
	rp.pos = m_centerOfMass + rp.displacement;
}

void DispRigidBody::findMinERotationPoint(RotationPoint & rp)
{
	real_t Fx, Fy, RdetF;

	rotationPointPrecalc(Fx, Fy, RdetF);
	real_t Fx2Fy2 = (Fx * Fx) + (Fy * Fy); //dot product...
	if (math::ale(Fx2Fy2, 0.0)) {
		rp.displacement(0) = Fy * RdetF * std::numeric_limits<real_t>::infinity();
		rp.displacement(1) = -Fx * RdetF * std::numeric_limits<real_t>::infinity();
	} else {
		rp.displacement(0) = Fy * RdetF / Fx2Fy2;
		rp.displacement(1) = -Fx * RdetF / Fx2Fy2;
	}
	rp.pos = m_centerOfMass + rp.displacement;
}

void DispRigidBody::rotationPointPrecalc(real_t & Fx, real_t & Fy, real_t & RdetF) const
{
	Fx = Fy = RdetF = 0.0;

	for (ForcePointsContainer::const_iterator forcePoint = forcePoints().begin(); forcePoint != forcePoints().end(); ++forcePoint) {
		Fx += forcePoint->first->coord(0);
		Fy += forcePoint->first->coord(1);
		//r det F = F det -r
		RdetF += forcePoint->first->det(m_centerOfMass - forcePoint->second);
	}
	for (ImpulsePointsContainer::const_iterator impPoint = impulsePoints().begin(); impPoint != impulsePoints().end(); ++impPoint) {
		Fx += impPoint->first(0);
		Fy += impPoint->first(1);
		//r det F = F det -r
		RdetF += impPoint->first.det(m_centerOfMass - impPoint->second);
	}
}

void DispRigidBody::updateIdisp()
{
	m_Idisp = Steiner(m(), I(), m_rp.displacement);
}

}
}

//(c)MP: Copyright © 2011, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
