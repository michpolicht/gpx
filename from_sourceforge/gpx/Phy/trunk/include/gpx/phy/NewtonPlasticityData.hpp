/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy_NEWTONPLASTICITYDATA_HPP_
#define GPX_Phy_NEWTONPLASTICITYDATA_HPP_

#include <gpx/platform.hpp>

namespace gpx {
namespace phy {

/**
 * Plasticity data.
 */
struct NewtonPlasticityData
{
	static const real_t INITIAL_E = 2.0;
	static const real_t INITIAL_S = 1.0;

	/**
	 * Elasticity. Common values lie inside [1.0, 2.0] interval. Edge cases:
	 *		- 1.0 - perfectly in-elastic.
	 *		- 2.0 - perfectly elastic (preserved kinetic energy).
	 */
	real_t e;

	/**
	 * Stickiness. Common values lie inside [0.0, 2.0] interval. Edge cases:
	 * 		- 0.0 - perfectly frictionless,
	 * 		- 1.0 - perfectly sticky,
	 * 		- 2.0 - perfectly resilient.
	 *
	 * @note this parameter is not self-sufficient and it may be affected by friction
	 * coefficients.
	 */
	real_t s;

	NewtonPlasticityData():
		e(INITIAL_E),
		s(INITIAL_S)
	{
	}
};

}
}

#endif /* GPX_Phy_NEWTONPLASTICITYDATA_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
