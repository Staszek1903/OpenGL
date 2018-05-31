#include "movementsystem.h"

MovementSystem::MovementSystem()
{

}

void MovementSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, double dt)
{
    Position::Handle pos;
    Rotation::Handle rot;

    Velocity::Handle vel;
    AngularVelComp::Handle angvel;

    for(auto en : entities.entities_with_components(pos, vel, rot, angvel)){
        pos->pos += vel->vel * static_cast<float> (dt);
        rot->euler_rot += angvel->euler *static_cast<float>(dt);
        std::cout<<"ent"<<std::endl;
    }
}
