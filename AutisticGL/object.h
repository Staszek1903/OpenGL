#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

#include "AutisticGL/gl_headers.h"
#include "AutisticGL/shadingprogram.h"
#include "AutisticGL/model.h"

namespace agl {

    class Object
    {
        glm::mat4 model_matrix, rotate_matrix;
        agl::ShadingProgram * program;
        agl::Model * model;
        sf::Texture * texture;

    public:
        Object();
        void move(glm::vec3 offset);
        void rotate(GLfloat angle, glm::vec3 vector);
        void rotate(glm::vec3 euler);
        glm::mat4 getMatrix() {return model_matrix;}
        glm::mat4 getRotationMatrix() {return rotate_matrix;}

        void set_shader(ShadingProgram &shader);
        void set_model(Model &model);
        void set_texture(sf::Texture &tex);

        void render(glm::mat4 view, glm::mat4 projection);
    };

}

#endif // OBJECT_H
