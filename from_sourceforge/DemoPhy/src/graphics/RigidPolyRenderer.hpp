/**
 * @file
 * @brief .
 */

#ifndef RIGIDPOLYRENDERER_HPP_
#define RIGIDPOLYRENDERER_HPP_

#include "../physics/RigidPoly.hpp"
#include "Renderer.hpp"

namespace pmepp2_s {

class RigidPolyRenderer : public Renderer
{
	const RigidPoly & m_poly;

	public:
		RigidPolyRenderer(const RigidPoly & poly);

		virtual ~RigidPolyRenderer();

		//gpx::gra2d::Renderer
		virtual void render(gpx::gra2d::RenderContext * context);
};

}

#endif /* RIGIDPOLYRENDERER_HPP_ */
