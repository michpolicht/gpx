/*
 * Renderer.cpp
 *
 *      Author: doc
 */

#include "../../../include/gpx/gra2d/Renderer.hpp"
#include "../../../include/gpx/gra2d/Scene.hpp"


namespace gpx {
namespace gra2d {

Renderer::Renderer():
		m_painterPlane(0),
		m_scene(0),
		m_context(0),
		m_blendMode(INITIAL_BLEND_MODE)
{
}

Renderer::~Renderer()
{
}

RenderContext::blendMode_t Renderer::blendMode() const
{
	return m_blendMode;
}

void Renderer::setBlendMode(RenderContext::blendMode_t blendMode)
{
	m_blendMode = blendMode;
}

Scene::painterPlane_t Renderer::painterPlane() const
{
	return m_painterPlane;
}

const RenderContext * Renderer::renderContext() const
{
	return m_context;
}

void Renderer::update()
{
	m_context->pushMatrix();
	m_context->setBlendMode(blendMode());
	render(m_context);
	m_context->popMatrix();
}




void Renderer::setPainterPlane(Scene::painterPlane_t plane)
{
	this->m_painterPlane = plane;
}

void Renderer::setRenderContext(RenderContext * context)
{
	this->m_context = context;
}



}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
