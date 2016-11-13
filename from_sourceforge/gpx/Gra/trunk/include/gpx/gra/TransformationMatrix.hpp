/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_TRANSFORMATIONMATRIX_HPP_
#define GPX_Gra_TRANSFORMATIONMATRIX_HPP_

#include <gpx/math/structures.hpp>

namespace gpx {
namespace gra {

/**
 * Transformation matrix. Equivalent of gpx::phy::Transformation matrix.
 * Class is a container for 4x4 matrix stored in column-major order.
 * Storage is compatible with OpenGL, thus OpenGL functions could literally work on instances
 * of this class. Initially matrix is an identity matrix.
 *
 * @warning for current requirements of 2d engine, methods of this class are using
 * 2x2 "rotation" minor and 1x2 "translation" block. Methods of this class can not
 * be used for general purpose calculus!
 */
class GPX_API TransformationMatrix : public math::Matrix<4, 4>
{
	typedef math::Matrix<4, 4> Parent;

	public:
		/**
		 * Default constructor.
		 */
		TransformationMatrix();

		using Parent::prod;

		/**
		 * 2D vector product.
		 * @param vec vector multiplier. Vector [x, y] is mapped to homogenous
		 * coordinates [x, y, 0, 0].
		 * @return product of matrix multiplied by vector.
		 */
//		math::Vector<2> prod(math::const_VectorRef<2> vec) const;

		using Parent::operator *;

		/**
		 * 2D vector product. Alias of prod().
		 * @param vec vector multiplier. Vector [x, y] is mapped to homogenous
		 * coordinates [x, y, 0, 0].
		 * @return product of matrix multiplied by vector.
		 */
//		math::Vector<2> operator *(math::const_VectorRef<2> vector) const;

		/**
		 * 2D point product.
		 * @param point point multiplier. Point [x, y] is mapped to vector
		 * with homogenous coordinates [x, y, 0, 1]. Matrix is then multiplied
		 * by this vector.
		 * @return product of matrix multiplied by vector mapped to a point.
		 */
		math::Point<2> prod(math::const_PointRef<2> point) const;

		/**
		 * 2D point product. Alias of prod().
		 * @param point point multiplier. Point [x, y] is mapped to vector
		 * with homogenous coordinates [x, y, 0, 1]. Matrix is then multiplied
		 * by this vector.
		 * @return product of matrix multiplied by vector mapped to a point.
		 */
		math::Point<2> operator *(math::const_PointRef<2> point) const;

};

}
}

#endif /* GPX_Gra_TRANSFORMATIONMATRIX_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
