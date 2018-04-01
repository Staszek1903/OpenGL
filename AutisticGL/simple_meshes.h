#ifndef SIMPLE_MESHES_H
#define SIMPLE_MESHES_H

#include "AutisticGL/gl_headers.h"

namespace agl {


static const glm::vec3 triangle_v[] = {
   {-1.0f, -1.0f, -1.0f},
   {1.0f, -1.0f, -1.0f},
   {0.0f,  1.0f, 0.0f},
    {0.0f,  -1.0f, 1.0f}
};

static const glm::vec3 triangle_c [] =
{{1.0f,0.0f,0.0f},
{0.0f,1.0f,0.0f},
{0.0f,0.0f,1.0f},
{0.0f,0.0f,1.0f}};

static const unsigned short triangle_e [] =
{
    2,1,0, 0,1,3, 1,2,3, 3,2,0
};

static const glm::vec3 cube_v [] =
{
    {-1.0f, 1.0f, -1.0f},
    {1.0f,  1.0f, -1.0f},
    {1.0f, -1.0f, -1.0f},
    {-1.0f,-1.0f, -1.0f},

    {-1.0f, 1.0f, 1.0f},
    {1.0f,  1.0f, 1.0f},
    {1.0f, -1.0f, 1.0f},
    {-1.0f,-1.0f, 1.0f}
};


static const glm::vec3 cube_c [] =
{
    {0.0f, 1.0f, 0.0f},
    {1.0f,  1.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {0.0f,0.0f, 0.0f},

    {0.0f, 1.0f, 1.0f},
    {1.0f,  1.0f, 1.0f},
    {1.0f, 0.0f, 1.0f},
    {0.0f,0.0f, 1.0f}
};

static const unsigned short cube_e [] =
{
    0,1,2, 3,0,2, 6,5,4, 6,4,7, 6,2,1, 5,6,1, 0,7,4, 0,3,7, 5,1,0, 4,5,0, 3,2,6, 3,6,7
};

}

#endif // SIMPLE_MESHES_H
