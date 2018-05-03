TEMPLATE = app
CONFIG += console
CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
LIBS += -lGLEW  -lGL -lglfw
LIBS += -lassimp
LIBS += -lentityx

SOURCES += main.cpp \
    program.cpp \
    AutisticGL/buffer.cpp \
    AutisticGL/camera.cpp \
    AutisticGL/object.cpp \
    AutisticGL/model.cpp \
    AutisticGL/shader.cpp \
    AutisticGL/shadingprogram.cpp \
    AutisticGL/container.cpp \
    resourcemanager.cpp \
    AutisticGL/functions.cpp \
    game.cpp \
    Systems/rendersystem.cpp

HEADERS += \
    program.h \
    AutisticGL/buffer.h\
    AutisticGL/camera.h \
    AutisticGL/gl_headers.h\
    AutisticGL/object.h \
    AutisticGL/model.h \
    AutisticGL/shader.h \
    AutisticGL/shadingprogram.h \
    AutisticGL/simple_meshes.h \
    AutisticGL/container.h \
    resourcemanager.h \
    AutisticGL/functions.h \
    game.h \
    Systems/rendersystem.h \
    Components/position.h \
    Components/modelcomp.h \
    Components/shadercomp.h \
    Components/texturecomp.h \
    Components/rotation.h

DISTFILES += \
    ../build-opengl2-Desktop-Release/shaders/texture_fragment_shader.frag \
    ../build-opengl2-Desktop-Release/shaders/texture_vertex_shader.vert \
    ../../opengl3/build-opengl3-Desktop-Debug/shaders/sky_shader.frag \
    ../../opengl3/build-opengl3-Desktop-Debug/shaders/sky_shader.vert
