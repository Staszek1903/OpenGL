#include "skybox.h"

agl::SkyBox * agl::SkyBox::instance = nullptr;

agl::SkyBox &agl::SkyBox::getRef()
{
    if(!instance)
        instance = new SkyBox;
    return *instance;
}

void agl::SkyBox::deleteRef()
{
    if(instance)
        delete instance;
}

agl::SkyBox::SkyBox()
{
    agl::Shader v_shader, f_shader;
    v_shader.load("./shaders/skybox_shader.vert",GL_VERTEX_SHADER);
    f_shader.load("./shaders/skybox_shader.frag",GL_FRAGMENT_SHADER);

    shad_prog.createProgram();
    shad_prog.attachShader(v_shader);
    shad_prog.attachShader(f_shader);
    shad_prog.link();
    shad_prog.detachShaders();

    shad_prog.setUniformEnum("MVP",agl::Uniforms::MVP);
    shad_prog.setUniformEnum("myTextureSampler", agl::Uniforms::TEX_SAMPLER);

    setShader(shad_prog);

    model.loadFromOBJ("./objects/skybox.obj");
    setModel(model);

    texture.loadFromFile("./textures/skybox.png");
    setTexture(texture);
}
