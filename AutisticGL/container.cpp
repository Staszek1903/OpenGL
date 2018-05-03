#include "container.h"

agl::Container::Container()
{

}

sf::Texture &agl::Container::load_texture(std::string dir, std::string id)
{
    sf::Texture temp;
    temp.loadFromFile(dir);
    textures.push_back(temp);

    assert(ids.find(id) == ids.end());

    ids[id] = textures.size()-1;

    return(textures.at(ids[id]));
}

sf::Texture &agl::Container::get_texture(std::string id)
{
    if(ids.find(id) == ids.end())
        std::cout<<"no texture: "<<id<<std::endl;
    return textures.at(ids.at(id));
}

agl::Model &agl::Container::load_model(std::string dir, std::string id, bool texture)
{
    agl::Model temp;
    assert(temp.loadFromFile(dir, texture));
    models.push_back(std::move(temp));

    assert(ids.find(id) == ids.end());

    ids[id] = models.size()-1;

    return(models.at(ids[id]));
}

agl::Model &agl::Container::get_model(std::string id)
{
    if(ids.find(id) == ids.end())
        std::cout<<"no model: "<<id<<std::endl;
    return models.at(ids.at(id));
}

agl::ShadingProgram &agl::Container::load_shader(std::string vertex_dir, std::string fragment_dir, std::string id)
{
    agl::Shader vs, fs;
    agl::ShadingProgram program;
    vs.load(vertex_dir.c_str(), GL_VERTEX_SHADER);
    fs.load(fragment_dir.c_str(), GL_FRAGMENT_SHADER);

    program.createProgram();
    program.attachShader(vs);
    program.attachShader(fs);
    program.link();
    program.detachShaders();

    shaders.push_back(std::move(program));

    ids[id] = shaders.size()-1;

    return(shaders.at(ids[id]));
}

agl::ShadingProgram &agl::Container::get_shader(std::string id)
{
    if(ids.find(id) == ids.end())
        std::cout<<"no shader: "<<id<<std::endl;
    return shaders.at(ids.at(id));
}
