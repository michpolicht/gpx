#define GPX_UNORDERED_SET_HEADER 1
#define GPX_UNORDERED_MAP_HEADER 1
#define GPX_EXT_UNORDERED_SET 1
#define GPX_EXT_UNORDERED_MAP 1

#ifdef GPX_UNORDERED_SET_HEADER
	#include <tr1/unordered_set>
#endif

#ifdef GPX_UNORDERED_MAP_HEADER
	#include <tr1/unordered_map>
#endif

int main(int, char * [])
{
	#ifdef GPX_EXT_UNORDERED_SET
		std::tr1::unordered_set<int, int, std::tr1::hash<int> > set;
	#endif
	#ifdef GPX_EXT_UNORDERED_MAP
		std::tr1::unordered_map<int, int, std::tr1::hash<int> > map;
	#endif
	return 0;
}

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
