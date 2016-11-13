#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <gpx/gra2d/Renderer.hpp>
#include <gpx/utils/Array.hpp>

namespace pmepp2_s {

class Renderer : public gpx::gra2d::Renderer
{
	public:
		typedef gpx::utils::Array<3, GLfloat> Color;

		Renderer();

		virtual void light();

		virtual void highlight();

		virtual void playdown();

		virtual void off();

	protected:
		const Color & color() const;

	private:
		static const Color OFF_COLOR;	//private prevents SIOF
		static const Color LIGHT_COLOR;	//private prevents SIOF
		static const Color HIGHLIGHT_COLOR;	//private prevents SIOF

		Color m_color;
		bool m_lit;
};

}

#endif // RENDERER_HPP
