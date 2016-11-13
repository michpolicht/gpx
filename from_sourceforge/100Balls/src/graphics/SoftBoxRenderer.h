/**
 * @file
 * @brief .
 */

#ifndef GPX_100Balls_SOFTBOXRENDERER_H_
#define GPX_100Balls_SOFTBOXRENDERER_H_


#include <gpx/gra2d/Renderer.hpp>

class BoxModel;
class SoftBox;


class SoftBoxRenderer : public gpx::gra2d::Renderer
{
	SoftBox * box;
	BoxModel * model;

	public:
		SoftBoxRenderer(SoftBox * box);

		virtual ~SoftBoxRenderer();

		virtual void render(gpx::gra2d::RenderContext * context);
};

#endif /* GPX_100Balls_SOFTBOXRENDERER_H_ */
