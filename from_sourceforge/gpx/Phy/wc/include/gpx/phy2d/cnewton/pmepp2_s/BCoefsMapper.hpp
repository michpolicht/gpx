/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_CNEWTON_PMEPP2_S_BCOEFSMAPPER_HPP_
#define GPX_Phy2d_CNEWTON_PMEPP2_S_BCOEFSMAPPER_HPP_

#include "Cluster.hpp"

#include <gpx/math/Vector.hpp>

namespace gpx {
namespace phy2d {
namespace cnewton {
namespace pmepp2_s {

/**
 * B coefficients mapper. For the system of linear equations A Fdt = B, each element of
 * vector B has to be placed in respect to appropriate velocity b_v. Velocity b_v
 * corresponds with specific collision point it is being calculated for. Collision
 * points are given collision indices, which can be used to identify vector coordinates b_v.
 * Mapper class provides a standard way for the user classes to put their additions into
 * vector B.
 */
class GPX_API BCoefsMapper
{
	public:
		BCoefsMapper(math::Vector<> & b);

	public:
		/**
		 * Add value to an existing vector coordinate.
		 * @param v point index (in subscript type of access - not collision index value!).
		 * @param val value to be added.
		 */
		void add(std::size_t v, real_t val);

		/**
		 * Get value.
		 * @param v point index (in subscript type of access - not collision index value!).
		 * @return value of specified coordinate.
		 */
		real_t get(std::size_t v) const;

	private:
		math::Vector<> & m_b;
};

}
}
}
}

#endif /* GPX_Phy2d_CNEWTON_PMEPP2_S_BCOEFSMAPPER_HPP_ */

//(c)MP: Copyright © 2013, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
