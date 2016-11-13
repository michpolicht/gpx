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
		/**
		 * Constructor.
		 * @param m mass;
		 */
		MaterialBody(real_t m);

		/**
		 * Destructor.
		 */
		virtual ~MaterialBody();

		/**
		 * Set velocity.
		 * @param v velocity vector.
		 */
		void setV(math::const_VectorRef<2> v);

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
		void setM(real_t m);

		/**
		 * Get momentum.
		 * @return momentum vector.
		 */
		const math::Vector<2> & p() const;

		/**
		 * Set momentum.
		 * @param p momentum vector.
		 */
		void setP(math::const_VectorRef<2> p);

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
		void mountForce(const Force * force, math::const_PointRef<2> point = math::Point<2>());

		/**
		 * Unmount force.
		 * @param force force object. Can not be null.
		 */
		void unmountForce(const Force * force);

		/**
		 * Read force point value.
		 * @param force force object.
		 */
		math::Point<2> forcePoint(const Force & force) const;

		/**
		 * Update force point position.
		 * @param point force point.
		 * @param pos new force point position.
		 */
		void updateForcePoint(const Force & force, math::const_PointRef<2> pos);

		/**
		 * Apply impulse. Impulse immediately affects momentum stored in active buffer.
		 * @point point of application.
		 */
		virtual void applyImpulse(const Impulse & impulse, math::const_PointRef<2> point = math::Point<2>());

		/**
		 * Update object. This function is responsible for updating physical parameters.
		 * For double buffered parameters all new data should be written into background
		 * buffer.
		 * @param dt elapsed time.
		 */
		//IMovable
		virtual void update(real_t dt);

		//IRecordable
		virtual std::size_t snapshotSize() const;

		//IRecordable
		virtual void store(char * snapshot) const;

		//IRecordable
		virtual void restore(char * snapshot);

	protected:
		typedef ext::UnorderedMap<const Force *, math::Point<2>, utils::hash<const Force * > > ForcePointsContainer;

		/**
		 * Get force points (const version).
		 * @return map containing forces and points they are attached to.
		 */
		const ForcePointsContainer & forcePoints() const;

		/**
		 * Get force points.
		 * @return map containing forces and points they are attached to.
		 */
		ForcePointsContainer & forcePoints();

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
		 * Set background momentum.
		 * @param p momentum vector.
		 */
		void setPB(math::const_VectorRef<2> p);

		/**
		 * Calculate resultant force.
		 * @return resultant force.
		 */
		Force resultantForce() const;

	private:
		real_t m_m; 								///< Mass.
		utils::DoubleBuffer<math::Vector<2> > m_p;	///< Momentum (double buffered).

		//Although for material point there is only one point where force may work,
		//it is convenient to provide general container for attaching forces for subclasses
		//and to satisfy interfaces.
		//Container holds pairs (force, mount point).
		ForcePointsContainer m_forcePoints;		///< Force-point pairs container.
};

}
}

#endif /* GPX_Phy2d_MATERIALBODY_HPP_ */
