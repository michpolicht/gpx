/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra2d_RENDERER_HPP_
#define GPX_Gra2d_RENDERER_HPP_

#include "RenderContext.hpp"
#include "Scene.hpp"		//included for RenderContext usage convenience
#include "View.hpp"			//included for RenderContext usage convenience

#include <gpx/platform.hpp>
#include <gpx/math/structures.hpp>

namespace gpx {
namespace gra2d {


/**
 * Renderer.
 */
class GPX_API Renderer
{
	friend class Scene;	//access to painterPlane (alternatively Scene might have additional associative structure to bind Renderers with painter planes).

	public:
		static const RenderContext::blendMode_t INITIAL_BLEND_MODE = RenderContext::BLEND_NONE;

	public:
		/**
		 * Get blend mode.
		 * @return blend mode.
		 */
		RenderContext::blendMode_t blendMode() const;

		/**
		 * Set blend mode.
		 * @param blendMode blend mode.
		 */
		void setBlendMode(RenderContext::blendMode_t blendMode);

		/**
		 * Get painter plane. Until renderer is not attached to scene, this parameter is
		 * irrelevant.
		 * @return painter plane.
		 *
		 * @note painter plane may be changed by Scene object after each update().
		 */
		Scene::painterPlane_t painterPlane() const;

		/**
		 * Get render context.
		 * @return render context or 0 when no render context has been set.
		 */
		const RenderContext * renderContext() const;

		/**
		 * Implement this method to provide custom rendering.
		 */
		virtual void render(RenderContext * context) = 0;

	protected:
		/**
		 * Constructor.
		 */
		Renderer();

		/**
		 * Destructor.
		 */
		virtual ~Renderer();

	private:
		/**
		 * Update. This function will perform common tasks and call render().
		 *
		 * @note accessed by Scene.
		 *
		 * @warning do not call this function while context has not been set (that is
		 * renderer was not added to the scene).
		 */
		void update();

		/**
		 * Set painter plane.
		 *
		 * @note accessed by Scene.
		 *
		 * @param plane painter plane.
		 */
		void setPainterPlane(Scene::painterPlane_t plane); //accessed by Scene

		/**
		 * Set render context.
		 * @param context context.
		 */
		void setRenderContext(RenderContext * context); //accessed by Scene

	private:
		Scene::painterPlane_t m_painterPlane;
		const Scene * m_scene;
		RenderContext * m_context;
		RenderContext::blendMode_t m_blendMode;
};


}
}

#endif /* GPX_Gra2d_RENDERER_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
