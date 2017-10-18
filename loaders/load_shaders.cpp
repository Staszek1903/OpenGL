#include "load_shaders.h"

GLuint load_shaders(const char * vertex_dir, const char * fragment_dir)
{
    GLuint vertex_shaderID = glCreateShader(GL_VERTEX_SHADER),
           fragment_shaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertex_shader_code, fragment_shader_code;
    std::fstream shader_file;

    shader_file.open(vertex_dir,std::ios::in);
    if(shader_file.good())
    {
        std::string line = "";
        while(std::getline(shader_file, line))
            vertex_shader_code += "\n" + line;
        shader_file.close();
    }
    else
    {
        std::cout<<"nie można otworzyć v_shadera: "<<vertex_dir<<std::endl;
        return 0;
    }

    shader_file.open(fragment_dir,std::ios::in);
    if(shader_file.good())
    {
        std::string line = "";
        while(std::getline(shader_file, line))
            fragment_shader_code += "\n" + line;
        shader_file.close();
    }
    else
    {
        std::cout<<"nie można otworzyć v_shadera: "<<vertex_dir<<std::endl;
        return 0;
    }

    std::cout<< "VERTEX SHADER:"<<std::endl<<std::endl<< vertex_shader_code<<std::endl<<std::endl;
    std::cout<< "FRAGMENT SHADER:"<<std::endl<<std::endl<< fragment_shader_code<<std::endl<<std::endl;

    GLint result = GL_FALSE;
    int infoLogLenght;

    //compile vertex shader
    std::cout<<"Compilacja vertex shader"<<std::endl;
    char const * vertex_source_pointer = vertex_shader_code.c_str();
    glShaderSource(vertex_shaderID,1, &vertex_source_pointer, NULL);
    glCompileShader(vertex_shaderID);

    //check vertex shader

    glGetShaderiv(vertex_shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertex_shaderID, GL_INFO_LOG_LENGTH, &infoLogLenght);
    std::cout<<"info log: "<<infoLogLenght<<std::endl;
    if(infoLogLenght > 0)
    {
        char * errorMessage = new char[infoLogLenght+1];
        glGetShaderInfoLog(vertex_shaderID, infoLogLenght, NULL, errorMessage);
        std::cout<<errorMessage<<std::endl;
        delete [] errorMessage;
    }

    //compile fragment shader
    std::cout<<"Compilacja fragment shader"<<std::endl;
    char const * fragment_source_pointer = fragment_shader_code.c_str();
    glShaderSource(fragment_shaderID,1, &fragment_source_pointer, NULL);
    glCompileShader(fragment_shaderID);

    //check fragment shader

    glGetShaderiv(fragment_shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragment_shaderID, GL_INFO_LOG_LENGTH, &infoLogLenght);
    std::cout<<"info log: "<<infoLogLenght<<std::endl;
    if(infoLogLenght > 0)
    {
        char * errorMessage = new char[infoLogLenght+1];
        glGetShaderInfoLog(fragment_shaderID, infoLogLenght, NULL, errorMessage);
        std::cout<<errorMessage<<std::endl;
        delete [] errorMessage;
    }

    //Link program
    std::cout<<"Linking program"<<std::endl;

    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertex_shaderID);
    glAttachShader(programID, fragment_shaderID);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLenght);
    std::cout<<"info log: "<<infoLogLenght<<std::endl;
    if(infoLogLenght > 0)
    {
        char * errorMessage = new char[infoLogLenght+1];
        glGetProgramInfoLog(programID, infoLogLenght, NULL, errorMessage);
        std::cout<<errorMessage<<std::endl;
        delete [] errorMessage;
    }

    glDetachShader(programID,vertex_shaderID);
    glDetachShader(programID,fragment_shaderID);
    glDeleteShader(vertex_shaderID);
    glDeleteShader(fragment_shaderID);

    return programID;

}
