#ifndef LOAD_OBJ_H
#define LOAD_OBJ_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <gl_headers.h>

bool load_obj(std::string dir, std::vector<glm::vec3> &v, std::vector<glm::vec2> &uv, std::vector<glm::vec3> &n);

#endif // LOAD_OBJ_H
