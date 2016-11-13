/**
 * @file
 * @brief .
 */

#ifndef GPX_PHY2D_RIGIDBODYRENDERER_HPP_
#define GPX_PHY2D_RIGIDBODYRENDERER_HPP_

#include <gpx/platform.hpp>

#include "../gra2d/Renderer.hpp"
#include "../gra2d/PointRenderer.hpp"
#include "../gra2d/VectorRenderer.hpp"


namespace gpx {
namespace phy2d {


class RigidBody;


class GPX_API RigidBodyRenderer: public gra2d::Renderer
{
	protected:
		const RigidBody * m_rigidBody;

		bool m_renderRotationPoint;
		bool m_renderCenterOfMass;
		bool m_renderForcePoints;
		gra2d::PointRenderer m_pointRenderer;
		gra2d::VectorRenderer m_vectorRenderer;

	public:
		/**
		 * Constructor.
		 * @param rigidBody rigid body to be rendered.
		 */
		RigidBodyRenderer(const RigidBody * rigidBody);

		/**
		 * Destructor.
		 */
		virtual ~RigidBodyRenderer();

		//overriden gra::Renderer
		virtual void render(gra2d::RenderContext * context);
};

}
}

#endif /* GPX_PHY2D_RIGIDBODYRENDERER_HPP_ */
