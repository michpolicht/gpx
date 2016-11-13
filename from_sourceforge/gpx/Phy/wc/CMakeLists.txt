PROJECT(gpx-phy)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
ENABLE_LANGUAGE(CXX)

SET(GPX_PHY_VERSION_MAJOR \"pre-alpha\")
SET(GPX_PHY_VERSION_MINOR 11)
SET(GPX_PHY_VERSION_MICRO 0)


#checks
INCLUDE(CheckIncludeFileCxx)

SET(GPX_UNORDERED_MAP_HEADER_DESC "STL unordered map header (e.g., unordered_map).")
SET(GPX_UNORDERED_MAP_HEADERS "unordered_map" "tr1/unordered_map" "ext/hash_map" "hash_map")
FOREACH(HEADER ${GPX_UNORDERED_MAP_HEADERS})
	CHECK_INCLUDE_FILE_CXX(${HEADER} GPX_${HEADER}_FOUND)
	IF(GPX_${HEADER}_FOUND)
		SET(GPX_UNORDERED_MAP_HEADER ${HEADER} CACHE FILEPATH ${GPX_UNORDERED_MAP_HEADER_DESC})
		BREAK()
	ENDIF()
ENDFOREACH()
IF (NOT GPX_UNORDERED_MAP_HEADER)
	SET(GPX_UNORDERED_MAP_HEADER "" CACHE FILEPATH ${GPX_UNORDERED_MAP_HEADER_DESC})
	MESSAGE(SEND_ERROR "STL unordered map header not found, please set up GPX_UNORDERED_MAP_HEADER variable manually")
ENDIF()

SET(GPX_UNORDERED_SET_HEADER_DESC "STL unordered set header (e.g., unordered_set).")
SET(GPX_UNORDERED_SET_HEADERS "unordered_set" "tr1/unordered_set" "ext/hash_set" "hash_set")
FOREACH(HEADER ${GPX_UNORDERED_SET_HEADERS})
	CHECK_INCLUDE_FILE_CXX(${HEADER} GPX_${HEADER}_FOUND)
	IF(GPX_${HEADER}_FOUND)
		SET(GPX_UNORDERED_SET_HEADER ${HEADER} CACHE FILEPATH ${GPX_UNORDERED_SET_HEADER_DESC})
		BREAK()
	ENDIF()
ENDFOREACH()
IF (NOT GPX_UNORDERED_SET_HEADER)
	SET(GPX_UNORDERED_SET_HEADER "" CACHE FILEPATH ${GPX_UNORDERED_SET_HEADER_DESC})
	MESSAGE(SEND_ERROR "STL unordered set header not found, please set up GPX_UNORDERED_SET_HEADER variable manually")
ENDIF()

INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindUnorderedMap.cmake)
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindUnorderedSet.cmake)
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindHashFunc.cmake)


#include dirs
FIND_PATH(GPX_X_INCLUDE_DIR
    NAMES gpx/platform.hpp 
    PATHS ../../X/trunk/include/ )

INCLUDE_DIRECTORIES(${GPX_X_INCLUDE_DIR})


#configure
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/gpx/phy_version.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/gpx/phy_version.hpp)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/gpx/phy_config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/gpx/phy_config.hpp)


#sources_begin
SET(SRCS
src/gpx/phy/NewtonFrictionTable.cpp
src/gpx/phy/NewtonPlasticityTable.cpp
src/gpx/phy/PhyLog.cpp
src/gpx/phy/TransformationMatrix.cpp
src/gpx/phy2d/Board.cpp
src/gpx/phy2d/CMaterialBody.cpp
src/gpx/phy2d/CRigidBody.cpp
src/gpx/phy2d/DragnDropCollider.cpp
src/gpx/phy2d/Force.cpp
src/gpx/phy2d/Hook.cpp
src/gpx/phy2d/MaterialBody.cpp
src/gpx/phy2d/MovableObject.cpp
src/gpx/phy2d/NewtonCollider.cpp
src/gpx/phy2d/NewtonCollisionExecutor.cpp
src/gpx/phy2d/RigidBody.cpp
src/gpx/phy2d/StaticObject.cpp
)
#sources_end


#build
ADD_DEFINITIONS(-DGPX_BUILD)
OPTION(BUILD_SHARED_LIBS "Select to build shared or static library." ON)
IF(BUILD_SHARED_LIBS)
    ADD_DEFINITIONS(-DGPX_DYNAMIC)
ENDIF()
ADD_LIBRARY(gpx-phy ${SRCS})

#(c)MP: Copyright © 2010, Michał Policht. All rights reserved.
#(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
#(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
