#ifndef BUFFER_H
#define BUFFER_H

#include "AutisticGL/gl_headers.h"

namespace agl {

    class Buffer
    {
        GLuint buffer;
        GLuint type;
    public:
        Buffer();
        ~Buffer();

        Buffer(const Buffer&) = default;
        Buffer(Buffer&&)= default;
        Buffer& operator= (const Buffer&)= default;
        Buffer& operator= (Buffer&&)= default;

        void create(GLuint type);
        void release();
        void loadData(const void * data, GLuint size);
        void setAttribPoiter(GLuint layout, GLuint size);
        void bind();
        void unbind();

        GLuint getID() {return buffer;}
    };
}

#endif // BUFFER_H
