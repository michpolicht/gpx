/**
 * @file
 * @brief .
 */

#ifndef GPX_100Balls_SOFTPOLYGONRENDERER_H_
#define GPX_100Balls_SOFTPOLYGONRENDERER_H_

#include <gpx/gra2d/Renderer.hpp>

class SoftPolygon;

class SoftPolygonRenderer : public gpx::gra2d::Renderer
{
	protected:
		SoftPolygon * m_spoly;

	public:
		SoftPolygonRenderer();

		virtual ~SoftPolygonRenderer();

		SoftPolygonRenderer(SoftPolygon * spoly);

		virtual void render(gpx::gra2d::RenderContext * context);
};

#endif /* GPX_100Balls_SOFTPOLYGONRENDERER_H_ */
