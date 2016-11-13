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
	static real_t InitialE()
	{
		return 2.0;
	}

	static real_t InitialS()
	{
		return 1.0;
	}

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
		e(InitialE()),
		s(InitialS())
	{
	}
};

}
}

#endif /* GPX_Phy_NEWTONPLASTICITYDATA_HPP_ */
