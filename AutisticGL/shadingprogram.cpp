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
    {std::cout << "BAD UNIFORM"<<std::endl; return -1;}

    return uniforms[_enum];
}

//void agl::ShadingProgram::getUniforms()
//{
//    mvp_matrixID = glGetUniformLocation(shading_programID, "MVP");
//    ModelMatrixID = glGetUniformLocation(shading_programID, "M");
//    ModelRotationID = glGetUniformLocation(shading_programID, "M_rot");
//    lightID = glGetUniformLocation(shading_programID, "LightPos");
//    camera_posID = glGetUniformLocation(shading_programID, "CameraPos");
//    texture_samplerID = glGetUniformLocation(shading_programID, "myTextureSampler");
//}

GLuint agl::ShadingProgram::getID()
{
    return shading_programID;
}

