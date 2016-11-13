/**
 * @file
 * @brief .
 */

#ifndef GPX_X_UTILS_MULTITON_HPP_
#define GPX_X_UTILS_MULTITON_HPP_

#include "../platform.hpp"
#include "NonCopyable.hpp"

#include <vector>

namespace gpx {
namespace utils {

/**
 * Multiton. Multiton extends the idea of Singleton, providing access to multiple instances
 * of some class.
 *
 * @param C derived class. Derived class must provide default constructor. It may be
 * necessary to make Multiton<C> a friend of C to grant access to its constructor and
 * destructor.
 */
template <class C>
class Multiton
{
	public:
		typedef std::vector<C> InstancesContainer;

	public:
		static InstancesContainer & Instances()
		{
			static InstancesContainer instances; //initialization on first use prevents SIOF
			return instances;
		}

		static void Resize(std::size_t n)
		{
			Instances().resize(n);
		}

		static std::size_t Size()
		{
			return Instances().size();
		}

		/**
		 * Get instance. Gets a reference to one of the instances.
		 * @param n instance number.
		 * @return a reference to the instance.
		 *
		 * @warning destructors will be called on static de-initialization. Beware of
		 * using multiton instances in destructor of some other static object. If
		 * that's unavoidable, assure that multitons or any static objects are
		 * constructed in the reverse order they are going to be destructed.
		 */
		static C & Instance(std::size_t n)
		{
			GPX_ASSERT(n < Instances().size(), "Instance(" << n << ") is out of bounds");
			return Instances()[n];
		};

	protected:
		// shield the constructor and destructor to prevent outside sources
		// from creating or destroying a Singleton instance.

		/**
		 * Default constructor.
		 */
		Multiton() {};

		/**
		 * Destructor.
		 */
		~Multiton() {};
};

}
}

#endif /* GPX_X_UTILS_MULTITON_HPP_ */

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
