TEMPLATE = app
CONFIG += console
CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
LIBS += -lGLEW  -lGL -lglfw
LIBS += -lassimp

SOURCES += main.cpp \
    program.cpp \
    AutisticGL/camera.cpp \
    AutisticGL/object.cpp \
    AutisticGL/container.cpp \
    AutisticGL/glmanager.cpp \
    AutisticGL/model.cpp \
    AutisticGL/shader.cpp \
    AutisticGL/shadingprogram.cpp \
    AutisticGL/skybox.cpp

HEADERS += \
    program.h \
    AutisticGL/camera.h \
    AutisticGL/object.h \
    AutisticGL/container.h \
    AutisticGL/glmanager.h \
    AutisticGL/model.h \
    AutisticGL/shader.h \
    AutisticGL/shadingprogram.h \
    AutisticGL/skybox.h

DISTFILES += \
    ../build-opengl2-Desktop-Release/shaders/texture_fragment_shader.frag \
    ../build-opengl2-Desktop-Release/shaders/texture_vertex_shader.vert
