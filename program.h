#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <AutisticGL/gl_headers.h>

#include "AutisticGL/functions.h"
#include "AutisticGL/shader.h"
#include "AutisticGL/shadingprogram.h"
#include "AutisticGL/model.h"
#include "AutisticGL/object.h"
#include "AutisticGL/camera.h"

#include "resourcemanager.h"
#include "game.h"


class Program
{
    agl::Camera camera;
    glm::vec2 mousePos;
    Game game;

    sf::Clock clock;
    sf::Time time;

public:
    explicit Program();
    ~Program();

    void run();

private:
    void input();
    void update(double dt);
    void render();
};

#endif // PROGRAM_H
