#include "rendersystem.h"

RenderSystem::RenderSystem(sf::RenderWindow &win, agl::Camera &camera, glm::mat4& projection)
    :win(win), camera(camera), projection(projection)
{

}

void RenderSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, double dt)
{
    GLObjectComp::Handle obj;
    Position::Handle p;
    Rotation::Handle r;
    Scale::Handle scale;

    for(auto en : entities.entities_with_components(obj, p, r))
    {
        //std::cout<<"jest entit"<<std::endl;
//        if(en.has_component<Scale>()){
//            scale = en.component<Scale>();
//            obj->set_scale(scale->scale);
//        }

        obj->set_position(p->pos);
        obj->set_rotation(r->euler_rot);

        obj->render(camera.getMatrix(), projection);
    }
}
