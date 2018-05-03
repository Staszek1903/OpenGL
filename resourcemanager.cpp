#include "resourcemanager.h"

ResourceManager * ResourceManager::instance = nullptr;

ResourceManager::ResourceManager()
{
    agl::init_GL_context(window);

    contaiter.load_model("./objects/skybox2.obj","skybox_model", true);
    contaiter.load_model("./objects/herub2.obj","herubin_model", true);
    contaiter.load_model("./objects/herubin_smoth.obj","herubin_sm_model", false );

    contaiter.load_texture("./textures/herub2_tex.png", "herubin_texture");
    contaiter.load_texture("./textures/canvas5.png", "skybox_texture");

    agl::ShadingProgram & program = contaiter.load_shader("./shaders/shader.vert","./shaders/shader.frag","shader");
    program.setUniformEnum("light_vec",0);
    program.setUniformEnum("MVP", 1);
    program.setUniformEnum("rotate_mat",2);

    agl::ShadingProgram & tex_program = contaiter.load_shader("./shaders/tex_shader.vert","./shaders/tex_shader.frag","tex_shader");
    tex_program.setUniformEnum("light_vec",0);
    tex_program.setUniformEnum("MVP",1);
    tex_program.setUniformEnum("rotate_mat",2);
    tex_program.setUniformEnum("texture_samp",3);

    agl::ShadingProgram & sky_program = contaiter.load_shader("./shaders/sky_shader.vert","./shaders/sky_shader.frag", "sky_shader");
    sky_program.setUniformEnum("MVP",1);
    sky_program.setUniformEnum("texture_samp",3);
}

ResourceManager &ResourceManager::get()
{
    if(!instance)
        instance = new ResourceManager;
    return *instance;
}

void ResourceManager::release()
{

}
