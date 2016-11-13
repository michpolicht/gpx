TARGET = libgpx-phy
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

SOURCES += \
    src/gpx/phy/NewtonFrictionTable.cpp \
    src/gpx/phy/NewtonPlasticityTable.cpp \
    src/gpx/phy/PhyLog.cpp \
    src/gpx/phy/TransformationMatrix.cpp \
    src/gpx/phy2d/cnewton/pmepp2_s/ACoefsMapper.cpp \
    src/gpx/phy2d/cnewton/pmepp2_s/BasicExecutor.cpp \
    src/gpx/phy2d/cnewton/pmepp2_s/BCoefsMapper.cpp \
    src/gpx/phy2d/cnewton/pmepp2_s/CMaterialBody.cpp \
    src/gpx/phy2d/cnewton/pmepp2_s/Collider.cpp \
    src/gpx/phy2d/cnewton/pmepp2_s/CRigidBody.cpp \
    src/gpx/phy2d/cnewton/pmepp2_s/DetectionDataContainer.cpp \
    src/gpx/phy2d/cnewton/pmepp2_s/FixedWrapper.cpp \
    src/gpx/phy2d/cnewton/pmepp2_s/Introspector.cpp \
    src/gpx/phy2d/cnewton/pmepp2_s/MovableWrapper.cpp \
    src/gpx/phy2d/cnewton/pmepp2_s/PassiveWrapper.cpp \
    src/gpx/phy2d/MaterialBody.cpp \
    src/gpx/phy2d/MovableObject.cpp \
    src/gpx/phy2d/PhyObject.cpp \
    src/gpx/phy2d/RigidBody.cpp \
    src/gpx/phy2d/StaticObject.cpp

HEADERS += \
    include/gpx/phy/IMovable.hpp \
    include/gpx/phy/material.hpp \
    include/gpx/phy/NewtonFrictionData.hpp \
    include/gpx/phy/NewtonFrictionTable.hpp \
    include/gpx/phy/NewtonPlasticityData.hpp \
    include/gpx/phy/NewtonPlasticityTable.hpp \
    include/gpx/phy/PhyLog.hpp \
    include/gpx/phy/TransformationMatrix.hpp \
    include/gpx/phy2d/cdetect/interseg/CPoly.hpp \
    include/gpx/phy2d/cdetect/interseg/ICPoly.hpp \
    include/gpx/phy2d/cdetect/interseg/ICPolyGroup.hpp \
    include/gpx/phy2d/cnewton/pmepp2_s/ACoefsMapper.hpp \
    include/gpx/phy2d/cnewton/pmepp2_s/BasicExecutor.hpp \
    include/gpx/phy2d/cnewton/pmepp2_s/BCoefsMapper.hpp \
    include/gpx/phy2d/cnewton/pmepp2_s/Cluster.hpp \
    include/gpx/phy2d/cnewton/pmepp2_s/CMaterialBody.hpp \
    include/gpx/phy2d/cnewton/pmepp2_s/Collider.hpp \
    include/gpx/phy2d/cnewton/pmepp2_s/CRigidBody.hpp \
    include/gpx/phy2d/cnewton/pmepp2_s/DetectionDataContainer.hpp \
    include/gpx/phy2d/cnewton/pmepp2_s/FixedWrapper.hpp \
    include/gpx/phy2d/cnewton/pmepp2_s/ICFixed.hpp \
    include/gpx/phy2d/cnewton/pmepp2_s/ICMovable.hpp \
    include/gpx/phy2d/cnewton/pmepp2_s/Introspector.hpp \
    include/gpx/phy2d/cnewton/pmepp2_s/MovableWrapper.hpp \
    include/gpx/phy2d/cnewton/pmepp2_s/PassiveWrapper.hpp \
    include/gpx/phy2d/MaterialBody.hpp \
    include/gpx/phy2d/MovableObject.hpp \
    include/gpx/phy2d/PhyObject.hpp \
    include/gpx/phy2d/RigidBody.hpp \
    include/gpx/phy2d/StaticObject.hpp \
    include/gpx/phy_config.hpp \
    include/gpx/phy_version.hpp \
    include/gpx/phy2d/Force.hpp \
    include/gpx/phy2d/ILocalFrame.hpp \
    include/gpx/phy/(del)ITimePerformer.hpp \
    include/gpx/phy/(del)IPerformer.hpp \
    include/gpx/phy/IRecordable.hpp \
    include/gpx/phy/RecordableInt.hpp \
    include/gpx/phy/RecordableFloat.hpp \
    include/gpx/phy/RecordableFloatPoint.hpp \
    include/gpx/phy/RecordableFloatVector.hpp \
    include/gpx/phy/RecordableFloatMatrix.hpp

OTHER_FILES += \
    putlic.sh \
    cmakesrcs.awk \
    striplic.awk \
    CMakeLists.txt \
    Makefile
