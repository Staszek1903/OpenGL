#ifndef MODEL_H
#define MODEL_H

#include <AutisticGL/gl_headers.h>
#include <iostream>
#include "AutisticGL/simple_meshes.h"
#include "AutisticGL/buffer.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <vector>

namespace agl
{
    class Model
    {
        GLuint VAO;
        bool created;
        std::vector <agl::Buffer> buffers;

        GLuint size;

        bool textured;

    public:
        Model();
        ~Model();
        Model( const Model &) = delete;
        Model & operator +(const Model & ) = delete;
        Model(Model && other);
        Model & operator =(Model && other);

        void loadFromMemory(const void *v, const void *c, GLuint buf_size, const unsigned short *e, GLuint elem_size);
        bool loadFromFile(const std::string & dir, bool texture);
        void load_cube();
        void load_tetra();

        void create();
        void release();
        void addBuffer(agl::Buffer b);
        Buffer addBuffer(GLuint type, const void *data, GLuint size);
        void bindBuffers();

        GLuint get_size(){return size;}
        GLuint get_vao(){return VAO;}
        bool is_textured(){return textured;}

        void bind();
    };
}


#endif // MODEL_H
