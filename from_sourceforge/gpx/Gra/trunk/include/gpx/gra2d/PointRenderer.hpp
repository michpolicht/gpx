/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra2d_POINTRENDERER_HPP_
#define GPX_Gra2d_POINTRENDERER_HPP_

#include <gpx/platform.hpp>
#include <gpx/utils/Array.hpp>
#include <gpx/math/structures.hpp>

#include "Renderer.hpp"


namespace gpx {
namespace gra2d {


/**
 * Point renderer.
 */
class GPX_API PointRenderer: public Renderer
{
	public:
		/**
		 * Render style:
		 * 	- @p Dot - render point as dot. Dot size can be controlled by DotSize static member.
		 * 	- @p Cross - render point as cross. Point size can be controlled by CrossSize static member.
		 */
		enum Style {Dot, Cross};

		static const real_t INITIAL_DOT_SIZE = 4.0;
		static real_t DotSize;
		static const real_t INITIAL_CROSS_SIZE = 6.0;
		static real_t CrossSize;
		static const utils::Array<4> INITIAL_COLOR;

	protected:
		const real_t * m_point;
		Style m_style;
		utils::Array<4> m_color;

	public:
		/**
		 * Constructor.
		 * @param point point.
		 * @param style point render @ref Style "style".
		 */
		PointRenderer(const real_t point[2], PointRenderer::Style style = Cross);

		/**
		 * Destructor.
		 */
		virtual ~PointRenderer();

		const real_t * point() const;

		void setPoint(const real_t point[2]);

		const utils::Array<4> & color() const;

		void setColor(const utils::Array<4> & color);

		PointRenderer::Style style() const;

		void setStyle(PointRenderer::Style style);

		//Renderer
		virtual void render(RenderContext * context);
};

}
}

#endif /* GPX_Gra2d_POINTRENDERER_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
