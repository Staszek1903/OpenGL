#ifndef GAME_H
#define GAME_H

#include <entityx/entityx.h>
#include "resourcemanager.h"
#include "Systems/rendersystem.h"
#include "AutisticGL/camera.h"

class Game : public entityx::EntityX
{
    glm::mat4 projection;
    agl::Camera & camera;
public:
    Game(agl::Camera & camera);
    void init();
    void update();
    void render();

private:
    void new_entit(std::string model, std::string shader, std::string texture, glm::vec3 position);
};

#endif // GAME_H
