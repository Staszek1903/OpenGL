#ifndef SHADERCOMP_H
#define SHADERCOMP_H

#include <entityx/entityx.h>
#include "AutisticGL/shadingprogram.h"

struct ShaderComp : public entityx::Component<ShaderComp>
{
    ShaderComp(agl::ShadingProgram & s)
        :shader(s){}
    agl::ShadingProgram &shader;
};

#endif // SHADERCOMP_H
