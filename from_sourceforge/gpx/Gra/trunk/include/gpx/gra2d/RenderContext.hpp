/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra2d_RENDERCONTEXT_HPP_
#define GPX_Gra2d_RENDERCONTEXT_HPP_

#include <vector>
#include <stack>

#include <gpx/platform.hpp>

#include "../gl_wrap.hpp"	//for convenience


namespace gpx {
namespace gra2d {

class Scene;
class View;


/**
 * Rendering context.
 */
class GPX_API RenderContext
{
	public:
		typedef float time_t;

		enum blendMode_t {
				BLEND_NONE,
				BLEND_ALPHA,
				BLEND_ADD,
				BLEND_MULTIPLY
		};

	public:
		static const blendMode_t INITIAL_BLEND_MODE = BLEND_NONE;

	public:
		RenderContext(const Scene * const scene);

		virtual ~RenderContext();

		const Scene * scene() const;

		void setCurrentView(const View * view);

		const View * currentView() const;

		blendMode_t blendMode() const;

		/**
		 * Set blend mode.
		 * @param blend mode.
		 */
		void setBlendMode(blendMode_t blendMode);

		time_t frameTime() const;

		void pushMatrix();

		void popMatrix();

	protected:
		/**
		 * Matrix storage. Wraps array representing certain matrix so that its values can be
		 * copied (ISO C++ forbids direct copying of plain arrays).
		 */
		struct MatrixStorage
		{
			real_t elements[16];
		};

		typedef std::stack<MatrixStorage, std::vector<MatrixStorage> > ModelviewStackContainer;

	protected:
		static int M_GlModelviewStackDepth;

	private:
		const Scene * const m_scene;
		const View * m_view;
		int m_matrixStackCtr;
		ModelviewStackContainer m_modelviewStack;
		blendMode_t m_blendMode;

	private:
		static const int SPEC_GL_MODELVIEW_STACK_DEPTH = 32;	//maximal number of matrices that can be put on the modelview stack according to opengl specs
};


}
}

#endif /* GPX_Gra2d_RENDERCONTEXT_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
