PROJECT(gpx-gra)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
ENABLE_LANGUAGE(CXX)

#version
SET(GPX_GRA_VERSION_MAJOR \"pre-alpha\")
SET(GPX_GRA_VERSION_MINOR 11)
SET(GPX_GRA_VERSION_MICRO 0)
SET(GPX_BRANCH "trunk")

#checks


#libraries

#GPX
FIND_PATH(GPX_X_INCLUDE_DIR
    NAMES gpx/platform.hpp 
    PATHS ../../X/${GPX_BRANCH}/include/ 
    DOC "GPX X include directory")
MESSAGE(STATUS "GPX X include dir - "${GPX_X_INCLUDE_DIR})
SET(GPX_GRA_INCLUDES ${GPX_GRA_INCLUDES} ${GPX_X_INCLUDE_DIR})

FIND_PATH(GPX_PHY_INCLUDE_DIR
    NAMES gpx/phy_config.hpp
    PATHS ../../Phy/${GPX_BRANCH}/include/ 
    DOC "GPX Phy include directory.")
MESSAGE(STATUS "GPX Phy include dir - "${GPX_PHY_INCLUDE_DIR})
SET(GPX_GRA_INCLUDES ${GPX_GRA_INCLUDES} ${GPX_PHY_INCLUDE_DIR})
FIND_LIBRARY(GPX_PHY_LIB
    NAMES gpx-phy
    PATHS ../../Phy/${GPX_BRANCH}/build
    DOC "gpx-phy library file.")
MESSAGE(STATUS "GPX Phy lib - "${GPX_PHY_LIB})
SET(GPX_GRA_LIBS ${GPX_GRA_LIBS} ${GPX_PHY_LIB})

#SFML
SET(SFML_INCLUDE_PATHS  "../../../SFML/include")
FIND_PATH(SFML_INCLUDE_DIR
    NAMES SFML/System.hpp SFML/Window.hpp SFML/Graphics.hpp
    PATHS ${SFML_INCLUDE_PATHS}
    DOC "SFML include directory")
MESSAGE(STATUS "SFML include dir - "${SFML_INCLUDE_DIR})
SET(GPX_GRA_INCLUDES ${GPX_GRA_INCLUDES} ${SFML_INCLUDE_DIR})

SET(GPX_SFML_LIB_PATHS "../../../SFML/lib/mingw" "../../../SFML/lib")

FIND_LIBRARY(SFML_LIB_GRAPHICS
    NAMES sfml-graphics
    PATHS ${GPX_SFML_LIB_PATHS}
    DOC "sfml-graphics dynamic library file.")
MESSAGE(STATUS "SFML Graphics dynamic library - "${SFML_LIB_GRAPHICS})

FIND_LIBRARY(SFML_LIB_WINDOW
    NAMES sfml-window
    PATHS ${GPX_SFML_LIB_PATHS}
    DOC "sfml-window dynamic library file.")
MESSAGE(STATUS "SFML Window dynamic library - "${SFML_LIB_WINDOW})

FIND_LIBRARY(SFML_LIB_SYSTEM
    NAMES sfml-system
    PATHS ${GPX_SFML_LIB_PATHS}
    DOC "sfml-system dynamic library file.")
MESSAGE(STATUS "SFML System dynamic library - "${SFML_LIB_SYSTEM})

FIND_LIBRARY(SFML_LIB_GRAPHICS_S
    NAMES sfml-graphics-s
    PATHS ${GPX_SFML_LIB_PATHS}
    DOC "sfml-graphics static library file.")
MESSAGE(STATUS "SFML Graphics static library - "${SFML_LIB_GRAPHICS_S})

FIND_LIBRARY(SFML_LIB_WINDOW_S
    NAMES sfml-window-s
    PATHS ${GPX_SFML_LIB_PATHS}
    DOC "sfml-window static library file.")
MESSAGE(STATUS "SFML Window static library - "${SFML_LIB_WINDOW_S})

FIND_LIBRARY(SFML_LIB_SYSTEM_S
    NAMES sfml-system-s
    PATHS ${GPX_SFML_LIB_PATHS}
    DOC "sfml-system static library file.")
MESSAGE(STATUS "SFML System static library - "${SFML_LIB_SYSTEM_S})
OPTION(SFML_DYNAMIC "Select when using dynamic versions of SFML libraries." ON)
IF(SFML_DYNAMIC)
    ADD_DEFINITIONS(-DSFML_DYNAMIC)
    SET(GPX_GRA_LIBS ${GPX_GRA_LIBS} ${SFML_LIB_GRAPHICS})
    SET(GPX_GRA_LIBS ${GPX_GRA_LIBS} ${SFML_LIB_WINDOW})
    SET(GPX_GRA_LIBS ${GPX_GRA_LIBS} ${SFML_LIB_SYSTEM})
    MESSAGE(STATUS "Using dynamic versions of SFML libraries")
ELSE()
    SET(GPX_GRA_LIBS ${GPX_GRA_LIBS} ${SFML_LIB_GRAPHICS_S})
    SET(GPX_GRA_LIBS ${GPX_GRA_LIBS} ${SFML_LIB_WINDOW_S})
    SET(GPX_GRA_LIBS ${GPX_GRA_LIBS} ${SFML_LIB_SYSTEM_S})
    MESSAGE(STATUS "Using static versions of SFML libraries")
ENDIF()

#OpenGL
INCLUDE(FindOpenGL)
MESSAGE(STATUS "OpenGL found - "${OPENGL_FOUND})
MESSAGE(STATUS "GLU found - "${OPENGL_GLU_FOUND})
IF (OPENGL_INCLUDE_DIR)
    MESSAGE(STATUS "OpenGL include dir - "${OPENGL_INCLUDE_DIR})
ENDIF()
IF (OPENGL_FOUND)
    MESSAGE(STATUS "OpenGL library - "${OPENGL_gl_LIBRARY})
ENDIF()
IF (OPENGL_GLU_FOUND)
    MESSAGE(STATUS "GLU library - "${OPENGL_glu_LIBRARY})
ENDIF()
SET(GPX_GRA_INCLUDES ${GPX_GRA_INCLUDES} ${OPENGL_INCLUDE_DIR})
SET(GPX_GRA_LIBS ${GPX_GRA_LIBS} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})


#includes
INCLUDE_DIRECTORIES(${GPX_GRA_INCLUDES})


#configure
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/gpx/gra_version.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/gpx/gra_version.hpp)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/gpx/gra_config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/gpx/gra_config.hpp)


#sources_begin
SET(SRCS
src/gpx/glsl/AttribInfo.cpp
src/gpx/glsl/Program.cpp
src/gpx/glsl/Shader.cpp
src/gpx/glsl/UniformInfo.cpp
src/gpx/glsl/VertexShader.cpp
src/gpx/gra/GraLog.cpp
src/gpx/gra/RenderWindow.cpp
src/gpx/gra/Requirements.cpp
src/gpx/gra/TransformationMatrix.cpp
src/gpx/gra/Viewport.cpp
src/gpx/gra2d/Clip.cpp
src/gpx/gra2d/GraphicsObject.cpp
src/gpx/gra2d/GraphicsObjectRenderer.cpp
src/gpx/gra2d/PointRenderer.cpp
src/gpx/gra2d/RenderContext.cpp
src/gpx/gra2d/Renderer.cpp
src/gpx/gra2d/Scene.cpp
src/gpx/gra2d/VectorRenderer.cpp
src/gpx/gra2d/View.cpp
src/gpx/gui/BoxOffsetFrame.cpp
src/gpx/gui/BoxWidget.cpp
src/gpx/gui/BoxWidgetRenderer.cpp
src/gpx/gui/Button.cpp
src/gpx/gui/Container.cpp
src/gpx/gui/ContainerRenderer.cpp
src/gpx/gui/ContentButton.cpp
src/gpx/gui/ContentButtonRenderer.cpp
src/gpx/gui/DFlowLayout.cpp
src/gpx/gui/Dispatcher.cpp
src/gpx/gui/Font.cpp
src/gpx/gui/FontFamily.cpp
src/gpx/gui/FpsWidget.cpp
src/gpx/gui/HFlowLayout.cpp
src/gpx/gui/Icon.cpp
src/gpx/gui/Image.cpp
src/gpx/gui/Layout.cpp
src/gpx/gui/LayoutRenderer.cpp
src/gpx/gui/Rect.cpp
src/gpx/gui/RenderTarget.cpp
src/gpx/gui/Text.cpp
src/gpx/gui/TextButton.cpp
src/gpx/gui/VFlowLayout.cpp
src/gpx/gui/Widget.cpp
src/gpx/gui/WidgetDispatcher.cpp
src/gpx/gui/WidgetLogic.cpp
src/gpx/gui/WidgetRenderer.cpp
src/gpx/model/PolyPainter.cpp
src/gpx/phy2d/BoardRenderer.cpp
src/gpx/phy2d/joints/JointRenderer.cpp
src/gpx/phy2d/RigidBodyRenderer.cpp
src/glew/glew.c
)
#sources_end


#build
ADD_DEFINITIONS(-DGPX_BUILD -DGLEW_STATIC)
OPTION(BUILD_SHARED_LIBS "Select to build shared or static library." ON)
IF(BUILD_SHARED_LIBS)
    ADD_DEFINITIONS(-DGPX_DYNAMIC)
ENDIF()
ADD_LIBRARY(gpx-gra ${SRCS})
TARGET_LINK_LIBRARIES(gpx-gra ${GPX_GRA_LIBS})

#(c)MP: Copyright © 2010, Michał Policht. All rights reserved.
#(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
#(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
