TEMPLATE = app
CONFIG += windows
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += object_parallel_to_source
QMAKE_CXXFLAGS += -std=c++11

DEFINES += GPX_DYNAMIC

#X
INCLUDEPATH += $$PWD/../../gpx/X/wc/include
DEPENDPATH += $$PWD/../../gpx/X/wc/include

#Phy
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../gpx-build/Phy/wc/release -llibgpx-phy
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../gpx-build/Phy/wc/debug -llibgpx-phy
else:unix: LIBS += -L$$PWD/../../gpx-build/Phy/wc -llibgpx-phy
INCLUDEPATH += $$PWD/../../gpx/Phy/wc/include
DEPENDPATH += $$PWD/../../gpx/Phy/wc/include

#Gra
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../gpx-build/Gra/trunk/release -llibgpx-gra
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../gpx-build/Gra/trunk/debug -llibgpx-gra
else:unix: LIBS += -L$$PWD/../../gpx-build/Gra/trunk -llibgpx-gra
INCLUDEPATH += $$PWD/../../gpx/Gra/trunk/include
DEPENDPATH += $$PWD/../../gpx/Gra/trunk/include

#GLEW
DEFINES += GLEW_STATIC

#OpenGL
unix|win32: LIBS += -lglu32
unix|win32: LIBS += -lopengl32

#SFML
DEFINES += SFML_DYNAMIC
unix|win32: LIBS += -L$$PWD/../../SFML/lib/mingw/ -lsfml-graphics
unix|win32: LIBS += -L$$PWD/../../SFML/lib/mingw/ -lsfml-window
unix|win32: LIBS += -L$$PWD/../../SFML/lib/mingw/ -lsfml-system
INCLUDEPATH += $$PWD/../../SFML/include
DEPENDPATH += $$PWD/../../SFML/include


SOURCES += main.cpp \
    graphics/InclinedPlaneRenderer.cpp \
    graphics/MaterialPolyRenderer.cpp \
    graphics/RigidPolyRenderer.cpp \
    graphics/WallRenderer.cpp \
    model/BallModel.cpp \
    model/BoxModel.cpp \
    model/InclinedPlaneModel.cpp \
    model/WallModel.cpp \
    physics/InclinedPlane.cpp \
    physics/MaterialPoly.cpp \
    physics/RigidPoly.cpp \
    physics/Wall.cpp \
    glew/glew.c \
    Introspector.cpp \
    graphics/Renderer.cpp \
    Recorder.cpp

HEADERS += \
    glew/glew.h \
    glew/glxew.h \
    glew/wglew.h \
    graphics/InclinedPlaneRenderer.hpp \
    graphics/MaterialPolyRenderer.hpp \
    graphics/RigidPolyRenderer.hpp \
    graphics/WallRenderer.hpp \
    model/BallModel.hpp \
    model/BoxModel.hpp \
    model/InclinedPlaneModel.hpp \
    model/WallModel.hpp \
    physics/InclinedPlane.hpp \
    physics/MaterialPoly.hpp \
    physics/RigidPoly.hpp \
    physics/Wall.hpp \
    Introspector.hpp \
    graphics/Renderer.hpp \
    Recorder.hpp

