#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

#include "model.h"
#include "shadingprogram.h"

#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace agl {

    enum Uniforms
    {
        MVP,
        MODEL_MATRIX,
        MODEL_ROTATION,
        TEX_SAMPLER,
        LIGHT_POS,
        CAMERA_POS,
        UIFORMS_COUT
    };


    class Object
    {
    public:
        Object();
        void setModel(agl::Model & model);
        void setShader(agl::ShadingProgram & shader);
        void setTexture(sf::Texture & tex);

        void move(glm::vec3 offset);
        void rotate(float v, float h);
        void setScale(float s);

        glm::mat4 getMatrix();
        glm::mat4 getRotationMatrix();

        void printBufferID();

        ShadingProgram * shader_ptr;
        sf::Texture * texture_ptr;

        GLuint vertex_arrayID;
        GLuint vertex_bufferID;
        GLuint normal_bufferID;
        GLuint uv_bufferID;
        GLuint elements_bufferID;
        GLuint shading_programID;

        GLuint vertex_num;
    protected:
        glm::vec3 position;
        float scale;
        float vertical_angle, horizontal_angle;
    };
}

#endif // OBJECT_H
