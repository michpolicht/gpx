/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy_ABSTRACTJOINT_HPP_
#define GPX_Phy_ABSTRACTJOINT_HPP_

#include <gpx/math/structures.hpp>

namespace gpx {
namespace phy2d {
namespace joints {


/**
 * Abstract joint.
 */
class AbstractJoint
{
	public:
		/**
		 * Constructor.
		 * @param v1 first vertex.
		 * @param v2 second vertex.
		 */
		AbstractJoint(const math::const_VectorPtr<2> & v1, const math::const_VectorPtr<2> & v2);

		/**
		 * Modify initial distance between vertices @a v1 and @a v2 passed to the constructor.
		 * @param dst new initial distance to be set.
		 */
		void setDistance(const math::const_VectorPtr<2> & dst);

		/**
		 * Get initial distance.
		 * @return initial (or modified by setDistance()) distance between vertices @a v1
		 * and @a v2 passed to the constructor.
		 */
		const math::Vector<2> & distance() const;

		/**
		 * Get first vertex pointer.
		 * @return first vertex pointer.
		 */
		const math::const_VectorPtr<2> & v1() const;

		/**
		 * Get second vertex pointer.
		 * @return second vertex pointer.
		 */
		const math::const_VectorPtr<2> & v2() const;

		/**
		 * Vector field value. Function should return vector field value considering
		 * vertices passed to the constructor and possibly their initial distance.
		 * @return field value.
		 */
		virtual math::Vector<2> value() = 0;

	private:
		const math::const_VectorPtr<2> m_v1;
		const math::const_VectorPtr<2> m_v2;
		math::Vector<2> m_dst;	//initial distance between vertices v1 and v2
};


inline
AbstractJoint::AbstractJoint(const math::const_VectorPtr<2> & v1, const math::const_VectorPtr<2> & v2):
		m_v1(v1),
		m_v2(v2),
		m_dst(this->m_v2 - this->m_v1)
{
}

inline
void AbstractJoint::setDistance(const math::const_VectorPtr<2> & dst)
{
	this->m_dst = dst;
}

inline
const math::Vector<2> & AbstractJoint::distance() const
{
	return m_dst;
}

inline
const math::const_VectorPtr<2> & AbstractJoint::v1() const
{
	return m_v1;
}

inline
const math::const_VectorPtr<2> & AbstractJoint::v2() const
{
	return m_v2;
}



}
}
}


#endif /* GPX_Phy_ABSTRACTJOINT_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
