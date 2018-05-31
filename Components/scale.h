#ifndef SCALE_H
#define SCALE_H

#include <entityx/entityx.h>
#include <glm/glm.hpp>

struct Scale : public entityx::Component<Scale>
{
    Scale(glm::vec3 scale)
        :scale(scale){}
    Scale(float scale)
        :scale(scale,scale,scale){}

    glm::vec3 scale;
};

#endif // SCALE_H
