/**
 * @file
 * @brief .
 */

#include "../../../../../include/gpx/phy2d/cnewton/pmepp2_s/BasicExecutor.hpp"

#include <gpx/log.hpp>

namespace gpx {
namespace phy2d {
namespace cnewton {
namespace pmepp2_s {

BasicExecutor::~BasicExecutor()
{
}

//void BasicExecutor::perform(const CollisionData & movingData, const CollisionData & passiveData)
//{
//	real_t ax = passiveData.a(0) + movingData.a(0);
//	real_t ay = passiveData.a(1) + movingData.a(1);
//
//	//calculate normal impulse
//	real_t bx = (passiveData.pData.e * passiveData.b(0)) - (movingData.pData.e * movingData.b(0));
//	real_t by = (passiveData.pData.e * passiveData.b(1)) - (movingData.pData.e * movingData.b(1));
//	real_t normalProj = math::Vector<2>( bx / ax, by / ay).dot(passiveData.dData.normal);
//	Impulse normalFdt(passiveData.dData.normal);
//	if (normalProj > 0.0)
//		normalFdt *= normalProj;
//	else
//		normalFdt.zero();
//	GPX_DEBUG("normalFdt: " << normalFdt);
//
//	//calculate parallel impulse
//	bx = (passiveData.pData.s * passiveData.b(0)) - (movingData.pData.s * movingData.b(0));
//	by = (passiveData.pData.s * passiveData.b(1)) - (movingData.pData.s * movingData.b(1));
//	real_t parallelProj = math::Vector<2>(bx / ax, by / ay).dot(passiveData.dData.normal.orthoCCW());
//	Impulse parallelFdt(passiveData.dData.normal.orthoCCW() * parallelProj);
//	GPX_DEBUG("parallelFdt: " << parallelFdt);
//
//	//round away and mount impulses
//	ICMovable * moving = movingData.dData.bData.moving;
//	moving->roundAwayImpulses(normalFdt, parallelFdt, movingData);
//	if (passiveData.dData.bData.passiveMov) {
//		ICMovable * passiveMov = passiveData.dData.bData.passiveMov;
//		normalFdt.invert();	//invert
//		parallelFdt.invert();
//		passiveMov->roundAwayImpulses(normalFdt, parallelFdt, passiveData);
//		//mount inverted on fixedMov first then
////		passiveImpulses.push_back(ImpulseData(normalFdt, parallelFdt, passiveData.dData.pre));
//		passiveMov->applyImpulse(normalFdt, passiveData.dData.pre);
//		passiveMov->applyImpulse(parallelFdt, passiveData.dData.pre);
//		normalFdt.invert();	//invert back for moving
//		parallelFdt.invert();
//	}
//	moving->applyImpulse(normalFdt, movingData.dData.pre);
//	moving->applyImpulse(parallelFdt, movingData.dData.pre);
//}

}
}
}
}

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
