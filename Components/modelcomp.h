#ifndef MODELCOMP_H
#define MODELCOMP_H

#include <entityx/entityx.h>
#include "AutisticGL/model.h"

struct ModelComp : public entityx::Component<ModelComp>
{
    ModelComp(agl::Model & model)
        :model(model){}

    agl::Model &model;
};

#endif // MODELCOMP_H
