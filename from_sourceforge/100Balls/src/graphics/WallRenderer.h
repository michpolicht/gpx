/**
 * @file
 * @brief .
 */

#ifndef Balls_WALLRENDERER_H_
#define Balls_WALLRENDERER_H_

#include <gpx/gra2d/Renderer.hpp>

class WallModel;
class Wall;

class WallRenderer: public gpx::gra2d::Renderer
{
	Wall * wall;
	WallModel * model;

	public:
		WallRenderer(Wall * wall);

		virtual ~WallRenderer();

		//gpx::gra2d::Renderer
		virtual void render(gpx::gra2d::RenderContext * context);
};

#endif /* Balls_WALLRENDERER_H_ */
