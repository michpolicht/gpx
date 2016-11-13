TARGET = libgpx-gra
TEMPLATE = lib
CONFIG -= qt
CONFIG += object_parallel_to_source

DEFINES += GPX_BUILD

#shared library build
DEFINES += GPX_DYNAMIC
CONFIG += shared

#static library build
#CONFIG += static

#X
INCLUDEPATH += $$PWD/../../X/wc/include
DEPENDPATH += $$PWD/../../X/wc/include

#Phy
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Phy/wc/release -llibgpx-phy
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Phy/wc/debug -llibgpx-phy
else:unix: LIBS += -L$$OUT_PWD/../../Phy/wc -llibgpx-phy
INCLUDEPATH += $$PWD/../../Phy/wc/include
DEPENDPATH += $$PWD/../../Phy/wc/include

#GLEW
DEFINES += GLEW_STATIC

#OpenGL
unix|win32: LIBS += -lglu32
unix|win32: LIBS += -lopengl32

#SFML
DEFINES += SFML_DYNAMIC
unix|win32: LIBS += -L$$PWD/../../../SFML/lib/mingw/ -lsfml-graphics
unix|win32: LIBS += -L$$PWD/../../../SFML/lib/mingw/ -lsfml-window
unix|win32: LIBS += -L$$PWD/../../../SFML/lib/mingw/ -lsfml-system
INCLUDEPATH += $$PWD/../../../SFML/include
DEPENDPATH += $$PWD/../../../SFML/include

SOURCES += \
    src/gpx/glsl/AttribInfo.cpp \
    src/gpx/glsl/Program.cpp \
    src/gpx/glsl/Shader.cpp \
    src/gpx/glsl/UniformInfo.cpp \
    src/gpx/glsl/VertexShader.cpp \
    src/gpx/gra/GraLog.cpp \
    src/gpx/gra/RenderWindow.cpp \
    src/gpx/gra/Requirements.cpp \
    src/gpx/gra/TransformationMatrix.cpp \
    src/gpx/gra/Viewport.cpp \
    src/gpx/gra2d/Clip.cpp \
    src/gpx/gra2d/GraphicsObject.cpp \
    src/gpx/gra2d/GraphicsObjectRenderer.cpp \
    src/gpx/gra2d/PointRenderer.cpp \
    src/gpx/gra2d/RenderContext.cpp \
    src/gpx/gra2d/Renderer.cpp \
    src/gpx/gra2d/Scene.cpp \
    src/gpx/gra2d/VectorRenderer.cpp \
    src/gpx/gra2d/View.cpp \
    src/gpx/gui/BoxOffsetFrame.cpp \
    src/gpx/gui/BoxWidget.cpp \
    src/gpx/gui/BoxWidgetRenderer.cpp \
    src/gpx/gui/Button.cpp \
    src/gpx/gui/Container.cpp \
    src/gpx/gui/ContainerRenderer.cpp \
    src/gpx/gui/ContentButton.cpp \
    src/gpx/gui/ContentButtonRenderer.cpp \
    src/gpx/gui/DFlowLayout.cpp \
    src/gpx/gui/Dispatcher.cpp \
    src/gpx/gui/Font.cpp \
    src/gpx/gui/FontFamily.cpp \
    src/gpx/gui/FpsWidget.cpp \
    src/gpx/gui/HFlowLayout.cpp \
    src/gpx/gui/Icon.cpp \
    src/gpx/gui/Image.cpp \
    src/gpx/gui/Layout.cpp \
    src/gpx/gui/LayoutRenderer.cpp \
    src/gpx/gui/Rect.cpp \
    src/gpx/gui/RenderTarget.cpp \
    src/gpx/gui/Screen.cpp \
    src/gpx/gui/Text.cpp \
    src/gpx/gui/TextButton.cpp \
    src/gpx/gui/VFlowLayout.cpp \
    src/gpx/gui/ViewDispatcher.cpp \
    src/gpx/gui/Widget.cpp \
    src/gpx/gui/WidgetLogic.cpp \
    src/gpx/gui/WidgetRenderer.cpp \
    src/gpx/model/PolyPainter.cpp \
    src/gpx/phy2d/RigidBodyRenderer.cpp \
    src/glew/glew.c

HEADERS += \
    include/glew/glew.h \
    include/glew/glxew.h \
    include/glew/wglew.h \
    include/gpx/glsl/AttribInfo.hpp \
    include/gpx/glsl/Program.hpp \
    include/gpx/glsl/Shader.hpp \
    include/gpx/glsl/UniformInfo.hpp \
    include/gpx/glsl/VertexShader.hpp \
    include/gpx/gra/Color.hpp \
    include/gpx/gra/GraLog.hpp \
    include/gpx/gra/RenderWindow.hpp \
    include/gpx/gra/Requirements.hpp \
    include/gpx/gra/TransformationMatrix.hpp \
    include/gpx/gra/Viewport.hpp \
    include/gpx/gra2d/Clip.hpp \
    include/gpx/gra2d/GraphicsObject.hpp \
    include/gpx/gra2d/GraphicsObjectRenderer.hpp \
    include/gpx/gra2d/PointRenderer.hpp \
    include/gpx/gra2d/RenderContext.hpp \
    include/gpx/gra2d/Renderer.hpp \
    include/gpx/gra2d/Scene.hpp \
    include/gpx/gra2d/VectorRenderer.hpp \
    include/gpx/gra2d/View.hpp \
    include/gpx/gui/BoxOffset.hpp \
    include/gpx/gui/BoxOffsetFrame.hpp \
    include/gpx/gui/BoxWidget.hpp \
    include/gpx/gui/BoxWidgetRenderer.hpp \
    include/gpx/gui/Button.hpp \
    include/gpx/gui/Container.hpp \
    include/gpx/gui/ContainerRenderer.hpp \
    include/gpx/gui/ContentButton.hpp \
    include/gpx/gui/ContentButtonRenderer.hpp \
    include/gpx/gui/CursorEvent.hpp \
    include/gpx/gui/DFlowLayout.hpp \
    include/gpx/gui/Dispatcher.hpp \
    include/gpx/gui/events.hpp \
    include/gpx/gui/Font.hpp \
    include/gpx/gui/FontFamily.hpp \
    include/gpx/gui/FpsWidget.hpp \
    include/gpx/gui/HFlowLayout.hpp \
    include/gpx/gui/Icon.hpp \
    include/gpx/gui/IEventListener.hpp \
    include/gpx/gui/IGuiDetection.hpp \
    include/gpx/gui/Image.hpp \
    include/gpx/gui/Layout.hpp \
    include/gpx/gui/LayoutRenderer.hpp \
    include/gpx/gui/Rect.hpp \
    include/gpx/gui/RenderTarget.hpp \
    include/gpx/gui/Screen.hpp \
    include/gpx/gui/ScrollEvent.hpp \
    include/gpx/gui/Text.hpp \
    include/gpx/gui/TextButton.hpp \
    include/gpx/gui/TriggerEvent.hpp \
    include/gpx/gui/VFlowLayout.hpp \
    include/gpx/gui/ViewDispatcher.hpp \
    include/gpx/gui/Widget.hpp \
    include/gpx/gui/WidgetLogic.hpp \
    include/gpx/gui/WidgetRenderer.hpp \
    include/gpx/model/FramePainter.hpp \
    include/gpx/model/PolyPainter.hpp \
    include/gpx/phy2d/RigidBodyRenderer.hpp \
    include/gpx/gl_wrap.hpp \
    include/gpx/glew_wrap.hpp \
    include/gpx/gra_config.hpp \
    include/gpx/gra_version.hpp \
    include/gpx/gra_config.hpp.in \
    include/gpx/gra_version.hpp.in
