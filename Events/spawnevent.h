#ifndef SPAWNEVENT_H
#define SPAWNEVENT_H

#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

class SpawnEvent: public entityx::Event<SpawnEvent>
{
public:
    SpawnEvent(int type,  glm::vec3 pos, glm::vec3 vel);

    enum{
        MINION
    };

    int type;
    glm::vec3 pos;
    glm::vec3 vel;
};

#endif // SPAWNEVENT_H
