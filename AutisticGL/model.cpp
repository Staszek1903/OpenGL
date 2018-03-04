#include "model.h"

agl::Model::Model()
{

}

agl::Model::~Model()
{
    glDeleteBuffers(1, &vertex_bufferID);
    glDeleteBuffers(1, &uv_bufferID);
    glDeleteBuffers(1, &normal_bufferID);
    glDeleteBuffers(1, &elements_bufferID);
    glDeleteVertexArrays(1, &vertex_arrayID);
}

bool agl::Model::loadFromOBJ(const char *dir)
{
    //load obj
    std::vector <glm::vec3> vertex_vector, normal_vector;
    std::vector <glm::vec2> uv_vector;
    std::vector <unsigned short> indices;


    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(dir, aiProcess_Triangulate | aiProcess_FlipUVs|aiProcess_CalcTangentSpace       |
                                                                 aiProcess_JoinIdenticalVertices  |
                                           aiProcess_SortByPType);

    if(scene)
        std::cout<<"ZAŁADOWANO MODEL: "<<dir<<std::endl;
    else
    {   std::cout<<"NIEZALADOWANO: "<<dir<<std::endl; return false; }

    aiMesh * mesh = scene->mMeshes[0];
    for(int i=0; i<mesh->mNumVertices; ++i)
    {
        aiVector3D v = mesh->mVertices[i];
        aiVector3D n = mesh->mNormals[i];
        aiVector3D t = mesh->mTextureCoords[0][i];
        vertex_vector.push_back(glm::vec3(v.x,v.y,v.z));
        normal_vector.push_back(glm::vec3(n.x,n.y,n.z));
        uv_vector.push_back(glm::vec2(t.x,t.y));
    }

    for(int i=0; i<mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for(int j=0; j<face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }

//    char temp;
//    std::cout<<"WAITING ";
//    std::cin>>temp;

    this->size = indices.size();
    std::cout<<"obj size: "<<this->size<<std::endl;

    //generate vertex array
    glGenVertexArrays(1, &vertex_arrayID);
    glBindVertexArray(vertex_arrayID); //ustawia array jako aktywny

    //generate vertex buffer
    glGenBuffers(1, &vertex_bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_bufferID);
    glBufferData(GL_ARRAY_BUFFER, vertex_vector.size() * sizeof(glm::vec3), &vertex_vector[0], GL_STATIC_DRAW);

    //generate normal buffer
    glGenBuffers(1, &normal_bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, normal_bufferID);
    glBufferData(GL_ARRAY_BUFFER, vertex_vector.size() * sizeof(glm::vec3), &normal_vector[0], GL_STATIC_DRAW);

    //generate texture buffer
    glGenBuffers(1, &uv_bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, uv_bufferID);
    glBufferData(GL_ARRAY_BUFFER, uv_vector.size() * sizeof(glm::vec3), &uv_vector[0], GL_STATIC_DRAW);

    //genrate indices buffer;
    glGenBuffers(1, &elements_bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements_bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

    std::cout<<"LOADED: "<<dir<<" v_array: "<<vertex_arrayID
            <<"\nbuffers: "<<vertex_bufferID<<" "
           <<normal_bufferID<<" "<<uv_bufferID<<" "<<elements_bufferID<<std::endl;

    return true;

}
