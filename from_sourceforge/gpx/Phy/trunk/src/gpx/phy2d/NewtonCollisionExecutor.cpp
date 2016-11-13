/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/phy2d/NewtonCollisionExecutor.hpp"

#include <gpx/log.hpp>

namespace gpx {
namespace phy2d {

NewtonCollisionExecutor::NewtonCollisionExecutor(phy::NewtonFrictionTable & frictionTable):
		m_frictionTable(frictionTable)
{
}

void NewtonCollisionExecutor::perform(const NewtonCollisionData & movingData,
									  const NewtonCollisionData & passiveData)
{
	real_t ax = passiveData.a(0) + movingData.a(0);
	real_t ay = passiveData.a(1) + movingData.a(1);

	//calculate normal impulse
	real_t bx = passiveData.bn(0) - movingData.bn(0);
	real_t by = passiveData.bn(1) - movingData.bn(1);
	real_t normalProj = math::Vector<2>( bx / ax, by / ay).dot(passiveData.bData.normal);
	Impulse normalFdt(passiveData.bData.normal * normalProj);
	GPX_DEBUG("normalFdt: " << normalFdt);

	//calculate parallel impulse
	bx = passiveData.bp(0) - movingData.bp(0);
	by = passiveData.bp(1) - movingData.bp(1);
	real_t parallelProj = math::Vector<2>( bx / ax, by / ay).dot(passiveData.bData.normal.orthoCCW());

	//friction coefficients are temporary, shall be replaced by material data in future
//		real_t fd = std::numeric_limits<real_t>::infinity();	//tmp
	real_t fd = 0.0;	//tmp
	real_t fs = 0.0;	//tmp
	real_t ff = std::abs(parallelProj / normalProj); //friction coefficient is tg(alpha)
//		std::cout << "ff: " << ff << std::endl;
	Impulse parallelFdt(passiveData.bData.normal.orthoCCW());

	parallelFdt *= parallelProj;	//tmp uncomment code below
//		parallelFdt.zero(); //tmp
	GPX_DEBUG("parallelFdt: " << parallelFdt);
//	GPX_DEBUG("fixed a: " << passiveData.a << "fixed b: " << passiveData.b);
//	GPX_DEBUG("moving a: " << movingData.a << "moving b: " << movingData.b);

	/* good code, uncomment this
	if (movingData.b.ale(fixedData.b) && (ff <= fs)) {
		//static friction (impulse)
		parallelFdt *= parallelProj;
//			std::cout << "static friction" << std::endl;
	} else //max static friction exceeded, or objects in relative motion
		if (ff < fd) {
			//dynamic friction (impulse)
			parallelFdt *= parallelProj;
//				std::cout << "dynamic friction" << std::endl;
		} else {
			//constant dynamic friction (force)
//			parallelFdt *= fd * normalProj * dt; //?
			parallelFdt *= fd * normalProj; //?
//				std::cout << "constant friction" << std::endl;
		}
	 */

	//round away and mount impulses
	ICNewtonMovable * moving = movingData.bData.dData.moving;
	moving->roundAwayImpulse(normalFdt, movingData, true);
	moving->roundAwayImpulse(parallelFdt, movingData, false);
	if (passiveData.bData.dData.passiveMov) {
		ICNewtonMovable * passiveMov = passiveData.bData.dData.passiveMov;
		normalFdt.invert();	//invert
		parallelFdt.invert();
		passiveMov->roundAwayImpulse(normalFdt, passiveData, true);
		passiveMov->roundAwayImpulse(parallelFdt, passiveData, false);
		//mount inverted on fixedMov first then
		passiveMov->mountImpulse(normalFdt, passiveData.bData.points.eff);
		passiveMov->mountImpulse(parallelFdt, passiveData.bData.points.eff);
		normalFdt.invert();	//invert back for moving
		parallelFdt.invert();
	}
	moving->mountImpulse(normalFdt, movingData.bData.points.eff);
	moving->mountImpulse(parallelFdt, movingData.bData.points.eff);
}


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
