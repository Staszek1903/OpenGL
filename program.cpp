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
{
    std::cout<<"debug"<<std::endl;
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

    // During init, enable debug output
//    glEnable              ( GL_DEBUG_OUTPUT );
//    glDebugMessageCallback( (GLDEBUGPROC) MessageCallback, 0 );


    cube_model.loadFromFile("./objects/skybox2.obj", true);
    tri_model.load_tetra();
    assert(her_model.loadFromFile("./objects/herub2.obj", true));
    assert(hersm_model.loadFromFile("./objects/herubin_smoth.obj", false ));
    obj.set_model(hersm_model);
    obj.set_shader(program);
    obj.move(glm::vec3(-3,0,10));
    obj2.set_model(cube_model);
    obj2.set_shader(program);
    obj2.move(glm::vec3(0,3,10));
    obj3.set_model(her_model);
    obj3.set_shader(tex_program);
    obj3.move(glm::vec3(3,0,10));

    her_tex.loadFromFile("./textures/herub2_tex.png");
    sky_tex.loadFromFile("./textures/canvas5.png");

    agl::Shader vs, fs;
    vs.load("./shaders/shader.vert", GL_VERTEX_SHADER);
    fs.load("./shaders/shader.frag", GL_FRAGMENT_SHADER);

    program.createProgram();
    program.attachShader(vs);
    program.attachShader(fs);
    program.link();
    program.detachShaders();
    
    program.setUniformEnum("light_vec",0);
    program.setUniformEnum("MVP", 1);
    program.setUniformEnum("rotate_mat",2);

    agl::Shader vs2, fs2;
    vs2.load("./shaders/tex_shader.vert", GL_VERTEX_SHADER);
    fs2.load("./shaders/tex_shader.frag", GL_FRAGMENT_SHADER);

    tex_program.createProgram();
    tex_program.attachShader(vs2);
    tex_program.attachShader(fs2);
    tex_program.link();
    tex_program.detachShaders();

    tex_program.setUniformEnum("light_vec",0);
    tex_program.setUniformEnum("MVP",1);
    tex_program.setUniformEnum("rotate_mat",2);
    tex_program.setUniformEnum("texture_samp",3);

    agl::Shader vs3, fs3;
    vs3.load("./shaders/sky_shader.vert", GL_VERTEX_SHADER);
    fs3.load("./shaders/sky_shader.frag", GL_FRAGMENT_SHADER);

    sky_program.createProgram();
    sky_program.attachShader(vs3);
    sky_program.attachShader(fs3);
    sky_program.link();
    sky_program.detachShaders();

    sky_program.setUniformEnum("MVP",1);
    sky_program.setUniformEnum("texture_samp",3);

    projection = glm::perspective(
                glm::radians(50.0f),                                    //FOV
                800.0f/600.0f,
                0.1f,                                                   //near clip
                100.0f);

    view = glm::lookAt(glm::vec3(0,0,0), glm::vec3(0,0,1), glm::vec3(0,1,0));
}

Program::~Program()
{}

void Program::run()
{
    while(win.isOpen())
    {
        //std::cout<<"RUn";
        input();
        update();
        render();
    }
}

void Program::input()
{
    static bool drag = false;
    static bool pan = false;

    sf::Event ev;
    while(win.pollEvent(ev))
    {
        if(ev.type == sf::Event::KeyPressed)
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
                obj.rotate(rot.x, glm::vec3(0,1,0));
                obj.rotate(rot.y, glm::vec3(1,0,0));
                obj2.rotate(rot.x, glm::vec3(0,1,0));
                obj2.rotate(rot.y, glm::vec3(1,0,0));
                obj3.rotate(rot.x, glm::vec3(0,1,0));
                obj3.rotate(rot.y, glm::vec3(1,0,0));

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

void Program::update()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        camera.moveAlongDirection(glm::vec3(-0.1,0,0));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        camera.moveAlongDirection(glm::vec3(0.1,0,0));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        camera.moveAlongDirection(glm::vec3(0,0.1,0));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        camera.moveAlongDirection(glm::vec3(0,-0.1,0));
}

void Program::render()
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sky_program.use();
    //std::cout<<sky_program.getID()<<std::endl;
    sky_program.setUniform(1, projection * camera.getRotationMatrix());// * obj2.getMatrix());
    sky_program.setUniform(3, 0);
    sf::Texture::bind(&sky_tex);
    sky_program.render(cube_model);

    glEnable(GL_DEPTH_TEST);

    program.use();
    program.setUniform(0,glm::vec3(0,0,1));
    program.setUniform(1, projection * camera.getMatrix() * obj.getMatrix());
    program.setUniform(2,obj.getRotationMatrix());
    program.render(hersm_model);

    tex_program.use();
    tex_program.setUniform(0,glm::vec3(0,0,1));
    tex_program.setUniform(1, projection * camera.getMatrix() * obj3.getMatrix());
    tex_program.setUniform(2, obj3.getRotationMatrix());
    tex_program.setUniform(3, 0);
    sf::Texture::bind(&her_tex);
    tex_program.render(her_model);

//    obj2.render(camera.getMatrix(), projection);
//    obj3.render(camera.getMatrix(), projection);


    win.display();
}
