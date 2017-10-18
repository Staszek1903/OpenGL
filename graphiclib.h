#ifndef GRAPHICLIB_H
#define GRAPHICLIB_H

#include <gl_headers.h>
#include <buffers.h>
#include <loaders/loadbmp.h>
#include <SFML/Graphics.hpp>

class GraphicLib
{
    sf::Texture sf_tex;

    int vertex_size;

    GLuint v_array;
    GLuint v_buffer;
    GLuint n_buffer;
    GLuint t_buffer;
    GLuint texture_programID, colour_programID;
    GLuint texture_matrixID, colour_matrixID;
    GLuint texture_samplerID, lightID;
    GLuint ModelMatrixID;
    GLuint ViewMatrixID;

    glm::mat4 projection_matrix,
        view_matrix,
        model1_matrix,
        model2_matrix,
        mvp1_matrix,
        mvp2_matrix;

    glm::vec4 &camera_pos,
        &camera_direction;

    float &vertical_angle, &horizontal_angle;


public:
    GraphicLib(float ratio, float &camera_v, float & camera_h, glm::vec4 & camera_p, glm::vec4 &camera_d);
    ~GraphicLib();
    void draw();

private:
    glm::vec4 getCameraDir();
};

#endif // GRAPHICLIB_H
