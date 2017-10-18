#include "graphiclib.h"
#include <loaders/load_shaders.h>
#include <loaders/load_obj.h>

GraphicLib::GraphicLib(float ratio, float &camera_v, float & camera_h, glm::vec4 &camera_p, glm::vec4 &camera_d)
    :camera_pos(camera_p), camera_direction(camera_d),vertical_angle(camera_v), horizontal_angle(camera_h)
{
    //init glew
    glewInit();

    //load obj
    std::vector <glm::vec3> vertex_vector, normal_vector;
    std::vector <glm::vec2> uv_vector;
    if(!load_obj("/home/patryk/C++proj/opengl/OpenGl/objects/star_monkey.obj", vertex_vector, uv_vector, normal_vector))
    {
        std::cout<<"OBJ NOT LOADED"<<std::endl;
        return;
    }

    vertex_size = vertex_vector.size();

    //load shaders
    texture_programID = load_shaders("/home/patryk/C++proj/opengl/OpenGl/shaders/texture_vertex_shader.vert",
                 "/home/patryk/C++proj/opengl/OpenGl/shaders/texture_fragment_shader.frag");
    colour_programID = load_shaders("/home/patryk/C++proj/opengl/OpenGl/shaders/colour_vertex_shader.vert",
                                    "/home/patryk/C++proj/opengl/OpenGl/shaders/colour_fragment_shader.frag");

    //opengl version
    std::cout<<glGetString(GL_VERSION)<<std::endl;

    //generate vertex array
    glGenVertexArrays(1, &v_array);
    glBindVertexArray(v_array); //ustawia array jako aktywny

    //generate vertex buffer
    glGenBuffers(1, &v_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_vector.size() * sizeof(glm::vec3), &vertex_vector[0], GL_STATIC_DRAW);

    //generate normal buffer
    glGenBuffers(1, &n_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, n_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_vector.size() * sizeof(glm::vec3), &normal_vector[0], GL_STATIC_DRAW);

    //generate texture buffer
    glGenBuffers(1, &t_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, t_buffer);
    glBufferData(GL_ARRAY_BUFFER, uv_vector.size() * sizeof(glm::vec3), &uv_vector[0], GL_STATIC_DRAW);

    //setting matrixes
    projection_matrix = glm::perspective(
                glm::radians(50.0f),                                    //FOV
                //(float)win.getSize().x/ (float)win.getSize().y,         //Aspect Ratio
                ratio,
                0.1f,                                                   //near clip
                100.0f);                                                //far clip

    camera_pos = glm::vec4(0,0,-3,1);

    model1_matrix = glm::translate(model1_matrix, glm::vec3(-2.0f,0.0f, 0.0f));
    model2_matrix = glm::translate(model2_matrix, glm::vec3(2.0f,0.0f, 0.0f));

    //getting matrix ID from shader
    texture_matrixID = glGetUniformLocation(texture_programID, "MVP");
    ViewMatrixID = glGetUniformLocation(texture_programID, "V");
    ModelMatrixID = glGetUniformLocation(texture_programID, "M");
    texture_samplerID = glGetUniformLocation(texture_programID, "myTextureSampler");
    lightID = glGetUniformLocation(texture_programID, "LightPosition_worldspace");


    sf_tex.loadFromFile("/home/patryk/C++proj/opengl/OpenGl/textures/star.jpg");

}

GraphicLib::~GraphicLib()
{
    glDeleteBuffers(1, &v_buffer);
    glDeleteBuffers(1, &t_buffer);
    glDeleteBuffers(1, &n_buffer);
    glDeleteProgram(texture_programID);
    glDeleteVertexArrays(1, &v_array);
}

void GraphicLib::draw()
{
    camera_direction = getCameraDir();

    glm::vec3 c_pos(camera_pos.x, camera_pos.y, camera_pos.z);
    glm::vec3 c_dir(camera_direction.x, camera_direction.y, camera_direction.z);

    view_matrix = glm::lookAt(
                c_pos, //camera positionopengl
                c_pos + c_dir, //point looking at
                glm::vec3(0,1,0)  //up vector
                );

    glClearColor(0.0f,0.0f,0.4f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mvp1_matrix = projection_matrix * view_matrix * model1_matrix;
    mvp2_matrix = projection_matrix * view_matrix * model2_matrix;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glUseProgram(texture_programID);

    //DRAWING CUBE
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, v_array);
    glVertexAttribPointer(
                0,          //atrybut 0 match with layout
                3,          //sizeobjects files
                GL_FLOAT,   //type
                GL_FALSE,   //normalized
                0,          //stride
                (void*)0    //array buffer offset
                );


    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, t_buffer);
    glVertexAttribPointer(
                1,          //atrybut 1 match with layout
                2,          //size
                GL_FLOAT,   //type
                GL_FALSE,   //normalized
                0,          //stride
                (void*)0
                );

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, n_buffer);
    glVertexAttribPointer(
                2,          //atrybut 1 match with layout
                3,          //size
                GL_FLOAT,   //type
                GL_FALSE,   //normalized
                0,          //stride
                (void*)0
                );

    glUniformMatrix4fv(texture_matrixID, 1, GL_FALSE, &mvp1_matrix[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &model1_matrix[0][0]);
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &view_matrix[0][0]);
    glUniform1i(texture_samplerID,0);
    glUniform3f(lightID, 4.0f,4.0f,4.0f);

    glActiveTexture(GL_TEXTURE0);
    sf::Texture::bind(&sf_tex);

    glDrawArrays(GL_TRIANGLES,0,vertex_size);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);


    //DRAWING TRIANGLE
//    glEnableVertexAttribArray(1);
//    glBindBuffer(GL_ARRAY_BUFFER, c_buffer);
//    glVertexAttribPointer(
//                1,          //atrybut 1 match with layout
//                3,          //size
//                GL_FLOAT,   //type
//                GL_FALSE,   //normalized
//                0,          //stride
//                (void*)0
//                );

//    glUseProgram(colour_programID);
//    glUniformMatrix4fv(colour_matrixID, 1, GL_FALSE, &mvp2_matrix[0][0]);
//    glDrawArrays(GL_TRIANGLES,12*3,3*3);

}

glm::vec4 GraphicLib::getCameraDir()
{
    return(glm::vec4(glm::cos(vertical_angle)*glm::sin(horizontal_angle),
                     glm::sin(vertical_angle),
                     glm::cos(vertical_angle)*glm::cos(horizontal_angle),
                     1));
}
