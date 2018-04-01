#ifndef SHADINGPROGRAM_H
#define SHADINGPROGRAM_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>
#include <string>
#include <map>
#include <glm/glm.hpp>

#include "AutisticGL/shader.h"
#include "AutisticGL/model.h"

namespace agl {

    class ShadingProgram
    {
    public:
        ShadingProgram();
        ~ShadingProgram();
        void createProgram();
        void attachShader(agl::Shader & shader);
        bool link();
        void detachShaders();
        bool setUniformEnum(const std::string name, GLuint _enum);
        GLuint getUniformID(GLuint _enum);

        void setUniform(GLuint _enum, glm::vec3 v);
        void setUniform(GLuint _enum, glm::vec2 v);
        void setUniform(GLuint _enum, glm::mat4 v);
        void setUniform(GLuint _enum, int v);

        void render(Model &model);

        GLuint getID();
        void use();

    protected:
        std::vector<GLuint> attached_shaders;
        GLuint shading_programID;
        std::map <GLuint, GLuint> uniforms;
    };
}

#endif // SHADINGPROGRAM_H
