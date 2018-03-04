#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
#include <fstream>

namespace agl {

    class Shader
    {
    public:
        Shader();
        ~Shader();
        bool load(const char *dir, GLuint shader_type);
        GLuint getID();

    protected:
        GLuint shaderID;
    };

}


#endif // SHADER_H
