#include "buffer.h"



agl::Buffer::Buffer()
    :buffer(0), type(0)
{

}

agl::Buffer::~Buffer()
{

}

void agl::Buffer::create(GLuint type)
{
    glGenBuffers(1, &buffer);
    this->type = type;
}

void agl::Buffer::release()
{
     glDeleteBuffers(1,&buffer);
}

void agl::Buffer::loadData(const void *data, GLuint size)
{
    glBindBuffer(type, buffer);
    glBufferData(type, size, data, GL_STATIC_DRAW);
    glBindBuffer(type, 0);
}

void agl::Buffer::setAttribPoiter(GLuint layout, GLuint size)
{
    glBindBuffer(this->type, buffer);
    glEnableVertexAttribArray(layout);
    glVertexAttribPointer(layout,size,GL_FLOAT,GL_FALSE,0,(void*)0);
    glBindBuffer(type, 0);
}

void agl::Buffer::bind()
{
    glBindBuffer(type, buffer);
}

void agl::Buffer::unbind()
{
    glBindBuffer(type,0);
}
