#include "shadingprogram.h"

agl::ShadingProgram::ShadingProgram()
{

}

agl::ShadingProgram::~ShadingProgram()
{
    glDeleteProgram(shading_programID);
}

void agl::ShadingProgram::createProgram()
{
    shading_programID = glCreateProgram();
}

void agl::ShadingProgram::attachShader(agl::Shader &shader)
{
    glAttachShader(shading_programID, shader.getID());
    attached_shaders.push_back(shader.getID());
}

bool agl::ShadingProgram::link()
{
    GLint result = GL_FALSE;
    GLint infoLogLenght = 0;

    glLinkProgram(shading_programID);
    glGetProgramiv(shading_programID, GL_LINK_STATUS, &result);
    glGetProgramiv(shading_programID, GL_INFO_LOG_LENGTH, &infoLogLenght);
    std::cout<<"info log: "<<infoLogLenght<<std::endl;
    if(result == GL_FALSE)
    {
        char * errorMessage = new char[infoLogLenght+1];
        glGetProgramInfoLog(shading_programID, infoLogLenght, NULL, errorMessage);
        std::cout<<errorMessage<<std::endl;
        delete [] errorMessage;

        return false;
    }

    std::cout<<"SHADER ID: " << getID()<<std::endl;

    return true;
}

void agl::ShadingProgram::detachShaders()
{
    for(auto shader : attached_shaders)
        glDetachShader(shading_programID,shader);
}

bool agl::ShadingProgram::setUniformEnum(const std::string name, GLuint _enum)
{
    uniforms[_enum] = glGetUniformLocation(shading_programID, name.c_str());
    return true;
}

GLuint agl::ShadingProgram::getUniformID(GLuint _enum)
{
    if(uniforms.find(_enum) == uniforms.end())
    {std::cout << "BAD UNIFORM "<< _enum <<std::endl; return -1;}

    return uniforms[_enum];
}

void agl::ShadingProgram::setUniform(GLuint _enum, glm::vec3 v)
{
    //std::cout<<"uniform 3f"<<std::endl;
    glUniform3fv(getUniformID(_enum), 1, &v[0]);
}

void agl::ShadingProgram::setUniform(GLuint _enum, glm::vec2 v)
{
    //std::cout<<"uniform 2f"<<std::endl;
    glUniform2fv(getUniformID(_enum), 1, &v[0]);
}

void agl::ShadingProgram::setUniform(GLuint _enum, glm::mat4 v)
{
    //std::cout<<"uniform mat4f"<<std::endl;
    glUniformMatrix4fv(getUniformID(_enum), 1, GL_FALSE, &v[0][0]);
}

void agl::ShadingProgram::setUniform(GLuint _enum, int v)
{
    glUniform1i(getUniformID(_enum), v);
}

void agl::ShadingProgram::render(agl::Model &model)
{
    model.bind();

    glDrawElements(
        GL_TRIANGLES,      // mode
        model.get_size(),    // count
        GL_UNSIGNED_SHORT,   // type
        (void*)0           // element array buffer offset
    );
}

GLuint agl::ShadingProgram::getID()
{
    return shading_programID;
}

void agl::ShadingProgram::use()
{
    glUseProgram(shading_programID);
}

