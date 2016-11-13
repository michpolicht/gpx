/*
 * Scene.h
 *
 *      Author: doc
 */

#ifndef GPX_Gra2d_SCENE_HPP_
#define GPX_Gra2d_SCENE_HPP_

#include <list>
#include <queue>

#include <gpx/platform.hpp>
#include <gpx/utils/functions.hpp>

#include "RenderContext.hpp"
#include "Clip.hpp"


namespace gpx {
namespace gra2d {

class View;
class Renderer;


/**
 * Renderer plane comparing functor. Compares renderers in terms of greater painter plane
 * number.
 */
class RendererPlaneCompareFunctor
{
	public:
		bool operator()(Renderer * & x, Renderer * & y) const;
};


/**
 * Scene.
 */
class GPX_API Scene
{
	public:
		typedef std::list<Renderer * > RenderersContainer;
		typedef unsigned int painterPlane_t;
		typedef std::priority_queue<Renderer *, std::vector<Renderer *>, RendererPlaneCompareFunctor> RemovedRenderersContainer;

	protected:
		RenderersContainer m_renderers;
		RemovedRenderersContainer m_removedRenderers;
		painterPlane_t m_topPainterPlane;
		RenderContext m_context;
		Clip m_clip;

	protected:
		/**
		 * Remove scheduled renderers. Painter planes are renumbered during removal.
		 */
		void removeScheduled();

	public:
		Scene(const Clip & clip);

		Scene(real_t width, real_t height);

		Scene(real_t clipL, real_t clipR, real_t clipB, real_t clipT);

		/**
		 * Destructor.
		 */
		virtual ~Scene();

		Clip & clip();

		const Clip & clip() const;

		real_t width() const;

		real_t height() const;

		/**
		 * Add renderer to scene. Renderer is added to the top plane of the scene.
		 * Renderer also receives painter plane number. If maximal number of painter planes
		 * is reached renderer will not be added to the scene. Its painter plane will be
		 * set to 0.
		 * @param renderer renderer to be added.
		 */
		void add(Renderer * renderer);

		/**
		 * Remove renderer from scene.
		 * @param renderer renderer to remove.
		 *
		 * @note renderer may not be removed immediately but rather scheduled for removal.
		 * Scheduled pointer becomes invalid and won't be used however.
		 */
		void remove(Renderer * renderer);

		/**
		 * Upadate scene.
		 * @param view.
		 */
		void update(const View * view);
};


}
}

#endif /* GPX_Gra2d_SCENE_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
