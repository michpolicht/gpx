/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy_TRANSFORMATIONMATRIX_HPP_
#define GPX_Phy_TRANSFORMATIONMATRIX_HPP_

#include <gpx/platform.hpp>
#include <gpx/math/structures.hpp>
//#include <Eigen/Core>

//USING_PART_OF_NAMESPACE_EIGEN


namespace gpx {
namespace phy {

/**
 * Transformation matrix. Class is a container for 4x4 matrix stored in column-major order.
 * Storage is compatible with OpenGL, thus OpenGL functions could literally work on instances
 * of this class. Initially matrix is an identity matrix.
 *
 * @warning for current requirements of 2d engine, methods of this class are using
 * 2x2 "rotation" minor and 1x2 "translation" block. Methods of this class can not
 * be used for general purpose calculus!
 */
class GPX_API TransformationMatrix : public math::Matrix<4, 4>
{
	public:
		/**
		 * Default constructor.
		 */
		TransformationMatrix();

		/**
		 * Multiplication operator.
		 * @param vector vector to be multiplied.
		 * @return multiplied vector.
		 */
		math::Vector<2> operator *(const math::const_VectorPtr<2> & vector) const;

		/**
		 * Multiply matrix by 2d vector. Since matrix is 4x4, 2d vector (x, y) is mapped to
		 * 4d (x, y, 0.0, 1.0) vector in homogeneous coordinates.
		 * @param vector vector to be multiplied.
		 * @return @a vector after multiplication.
		 */
		math::VectorPtr<2> & mult(math::VectorPtr<2> & vector) const;
};


}
}

#endif /* GPX_Phy_TRANSFORMATIONMATRIX_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
