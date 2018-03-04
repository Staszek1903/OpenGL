#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
//assimp headers
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace agl {
    class Model
    {
    public:
        Model();
        ~Model();
       bool loadFromOBJ(const char * dir);

       GLuint vertex_arrayID;
       GLuint vertex_bufferID;
       GLuint normal_bufferID;
       GLuint uv_bufferID;
       GLuint elements_bufferID;
       GLuint size;
    protected:
    };
}

#endif // MODEL_H
