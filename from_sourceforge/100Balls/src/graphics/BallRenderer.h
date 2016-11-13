/**
 * @file /100Balls/src/graphics/BallRenderer.h
 * @brief .
 */

#ifndef Balls_BALLRENDERER_H_
#define Balls_BALLRENDERER_H_

#include <gpx/gra2d/Renderer.hpp>

class Ball;
class BallModel;

class BallRenderer: public gpx::gra2d::Renderer
{
	Ball * ball;
	BallModel * model;

	public:
		BallRenderer(Ball * ball);
		virtual ~BallRenderer();

		//gpx::gra2d::Renderer
		virtual void render(gpx::gra2d::RenderContext * context);
};

#endif /* Balls_BALLRENDERER_H_ */
