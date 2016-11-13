/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_CNEWTON_PMEPP2_S_ACOEFSMAPPER_HPP_
#define GPX_Phy2d_CNEWTON_PMEPP2_S_ACOEFSMAPPER_HPP_

#include "Cluster.hpp"

#include <gpx/math/Matrix.hpp>

namespace gpx {
namespace phy2d {
namespace cnewton {
namespace pmepp2_s {

/**
 * A coefficients mapper. For the system of linear equations A Fdt = B, each element of
 * matrix A has to be placed in respect to appropriate collision impulse Fdt_i and
 * velocity b_v. Impulse Fdt_i and velocity b_v correspond with collision points
 * they are calculated for (and attached to, in case of impulses). Collision points are
 * given collision indices, which can be used to identify impulses Fdt_i and velocities
 * b_v, therefore defining placement of matrix element a_vi. Mapper class provides a standard
 * way for the user classes to put their additions into matrix A.
 */
class GPX_API ACoefsMapper
{
	public:
		ACoefsMapper(math::Matrix<> & a);

	public:
		/**
		 * Add value to an existing matrix element.
		 * @param v iterator pointing to collision index of point for which velocity
		 * b_v has been found.
		 * @param i iterator pointing to collision index of point for which collision
		 * impulse Fdt_i is being calculated.
		 * @param val value to be added.
		 */
		void add(std::size_t v, std::size_t i, real_t val);

		/**
		 * Get value.
		 * @param v iterator pointing to collision index of point for which velocity
		 * b_v has been found.
		 * @param i iterator pointing to collision index of point for which collision
		 * impulse Fdt_i is being calculated.
		 * @return matrix value at specified position.
		 */
		real_t get(std::size_t v, std::size_t i) const;

	private:
		math::Matrix<> & m_a;
};

}
}
}
}

#endif /* GPX_Phy2d_CNEWTON_PMEPP2_S_ACOEFSMAPPER_HPP_ */

//(c)MP: Copyright © 2013, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
