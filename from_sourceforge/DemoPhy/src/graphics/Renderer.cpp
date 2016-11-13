#include "Renderer.hpp"

namespace pmepp2_s {

const Renderer::Color Renderer::OFF_COLOR = {0.0, 0.0, 0.0};
const Renderer::Color Renderer::LIGHT_COLOR = {0.0, 1.0, 0.0};
const Renderer::Color Renderer::HIGHLIGHT_COLOR = {1.0, 0.0, 0.0};

Renderer::Renderer():
	m_color(OFF_COLOR),
	m_lit(false)
{
}

void Renderer::light()
{
	m_color = LIGHT_COLOR;
	m_lit = true;
}

void Renderer::highlight()
{
	m_color = HIGHLIGHT_COLOR;
}

void Renderer::playdown()
{
	if (m_lit)
		m_color = LIGHT_COLOR;
	else
		m_color = OFF_COLOR;
}

void Renderer::off()
{
	m_color = OFF_COLOR;
	m_lit = false;
}

const Renderer::Color & Renderer::color() const
{
	return m_color;
}

}
