/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_HOOK_HPP_
#define GPX_Phy2d_HOOK_HPP_

#include "../phy/TransformationMatrix.hpp"
#include "../phy/IPerformer.hpp"

#include <gpx/platform.hpp>

namespace gpx {
namespace phy2d {

/**
 * Hook. Hook may be attached to one of existing vertices. Hook simply multiplies this vertex
 * by given transformation matrix on each @ref update() "update". Result is written to
 * separate memory location which may be reached via tVertex() function.
 */
class GPX_API Hook : public phy::IPerformer
{
	public:
		/**
		 * Constructor.
		 * @param vertex vertex.
		 * @param tMatrix transformation matrix.
		 */
		Hook(const real_t vertex[2], const phy::TransformationMatrix & tMatrix);

		/**
		 * Destructor.
		 */
		virtual ~Hook();

		/**
		 * Get transformation matrix.
		 * @return transformation matrix.
		 */
		const phy::TransformationMatrix & tMatrix() const;

		/**
		 * Get vertex.
		 * @return vertex.
		 */
		const math::const_VectorPtr<2> & vertex() const;

		/**
		 * Get transformed vertex.
		 * @return reference to vector with transformed vertex position.
		 */
		const math::Vector<2> & tVertex() const;

		/**
		 * Update hook position.
		 */
		void update();

	private:
		const math::const_VectorPtr<2> m_vertex;	//vertex
		const phy::TransformationMatrix & m_tMatrix;
		math::Vector<2> m_tVertex;	//hook position
};


inline
const phy::TransformationMatrix & Hook::tMatrix() const
{
	return m_tMatrix;
}

inline
const math::const_VectorPtr<2> & Hook::vertex() const
{
	return m_vertex;
}

inline
const math::Vector<2> & Hook::tVertex() const
{
	return m_tVertex;
}


}
}

#endif /* GPX_Phy2d_HOOK_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
