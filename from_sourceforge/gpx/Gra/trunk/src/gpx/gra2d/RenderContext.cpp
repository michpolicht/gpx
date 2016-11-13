/**
 * @file
 * @brief .
 */

#include <gpx/log.hpp>

#include "../../../include/gpx/gra2d/RenderContext.hpp"
#include "../../../include/gpx/gra2d/View.hpp"

namespace gpx {
namespace gra2d {

int RenderContext::M_GlModelviewStackDepth;

RenderContext::RenderContext(const Scene * const scene):
		m_scene(scene),
		m_view(0),
		m_matrixStackCtr(0),
		m_blendMode(INITIAL_BLEND_MODE)
{
	glGetv(GL_MAX_MODELVIEW_STACK_DEPTH, & M_GlModelviewStackDepth);
}

RenderContext::~RenderContext()
{
}

const Scene * RenderContext::scene() const
{
	return m_scene;
}

void RenderContext::setCurrentView(const View * view)
{
	this->m_view = view;
}

const View * RenderContext::currentView() const
{
	return m_view;
}

RenderContext::blendMode_t RenderContext::blendMode() const
{
	return m_blendMode;
}

void RenderContext::setBlendMode(blendMode_t blendMode)
{
	if (m_blendMode != blendMode) {
		if (blendMode != BLEND_NONE) {
			if (m_blendMode == BLEND_NONE)
				glEnable(GL_BLEND);
			switch (blendMode) {
				case BLEND_ALPHA:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					break;
				case BLEND_ADD:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE);
					break;
				case BLEND_MULTIPLY:
					glBlendFunc(GL_DST_COLOR, GL_ZERO);
					break;
				default:
					GPX_WARN("unrecognized blend mode code: " << blendMode);
					break;
			}
		} else
			glDisable(GL_BLEND);
	}
	m_blendMode = blendMode;
}

RenderContext::time_t RenderContext::frameTime() const
{
	return static_cast<RenderContext::time_t>(currentView()->renderWindow().GetFrameTime());
}

void RenderContext::pushMatrix()
{
	m_matrixStackCtr++;
#ifndef NDEBUG
	if (m_matrixStackCtr >= SPEC_GL_MODELVIEW_STACK_DEPTH)
		GPX_DEBUG("OpenGL-specified modelview matrix stack depth (" << SPEC_GL_MODELVIEW_STACK_DEPTH << ") exceeded");
#endif /* NDEBUG */
	if (m_matrixStackCtr < M_GlModelviewStackDepth)
		glPushMatrix();  //use hardware stack
	else {
		//use software stack
		GPX_WARN("maximal depth (" << M_GlModelviewStackDepth << ") of hardware stack of modelview matrix exceeded");
		GPX_INFO("using software stack for modelview matrix");
		MatrixStorage matrix;
		glGetv(GL_MODELVIEW_MATRIX, matrix.elements);
		m_modelviewStack.push(matrix);
	}
}

void RenderContext::popMatrix()
{
	if (m_matrixStackCtr < M_GlModelviewStackDepth)
		glPopMatrix();	//use hardware stack
	else {
		//use software stack
		glLoadMatrix(m_modelviewStack.top().elements);
		m_modelviewStack.pop();
	}
	m_matrixStackCtr--;
}


}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
