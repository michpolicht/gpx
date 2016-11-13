# - Find unordered set name
# attempts to find fully qualified name of unordered set supported by local STL library
#  GPX_EXT_UNORDERED_SET - defined by the results
#

SET(GPX_UNORDERED_SET_NAMES 
	"std::unordered_set" 
	"std::tr1::unordered_set" 
	"__gnu_cxx::hash_set" 
)

SET(GPX_EXT_UNORDERED_SET_DESC "STL unordered set class name (e.g., std::unordered_set)")
IF (NOT GPX_EXT_UNORDERED_SET)
    FOREACH(UNORDERED_SET_NAME ${GPX_UNORDERED_SET_NAMES})
    	MESSAGE(STATUS "Looking for STL ${UNORDERED_SET_NAME}")
    	CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindUnorderedSet.cpp.in ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindUnorderedSet.cpp)
    	TRY_COMPILE(COMPILED ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindUnorderedSet.cpp)
    	IF(COMPILED)
    		MESSAGE(STATUS "Found STL ${UNORDERED_SET_NAME}")
    		SET(GPX_EXT_UNORDERED_SET ${UNORDERED_SET_NAME} CACHE STRING ${GPX_EXT_UNORDERED_SET_DESC})
    		BREAK()
    	ENDIF()
    ENDFOREACH()
ENDIF()
IF (NOT GPX_EXT_UNORDERED_SET)
	SET(GPX_EXT_UNORDERED_SET "" CACHE STRING ${GPX_EXT_UNORDERED_SET_DESC})
	MESSAGE(WARNING "STL unordered set not found, you may try set up GPX_EXT_UNORDERED_SET variable manually")
ENDIF()

#(c)MP: Copyright © 2010, Michał Policht. All rights reserved.
#(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
#(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
