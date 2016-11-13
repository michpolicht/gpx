/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra2d_VIEW_HPP_
#define GPX_Gra2d_VIEW_HPP_


#include <gpx/platform.hpp>
#include <gpx/math/structures.hpp>
#include <gpx/utils/IObserver.hpp>

#include "Scene.hpp"
#include "../gra/RenderWindow.hpp"


namespace gpx {
namespace gra2d {

class GPX_API View : public utils::IObserver<Clip>,
					 public utils::IObserver<gra::Viewport>
{
	public:
		/**
		 * Constructor.
		 * @param renderWindow render window.
		 * @param scene scene with which view is related with.
		 * @param viewport viewport.
		 *
		 * @note scene's clip region is used. That is entire scene will be shown up in the
		 * view.
		 */
		View(gra::RenderWindow & renderWindow, Scene & scene);

		/**
		 * Constructor.
		 * @param renderWindow render window.
		 * @param scene scene with which view is related with.
		 * @param viewport viewport.
		 *
		 * @note scene's clip region is used. That is entire scene will be shown up in the
		 * view.
		 */
		View(gra::RenderWindow & renderWindow, Scene & scene, Clip & clip);

		/**
		 * Constructor.
		 * @param renderWindow render window.
		 * @param scene scene with which view is related with.
		 * @param viewport viewport.
		 *
		 * @note scene's clip region is used. That is entire scene will be shown up in the
		 * view.
		 */
		View(gra::RenderWindow & renderWindow, Scene & scene, gra::Viewport & viewport);

		/**
		 * Constructor.
		 * @param renderWindow render window.
		 * @param scene scene with which view is related with.
		 * @param clip defines view's clip region.
		 * @param viewport viewport.
		 */
		View(gra::RenderWindow & renderWindow, Scene & scene, Clip & clip, gra::Viewport & viewport);

		/**
		 * Destructor.
		 */
		virtual ~View();

	public:
		Scene & scene();

		gra::Viewport & viewport();

		const gra::Viewport & viewport() const;

		gra::RenderWindow & renderWindow();

		const gra::RenderWindow & renderWindow() const;

		/**
		 * Obtain scene/viewport ratio.
		 */
		math::Vector<2> svRatio() const;

		real_t svWidthRatio() const;

		real_t svHeightRatio() const;

		math::Point<2> mapToScene(real_t x, real_t y) const;

		math::Point<2> mapToScene(math::const_PointRef<2> point) const;

		math::Point<2> mapToScene(int x, int y) const;

		math::Point<2> mapToScene(math::const_PointRef<2, int> point) const;

		math::Point<2> mapToViewport(real_t x, real_t y) const;

		math::Point<2> mapToViewport(math::const_PointRef<2> point) const;

//		void resize(GLint viewportW, GLint viewportH);
//
//		void resize(GLint viewportX, GLint viewportY, GLint viewportW, GLint viewportH);

		virtual void event(const utils::Observable<Clip>::Event & e);

		virtual void event(const utils::Observable<gra::Viewport>::Event & e);

		void update();

	protected:
		/**
		 * Setup. Performs tasks in response to certain update of view parameters.
		 */
		void setup();

	private:
		/**
		 * Initialize. This method is a part of constructor.
		 */
		void init();

	private:
		Scene & m_scene;
		gra::RenderWindow & m_renderWindow;
		gra::Viewport & m_viewport;
		Clip & m_clip;
		bool m_doSetup;
		GLdouble m_projectionMatrix[16];	//not real_t, since glu[Un]Project operates on double
//		real_t zoom;
};

}
}

#endif /* GPX_Gra2d_VIEW_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
