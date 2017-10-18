#include "loadbmp.h"

GLuint loadBMP(const char * imagepath)
{
    std::cout<<"opening BMP: "<<imagepath<<std::endl;

    char header[54];
    unsigned int dataPos;       //where data begins;
    unsigned int width, height;
    unsigned int imageSize;     //width * heignt * 3
    char * data;

    std::fstream file;
    file.open(imagepath, std::ios::in | std::ios::binary);
    if(!file.good())
    {
        std::cout<<"cannot open file"<<std::endl;
        file.close();
        return 0;
    }

    file.read(header, 54);
    if(header[0] != 'B' || header[1] != 'M')
    {
        std::cout <<"not BMP file format"<<std::endl;
        file.close();
        return 0;
    }

    //std::cout<<"DEbUG"<<std::endl;
    dataPos = *(unsigned int*)(header+0x0A);
    imageSize = *(unsigned int*)(header+0x22);
    width = *(unsigned int*)(header+0x12);
    height = *(unsigned int *)(header+0x16);
    //std::cout<<"DEbUG"<<std::endl;

    if(imageSize == 0)
        imageSize = width * height * 3;
    if(dataPos == 0)
        dataPos = 54;

    std::cout<<"dataPos: "<<dataPos<<std::endl;
    std::cout<<"imageSize: "<<imageSize<<std::endl;
    std::cout<<"width: "<<width<<std::endl;
    std::cout<<"height: "<<height<<std::endl;

    data = new char [imageSize];
    file.read(data, imageSize);
    file.close();


    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    delete[] data;
    return textureID;
}
