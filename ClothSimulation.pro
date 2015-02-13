QT       += core gui opengl widgets declarative

TARGET   = SpaceRocketGraphics
TEMPLATE = app


SOURCES += main.cpp\
    glwidget.cpp \
    window.cpp \
    particle.cpp \
    spring.cpp \
    cloth.cpp \
    object.cpp


HEADERS  += \
    glwidget.h \
    window.h \
    ui_MainWindow.h \
    particle.h \
    spring.h \
    Utilities.h \
    cloth.h \
    object.h

#FORMS    +=
QT += widgets

