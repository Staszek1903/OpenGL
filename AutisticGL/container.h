#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <assert.h>
#include "model.h"
#include "shadingprogram.h"

namespace agl {
    class Container
    {
        std::vector < sf::Texture > textures;
        std::vector < agl::Model > models;
        std::vector < agl::ShadingProgram > shaders;
        std::map <std::string, int> ids;
    public:
        Container();

        sf::Texture & load_texture(std::string dir, std::string id);
        sf::Texture & get_texture(std::string id);

        agl::Model & load_model(std::string dir, std::string id, bool texture);
        agl::Model & get_model(std::string id);

        agl::ShadingProgram & load_shader(std::string vertex_dir, std::string fragment_dir, std::string id);
        agl::ShadingProgram & get_shader(std::string id);

    };
}

#endif // CONTAINER_H
