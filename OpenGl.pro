TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
CONFIG(release, debug|release): LIBS += -L/home/patryk/entityx-build -lentityx

LIBS +=-lGLEW -lglfw -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread
LIBS += -lGLU

SOURCES += main.cpp \
    program.cpp \
    graphiclib.cpp \
    loaders/loadbmp.cpp \
    loaders/load_shaders.cpp \
    loaders/load_obj.cpp

HEADERS += \
    program.h \
    gl_headers.h \
    graphiclib.h \
    buffers.h \
    loaders/loadbmp.h \
    loaders/load_shaders.h \
    loaders/load_obj.h

DISTFILES += \
    shaders/colour_fragment_shader.frag \
    shaders/colour_vertex_shader.vert \
    shaders/texture_fragment_shader.frag \
    shaders/texture_vertex_shader.vert
