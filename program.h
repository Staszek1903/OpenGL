#ifndef PROGRAM_H
#define PROGRAM_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <graphiclib.h>

class Program
{
    sf::RenderWindow win;

    //opnGL nauka

    float vertical_angle, horizontal_angle;
    glm::vec4 camera_pos,
        camera_direction;

    GraphicLib graphic;

public:
    Program();
    void run();

private:
    void input();
    void update();
    void render();

};

#endif // PROGRAM_H
