/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_CRIGIDBODY_HPP_
#define GPX_Phy2d_CRIGIDBODY_HPP_

#include "RigidBody.hpp"
#include "ICNewtonMovable.hpp"
#include "ICDragnDrop.hpp"

namespace gpx {
namespace phy2d {

/**
 * Colliding rigid body. Abstract class representing colliding object in aspects of
 * Newton dynamics.
 *
 * @todo make constructor and destructor protected since this is abstract class.
 */
class GPX_API CRigidBody : public RigidBody,
						   public virtual ICDragnDrop,
						   public virtual ICNewtonMovable
{
	public:
		static const real_t INITIAL_DISLOC_MULTIPLIER = 1.0;	///< Dislocation multiplier default value.

	public:
		/**
		 * Constructor.
		 * @param mass mass.
		 * @param I moment of inertia (calculated for center of mass).
		 * @param material material id.
		 * @param boundR bounding radius. Using default value (-1.0) will trigger
		 * findBoundR() function on each request to obtain bounding radius (see
		 * obtainBoundR()). This may be quite slow. To gain some efficiency, for objects
		 * which are not shifting their shape provide @a boundR value, use static
		 * version FindBoundR() during object creation or re-implement virtual
		 * findBoundR() function.
		 */
		CRigidBody(real_t mass, real_t I, phy::material_t material = 0, real_t boundR = -1.0);

		/**
		 * Destructor.
		 */
		virtual ~CRigidBody();

	public:
		/**
		 * Find bounding radius. Finds bounding radius from given vertices.
		 * @param cvertices vertices.
		 * @return bounding radius.
		 */
		//@todo move FindBoundR functions to gpx::model?
		static real_t FindBoundR(const model::VertexData<2> & cvertices);

//		static real_t FindBoundR(const model::PolyGroup<POLY> & polyGroup)

	public:
		phy::material_t material() const;

		void setMaterial(phy::material_t material);

		/**
		 * Find bounding radius. Finds bounding radius using c-model vertices.
		 * Default implementation might be quite slow since it iterates over each c-vertex.
		 * @return bounding radius value.
		 */
		virtual real_t findBoundR();

        /**
         * Set boundR.
         * @param boundR bounding radius or -1.0 to force bounding radius detection.
         */
		void setBoundR(real_t boundR);

		/**
		 * Get boundR value.
		 * @return boundR value.
		 *
		 * @note this function will return current boundR value which may be -1.0.
		 *
		 * @see obtainBoundR().
		 */
		real_t boundR() const;

		/**
		 * Obtain bounding radius. For convenience this function checks current boundR value
		 * and performs findBoundR() if necessary.
		 * @return bounding radius. In case boundR value is set to -1.0 this function will
		 * call findBoundR() and return calculated value.
		 *
		 * @see boundR().
		 */
		real_t obtainBoundR();

		/**
		 * Get dislocation vector multiplier.
		 * @return dislocation vector multiplier.
		 */
		real_t dislocMultiplier() const;

		/**
		 * Set multiplier for dislocation vector. To prevent locking in pseudo-stable states
		 * GPX dislocates bodies slightly. By default dislocation is proportional to
		 * angular momentum and bounding radius. This value is estimated as an upper bound
		 * of arbitrary c-vertex rotational motion path, that may lead to unexpected
		 * subsequent collision. By using this multiplier, dislocation vector may be
		 * fine-tuned. Although there's no limitation for multiplier value, typical values
		 * would be located inside interval [0.0, 1.0], where 0.0 removes dislocation
		 * effect completely and 1.0 leaves dislocation vector at its default upper bound
		 * estimated value.
		 * @param dislocMulitplier dislocation vector multiplier.
		 */
		void setDislocMultiplier(real_t dislocMultiplier);

		//virtual phy::DragnDropColliding
		virtual void performDragnDrop(DragnDropCollider * collider);

		//phy::INewtonCollidingMovable
		void mountImpulse(const Impulse & impulse, const math::const_VectorPtr<2> & point = math::Vector<2>(0.0, 0.0));

		//phy::INewtonCollidingMovable
		void roundAwayImpulse(Impulse & impulse, const NewtonCollisionData & data, bool normal);

		//phy::INewtonColliding
		math::Vector<2> aCoef(const NewtonCollisionBase & bData) const;

		//phy::INewtonColliding
		math::Vector<2> bCoef(real_t b, const NewtonCollisionBase & bData) const;

		//phy::INewtonColliding
		phy::material_t material(element_t element) const;

	private:
		phy::material_t m_material;	///< Material.
		real_t m_boundR;       	///< Bounding radius cache.
		real_t m_dislocMultiplier;	///< Dislocation multiplier.
};

}
}

#endif /* GPX_Phy2d_CRIGIDBODY_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
