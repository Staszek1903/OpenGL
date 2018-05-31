#ifndef VELOCITY_H
#define VELOCITY_H

#include <entityx/entityx.h>
#include <glm/glm.hpp>

struct Velocity : public entityx::Component<Velocity>
{
public:
    Velocity(glm::vec3 vel)
        :vel(vel){}
    glm::vec3 vel;
};

#endif // VELOCITY_H
