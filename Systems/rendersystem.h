#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>
#include "Components/modelcomp.h"
#include "Components/shadercomp.h"
#include "Components/texturecomp.h"
#include "Components/position.h"
#include "Components/rotation.h"
#include "AutisticGL/object.h"
#include "AutisticGL/camera.h"

class RenderSystem : public entityx::System<RenderSystem>
{
    sf::RenderWindow &win;
    glm::mat4 &projection;
    agl::Camera &camera;

public:
    RenderSystem(sf::RenderWindow &win, agl::Camera &camera, glm::mat4& projection);

    void update(entityx::EntityManager &entities, entityx::EventManager &events, double dt);
};

#endif // RENDERSYSTEM_H
