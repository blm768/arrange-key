QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = arrange-key
TEMPLATE = app

# TODO: use CONFIG += c++17 once qmake supports it.
QMAKE_CXXFLAGS += -std=c++17
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        compose_parser.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        compose_parser.h \
        mainwindow.h

FORMS += \
        mainwindow.ui
