#ifndef LOAD_SHADERS_H
#define LOAD_SHADERS_H

#include <gl_headers.h>
#include <fstream>
#include <string>
#include <iostream>

GLuint load_shaders(const char * vertex_dir, const char * fragment_dir);

#endif // LOAD_SHADERS_H
