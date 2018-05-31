#include "object.h"

agl::Object::Object()
    :program(nullptr), model(nullptr), texture(nullptr)
{

}

void agl::Object::move(glm::vec3 offset)
{
    model_matrix = glm::translate(model_matrix,offset);
    position_matrix = glm::translate(position_matrix,offset);
}

void agl::Object::rotate(GLfloat angle, glm::vec3 vector)
{
    model_matrix = glm::rotate(model_matrix, angle, vector);
    rotate_matrix = glm::rotate(rotate_matrix, angle, vector);
}

void agl::Object::rotate(glm::vec3 euler)
{
    rotate(euler.x, glm::vec3(1,0,0));
    rotate(euler.y, glm::vec3(0,1,0));
    rotate(euler.z, glm::vec3(0,0,1));
}

void agl::Object::set_position(glm::vec3 pos)
{
    glm::mat4 pos_matrix;
    pos_matrix = glm::translate(pos_matrix, pos);
    position_matrix = pos_matrix;
    model_matrix = pos_matrix * rotate_matrix * scale_matrix;
}

void agl::Object::set_rotation(glm::vec3 euler)
{
    glm::mat4 rot_matrix;
    rot_matrix = glm::rotate(rot_matrix, euler.x, glm::vec3(1,0,0));
    rot_matrix = glm::rotate(rot_matrix, euler.y, glm::vec3(0,1,0));
    rot_matrix = glm::rotate(rot_matrix, euler.z, glm::vec3(0,0,1));

    rotate_matrix = rot_matrix;
    model_matrix = position_matrix * rotate_matrix * scale_matrix;
}

void agl::Object::set_scale(glm::vec3 scale)
{
    glm::mat4 new_scale;
    new_scale = glm::scale(new_scale, scale);
    scale_matrix = new_scale;
    model_matrix = position_matrix * rotate_matrix * scale_matrix;
}


void agl::Object::set_shader(agl::ShadingProgram &shader)
{
    program = &shader;
}

void agl::Object::set_model(agl::Model &model)
{
    this->model = &model;
}

void agl::Object::set_texture(sf::Texture &tex)
{
    this->texture = &tex;
}

void agl::Object::render(glm::mat4 view, glm::mat4 projection)
{    
    std::cout<<"program: "<<program->getID()<<std::endl;
    std::cout<<"model: "<<model->get_vao()<<std::endl;
    program->use();
    program->setUniform(0,glm::vec3(0,0,1));
    program->setUniform(1, projection * view * model_matrix);
    program->setUniform(2, rotate_matrix);

    if(model->is_textured()){
        program->setUniform(3, 0);
        sf::Texture::bind(texture);
    }

    program->render(*model);
}
