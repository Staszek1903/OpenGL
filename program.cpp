#include "program.h"


void MessageCallback( GLenum source,
                      GLenum type,
                      GLuint id,
                      GLenum severity,
                      GLsizei length,
                      const GLchar* message,
                      const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x\n, severity = 0x%x\n, message = %s\n\n\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "   OK   " ),
            type, severity, message );
}

Program::Program()
    :game(camera)
{
    // During init, enable debug output
    //    glEnable              ( GL_DEBUG_OUTPUT );
    //    glDebugMessageCallback( (GLDEBUGPROC) MessageCallback, 0 );

    game.init();
}

Program::~Program()
{
    ResourceManager::release();
}

void Program::run()
{
    sf::RenderWindow & win = ResourceManager::get().window;
    while(win.isOpen())
    {
        //std::cout<<"RUn";
        input();

        time += clock.restart();
        while(time > sf::seconds(0.01)){
            update(0.01);
            time -= sf::seconds(0.01);
        }
        render();
    }
}

void Program::input()
{
    sf::RenderWindow & win = ResourceManager::get().window;

    static bool drag = false;
    static bool pan = false;

    sf::Event ev;
    while(win.pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
            win.close();
        else if(ev.type == sf::Event::KeyPressed)
        {
            if(ev.key.code == sf::Keyboard::LAlt)
                win.close();
        }
        else if(ev.type == sf::Event::MouseMoved)
        {
            glm::vec2 temp(ev.mouseMove.x, 600.0f - ev.mouseMove.y);
            glm::vec2 rot = temp - mousePos;
            rot /= 100.0f;

            if(drag)
            {    


            }
            else if(pan)
            {
                camera.rotate(rot.y,rot.x);
            }
            mousePos.x = (float)ev.mouseMove.x;
            mousePos.y = 600.0f - (float)ev.mouseMove.y;


        }
        else if(ev.type == sf::Event::MouseButtonPressed)
        {
            if(ev.mouseButton.button == sf::Mouse::Left)
                drag = true;
            else
                pan = true;
        }
        else if(ev.type == sf::Event::MouseButtonReleased)
        {
            if(ev.mouseButton.button == sf::Mouse::Left)
                drag = false;
            else
                pan = false;
        }
    }
}

void Program::update(double dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        camera.moveAlongDirection(glm::vec3(-0.1,0,0));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        camera.moveAlongDirection(glm::vec3(0.1,0,0));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        camera.moveAlongDirection(glm::vec3(0,0.1,0));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        camera.moveAlongDirection(glm::vec3(0,-0.1,0));

    game.update(dt);
}

void Program::render()
{
    game.render();
}
