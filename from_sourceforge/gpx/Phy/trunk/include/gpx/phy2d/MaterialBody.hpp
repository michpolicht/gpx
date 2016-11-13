#ifndef GPX_Phy2d_MATERIALBODY_HPP_
#define GPX_Phy2d_MATERIALBODY_HPP_

#include "../phy_config.hpp"
#include "Force.hpp"
#include "MovableObject.hpp"

#include <vector>
#include <utility>

#include <gpx/platform.hpp>
#include <gpx/utils/functions.hpp>
#include <gpx/ext/UnorderedMap.hpp>
#include <gpx/math/structures.hpp>

namespace gpx {
namespace phy2d {

/**
 * Material body. Abstract class representing physical object in aspect of Newtonian dynamics.
 * Several parameters are considered in physical simulation of material point. This includes:
 * 	- Position and derivatives (velocity, acceleration).
 * 	- Mass.
 *  - Momentum (double buffered).
 *  - Impulses and forces.
 *	.
 * Momentum parameter is double buffered, thus phase-space is double buffered, since position
 * parameter inherited after MovableObject is double buffered also.
 */
class GPX_API MaterialBody : public MovableObject
{
	typedef MovableObject Parent;

	public:
		#ifdef GPX_EXT_UNORDERED_MAP
			typedef ext::UnorderedMap<Force *, math::Vector<2>, utils::hash<Force * > >::Type ForcePointsContainer;
		#else //fallback to std::map
			typedef std::map<Force *, math::Vector<2> > ForcePointsContainer;
		#endif /* GPX_EXT_UNORDERED_MAP */
			typedef std::pair<Impulse, math::Vector<2> > ImpulsePointPair;
			typedef std::vector<ImpulsePointPair> ImpulsePointsContainer;

	public:
		/**
		 * Set velocity.
		 * @param v velocity vector.
		 */
		virtual void setV(const math::const_VectorPtr<2> & v);

		/**
		 * Get mass.
		 * @return mass.
		 */
		real_t m() const;

		/**
		 * Set mass.
		 * @param m new mass.
		 *
		 * @note current momentum will be untouched.
		 */
		virtual void setM(real_t m);

		/**
		 * Get momentum.
		 * @return momentum vector.
		 */
		const math::Vector<2> & p() const;

		/**
		 * Set momentum.
		 * @param p momentum vector.
		 */
		virtual void setP(const math::const_VectorPtr<2> & p);

		/**
		 * Get kinetic energy. Calculates and returns kinetic energy.
		 * @return energy [J].
		 */
		virtual real_t kineticE() const;

		/**
		 * Mount permanent force at specified point. Each force may be attached to the
		 * object once. Previous mount point is lost if same force is attached again.
		 * @param force force object.
		 * @param point attachment point.
		 */
		virtual void mountForce(Force * force, const math::const_VectorPtr<2> & point = math::Vector<2>(0.0, 0.0));

		/**
		 * Unmount force.
		 * @param force force object.
		 */
		virtual void unmountForce(Force * force);

		/**
		 * Get force point.
		 * @param force force object.
		 * @return attachment point of specified force.
		 */
		const math::Vector<2> & forcePoint(Force * force) const;

		/**
		 * Update force point position.
		 * @param point force point.
		 * @param val new force point position.
		 */
		virtual void updateForcePoint(const math::Vector<2> & point, const math::const_VectorPtr<2> & val);

		/**
		 * Get force points.
		 * @return hash_map containing forces and points they are attached to.
		 */
		const ForcePointsContainer & forcePoints() const;

		/**
		 * Add impulse. Impulse will vanish after next update().
		 */
		virtual void mountImpulse(const Impulse & impulse, const math::const_VectorPtr<2> & point = math::Vector<2>(0.0, 0.0));

		/**
		 * Get impulse points.
		 * @return vector containing (impulse, point) pairs.
		 */
		const ImpulsePointsContainer & impulsePoints() const;

	protected:
		//space initially reserved by m_impulsePoints container (check constructor body)
		static const int IMPULSE_POINTS_NUM = 8;	///< Initial space reserved by impulse-point pairs container.

	protected:
		/**
		 * Constructor.
		 * @param m mass;
		 */
		MaterialBody(real_t m);

		/**
		 * Destructor.
		 */
		virtual ~MaterialBody();

	protected:
		/**
		 * Get active momentum.
		 * @return momentum from active buffer.
		 *
		 * @note this might seem to be equivalent of public method p(), but p() method
		 * doesn't give a warranty that returned value is actual value of active buffer.
		 */
		const math::Vector<2> & pA() const;

		/**
		 * Get i-element of active momentum vector.
		 * @return i coordinate of momentum vector.
		 */
		real_t pA(std::size_t i) const;

		/**
		 * Get background momentum.
		 * @return momentum from background buffer.
		 */
		const math::Vector<2> & pB() const;

		/**
		 * Get i-element of background momentum vector.
		 * @return i coordinate of momentum vector.
		 */
		real_t pB(std::size_t i) const;

		/**
		 * Resultant force.
		 * @return resultant force.
		 */
		const Force & resultantForce() const;

		/**
		 * Get i-element of force vector.
		 * @return i coordinate of force vector.
		 */
		real_t resultantForce(std::size_t i) const;

		//Parent
		virtual void update(real_t dt);

		//Parent
		virtual void updatePos(real_t dt, math::Vector<2> & posB);

		virtual void updateResultantForce(real_t dt, math::Vector<2> & resultantForce);

		virtual void updateP(real_t dt, math::Vector<2> & pB);

		/**
		 * Update impulse dependent parameters. "Impulse dependent" doesn't mean they have
		 * to depend on impulses only.
		 * @param dt elapsed time.
		 * @param pB momentum to be written.
		 *
		 * @note updateForceParams() is being called before this function.
		 */
//		virtual void updateImpulseParams(real_t dt, math::Vector<2> & pB);

		/**
		 * Update force dependent parameters. "Force dependent" doesn't mean they have to
		 * depend on forces only.
		 * @param dt elapsed time.
		 * @param resultantForce resultant force to be written. Current value can be
		 * accessed with resultantForce() method.
		 */
//		virtual void updateForceParams(real_t dt, math::Vector<2> & resultantForce);

	private:
		real_t m_m; 								///< Mass.
		utils::DoubleBuffer<math::Vector<2> > m_p;	///< Momentum (double buffered).

		Force m_resultantForce;	///< Resultant force.

		//Although for material point there is only one point where force may work,
		//it is convenient to provide general container for attaching forces for subclasses
		//(note that this class is logically abstract) and to satisfy interfaces.
		//Container holds pairs (force, mount point).
		ForcePointsContainer m_forcePoints;		///< Force-point pairs container.

		//impulses will be used once and erased
		//note that these are impulses (F * dt), not impulse forces (F).
		ImpulsePointsContainer m_impulsePoints;	///< Impulse-point pairs container.
};

}
}

#endif /* GPX_Phy2d_MATERIALBODY_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
