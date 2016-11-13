/**
 * @file
 * @brief .
 */

#ifndef GPX_100Balls_CPOLYGONRENDERER_H_
#define GPX_100Balls_CPOLYGONRENDERER_H_

#include <gpx/gra2d/Renderer.hpp>

class CPolygon;

class CPolygonRenderer : public gpx::gra2d::Renderer
{
	protected:
		CPolygon * cpoly;

	public:
		CPolygonRenderer();

		virtual ~CPolygonRenderer();

		CPolygonRenderer(CPolygon * cpoly);

		virtual void render(gpx::gra2d::RenderContext * context);
};

#endif /* GPX_100Balls_CPOLYGONRENDERER_H_ */
