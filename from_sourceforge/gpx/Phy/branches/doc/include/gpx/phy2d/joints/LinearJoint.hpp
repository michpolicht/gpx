/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_JOINTS_LINEARJOINT_HPP_
#define GPX_Phy2d_JOINTS_LINEARJOINT_HPP_

#include "../op.hpp"
#include "AbstractJoint.hpp"

#include <gpx/math/structures.hpp>

namespace gpx {
namespace phy2d {
namespace joints {

//todo k1, k2, k only for IsotropicLinearJoint (this might be eventually determined by constructor)
//also possible: leave IsotropicLinearJoint simply LinearJoint and provide AnisotropicLinearJoint for anisotropic version

/**
 * Isotropic linear joint.
 * @todo this should be isotropic, currently is anisotropic but without k1, k2.
 */
template <typename OP_T = op::Transparent>
class LinearJoint: public AbstractJoint
{
	public:
		/**
		 * Constructor.
		 * @param v1 first vertex.
		 * @param v2 second vertex.
		 * @param k linear coefficient.
		 */
		LinearJoint(const math::const_VectorPtr<2> & v1, const math::const_VectorPtr<2> & v2, real_t k);

		/**
		 * Linear multiplication of given argument.
		 * @param dst argument to be multiplied.
		 * @return @a k * @a dst.
		 */
//		math::Vector<2> & operator()(math::Vector<2> & dst);

		/**
		 * Linear multiplication of given argument.
		 * @param dst argument to be multiplied.
		 * @return @a k * @a dst.
		 */
		real_t operator()(real_t dst);

		/**
		 * Field value. Calculates field value considering current positions of vertices
		 * @a v1 and @a v2 passed to the constructor.
		 * @return field value for vertices @a v1 and @a v2.
		 */
		math::Vector<2> value();

	private:
		OP_T m_op;
		real_t m_k;
};


template <typename OP_T>
inline
LinearJoint<OP_T>::LinearJoint<OP_T>(const math::const_VectorPtr<2> & v1, const math::const_VectorPtr<2> & v2, real_t k):
		AbstractJoint(v1, v2),
		m_k(k)
{
}


//template <typename OP_T>
//inline
//math::Vector<2> & LinearJoint<OP_T>::operator()(math::Vector<2> & dst)
//{
//	dst *= k;
//	return dst;
//}

template <typename OP_T>
inline
real_t LinearJoint<OP_T>::operator()(real_t dst)
{
	return dst * m_k;
}

template <typename OP_T>
math::Vector<2> LinearJoint<OP_T>::value()
{
	math::Vector<2> curDst(m_v2 - m_v1);
	real_t kx = m_op(curDst.length() - m_dst.length(), *this);
	if (!curDst.isZero()) {
		curDst.normalize();
		curDst *= kx;
		return curDst;
	} else
		return math::Vector<2>();
}




}
}
}

#endif /* GPX_Phy2d_JOINTS_LINEARJOINT_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
