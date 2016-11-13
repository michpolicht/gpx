/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/phy2d/SNewtonCollider.hpp"
#include "../../../include/gpx/phy2d/ICNewtonMovable.hpp"
#include "../../../include/gpx/phy2d/Force.hpp"

#include <gpx/math/structures.hpp>
#include <gpx/log.hpp>

#include <iostream>

namespace gpx {
namespace phy2d {

SNewtonCollider::SNewtonCollider(NewtonCollisionExecutor & collisionContractor, phy::NewtonPlasticityTable & plasticityTable):
	m_collisionContractor(collisionContractor),
	m_plasticityTable(plasticityTable),
	m_subsequentCollisionLimit(INITIAL_SUBSEQUENT_COLLISION_LIMIT)
{
}

SNewtonCollider::~SNewtonCollider()
{
}

NewtonCollisionExecutor & SNewtonCollider::DefaultCollisionContractor()
{
	static NewtonCollisionExecutor executor;
	return executor;
}

int SNewtonCollider::subsequentCollisionLimit() const
{
	return m_subsequentCollisionLimit;
}

void SNewtonCollider::setSubsequentCollisionLimit(int limit)
{
	m_subsequentCollisionLimit = limit;
}

void SNewtonCollider::addFixed(ICNewton * obj)
{
	m_fixed.insert(obj);
}

void SNewtonCollider::removeFixed(ICNewton * obj)
{
	m_fixed.erase(obj);
}

void SNewtonCollider::addMovable(ICNewtonMovable * obj)
{
	m_movables.insert(obj);
}

void SNewtonCollider::removeMovable(ICNewtonMovable * obj)
{
	m_movables.erase(obj);
}

void SNewtonCollider::update(real_t dt)
{
    /*
	 * current simplifications: collision is considered in one point with one object at time.
	 */

	NewtonDetecionData dData;
	dData.dt = dt;
	bool collision;
	int pass = 0;

    //consider movable object i
	MovablesContainer::iterator i = m_movables.begin();
	while (i != m_movables.end()) {
		dData.moving = *i;
		dData.moving->update(dt);
		dData.moving->swapBuffers(); //swap to new position

		//handle collisions with other movable objects
		pass++;
		collision = false;
		for (MovablesContainer::iterator j = m_movables.begin(); j != m_movables.end(); ++j) {
			if (i == j)
				continue;
			dData.passive = *j;
			dData.passiveMov = *j;

			if (collision = updateHelper(dData))
				break; //skip to next pass or next i
		}
		//handle collisions with fixed objects
		if (!collision) {
			dData.passiveMov = 0;
			for (FixedContainer::iterator j = m_fixed.begin(); j != m_fixed.end(); ++j) {
				dData.passive = *j;
				if (collision = updateHelper(dData))
					break;	//skip to next pass or next i
			}
		}
		if (collision) {
			if (pass >= 2)
				GPX_DEBUG("subsequent collision (pass " << pass << ")");
			if (pass < subsequentCollisionLimit())
				continue;	//skip to the next pass
			else
				GPX_DEBUG("subsequent collision limit of " << subsequentCollisionLimit() << " passes exceeded");
		}
		++i;
		pass = 0;
	}
}

bool SNewtonCollider::updateHelper(const NewtonDetecionData & dData)
{
	NewtonCollisionBase movingBase(dData), passiveBase(dData);

	//case 1: moving is a wedge, passive is a bumper
	if (detectAndCollect(dData.moving, dData.passive, dData.moving, dData.passive, movingBase, passiveBase)
	//case 2: passive is a wedge, moving is a bumper
	|| detectAndCollect(dData.moving, dData.passive, dData.passive, dData.moving, passiveBase, movingBase)) {

		dData.moving->swapBuffers(); //move back to non-intersecting pos

		NewtonCollisionData movingData(movingBase, m_plasticityTable.get(dData.moving->material(movingBase.element)));
		NewtonCollisionData passiveData(passiveBase, m_plasticityTable.get(dData.passive->material(passiveBase.element)));

		movingData.mat = dData.moving->material(movingBase.element);
		passiveData.mat = dData.passive->material(passiveBase.element);

		//obtain coefficients
		movingData.a = dData.moving->aCoef(movingData.bData);
		movingData.bn = dData.moving->bCoef(movingData.pData.e, movingData.bData);
		movingData.bp = dData.moving->bCoef(movingData.pData.s, movingData.bData);
		passiveData.a = dData.passive->aCoef(passiveData.bData);
		passiveData.bn = dData.passive->bCoef(passiveData.pData.e, passiveData.bData);
		passiveData.bp = dData.passive->bCoef(passiveData.pData.s, passiveData.bData);

		m_collisionContractor.perform(movingData, passiveData);

		return true;
	}
	return false;
}

bool SNewtonCollider::detectAndCollect(ICNewtonMovable * moving,
									  ICNewton * passive,
									  ICNewton * wedge,
									  ICNewton * bumper,
									  NewtonCollisionBase & wedgeBase,
									  NewtonCollisionBase & bumperBase)
{
	for (ICPolyGroup::element_t wi = 0; wi < wedge->elements(); wi++) {
		const model::VertexData<2> & vertices = wedge->element(wi)->cvertices();
		for (model::VertexData<2>::const_iterator vertIt = vertices.begin(); vertIt != vertices.end(); ++vertIt) {
			for (ICPolyGroup::element_t bi = 0; bi < bumper->elements(); bi++) {
				if (bumper->element(bi)->test(bumper->mapToLocal(wedge->mapToGlobal(*vertIt)))) {
					//fill basic data
//					bumperData.bData.other = wedge;
//					wedgeData.bData.other = bumper;

					wedgeBase.wedge = true;
					bumperBase.wedge = false;

					wedgeBase.element = wi;
					bumperBase.element = bi;

					//obtain post collision point
		//			wedgeData.bData.points.post = vertIt;
					bumperBase.points.post = bumper->mapToLocal(wedge->mapToGlobal(*vertIt));

					moving->swapBuffers(); //swap to pre-collision

					//map post-collision point into pre-collision system as relative to bumper
					wedgeBase.points.post = wedge->mapToLocal(bumper->mapToGlobal(bumperBase.points.post));

					//obtain pre-collision points
					//get pre-collision vertices (however they may differ only for shape-shifting objects, in addition double buffered)
					const model::VertexData<2> & preVertices = wedge->element(wi)->cvertices();
					wedgeBase.points.pre = preVertices[vertices.distance(vertIt)];
					bumperBase.points.pre = bumper->mapToLocal(wedge->mapToGlobal(wedgeBase.points.pre));

					//obtain effective points
					bumperBase.points.eff = bumper->element(bi)->eff(bumperBase.points.pre, bumperBase.points.post);
					wedgeBase.points.eff = wedge->mapToLocal(bumper->mapToGlobal(bumperBase.points.eff));

					//obtain normal
					bumperBase.normal = bumper->element(bi)->normal(bumperBase.points);
					wedgeBase.normal = bumperBase.normal.inverse();

					moving->swapBuffers(); //back to the future

					//TEMP pseudocode attempt:
					wedgeBases.push(wedgeBase);
					bumperBases.push(bumperBase);
//					return true;	//@todo remove returns
				}
			}
		}
	}
	return false;
}

}
}

//(c)MP: Copyright © 2011, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
