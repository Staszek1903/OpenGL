#ifndef GLOBJECTCOMP_H
#define GLOBJECTCOMP_H

#include <entityx/entityx.h>
#include "AutisticGL/object.h"

class GLObjectComp : public entityx::Component<GLObjectComp>, public agl::Object
{
public:
    GLObjectComp(agl::Model & model, agl::ShadingProgram & shader, sf::Texture & tex);
};

#endif // GLOBJECTCOMP_H
