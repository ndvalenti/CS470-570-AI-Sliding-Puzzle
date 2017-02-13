QT += core
QT -= gui

CONFIG += c++11

TARGET = AI_SlidingPuzzle_1
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    slideboard.cpp \
    search.cpp

HEADERS += slideboard.h \
    search.h
