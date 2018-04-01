#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <AutisticGL/gl_headers.h>

#include "AutisticGL/shader.h"
#include "AutisticGL/shadingprogram.h"
#include "AutisticGL/model.h"
#include "AutisticGL/object.h"
#include "AutisticGL/camera.h"

class Program
{
    sf::RenderWindow win;

    agl::ShadingProgram program, tex_program, sky_program;

    agl::Model cube_model, tri_model, her_model, hersm_model;
    sf::Texture her_tex, sky_tex;
    agl::Object obj, obj2, obj3;
    agl::Camera camera;


    glm::vec2 mousePos;
    glm::mat4 view, projection;
public:
    explicit Program();
    ~Program();

    void run();

private:
    void input();
    void update();
    void render();
};

#endif // PROGRAM_H
