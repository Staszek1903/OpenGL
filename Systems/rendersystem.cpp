#include "rendersystem.h"

RenderSystem::RenderSystem(sf::RenderWindow &win, agl::Camera &camera, glm::mat4& projection)
    :win(win), camera(camera), projection(projection)
{

}

void RenderSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, double dt)
{
    ModelComp::Handle m;
    TextureComp::Handle t;
    ShaderComp::Handle s;
    Position::Handle p;
    Rotation::Handle r;

    agl::Object obj;

    for(auto en : entities.entities_with_components(m,t,s,p,r))
    {
        std::cout<<"jest entit"<<std::endl;
        obj.set_model(m->model);
        obj.set_shader(s->shader);
        obj.set_texture(t->texture);
        obj.move(p->pos);
        obj.rotate(r->euler_rot);

        obj.render(camera.getMatrix(), projection);
    }
}
