/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_DISPRIGIDBODY_HPP_
#define GPX_Phy2d_DISPRIGIDBODY_HPP_

#include "RigidBody.hpp"

namespace gpx {
namespace phy2d {

/**
 * Displaced rigid body.
 */
class GPX_API DispRigidBody : public RigidBody
{
	typedef RigidBody Parent;

	public:
		/**
		 * Constructor.
		 * @param m mass.
		 * @param I absolute moment of inertia (calculated for the center of mass).
		 * @param cm center of mass.
		 *
		 * @note rotation point is being set on center of mass. It can be modified by
		 * setRotationPoint function.
		 */
		DispRigidBody(real_t m, real_t I, const math::const_VectorPtr<2> & cm);

		virtual ~DispRigidBody();

	public:
		/**
		 * Calculate displaced moment of inertia. Calculates moment of inertia for given
		 * rotation point using Steiner's theorem.
		 * @param m mass.
		 * @param I absolute moment of inertia.
		 * @param displacement displacement toward the center of mass.
		 * @return displaced moment of inertia.
		 */
		static real_t Steiner(real_t m, real_t I, const math::const_VectorPtr<2> & displacement);

	public:
		/**
		 * Get displaced moment of inertia.
		 * @return displaced moment of inertia.
		 */
		real_t Idisp() const;

		//Parent
		virtual void setM(real_t m);

		//Parent
		virtual void setAngularV(real_t angularV);

		//Parent
		virtual void setI(real_t I);

		/**
		 * Get rotation point.
		 * @return rotation point coordinates.
		 */
		const math::Vector<2> & rotationPoint() const;

		/**
		 * Set rotation point.
		 * @param rpPos new rotation point coordinates.
		 */
		virtual void setRotationPoint(const math::const_VectorPtr<2> & rpPos);

		/**
		 * Get center of mass.
		 * @return center of mass.
		 */
		const math::Vector<2> & centerOfMass() const;

		/**
		 * Set center of mass.
		 * @param centerOfMass new center of mass coordinates.
		 *
		 * @note if body shall rotate freely, set also rotation point accordingly.
		 */
		virtual void setCenterOfMass(const math::const_VectorPtr<2> & centerOfMass);

		//Parent
		virtual real_t kineticE() const;

	protected:
		/**
		 * Rotation point.
		 */
		struct RotationPoint
		{
			math::Vector<2> pos;			///< Position of rotation point. Relative to object's (0.0, 0.0) point.
			math::Vector<2> displacement;	///< Displacement of rotation point from center of mass. Position of rotation point relative to center of mass.

			/**
			 * Constructor.
			 * @param I absolute moment of inertia.
			 * @param pos rotation point position.
			 * @param displacement displacement of rotation point from the center of mass.
			 * If this parameter is a zero vector, rotation point falls in with center of mass.
			 */
			RotationPoint(const math::const_VectorPtr<2> & pos, const math::const_VectorPtr<2> & displacement = math::Vector<2>());
		};									///< Rotation point.

	protected:
		//Parent
		virtual void updatePosAngle(real_t dt, math::Vector<2> & posB, real_t & angleB);

		//Parent
		virtual void updatePL(real_t dt, math::Vector<2> & pB, real_t & LB);

		//Parent
		virtual void updateResultantForceMoment(real_t dt, math::Vector<2> & resultantForce, real_t & resultantMoment);

		//Parent
		virtual void constructTMatrix(phy::TransformationMatrix & tMatrix, phy::TransformationMatrix & tInvMatrix);

		/**
		 * Find rotation point candidates providing extremal angular acceleration. Candidate
		 * point may denote either maximum or minimum. To find out which is which, recount
		 * physics for each of them and compare results.
		 * @param rpA first rotation point candidate.
		 * @param rpB second rotation point candidate.
		 */
		void findExtAngularARotationPoints(RotationPoint & rpA, RotationPoint & rpB);

		/**
		 * Find rotation point with maximal energy change for rotation. This is a point
		 * around which a free body is rotating.
		 * @param rp rotation point to be found.
		 */
		void findMaxERotationPoint(RotationPoint & rp);

		/**
		 * Find rotation point with minimal energy change for rotation. This point is
		 * a center of mass...
		 * @param rp rotation point to be found.
		 */
		void findMinERotationPoint(RotationPoint & rp);

	private:
		/**
		 * Rotation point pre-calculations. Helper function used by find*RotationPoint
		 * functions.
		 */
		void rotationPointPrecalc(real_t & Fx, real_t & Fy, real_t & RdetF) const;

		/**
		 * Update displaced moment of inertia for current rotation point.
		 */
		void updateIdisp();

	private:
		math::Vector<2> m_centerOfMass;		///< Center of mass.
		RotationPoint m_rp;					///< Rotation point.
		real_t m_Idisp;						///< Displaced moment of inertia. Moment of inertia calculated for given rotation point.
};

}
}

#endif /* GPX_Phy2d_DISPRIGIDBODY_HPP_ */

//(c)MP: Copyright © 2011, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
