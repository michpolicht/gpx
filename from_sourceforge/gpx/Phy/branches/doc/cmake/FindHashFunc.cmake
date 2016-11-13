# - Find hash function name
# attempts to find fully qualified name of hash function supported by local STL library
#  GPX_EXT_HASH_FUNC - defined by the results
#
# Must be included after FindUnorderedMap.cmake and FindUnorderedSet.cmake.

IF (GPX_EXT_UNORDERED_MAP OR GPX_EXT_UNORDERED_SET)
	SET(GPX_HASH_FUNC_NAMES 
		"std::hash" 
		"std::tr1::hash" 
		"__gnu_cxx::hash" 
	)

	SET(GPX_EXT_HASH_FUNC_DESC "STL hash function name (e.g., std::hash)")
	IF (NOT GPX_EXT_HASH_FUNC)
	    FOREACH(HASH_FUNC_NAME ${GPX_HASH_FUNC_NAMES})
	    	MESSAGE(STATUS "Looking for STL ${HASH_FUNC_NAME}")
	    	CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindHashFunc.cpp.in ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindHashFunc.cpp)
	    	TRY_COMPILE(COMPILED ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindHashFunc.cpp)
	    	IF(COMPILED)
	    		MESSAGE(STATUS "Found STL ${HASH_FUNC_NAME}")
	    		SET(GPX_EXT_HASH_FUNC ${HASH_FUNC_NAME} CACHE STRING ${GPX_EXT_HASH_FUNC_DESC})
	    		BREAK()
	    	ENDIF()
	    ENDFOREACH()
	ENDIF()
	
	#whenever GPX_EXT_UNORDERED_MAP or GPX_EXT_UNORDERED_SET is set, then hash function is required
	IF (NOT GPX_EXT_HASH_FUNC)
		SET(GPX_EXT_HASH_FUNC "" CACHE STRING ${GPX_EXT_HASH_FUNC_DESC})
		MESSAGE(SEND_ERROR "STL hash function not found, please set up GPX_EXT_HASH_FUNC variable manually or clean GPX_EXT_UNORDERED_MAP and GPX_EXT_UNORDERED_SET variables")
	ENDIF()
ENDIF()

#(c)MP: Copyright © 2010, Michał Policht. All rights reserved.
#(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
#(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
