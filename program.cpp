#include "program.h"


Program::Program()
    :vertical_angle(0.0f), horizontal_angle(0.0f), graphic(1366.0f/768.0f, vertical_angle, horizontal_angle,
                                                           camera_pos, camera_direction)
{
    //opengl context init
    sf::ContextSettings context;
    context.depthBits = 24;
    context.stencilBits = 8;
    context.antialiasingLevel = 4;
    context.majorVersion = 3;
    context.minorVersion = 0;

    win.create(sf::VideoMode(1366,768), "opngl", sf::Style::Close | sf::Style::Fullscreen,  context);


    win.setVerticalSyncEnabled(true);
    win.setFramerateLimit(100);

    win.setActive(true);
}

void Program::run()
{
    while (win.isOpen())
    {
        input();
        update();
        render();
    }
}

void Program::input()
{
    static sf::Vector2f mouse_prev_pos(0,0);
    static bool camera_movement(false);

    sf::Event ev;
    while (win.pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
            win.close();
        if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
            win.close();
        else if( ev.type == sf::Event::MouseButtonPressed)
            camera_movement = true;
       // else if( ev.type == sf::Event::MouseButtonReleased)
         //   camera_movement = false;
        else if( ev.type == sf::Event::MouseMoved)
        {
            sf::Vector2f mouse_pos(ev.mouseMove.x, ev.mouseMove.y);
            sf::Vector2f d(mouse_pos - mouse_prev_pos);

            if(camera_movement)
            {
                horizontal_angle += (d.x/200);
                vertical_angle += (d.y/200);
            }

            mouse_prev_pos = mouse_pos;
        }
    }

    const glm::vec4 right(
                glm::sin(horizontal_angle - glm::radians(90.0f)),
                0.0f,
                glm::cos(horizontal_angle - glm::radians(90.0f)),
                1.0f);

    const glm::vec4 up(glm::cross(glm::vec3(right.x, right.y, right.z),
                                         glm::vec3(camera_direction.x, camera_direction.y,  camera_direction.z)), 1.0f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        camera_pos +=  camera_direction/10.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        camera_pos -=  camera_direction /10.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        camera_pos -=  (right/10.0f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        camera_pos +=  (right/10.0f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        camera_pos +=  (up/10.0f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        camera_pos -=  (up/10.0f);
}

void Program::update()
{

}

void Program::render()
{
    graphic.draw();
    win.display();
}
