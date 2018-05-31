#ifndef SPAWNSYSTEM_H
#define SPAWNSYSTEM_H

#include "Events/spawnevent.h"
#include "resourcemanager.h"
#include "Components/globjectcomp.h"
#include "Components/position.h"
#include "Components/rotation.h"
#include "Components/velocity.h"
#include "Components/angularvelcomp.h"
#include "Components/scale.h"
#include <iostream>

class SpawnSystem : public entityx::System<SpawnSystem>, public entityx::Receiver<SpawnSystem>
{
    entityx::EntityManager &entities;

public:
    SpawnSystem(entityx::EventManager & event, entityx::EntityManager &manager);
    void update(entityx::EntityManager &entities, entityx::EventManager &events, double dt);
    void receive(const SpawnEvent & event);
};

#endif // SPAWNSYSTEM_H
