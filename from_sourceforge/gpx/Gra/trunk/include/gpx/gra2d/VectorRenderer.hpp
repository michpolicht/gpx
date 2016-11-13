/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra2d_VECTORRENDERER_HPP_
#define GPX_Gra2d_VECTORRENDERER_HPP_

#include <cstddef>

#include <gpx/platform.hpp>
#include <gpx/utils/Array.hpp>
#include <gpx/math/structures.hpp>

#include "Renderer.hpp"

namespace gpx {
namespace gra2d {

/**
 * Vector renderer. Renders vectors as arrows of adequate length and orientation.
 */
class GPX_API VectorRenderer: public Renderer
{
	protected:
		const real_t * m_initial;
		const real_t * m_vector;
		utils::Array<4> m_color;
		bool m_frontArrow;

	public:
		static const real_t INITIAL_ARROW_SIZE = 6.0;
		static const real_t INITIAL_ARROW_ANGLE = M_PI/6.0;
		static const utils::Array<4> INITIAL_COLOR;

	public:
		/**
		 * Constructor.
		 * @param point initial point. Pointer to 2d array. Might be null, but valid pointer
		 * must be set before render() is being called.
		 * @param vector vector. Pointer to 2d array. Might be null, but valid pointer
		 * must be set before render() is being called.
		 */
		VectorRenderer(const real_t point[2], const real_t vector[2]);

		/**
		 * Destructor.
		 */
		virtual ~VectorRenderer();

		/**
		 * Get vector.
		 * @return 2-element array containing vector coordinates.
		 */
		const real_t * vector() const;

		/**
		 * Set vector.
		 * @param vector array containing vector coordinates.
		 */
		void setVector(const real_t vector[2]);

		/**
		 * Get initial position.
		 * @return 2-element array containing initial vector position.
		 */
		const real_t * initial() const;

		/**
		 * Set initial point.
		 * @param initial array containing initial vector position.
		 */
		void setInitial(const real_t initial[2]);

		/**
		 * Set color.
		 * @param color array describing color values (RGBA).
		 */
		void setColor(const utils::Array<4> & color);

		/**
		 * Get color.
		 * @return array describing current color values (RGBA).
		 */
		const utils::Array<4> & color() const;

		/**
		 * Enable or disable front arrow.
		 * @param enable @p true to enables front arrow, @p false disables.
		 *
		 * @note front arrow may be not visible when vector length is 0.0.
		 */
		void setFrontArrow(bool enable);

		/**
		 * Check whether front arrow is enabled.
		 * @return @true when front arrow is enabled, @p false otherwise.
		 */
		bool frontArrow() const;

		//Renderer
		virtual void render(RenderContext * context);
};

}
}

#endif /* GPX_Gra2d_VECTORRENDERER_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
