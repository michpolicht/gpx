/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_OP_TRANSPARENT_HPP_
#define GPX_Phy2d_OP_TRANSPARENT_HPP_

namespace gpx {
namespace phy2d {
namespace op {


/**
 * Transparent functor. This functor may be used as transparency operator on specified
 * function. Transparent operator is "dumb", it does not affect underlying function, thus
 * it is usually used as default operator.
 */
class Transparent
{
	public:
		template <typename T, typename F>
		T & operator()(T & arg, F & f);

		template <typename T, typename F>
		T operator()(T arg, F & f);
};


template <typename T, typename F>
inline
T & Transparent::operator()(T & arg, F & f)
{
	return f(arg);
}

template <typename T, typename F>
inline
T Transparent::operator()(T arg, F & f)
{
	return f(arg);
}

}
}
}

#endif /* GPX_Phy2d_OP_TRANSPARENT_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
