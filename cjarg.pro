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
    settings.cpp \
    jtexture.cpp \
    spritebatch.cpp \
    gametimer.cpp \
    fpscounter.cpp \
    jsonparser.cpp \
    framebuffer.cpp \
    jargshader.cpp \
    texturegenerator.cpp \
    win.cpp \
    ui_wins.cpp \
    json/json_internalarray.inl \
    json/json_internalmap.inl \
    json/json_valueiterator.inl \
    json/json_reader.cpp \
    json/json_value.cpp \
    json/json_writer.cpp \
    lodepng/lodepng.cpp \
    pixmap.cpp \
    textureatlas.cpp \
    jhelper.inl \
    logic/map/sector.cpp \
    logic/map/block.cpp \
    logic/map/level.cpp \
    logic/map/levelworker.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    gamewindow.h \
    mouse.h \
    keyboard.h \
    logger.h \
    settings.h \
    jtexture.h \
    spritebatch.h \
    gametimer.h \
    fpscounter.h \
    jsonparser.h \
    ui_wins.h \
    ui_component.h \
    ui_win.h \
    texturegenerator.h \
    colorextender.h \
    framebuffer.h \
    jargshader.h \
    json/*.h \
    lodepng/lodepng.h \
    pixmap.h \
    textureatlas.h \
    fielsystem.h \
    logic/map/sector.h \
    logic/map/block.h \
    logic/map/level.h \
    logic/map/levelworker.h



win32:LIBS += -L$$PWD/3rdparty/lib/ -lopengl32 -lglew32 -lglfw3dll -lfreetype
unix:LIBS += -lGL -lGLEW -lglfw3 -lfreetype -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ljson_linux-gcc-4.8_libmt
unix:INCLUDEPATH += /usr/include/freetype2

win32:INCLUDEPATH += $$PWD/3rdparty/include
win32:DEPENDPATH += $$PWD/3rdparty/include

DISTFILES += \
    data/shaders/basic.glsl \
    data/shaders/font.glsl \
    data/fonts/Inconsolata.otf \
    data/shaders/color.glsl \
    data/textures/bath1.png \
    data/textures/bath2.png \
    data/textures/bath3.png \
    data/textures/bath4.png \
    data/textures/bath5.png \
    data/textures/bed1.png \
    data/textures/bed2.png \
    data/textures/bed3.png \
    data/textures/bed4.png \
    data/textures/bed5.png \
    data/textures/bochka.png \
    data/textures/briwall1.png \
    data/textures/bush1.png \
    data/textures/chair1.png \
    data/textures/cone1.png \
    data/textures/cone2.png \
    data/textures/crates1.png \
    data/textures/crates2.png \
    data/textures/crates3.png \
    data/textures/cvet.png \
    data/textures/cvet1.png \
    data/textures/cvet2.png \
    data/textures/cvet3.png \
    data/textures/door1.png \
    data/textures/door1_open.png \
    data/textures/door2.png \
    data/textures/door2_open.png \
    data/textures/door3.png \
    data/textures/door4.png \
    data/textures/error.png \
    data/textures/fence_s.png \
    data/textures/fence_s1.png \
    data/textures/fence_s2.png \
    data/textures/fence_w.png \
    data/textures/fence_w1.png \
    data/textures/fence_w2.png \
    data/textures/foodpolka.png \
    data/textures/foodpolka1.png \
    data/textures/foodpolka2.png \
    data/textures/foodpolka3.png \
    data/textures/foodpolka4.png \
    data/textures/fridge1.png \
    data/textures/fridge2.png \
    data/textures/glass_hor.png \
    data/textures/glass_ver.png \
    data/textures/heater.png \
    data/textures/liqpolka.png \
    data/textures/liqpolka1.png \
    data/textures/liqpolka2.png \
    data/textures/liqpolka3.png \
    data/textures/mbush1.png \
    data/textures/mbush2.png \
    data/textures/mbush3.png \
    data/textures/medpolka.png \
    data/textures/medpolka1.png \
    data/textures/medpolka2.png \
    data/textures/medpolka3.png \
    data/textures/medpolka4.png \
    data/textures/none.png \
    data/textures/notex.png \
    data/textures/palka.png \
    data/textures/plita.png \
    data/textures/rakovina.png \
    data/textures/rakovina2.png \
    data/textures/rakovina3.png \
    data/textures/rakovina4.png \
    data/textures/rock1.png \
    data/textures/rock2.png \
    data/textures/rock3.png \
    data/textures/rock4.png \
    data/textures/s1console1.png \
    data/textures/s1console2.png \
    data/textures/s1console3.png \
    data/textures/s1console4.png \
    data/textures/s1console5.png \
    data/textures/s1console6.png \
    data/textures/s1console7.png \
    data/textures/s1console8.png \
    data/textures/s1console9.png \
    data/textures/s1console10.png \
    data/textures/s1console11.png \
    data/textures/s1console12.png \
    data/textures/s1console13.png \
    data/textures/s1console14.png \
    data/textures/s1console15.png \
    data/textures/s1console16.png \
    data/textures/s1console17.png \
    data/textures/s1console18.png \
    data/textures/safe1.png \
    data/textures/safe2.png \
    data/textures/shkaf.png \
    data/textures/shkaf2.png \
    data/textures/shkaf3.png \
    data/textures/steelwall1.png \
    data/textures/steelwall2.png \
    data/textures/steelwall3.png \
    data/textures/steelwall4.png \
    data/textures/steelwall5.png \
    data/textures/steelwall6.png \
    data/textures/table_hor_left.png \
    data/textures/table_hor_mid.png \
    data/textures/table_hor_right.png \
    data/textures/table1.png \
    data/textures/trashcan.png \
    data/textures/trashcan1.png \
    data/textures/tree1.png \
    data/textures/tree2.png \
    data/textures/tumba1.png \
    data/textures/tumba2.png \
    data/textures/washer.png \
    data/textures/wearpolka.png \
    data/textures/wearpolka1.png \
    data/textures/wearpolka2.png \
    data/textures/wearpolka3.png \
    data/textures/wearpolka4.png

OTHER_FILES += \
    README.md \
    data/json/test_recipe.json \
    data/json/basic.json \
    data/json/aaa.json \
    data/json/error.json
