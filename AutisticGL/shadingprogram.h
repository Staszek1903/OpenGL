#ifndef SHADINGPROGRAM_H
#define SHADINGPROGRAM_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>
#include <string>
#include <map>

#include "AutisticGL/shader.h"

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
        //void getUniforms();
        GLuint getUniformID(GLuint _enum);
        GLuint getID();

        GLuint mvp_matrixID,
            texture_samplerID,
            lightID,
            ModelMatrixID,
            ModelRotationID,
            camera_posID;

    protected:
        std::vector<GLuint> attached_shaders;
        GLuint shading_programID;
        std::map <GLuint, GLuint> uniforms;
    };
}

#endif // SHADINGPROGRAM_H
