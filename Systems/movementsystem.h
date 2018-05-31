#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include <entityx/entityx.h>
#include <Components/position.h>
#include <Components/velocity.h>
#include <Components/rotation.h>
#include <Components/angularvelcomp.h>

class MovementSystem    : public entityx::System<MovementSystem>
{
public:
    MovementSystem();

    void update(entityx::EntityManager &entities, entityx::EventManager &events, double dt);
};

#endif // MOVEMENTSYSTEM_H
