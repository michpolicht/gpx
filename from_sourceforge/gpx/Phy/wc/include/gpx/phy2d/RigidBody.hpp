/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_RIGIDBODY_HPP_
#define GPX_Phy2d_RIGIDBODY_HPP_

#include "MaterialBody.hpp"

#include <gpx/platform.hpp>
#include <gpx/utils/DoubleBuffer.hpp>
#include <gpx/math/structures.hpp>

namespace gpx {
namespace phy2d {


/**
 * Rigid body. In comparison to MaterialObject, RigidBody brings additional parameters
 * into simulation:
 * 	- Current angle (double buffered) and derivatives (angular velocity, angular acceleration).
 * 	- Moment of inertia.
 *  - Angular momentum (double buffered).
 *  - Moments of impulses and forces.
 *  .
 * Angle and angular momentum are double-buffered parameters.
 */
class GPX_API RigidBody : public MaterialBody
{
	typedef MaterialBody Parent;

	public:
		/**
		 * Constructor.
		 * @param m mass.
		 * @param I absolute moment of inertia (calculated for the center of mass).
		 *
		 * @note center of mass is assumed to lie in (0.0, 0.0) of c-model coordinates.
		 */
		RigidBody(real_t m, real_t I);

		/**
		 * Destructor.
		 */
		virtual ~RigidBody();

	public:
		/**
		 * Get rotation angle.
		 * @return rotation angle (radians).
		 */
		real_t angle() const;

		/**
		 * Set rotation angle.
		 * @param angle rotation angle (radians).
		 */
		void setAngle(real_t angle);

		/**
		 * Set angular velocity.
		 * @param angularV new angular velocity.
		 */
		void setAngularV(real_t angularV);

		/**
		 * Get (absolute) moment of inertia.
		 * @return moment of inertia.
		 */
		real_t I() const;

		/**
		 * Set moment of inertia. Moment of inertia relative to rotation point will be
		 * calculated through Steiner's theorem.
		 * @param I new absolute moment of inertia.
		 */
		void setI(real_t I);

		/**
		 * Get angular momentum.
		 * @return angular momentum.
		 */
		real_t L() const;

		/**
		 * Set angular momentum.
		 * @param L angular momentum.
		 */
		void setL(real_t L);

		//Parent
		virtual real_t kineticE() const;

		//Parent
		virtual void applyImpulse(const Impulse & impulse, math::const_PointRef<2> point);

		//Parent
		virtual void update(real_t dt);

		//IRecordable
		virtual std::size_t snapshotSize() const;

		//IRecordable
		virtual void store(char * snapshot) const;

		//IRecordable
		virtual void restore(char * snapshot);

	protected:
		/**
		 * Get active angular momentum.
		 * @return angular momentum from active buffer.
		 *
		 * @note this might seem to be equivalent of public method L(), but L() method
		 * doesn't give a warranty that returned value is actual value of active buffer.
		 */
		real_t LA() const;

		/**
		 * Get background angular momentum.
		 * @return angular momentum from background buffer.
		 */
		real_t LB() const;

		/**
		 * Set background angular momentum.
		 * @param L angular momentum to be set.
		 */
		void setLB(real_t L);

		/**
		 * Get active angle.
		 * @return active angle.
		 */
		real_t angleA() const;

		/**
		 * Get background angle.
		 * @return background angle.
		 */
		real_t angleB() const;

		/**
		 * Set background angle.
		 * @param angle angle to be set.
		 */
		void setAngleB(real_t angle);

		/**
		 * Get sine of active angle.
		 * @return cached value of active angle sine.
		 */
		real_t angleSinA() const;

		/**
		 * Get sine of background angle.
		 * @return cached value of background angle sine.
		 */
		real_t angleSinB() const;

		/**
		 * Get cosine of active angle.
		 * @return cached value of active angle cosine.
		 */
		real_t angleCosA() const;

		/**
		 * Get cosine of background angle.
		 * @return cached value of background angle cosine.
		 */
		real_t angleCosB() const;

		/**
		 * Rotate to global coordinates. Rotates vector by current angle using cached sine
		 * and cosine values of current angle.
		 * @param v vector to be rotated.
		 */
		void rotateToGlobal(math::VectorRef<2> v) const;

		/**
		 * Rotate to local coordinates. Rotate vector by minus current angle, using cached
		 * sine and cosine values of current angle.
		 * @param v vector to be rotated.
		 */
		void rotateToLocal(math::VectorRef<2> v) const;

		/**
		 * Calculate resultant moment.
		 * @return resultant moment.
		 */
		real_t resultantMoment() const;

		//Parent
		virtual void constructTMatrix(phy::TransformationMatrix & tMatrix);

		//Parent
		virtual void constructTMatrixInv(phy::TransformationMatrix & tInvMatrix);

	private:
		utils::DoubleBuffer<real_t> m_angleSin;	///< Cached value of current angle's sine.
		utils::DoubleBuffer<real_t> m_angleCos;	///< Cached value of current angle's cosine.
		utils::DoubleBuffer<real_t> m_angle;	///< Rotation angle in radians going counterclockwise (double buffered).
		real_t m_I; 							///< Absolute moment of inertia (calculated for the center of mass).
		utils::DoubleBuffer<real_t> m_L;		///< Angular momentum (double buffered).
};

}
}

#endif /* GPX_Phy2d_RIGIDBODY_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
