#ifndef PROGRAM_H
#define PROGRAM_H

#include <SFML/Graphics.hpp>
#include "AutisticGL/glmanager.h"
#include "AutisticGL/camera.h"
#include "AutisticGL/shadingprogram.h"

//#include <string_view>

class Program
{    
public:
    Program();

    void run();

private:
    sf::RenderWindow win;
    agl::GLManager gl_manager;
    agl::Camera camera;
    agl::Model model, herubin_model;
    agl::ShadingProgram shading_program;
    sf::Texture texture, herubin_texture;
    agl::Object obj, herubin;

    void input();
    void update();
    void render();
};

#endif // PROGRAM_H
