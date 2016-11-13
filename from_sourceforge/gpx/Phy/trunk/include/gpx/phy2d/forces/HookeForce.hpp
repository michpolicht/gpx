/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy_FORCES_HOOKEFORCE_HPP_
#define GPX_Phy_FORCES_HOOKEFORCE_HPP_

#include "../../phy/IPerformer.hpp"
#include "../joints/LinearJoint.hpp"
#include "../Force.hpp"

#include <gpx/math/structures.hpp>

namespace gpx {
namespace phy2d {
namespace forces {

template <typename OP_T = op::Transparent>
class HookeForce: public Force, phy::IPerformer
{
	public:
		HookeForce(const real_t v1[2], const real_t v2[2], real_t k);

		void update();

	private:
		joints::LinearJoint<OP_T> m_linearJoint;
};


template <typename OP_T>
inline
HookeForce<OP_T>::HookeForce<OP_T>(const real_t v1[2], const real_t v2[2], real_t k):
	Force(),
	m_linearJoint(v1, v2, -k)
{}


template <typename OP_T>
inline
void HookeForce<OP_T>::update()
{
	Force::operator=(m_linearJoint.value());
}




}
}
}


#endif /* GPX_Phy_FORCES_HOOKEFORCE_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
