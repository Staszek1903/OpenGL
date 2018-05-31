#ifndef ANGULARVELCOMP_H
#define ANGULARVELCOMP_H

#include <entityx/entityx.h>
#include <glm/glm.hpp>

struct AngularVelComp : public entityx::Component<AngularVelComp>
{
public:
    AngularVelComp(glm::vec3 euler):
        euler(euler){}
    glm::vec3 euler;
};

#endif // ANGULARVELCOMP_H
