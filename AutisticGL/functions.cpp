#include "functions.h"

void agl::init_GL_context(sf::RenderWindow &win)
{
    sf::ContextSettings settings;

    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    win.create(sf::VideoMode(800,600), "tytul", sf::Style::Close, settings);
    std::cout<<"otworzono okno"<<std::endl;

    win.setVerticalSyncEnabled(true);
    win.setFramerateLimit(100);

    win.setActive(true);

    glewInit();
    std::cout<<"GL_VERSION: \""<<glGetString(GL_VERSION)<<"\""<<std::endl;
}
