# - Find unordered map name
# attempts to find fully qualified name of unordered map supported by local STL library
#  GPX_EXT_UNORDERED_MAP - defined by the results
#

SET(GPX_UNORDERED_MAP_NAMES 
	"std::unordered_map" 
	"std::tr1::unordered_map" 
	"__gnu_cxx::hash_map" 
)

SET(GPX_EXT_UNORDERED_MAP_DESC "STL unordered map class name (e.g., std::unordered_map)")
IF (NOT GPX_EXT_UNORDERED_MAP)
    FOREACH(UNORDERED_MAP_NAME ${GPX_UNORDERED_MAP_NAMES})
    	MESSAGE(STATUS "Looking for STL ${UNORDERED_MAP_NAME}")
    	CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindUnorderedMap.cpp.in ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindUnorderedMap.cpp)
    	TRY_COMPILE(COMPILED ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindUnorderedMap.cpp)
    	IF(COMPILED)
    		MESSAGE(STATUS "Found STL ${UNORDERED_MAP_NAME}")
    		SET(GPX_EXT_UNORDERED_MAP ${UNORDERED_MAP_NAME} CACHE STRING ${GPX_EXT_UNORDERED_MAP_DESC})
    		BREAK()
    	ENDIF()
    ENDFOREACH()
ENDIF()
IF (NOT GPX_EXT_UNORDERED_MAP)
	SET(GPX_EXT_UNORDERED_MAP "" CACHE STRING ${GPX_EXT_UNORDERED_MAP_DESC})
	MESSAGE(WARNING "STL unordered map not found, you may try set up GPX_EXT_UNORDERED_MAP variable manually")
ENDIF()

#(c)MP: Copyright © 2010, Michał Policht. All rights reserved.
#(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
#(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
