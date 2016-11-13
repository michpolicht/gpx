/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_NEWTONCOLLIDER_HPP_
#define GPX_Phy2d_NEWTONCOLLIDER_HPP_

#include "../phy_config.hpp"
#include "../phy/ITimePerformer.hpp"
#include "../phy/NewtonPlasticityTable.hpp"
#include "NewtonCollisionExecutor.hpp"

#include <gpx/platform.hpp>
#include <gpx/utils/functions.hpp>
#include <gpx/ext/UnorderedSet.hpp>

namespace gpx {
namespace phy2d {

class ICNewton;
class ICNewtonMovable;
class NewtonCollisionData;

/**
 * Newton collider. Collider updates movable objects, detects and handles collisions
 * between them and fixed objects.
 */
class GPX_API NewtonCollider : public virtual phy::ITimePerformer
{
	public:
		static const int INITIAL_SUBSEQUENT_COLLISION_LIMIT = 2;

	public:
		/**
		 * Constructor.
		 * @param collisionContractor object performing collision act.
		 */
		NewtonCollider(NewtonCollisionExecutor & collisionContractor = DefaultCollisionContractor(),
					   phy::NewtonPlasticityTable & plasticityTable = phy::NewtonPlasticityTable::Instance());

		/**
		 * Destructor.
		 */
		virtual ~NewtonCollider();

	public:
		static NewtonCollisionExecutor & DefaultCollisionContractor();

	public:
		/**
		 * Get subsequent collision limit.
		 * @return current subsequent collision limit.
		 */
		int subsequentCollisionLimit() const;

		/**
		 * Set subsequent collision limit.
		 * @param limit new subsequent collision limit.
		 */
		void setSubsequentCollisionLimit(int limit);

		/**
		 * Add fixed object.
		 * @param obj object to add.
		 */
		void addFixed(ICNewton * obj);

		/**
		 * Remove fixed object.
		 * @param obj object to remove.
		 */
		void removeFixed(ICNewton * obj);

		/**
		 * Add movable object.
		 * @param obj object to add.
		 */
		void addMovable(ICNewtonMovable * obj);

		/**
		 * Remove movable object.
		 * @param obj object to remove.
		 */
		void removeMovable(ICNewtonMovable * obj);

		/**
		 * Perform simulation and deal with collisions.
		 */
		void update(real_t dt);

	protected:
#ifdef GPX_EXT_UNORDERED_SET
		typedef ext::UnorderedSet<ICNewton * , utils::hash<ICNewton *> >::Type FixedContainer;
		typedef ext::UnorderedSet<ICNewtonMovable *, utils::hash<ICNewtonMovable *> >::Type MovablesContainer;
#else	//fallback to std::set
		typedef std::set<ICNewton *> FixedContainer;
		typedef std::set<ICNewtonMovable *> MovablesContainer;
#endif /* GPX_EXT_UNORDERED_SET */

	private:
		/**
		 * Update helper. Helper inline function used by update(). If collision occurred,
		 * impulse will be applied to @a moving object. If @a fixedMov is not 0, inverse
		 * impulse will be applied to it.
		 */
		bool updateHelper(const NewtonDetecionData & dData);

		/**
		 * Test for collision and collect collision data. Helper inline function used by updateHelper().
		 */
		bool detectAndCollect(ICNewtonMovable * moving,
							  ICNewton * fixed,
							  ICNewton * wedge,
							  ICNewton * bumper,
							  NewtonCollisionBase & wedgeBase,
							  NewtonCollisionBase & bumperBase);

	private:
		FixedContainer m_fixed;
		MovablesContainer m_movables;
		NewtonCollisionExecutor & m_collisionContractor;
		phy::NewtonPlasticityTable & m_plasticityTable;
		int m_subsequentCollisionLimit;
};



}
}

#endif /* GPX_Phy2d_NEWTONCOLLIDER_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
