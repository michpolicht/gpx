/**
 * @file
 * @brief .
 */

#ifndef MATERIALPOLYRENDERER_HPP_
#define MATERIALPOLYRENDERER_HPP_

#include "../physics/MaterialPoly.hpp"
#include "Renderer.hpp"

namespace pmepp2_s
{

class MaterialPolyRenderer : public Renderer
{
	const MaterialPoly & m_poly;

	public:
		MaterialPolyRenderer(const MaterialPoly & poly);

		virtual ~MaterialPolyRenderer();

		//gpx::gra2d::Renderer
		virtual void render(gpx::gra2d::RenderContext * context);
};

}

#endif /* MATERIALPOLYRENDERER_HPP_ */
