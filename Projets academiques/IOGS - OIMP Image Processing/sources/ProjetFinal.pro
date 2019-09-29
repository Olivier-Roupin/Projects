#-------------------------------------------------
#
# Project created by QtCreator 2016-11-24T15:24:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjetFinal
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    binarize.cpp \
    convolutionmask.cpp \
    image.cpp \
    inverse.cpp \
    layer.cpp \
    operation.cpp \
    pipelineoperation.cpp \
    rgb2grayscale.cpp \
    scale.cpp \
    rotation.cpp \
    rgb2hsl.cpp \
    hsl2rgb.cpp \
    colorshift.cpp \
    colorpick.cpp \
    colorpicknshift.cpp \
    histogram.cpp \
    etalement.cpp \
    egalisation.cpp \
    convolution.cpp \
    sobelfilter.cpp

HEADERS  += mainwindow.h \
    binarize.h \
    convolutionmask.h \
    image.h \
    inverse.h \
    layer.h \
    operation.h \
    pipelineoperation.h \
    rgb2grayscale.h \
    scale.h \
    rotation.h \
    rgb2hsl.h \
    hsl2rgb.h \
    colorshift.h \
    colorpick.h \
    colorpicknshift.h \
    histogram.h \
    etalement.h \
    egalisation.h \
    convolution.h \
    sobelfilter.h

FORMS    += mainwindow.ui
