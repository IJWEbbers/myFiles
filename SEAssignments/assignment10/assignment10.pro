TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        device.cpp \
        main.cpp \
        rotationmotor.cpp

HEADERS += \
    device.hpp \
    rotationmotor.hpp
