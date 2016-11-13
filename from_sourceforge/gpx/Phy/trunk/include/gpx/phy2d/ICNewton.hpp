/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_ICNEWTON_HPP_
#define GPX_Phy2d_ICNEWTON_HPP_

#include "../phy/material.hpp"
#include "../phy/NewtonPlasticityData.hpp"
#include "ILocalFrame.hpp"
#include "ICPolyGroup.hpp"

namespace gpx {
namespace phy2d {

class ICNewton;
class ICNewtonMovable;

/**
 * Newton detection data. On the detection level, structure contains candidates, which
 * may collide with each other. When collision is detected, objects are considered as
 * collision participants.
 */
struct NewtonDetecionData
{
	real_t dt;					///< Collision time.
	ICNewtonMovable * moving;	///< Colliding, moving object. Object violating passive's collision area.
	ICNewton * passive;			///< Object taking passive role in a collision. Fixed objects are always passive, while movables may be considered as moving or passive at different simulation stages.
	ICNewtonMovable * passiveMov;	///< Movable passive object. Points to passive object, when passive object is a movable. Otherwise it's set to @p 0.
};

/**
 * Newton collision base data. Basic data about collision.
 */
struct NewtonCollisionBase
{
	const NewtonDetecionData & dData;	///< Detection data. Contains pointers to colliding objects.
	CollisionPoints points;		///< Collision points.
	math::Vector<2> normal;		///< Normal to the "bumper's" surface (calculated by "bumper", given in global coordinates).
	bool wedge;					///< Indicates if object collides as a wedge or a bumper.
	ICPolyGroup::element_t element;	///< Colliding element index.
//	real_t dt;					///< Collision time.
//	ICNewton * me;		///< Object participating in collision itself.
//	ICNewton * other;	///< Other object, which object is colliding with.
//	bool moving;				///< Indicates whenever object moved into collision area or plays passive role in current collision. Fixed objects are always passive, while movables may be considered as moving or passive at different simulation stages.

	NewtonCollisionBase(const NewtonDetecionData & p_dData):
		dData(p_dData)
	{
	}
};

/**
 * Newton collision data. Complete data about collision.
 */
struct NewtonCollisionData
{
	const NewtonCollisionBase & bData;	///< Basic collision data.
	const phy::NewtonPlasticityData & pData;	///< Plasticity data.
	math::Vector<2> a;		///< a coefficients in collision equations aFdt = b (global coordinates).
	math::Vector<2> bn;		///< b coefficients in collision equations aFdt = b (normal impulse, global coordinates).
	math::Vector<2> bp;		///< b coefficients in collision equations aFdt = b (parallel impulse, global coordinates).
	phy::material_t mat;	///< Material id.

	NewtonCollisionData(const NewtonCollisionBase & p_bData, const phy::NewtonPlasticityData & p_pData):
		bData(p_bData),
		pData(p_pData)
	{
	}
};

/**
 * Newton-colliding.
 */
class ICNewton : public virtual ICPolyGroup,
				 public virtual ILocalFrame
{
	public:
		/**
		 * Get "a" coefficients. These are coefficients in form aFdt=b, where Fdt is an impulse.
		 * They have to be given in global coordinates. Separate paper shall explain how to
		 * calculate them.
		 */
		virtual math::Vector<2> aCoef(const NewtonCollisionBase & bData) const = 0;

		/**
		 * Get "b" coefficients for given elasticity. These are coefficients in form aFdt=b,
		 * where Fdt is an impulse. They have to be given in global coordinates. Separate
		 * paper shall explain how to calculate them.
		 * @param p plasticity.
		 */
		virtual math::Vector<2> bCoef(real_t p, const NewtonCollisionBase & bData) const = 0;

		/**
		 * Get stickiness ratio. This factor is used to calculate friction impulse.
		 * This impulse is compared with normal impulse, using friction coefficients,
		 * to calculate resulting friction.
		 *
		 * Stickiness ratio is related to "b" coefficients (bCoef()). Usually component
		 * of collision parallel to "bumper's" surface is expected to be at most perfectly
		 * in-elastic (objects moving in parallel direction with the same speed).
		 * In this case "b" and sticky ratio product shall be equal to velocity, thus
		 * s = v / b(v), where s is a sticky ratio and v is a velocity. For example,
		 * if "b" = 2.0*v (v - velocity), sticky ratio should be 0.5.
		 */
//		virtual real_t stickyRatio(const NewtonCollisionBase & bData) const = 0;

		/**
		 * Get material id.
		 * @param element element index.
		 */
		virtual phy::material_t material(element_t element) const = 0;
};

}
}

#endif /* GPX_Phy2d_ICNEWTON_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
