/**
 * @file
 * @brief .
 */


#include "../../../include/gpx/phy/TransformationMatrix.hpp"

namespace gpx {
namespace phy {

TransformationMatrix::TransformationMatrix():
	math::Matrix<4,4>()
{
}

math::Vector<2> TransformationMatrix::operator *(const math::const_VectorPtr<2> & vector) const
{
	math::Vector<2> result(vector);
	mult(result);
	return result;
}

math::VectorPtr<2> & TransformationMatrix::mult(math::VectorPtr<2> & vector) const
{
	math::Vector<2> copy(vector);
	vector.zero();
	int pos = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
			vector[j] += m_elements[pos++] * copy[i];
		pos += 2; //skip 2 elements for vector[2] and [3]
	}
	pos += 4; //skip whole column[2]
	for (int i = 0; i < 2; i++)
		vector[i] += m_elements[pos++];	//translation
	return vector;
}

}
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
