#include "glmanager.h"

agl::GLManager::GLManager(agl::Camera & camera)
    :camera(camera)
{

}

agl::GLManager::~GLManager()
{
    agl::SkyBox::deleteRef();
}

void agl::GLManager::create_window(sf::RenderWindow &win)
{
    //opengl context init
    sf::ContextSettings context;
    context.depthBits = 24;
    context.stencilBits = 8;
    context.antialiasingLevel = 4;
    context.majorVersion = 3;
    context.minorVersion = 0;

    win.create(sf::VideoMode(1366.0f,768.0f), "opngl", sf::Style::Close ,  context);

    win.setVerticalSyncEnabled(true);
    win.setFramerateLimit(100);

    win.setActive(true);
}

void agl::GLManager::init(float aspect_ratio)
{
    //version
    glewInit();
    std::cout<<"GL_VERSION: \""<<glGetString(GL_VERSION)<<"\""<<std::endl;
    //setting matrixes
    projection_matrix = glm::perspective(
                glm::radians(50.0f),                                    //FOV
                //(float)win.getSize().x/ (float)win.getSize().y,         //Aspect Ratio
                aspect_ratio,
                0.1f,                                                   //near clip
                100.0f);                                                //far clip
}

void agl::GLManager::reder_obj(agl::Object &obj)
{
    glm::mat4 mvp_matrix = projection_matrix * camera.getMatrix() * obj.getMatrix();

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glUseProgram(obj.shading_programID);

    //DRAWING CUBE
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, obj.vertex_bufferID);
    glVertexAttribPointer(
                0,          //atrybut 0 match with layout
                3,          //sizeobjects files
                GL_FLOAT,   //type
                GL_FALSE,   //normalized
                0,          //stride
                (void*)0    //array buffer offset
                );


    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, obj.uv_bufferID);
    glVertexAttribPointer(
                1,          //atrybut 1 match with layout
                2,          //size
                GL_FLOAT,   //type
                GL_FALSE,   //normalized
                0,          //stride
                (void*)0
                );

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, obj.normal_bufferID);
    glVertexAttribPointer(
                2,          //atrybut 1 match with layout
                3,          //size
                GL_FLOAT,   //type
                GL_FALSE,   //normalized
                0,          //stride
                (void*)0
                );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.elements_bufferID);

    glUniformMatrix4fv(obj.shader_ptr->getUniformID(agl::Uniforms::MVP), 1, GL_FALSE, &mvp_matrix[0][0]);
    glUniformMatrix4fv(obj.shader_ptr->getUniformID(agl::Uniforms::MODEL_MATRIX), 1, GL_FALSE, &obj.getMatrix()[0][0]);
    glUniformMatrix4fv(obj.shader_ptr->getUniformID(agl::Uniforms::MODEL_ROTATION), 1, GL_FALSE, &obj.getRotationMatrix()[0][0]);
    glUniform1i(obj.shader_ptr->getUniformID(agl::Uniforms::TEX_SAMPLER),0);
    glUniform3f(obj.shader_ptr->getUniformID(agl::Uniforms::LIGHT_POS), 100.0f,0.0f,-4.0f);
    glm::vec3 c_pos = camera.getPosition();
    glUniform3f(obj.shader_ptr->getUniformID(agl::Uniforms::CAMERA_POS), c_pos.x, c_pos.y, c_pos.z);

    glActiveTexture(GL_TEXTURE0);
    sf::Texture::bind(obj.texture_ptr);

    // Draw the triangles !
    glDrawElements(
        GL_TRIANGLES,      // mode
        obj.vertex_num,    // count
        GL_UNSIGNED_SHORT,   // type
        (void*)0           // element array buffer offset
    );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void agl::GLManager::render_skybox()
{
    glm::mat4 mvp_matrix = projection_matrix * camera.getRotationMatrix();

    glDisable(GL_DEPTH_TEST);

    glUseProgram(agl::SkyBox::getRef().shading_programID);

    //DRAWING CUBE
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, agl::SkyBox::getRef().vertex_bufferID);
    glVertexAttribPointer(
                0,          //atrybut 0 match with layout
                3,          //sizeobjects files
                GL_FLOAT,   //type
                GL_FALSE,   //normalized
                0,          //stride
                (void*)0    //array buffer offset
                );


    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, agl::SkyBox::getRef().uv_bufferID);
    glVertexAttribPointer(
                1,          //atrybut 1 match with layout
                2,          //size
                GL_FLOAT,   //type
                GL_FALSE,   //normalized
                0,          //stride
                (void*)0
                );

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, agl::SkyBox::getRef().normal_bufferID);
    glVertexAttribPointer(
                2,          //atrybut 1 match with layout
                3,          //size
                GL_FLOAT,   //type
                GL_FALSE,   //normalized
                0,          //stride
                (void*)0
                );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, agl::SkyBox::getRef().elements_bufferID);

    glUniformMatrix4fv(agl::SkyBox::getRef().shader_ptr->getUniformID(agl::Uniforms::MVP), 1, GL_FALSE, &mvp_matrix[0][0]);
    glUniform1i(agl::SkyBox::getRef().shader_ptr->getUniformID(agl::Uniforms::TEX_SAMPLER),0);

    glActiveTexture(GL_TEXTURE0);
    sf::Texture::bind(agl::SkyBox::getRef().texture_ptr);

    // Draw the triangles !
    glDrawElements(
        GL_TRIANGLES,      // mode
        agl::SkyBox::getRef().vertex_num,    // count
        GL_UNSIGNED_SHORT,   // type
        (void*)0           // element array buffer offset
    );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}
