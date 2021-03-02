TEMPLATE = app
TARGET = qml_test
CONFIG += warn_on qmltestcase

QT += quick charts concurrent

SOURCES += \
    testcontroller.cpp \
    tst_repetitions.cpp

HEADERS += \
    testcontroller.h

DISTFILES += \
    tst_repetitions.qml
