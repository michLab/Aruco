TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        aruco.cpp \
        main.cpp \
        camera/camera.cpp

HEADERS += \
    aruco.h \
    camera/camera.h


INCLUDEPATH += /usr/local/include/opencv \
            /usr/src/gtest/include/gtest \
            /usr/src/gmock/include/gmock




LIBS += -L/usr/local/lib/
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_videoio
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_imgcodecs
LIBS += -lopencv_aruco
LIBS += -lgtest -L/usr/local/lib/googletest -lpthread

DISTFILES += \
    README.md
