/**
 * @file
 * @brief .
 */

#ifndef WALLRENDERER_HPP_
#define WALLRENDERER_HPP_

#include "../model/WallModel.hpp"
#include "../physics/Wall.hpp"
#include "Renderer.hpp"

namespace pmepp2_s
{

class WallRenderer : public Renderer
{
	Wall & m_wall;
	WallModel & m_model;

	public:
		WallRenderer(Wall & wall);

		virtual ~WallRenderer();

		//gpx::gra2d::Renderer
		virtual void render(gpx::gra2d::RenderContext * context);
};

}

#endif /* WALLRENDERER_HPP_ */
