#include "object.h"

agl::Object::Object()
    :position(0.0f), scale(1.0f), vertical_angle(0), horizontal_angle(0)
{

}

void agl::Object::setModel(Model &model)
{
    vertex_arrayID  = model.vertex_arrayID;
    vertex_bufferID = model.vertex_bufferID;
    normal_bufferID = model.normal_bufferID;
    uv_bufferID = model.uv_bufferID;
    elements_bufferID = model.elements_bufferID;
    vertex_num = model.size;
}

void agl::Object::setShader(ShadingProgram &shader)
{
    shading_programID = shader.getID();
    shader_ptr = & shader;
}

void agl::Object::setTexture(sf::Texture & tex)
{
    texture_ptr = & tex;
}

void agl::Object::move(glm::vec3 offset)
{
    position += offset;
}

void agl::Object::rotate(float v, float h)
{
    vertical_angle += v;
    horizontal_angle += h;
}

void agl::Object::setScale(float s)
{
    scale = s;
}

glm::mat4 agl::Object::getMatrix()
{
    glm::mat4 translate_matrix,
            rotation_matrix,
            scale_matrix;
    scale_matrix = glm::scale(scale_matrix, glm::vec3(scale,scale,scale));
    translate_matrix = glm::translate(translate_matrix, position);
    rotation_matrix = glm::rotate(rotation_matrix,horizontal_angle, glm::vec3(0,1,0));
    rotation_matrix = glm::rotate(rotation_matrix,vertical_angle, glm::vec3(1,0,0));
    return ( translate_matrix * scale_matrix * rotation_matrix);
}

glm::mat4 agl::Object::getRotationMatrix()
{
    glm::mat4 model_rotation_matrix;
    model_rotation_matrix = glm::rotate(model_rotation_matrix,horizontal_angle, glm::vec3(0,1,0));
    model_rotation_matrix = glm::rotate(model_rotation_matrix,vertical_angle, glm::vec3(1,0,0));
    return model_rotation_matrix;
}

void agl::Object::printBufferID()
{
    std::cout<<"v_array: "<<vertex_arrayID
            <<"\nbuffers: "/*<<vertex_bufferID<<" "*/
           <<normal_bufferID<<" "<<uv_bufferID<<" "<<elements_bufferID<<std::endl;
}
