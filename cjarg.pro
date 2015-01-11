TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
#win32:QMAKE_LFLAGS += -shared

SOURCES += main.cpp \
    gamewindow.cpp \
    mouse.cpp \
    logger.cpp \
    keyboard.cpp \
    jargShader.cpp \
    settings.cpp \
    jtexture.cpp \
    spritebatch.cpp \
    FrameBuffer.cpp \
    TextureGenerator.cpp \
    Win.cpp \
    WinS.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    gamewindow.h \
    mouse.h \
    keyboard.h \
    logger.h \
    colorExtender.h \
    jargShader.h \
    settings.h \
    jtexture.h \
    spritebatch.h \
    FrameBuffer.h \
    TextureGenerator.h \
    WComponent.h \
    Win.h \
    WinS.h



win32:LIBS += -L$$PWD/3rdparty/lib/ -lglew32 -lglfw3dll -lfreetype
LIBS += -lopengl32
unix:LIBS += -lglew32 -lglfw3dll -lfreetype

win32:INCLUDEPATH += $$PWD/3rdparty/include
win32:DEPENDPATH += $$PWD/3rdparty/include

DISTFILES += \
    data/shaders/basic.glsl \
    data/shaders/font.glsl \
    data/fonts/Inconsolata.otf \
    data/shaders/color.glsl
