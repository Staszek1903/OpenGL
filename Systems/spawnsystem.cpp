#include "spawnsystem.h"

SpawnSystem::SpawnSystem(entityx::EventManager &event, entityx::EntityManager & manager)
    :entities(manager)
{
    event.subscribe<SpawnEvent>(*this);
}

void SpawnSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, double dt)
{

}

void SpawnSystem::receive(const SpawnEvent &event)
{
    std::cout<<"spawn: "<<event.type<<std::endl;
    ResourceManager & resource = ResourceManager::get();

    auto en = entities.create();
    en.assign<GLObjectComp>(resource.contaiter.get_model("herubin_model"),
                            resource.contaiter.get_shader("tex_shader"),
                            resource.contaiter.get_texture("herubin_texture"));
    en.assign<Position>(event.pos);
    en.assign<Rotation>(glm::vec3());
    en.assign<Velocity>(event.vel);
    en.assign<AngularVelComp>(glm::vec3(1,0,0));
    en.assign<Scale>(0.25f);
}
