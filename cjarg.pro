TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
#win32:QMAKE_LFLAGS += -shared

SOURCES += main.cpp \
    gamewindow.cpp \
    logic/map/sector.cpp \
    logic/map/block.cpp \
    logic/map/level.cpp \
    logic/map/levelworker.cpp \
    logic/map/point.cpp \
    ui/wins.cpp \
    ui/win.cpp \
    logic/base/database.cpp \
    logic/map/trivialgenerator.cpp \
    logic/entity/creature.cpp \
    logic/agents/agent.cpp \
    logic/agents/chest.cpp \
    logic/agents/gamepart.cpp \
    logic/entity/item.cpp \
    sge/basicjargshader.cpp \
    sge/colorextender.cpp \
    sge/cube.cpp \
    sge/font.cpp \
    sge/fpscounter.cpp \
    sge/gametimer.cpp \
    sge/helper.inl \
    sge/icosahedron.cpp \
    sge/keyboard.cpp \
    sge/logger.cpp \
    sge/material.cpp \
    sge/mesh.cpp \
    sge/mouse.cpp \
    sge/pixmap.cpp \
    sge/prefecences.cpp \
    sge/shader.cpp \
    sge/singleton.cpp \
    sge/SphereTesselator.cpp \
    sge/spritebatch.cpp \
    sge/texture.cpp \
    sge/textureatlas.cpp \
    sge/vpnt.cpp \
    sge/json/json_internalarray.inl \
    sge/json/json_internalmap.inl \
    sge/json/json_reader.cpp \
    sge/json/json_value.cpp \
    sge/json/json_valueiterator.inl \
    sge/json/json_writer.cpp \
    sge/lodepng/lodepng.cpp \
    sge/camera.cpp \
    sge/ClassicNoise.cpp \
    logic/agents/staticitem.cpp \
    logic/map/staticblock.cpp

HEADERS += \
    gamewindow.h \
    jsonparser.h \
    logic/map/*.h \
    ui/*.h \
    logic/base/database.h \
    logic/map/diamondsquare.h \
    logic/map/trivialgenerator.h \
    logic/entity/creature.h \
    logic/agents/agent.h \
    logic/agents/chest.h \
    logic/agents/gamepart.h \
    logic/entity/item.h \
    sge/*.h \
    sge/json/autolink.h \
    sge/json/config.h \
    sge/json/features.h \
    sge/json/forwards.h \
    sge/json/json.h \
    sge/json/json_batchallocator.h \
    sge/json/reader.h \
    sge/json/value.h \
    sge/json/writer.h \
    sge/lodepng/lodepng.h \
    sge/utfcpp/utf8.h \
    sge/utfcpp/utf8/checked.h \
    sge/utfcpp/utf8/core.h \
    sge/utfcpp/utf8/unchecked.h \
    sge/sge_geometry.h \
    sge/camera.h \
    sge/ClassicNoise.h \
    logic/agents/staticitem.h \
    logic/map/staticblock.h



win32:LIBS += -L$$PWD/3rdparty/lib/ -lopengl32 -lglew32 -lglfw3dll -lfreetype
unix:LIBS += -lGL -lGLEW -lglfw3 -lfreetype -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -lXcursor -lXinerama
unix:INCLUDEPATH += /usr/include/freetype2
INCLUDEPATH += $$PWD

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
    data/textures/wearpolka4.png \
    data/fonts/DejaVuSansMono.ttf

OTHER_FILES += \
    README.md \
    data/json/test_recipe.json \
    data/json/basic.json \
    data/json/aaa.json \
    data/json/error.json \
    data/shaders/minimal.glsl \
    data/textures/asfalt.png \
    data/textures/dirt1.png \
    data/textures/grass1.png \
    data/textures/asfalt_br.png \
    data/textures/grass5.png \
    data/textures/grass2.png \
    data/textures/grass3.png \
    data/textures/grass4.png \
    data/textures/grass6.png \
    data/textures/grass7.png \
    data/textures/conk1.png \
    data/shaders/normal.glsl \
    data/textures/grass_m.png

SUBDIRS += \
    sge/sge.pro \
    sge/json/json.pro
