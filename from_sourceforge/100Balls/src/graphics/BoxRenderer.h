#ifndef FastBall_BOXRENDERER_H_
#define FastBall_BOXRENDERER_H_

#include <gpx/gra2d/Renderer.hpp>

class BoxModel;
class Box;

class BoxRenderer : public gpx::gra2d::Renderer
{
	Box * box;
	BoxModel * model;

	public:
		BoxRenderer(Box * box);

		virtual void render(gpx::gra2d::RenderContext * context);
};


#endif /* FastBall_BOXRENDERER_H_ */
