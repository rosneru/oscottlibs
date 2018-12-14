TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wconversion -Wextra -pedantic #-Weffc++

LIBS += -lncurses \
        -lboost_unit_test_framework \

INCLUDEPATH +=  ../

SOURCES += \
    OscottLibs_test.cpp \
    ../LinkedList.cpp \
    ../LinkedListNode.cpp \
    ../SimpleString.cpp

HEADERS += \
    ../LinkedList.h \
    ../LinkedListNode.h \
    ../SimpleString.h \
    ../Array.h
