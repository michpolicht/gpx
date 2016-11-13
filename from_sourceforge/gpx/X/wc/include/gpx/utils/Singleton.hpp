/**
 * @file
 * @brief Singleton template.
 */

#ifndef GPX_X_UTILS_SINGLETON_HPP_
#define GPX_X_UTILS_SINGLETON_HPP_

#include "../platform.hpp"
#include "NonCopyable.hpp"

namespace gpx {
namespace utils {

/**
 * Singleton template.
 *
 * @param C derived class. Derived class must provide default constructor. It may be
 * necessary to make Singleton<C> a friend of C to grant access to its constructor and
 * destructor.
 */
template <class C>
class Singleton : NonCopyable
{
	public:
		/**
		 * Get instance. Gets a reference to the instance of the singleton class.
		 * @return a reference to the instance of the singleton class.
		 *
		 * @warning destructor will be called on static de-initialization. Beware of
		 * using singleton instance in destructor of some other static object. If
		 * that's unavoidable, assure that singletons or any static objects are
		 * constructed in the reverse order they are going to be destructed.
		 */
		static C & Instance()
		{
			static C instance;	//initialization on first use prevents SIOF
			return instance;
		}

	protected:
		// shield the constructor and destructor to prevent outside sources
		// from creating or destroying a Singleton instance.

		/**
		 * Default constructor.
		 */
		Singleton() {}

		/**
		 * Destructor.
		 */
		~Singleton() {}
};


}
}


#endif /* GPX_X_UTILS_SINGLETON_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
