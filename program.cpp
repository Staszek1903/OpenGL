#include "program.h"

Program::Program()
    :gl_manager(camera)
{
    std::cout<<"good ratio: "<<(1366.0f/768.0f)<<std::endl;
    gl_manager.create_window(win);
    gl_manager.init(1366.0f/768.0f);

    agl::Shader v_shader, f_shader;
    v_shader.load("./shaders/texture_vertex_shader.vert", GL_VERTEX_SHADER);
    f_shader.load("./shaders/texture_fragment_shader.frag", GL_FRAGMENT_SHADER);

    shading_program.createProgram();
    shading_program.attachShader(v_shader);
    shading_program.attachShader(f_shader);
    shading_program.link();
    shading_program.detachShaders();

    std::string uniform_names[static_cast<int> (agl::Uniforms::UIFORMS_COUT)] =
    {
        "MVP",
        "M",
        "M_rot",
        "LightPos"
        "CameraPos",
        "myTextureSampler"
    };

    for(int e = static_cast<int>(agl::Uniforms::MVP); e<static_cast<int>(agl::Uniforms::UIFORMS_COUT); ++e)
            shading_program.setUniformEnum(uniform_names[e],e);

    model.loadFromOBJ("./objects/star_monkey.obj");
    texture.loadFromFile("./textures/star.jpg");

    herubin_model.loadFromOBJ("./objects/Herubin.obj");
    herubin_texture.loadFromFile("./textures/Herubin.png");

    obj.setModel(model);
    obj.setShader(shading_program);
    obj.setTexture(texture);

    glm::vec3 offset(2.0f,0.0f,4.0f);
    obj.move(offset);
    obj.rotate(0.0f,3.14f);
    herubin.setScale(0.7);

    herubin.setModel(herubin_model);
    herubin.setTexture(herubin_texture);
    herubin.setShader(shading_program);
    herubin.move(glm::vec3(0.0f,0.0f, 8.0f));

    obj.printBufferID();
    herubin.printBufferID();

    //std::string_view test;
}


void Program::run()
{
    while(win.isOpen())
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
        static bool model_movement(false);

        sf::Event ev;
        while (win.pollEvent(ev))
        {
            if(ev.type == sf::Event::Closed)
                win.close();
            if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
                win.close();
            else if( ev.type == sf::Event::MouseButtonPressed)
            {
                if(ev.mouseButton.button == sf::Mouse::Left)
                    camera_movement = true;
                else
                    model_movement = true;
            }
            else if( ev.type == sf::Event::MouseButtonReleased)
            {
                if(ev.mouseButton.button == sf::Mouse::Left)
                    camera_movement = false;
                else
                    model_movement = false;
            }
            else if( ev.type == sf::Event::MouseMoved)
            {
                sf::Vector2f mouse_pos(ev.mouseMove.x, ev.mouseMove.y);
                sf::Vector2f d(mouse_pos - mouse_prev_pos);

                if(camera_movement)
                {
                    camera.rotate(d.y/200, d.x/200);
                }
                if(model_movement)
                {
//                    model_horizontal_angle += (d.x/200);
//                    model_vertical_angle += (d.y/200);
//                    std::cout<<"model: "<< model_horizontal_angle<<" "<<model_vertical_angle<<std::endl;
                }

                mouse_prev_pos = mouse_pos;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            camera.moveAlongDirection(glm::vec3(0.1f,0.0f,0.0f));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            camera.moveAlongDirection(glm::vec3(-0.1f,0.0f,0.0f));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            camera.moveAlongDirection(glm::vec3(0.0f,-0.1f,0.0f));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            camera.moveAlongDirection(glm::vec3(0.0f,0.1f,0.0f));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            camera.moveAlongDirection(glm::vec3(0.0f,0.0f,0.1f));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            camera.moveAlongDirection(glm::vec3(0.0f,0.0f,-0.1f));

}

void Program::update()
{
    herubin.rotate(0.01f,0.01f);
}

void Program::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gl_manager.render_skybox();
    gl_manager.reder_obj(obj);
    gl_manager.reder_obj(herubin);
    win.display();
}
