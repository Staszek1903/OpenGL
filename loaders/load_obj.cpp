#include "load_obj.h"

bool load_obj(std::__cxx11::string dir, std::vector<glm::vec3> &v, std::vector<glm::vec2> &uv, std::vector<glm::vec3> &n)
{
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;

    std::fstream plik;
    plik.open(dir, std::ios::in);

    if(!plik.good())
    {
        std::cout<<"Cannot open file : "<<dir<<std::endl;
        return false;
    }

    std::cout<<"opening obj file: " <<dir<<std::endl;

    int l = 0;
    while(true)
    {
        std::string head;
        plik>>head;

        if(plik.eof())
            break;

        std::cout<<head<<std::endl;

        if(head == "v")
        {
            float x,y,z;
            plik>>x>>y>>z;
            std::cout<<"vertex: "<<x<<" "<<y<<" "<<z<<std::endl;

            temp_vertices.push_back(glm::vec3(x,y,z));
        }
        else if (head == "vt")
        {
            float x,y;
            plik>>x>>y;
            std::cout<<"texture: "<<x<<" "<<y<<std::endl;
            temp_uvs.push_back(glm::vec2(x,y));
        }
        else if (head == "vn")
        {
            float x,y,z;
            plik>>x>>y>>z;
            std::cout<<"normal: "<<x<<" "<<y<<" "<<z<<std::endl;
            temp_normals.push_back(glm::vec3(x,y,z));
        }
        else if( head == "f")
        {
            std::string s[9];
            std::stringstream ss[9];
            int out[9];

            for(int i=0; i<3; ++i)
            {
                std::getline(plik,s[i*3],'/');
                std::getline(plik,s[i*3+1],'/');
                plik>>s[i*3+2];
            }

            for(int i=0; i<9; ++i)
            {
                ss[i]<<s[i];
                ss[i]>>out[i];
            }


            vertexIndices.push_back(out[0]);
            vertexIndices.push_back(out[3]);
            vertexIndices.push_back(out[6]);

            uvIndices.push_back(out[1]);
            uvIndices.push_back(out[4]);
            uvIndices.push_back(out[7]);

            normalIndices.push_back(out[2]);
            normalIndices.push_back(out[5]);
            normalIndices.push_back(out[8]);

        }
    }

    plik.close();

    for(int ind: vertexIndices)
        v.push_back(temp_vertices.at(ind-1));

    for(int norm: normalIndices)
        n.push_back(temp_normals.at(norm -1));

    for(int uvv: uvIndices)
        uv.push_back(temp_uvs.at(uvv -1));

    return true;
}
