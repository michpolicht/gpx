/*
 * Scene.cpp
 *
 *      Author: doc
 */

#include "../../../include/gpx/gra2d/Scene.hpp"
#include "../../../include/gpx/gra2d/View.hpp"
#include "../../../include/gpx/gra2d/Renderer.hpp"

#include <gpx/log/Log.hpp>

namespace gpx {
namespace gra2d {

inline
bool RendererPlaneCompareFunctor::operator()(Renderer * & x, Renderer * & y) const
{
	return x->painterPlane() > y->painterPlane();
}



void Scene::removeScheduled()
{
	//painter planes start from 1
	Scene::painterPlane_t plane = 1;
	RenderersContainer::iterator i = m_renderers.begin();
	while (i != m_renderers.end()) {
		(*i)->setPainterPlane(plane);
		if ((*i) == m_removedRenderers.top()) {
			i = m_renderers.erase(i);
			m_removedRenderers.pop();
		} else {
			++i;
			plane++;
		}
	}
	m_topPainterPlane = plane;
}

Scene::Scene(const Clip & clip):
		m_topPainterPlane(1),
		m_context(this),
		m_clip(clip)
{
}

Scene::Scene(real_t width, real_t height):
		m_topPainterPlane(1),
		m_context(this),
		m_clip(width, height)
{
}

Scene::Scene(real_t clipL, real_t clipR, real_t clipB, real_t clipT):
		m_topPainterPlane(1),
		m_context(this),
		m_clip(clipL, clipR, clipB, clipT)
{
}

Scene::~Scene()
{
}

Clip & Scene::clip()
{
	return m_clip;
}

const Clip & Scene::clip() const
{
	return m_clip;
}

real_t Scene::width() const
{
	return clip().width();
}

real_t Scene::height() const
{
	return clip().height();
}

void Scene::add(Renderer * renderer)
{
#ifndef NDEBUG
	if (renderer->renderContext() != 0)
		GPX_FATAL("renderer may be attached to one scene at time");
#endif /* NDEBUG */
	if (m_topPainterPlane == std::numeric_limits<painterPlane_t>::max()) {
		GPX_WARN("maximal number (" << std::numeric_limits<painterPlane_t>::max() << ") of painter planes achieved");
		renderer->setPainterPlane(0);
		return;
	}
	m_renderers.push_back(renderer);
	renderer->setPainterPlane(m_topPainterPlane);
	renderer->setRenderContext(& m_context);
	m_topPainterPlane++;
}

void Scene::remove(Renderer * renderer)
{
	m_removedRenderers.push(renderer);
	renderer->setRenderContext(0);
}

void Scene::update(const View * view)
{
	m_context.setBlendMode(RenderContext::BLEND_NONE); //reset blend mode
	m_context.setCurrentView(view);
	if (!m_removedRenderers.empty())
		removeScheduled();
	for (RenderersContainer::iterator i = m_renderers.begin(); i != m_renderers.end(); ++i)
		(*i)->update();
}

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
