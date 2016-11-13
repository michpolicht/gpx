TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11
#QMAKE_CXXFLAGS += -fno-implicit-templates

DEFINES += GPX_DYNAMIC

#X
INCLUDEPATH += $$PWD/../../gpx/X/wc/include
DEPENDPATH += $$PWD/../../gpx/X/wc/include

SOURCES += main.cpp \
    tests.hpp \
    const_VectorRefTest.hpp \
    VectorRefTest.hpp \
    VectorTest.hpp \
    MatrixTest.hpp

HEADERS += \
    tests.hpp \
    const_VectorRefTest.hpp \
    VectorRefTest.hpp \
    VectorTest.hpp \
    MatrixTest.hpp
