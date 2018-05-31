#include "game.h"

Game::Game(agl::Camera &camera)
    :camera(camera)
{

}

void Game::init()
{
    projection = glm::perspective(
                glm::radians(50.0f),                                    //FOV
                800.0f/600.0f,
                0.1f,                                                   //near clip
                100.0f);

    ResourceManager & resource = ResourceManager::get();
    systems.add<RenderSystem>(resource.window, camera, projection);
    systems.add<SpawnSystem>(events, entities);
    systems.add<MovementSystem>();

    systems.configure();

    new_entit("skybox_model","tex_shader","herubin_texture", glm::vec3(1,0,4));
    new_entit("herubin_model", "tex_shader", "herubin_texture", glm::vec3(1,0,7));
    new_entit("herubin_sm_model", "shader", "herubin_texture", glm::vec3(6,0,7));

    events.emit<SpawnEvent>(SpawnEvent::MINION, glm::vec3(0,0,10), glm::vec3(0,1,0));

}

void Game::update(double dt)
{
    systems.update<SpawnSystem>(dt);
    systems.update<MovementSystem>(dt);
}

void Game::render()
{
    sf::RenderWindow & win = ResourceManager::get().window;
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    agl::ShadingProgram &sky_program = ResourceManager::get().contaiter.get_shader("sky_shader");

    sky_program.use();
    sky_program.setUniform(1, projection * camera.getRotationMatrix());
    sky_program.setUniform(3, 0);
    sf::Texture::bind(&(ResourceManager::get().contaiter.get_texture("skybox_texture")));
    sky_program.render(ResourceManager::get().contaiter.get_model("skybox_model"));

    glEnable(GL_DEPTH_TEST);
//test
    agl::Model * model = &(ResourceManager::get().contaiter.get_model("herubin_model"));
    sf::Texture & texture = ResourceManager::get().contaiter.get_texture("herubin_texture");
    agl::ShadingProgram * program = &(ResourceManager::get().contaiter.get_shader("tex_shader"));




    program->use();
    program->setUniform(0, glm::vec3(0,1,0));
    program->setUniform(1, projection * camera.getMatrix());
    program->setUniform(2, camera.getRotationMatrix());

    if(model->is_textured()){
        program->setUniform(3, 0);
        sf::Texture::bind(&texture);
    }

    program->render(*model);




    agl::Object obj;
    obj.set_model(ResourceManager::get().contaiter.get_model("herubin_sm_model"));
    obj.set_shader(ResourceManager::get().contaiter.get_shader("shader"));
    //obj.set_texture(ResourceManager::get().contaiter.get_texture("herubin_texture"));
    obj.render(camera.getMatrix(), projection);

    //systems.update<RenderSystem>(0);

    win.display();
}

void Game::new_entit(std::string model, std::string shader, std::string texture, glm::vec3 position)
{
    ResourceManager & resource = ResourceManager::get();

    auto en = entities.create();
    en.assign<GLObjectComp>(resource.contaiter.get_model(model),
                            resource.contaiter.get_shader(shader),
                            resource.contaiter.get_texture(texture));
    en.assign<Position>(position);
    en.assign<Rotation>(glm::vec3());
}
