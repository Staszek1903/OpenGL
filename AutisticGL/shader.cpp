#include "shader.h"

agl::Shader::Shader()
{

}

agl::Shader::~Shader()
{
    glDeleteShader(shaderID);
}

bool agl::Shader::load(const char *dir, GLuint shader_type)
{
    shaderID = glCreateShader(shader_type);

    std::string shader_code;
    std::fstream file;

    file.open(dir,std::ios::in);
    if(file.good())
    {
        std::string line = "";
        while(std::getline(file, line))
            shader_code += "\n" + line;
        file.close();
    }
    else
    {
        std::cout<<"nie można otworzyć shadera: "<<dir<<std::endl;
        return false;
    }

    //compile vertex shader
    //std::cout<<"Compilacja shader"<<std::endl;
    char const * source_pointer = shader_code.c_str();
    glShaderSource(shaderID,1, &source_pointer, NULL);
    glCompileShader(shaderID);

    GLint result = GL_FALSE;
    GLint infoLogLenght = 0;

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLenght);
    std::cout<<"info log: "<<infoLogLenght<<std::endl;
    if(result == GL_FALSE)
    {
        char * errorMessage = new char[infoLogLenght+1];
        glGetShaderInfoLog(shaderID, infoLogLenght, NULL, errorMessage);
        std::cout<<errorMessage<<std::endl;
        delete [] errorMessage;

        return false;
    }

    std::cout<<"zaladowano shader: "<<dir<<std::endl;

    return true;
}

GLuint agl::Shader::getID()
{
    return shaderID;
}
