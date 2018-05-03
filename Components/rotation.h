#ifndef ROTATION_H
#define ROTATION_H

#include <entityx/entityx.h>
#include <glm/glm.hpp>

struct Rotation : public entityx::Component<Rotation>
{
    Rotation(glm::vec3 euler_rot)
        :euler_rot(euler_rot){}
    glm::vec3 euler_rot;
};

#endif // ROTATION_H
