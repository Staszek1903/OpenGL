#include "object.h"

agl::Object::Object()
{

}

void agl::Object::move(glm::vec3 offset)
{
    model_matrix = glm::translate(model_matrix,offset);
}

void agl::Object::rotate(GLfloat angle, glm::vec3 vector)
{
    model_matrix = glm::rotate(model_matrix, angle, vector);
    rotate_matrix = glm::rotate(rotate_matrix, angle, vector);
}

void agl::Object::set_shader(agl::ShadingProgram &shader)
{
    program = &shader;
}

void agl::Object::set_model(agl::Model &model)
{
    this->model = &model;
}

void agl::Object::render(glm::mat4 view, glm::mat4 projection)
{
    glm::mat4 mvp = projection*view*model_matrix;

    //std::cout<<"obj vao: "<<model->get_vao()<<std::endl;

    program->use();

    glm::vec3 light(1,0,0);

    program->setUniform(0,light);
    program->setUniform(1, mvp);
    program->setUniform(2, rotate_matrix);

    model->bind();

    glDrawElements(
        GL_TRIANGLES,      // mode
        model->get_size(),    // count
        GL_UNSIGNED_SHORT,   // type
        (void*)0           // element array buffer offset
    );
}
