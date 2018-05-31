#include "globjectcomp.h"

GLObjectComp::GLObjectComp(agl::Model &model, agl::ShadingProgram &shader, sf::Texture &tex)
{
    set_model(model);
    set_shader(shader);
    set_texture(tex);
}
