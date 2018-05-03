#ifndef POSITION_H
#define POSITION_H

#include <entityx/entityx.h>
#include <glm/glm.hpp>

struct Position : public entityx::Component<Position>
{
    Position(glm::vec3 pos)
        :pos(pos){}
    glm::vec3 pos;
};

#endif // POSITION_H
