#include "model.h"

agl::Model::Model()
    :VAO(0), created(false)
{
    std::cout<<"model init"<<std::endl;
}

agl::Model::~Model()
{
    if(created)
        release();
}

agl::Model &agl::Model::operator =(agl::Model &&other)
{
    VAO = other.VAO;
    other.VAO = 0;
    created = true;
    other.created = false;
    buffers = other.buffers;
    size = other.size;

    return *this;
}

agl::Model::Model( Model &&other)
{
    VAO = other.VAO;
    other.VAO = 0;
    created = true;
    other.created = false;
    buffers = other.buffers;
    size = other.size;
    textured = other.textured;
}

void agl::Model::loadFromMemory(const void * v, const void * c, GLuint buf_size, const unsigned short * e, GLuint elem_size)
{
    //glGenVertexArrays(1,&VAO);

    glm::vec3 * normals_ptr  = (glm::vec3*)(v);
    std::vector <glm::vec3> normals;
    for(GLuint i=0; i<buf_size/sizeof(glm::vec3); ++i)
    {
        normals.push_back(normals_ptr[i]);
        glm::vec3 & n = normals[normals.size()-1];
        n /= (sqrt(n.x*n.x + n.y*n.y + n.z*n.z));
    }


    create();

    agl::Buffer v_buf = addBuffer(GL_ARRAY_BUFFER,v,buf_size);
    agl::Buffer c_buf = addBuffer(GL_ARRAY_BUFFER,c,buf_size);
    agl::Buffer n_buf = addBuffer(GL_ARRAY_BUFFER, &normals[0], normals.size() * sizeof(glm::vec3));
    addBuffer(GL_ELEMENT_ARRAY_BUFFER,e,elem_size);

    bind();

    v_buf.setAttribPoiter(0,3);
    c_buf.setAttribPoiter(1,3);
    n_buf.setAttribPoiter(2,3);
    bindBuffers();

    size = elem_size / sizeof(unsigned short);
}

bool agl::Model::loadFromFile(const std::string &dir, bool texture)
{
    Assimp::Importer importer;
    this->textured = texture;

    const aiScene *scene = importer.ReadFile(dir, aiProcess_Triangulate | aiProcess_FlipUVs|aiProcess_CalcTangentSpace       |
                                       aiProcess_JoinIdenticalVertices  | aiProcess_GenSmoothNormals |
                 aiProcess_SortByPType);

    if(scene)
        std::cout<<"ZAŁADOWANO MODEL: "<<dir<<std::endl;
    else
    {   std::cout<<"NIEZALADOWANO: "<<dir<<std::endl; return false; }

    if(scene->mNumMeshes == 0)
    {   std::cout<<"NIE ZAWIRA MESHY: "<<std::endl; return false; }

    std::vector <glm::vec3> vertices, colors, normals;
    std::vector <glm::vec2> uvs;
    std::vector <unsigned short> elems;

    aiMesh *mesh = scene->mMeshes[0];

    for(unsigned int i=0; i<mesh->mNumVertices; ++i)
    {
        aiVector3D vertex = mesh->mVertices[i];
        aiVector3D normal = mesh->mNormals[i];
        aiVector3D uv = mesh->mTextureCoords[0][i];

        vertices.push_back(glm::vec3(vertex.x, vertex.y, vertex.z));
        colors.push_back(glm::vec3((vertex.x+1.0f)/2.0f, (vertex.y+1.0f)/2.0f, (vertex.z+1.0f)/2.0f));
        normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
        uvs.push_back(glm::vec2(uv.x, uv.y));
    }

    for(unsigned int i=0; i<mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        elems.push_back(face.mIndices[0]);
        elems.push_back(face.mIndices[1]);
        elems.push_back(face.mIndices[2]);
    }

    create();

    agl::Buffer v_buf = addBuffer(GL_ARRAY_BUFFER, &vertices[0], vertices.size()*sizeof(glm::vec3));

    agl::Buffer c_buf = texture?addBuffer(GL_ARRAY_BUFFER, &uvs[0], uvs.size()*sizeof(glm::vec2))
                                :addBuffer(GL_ARRAY_BUFFER, &colors[0], colors.size()*sizeof(glm::vec3));

    agl::Buffer n_buf = addBuffer(GL_ARRAY_BUFFER, &normals[0], normals.size()*sizeof(glm::vec3));
    addBuffer(GL_ELEMENT_ARRAY_BUFFER, &elems[0], elems.size() * sizeof(unsigned short));

    bind();

    v_buf.setAttribPoiter(0,3);
    c_buf.setAttribPoiter(1,texture?2:3);
    n_buf.setAttribPoiter(2,3);

    bindBuffers();

    size = elems.size();

    return true;
}

void agl::Model::load_cube()
{
    loadFromMemory(cube_v, cube_c, sizeof(cube_v), cube_e, sizeof(cube_e));
}

void agl::Model::load_tetra()
{
    loadFromMemory(triangle_v, triangle_c, sizeof(cube_v), triangle_e, sizeof(triangle_e));
}

void agl::Model::create()
{
    if(!created)
        glGenVertexArrays(1, &VAO);
}

void agl::Model::release()
{
    glDeleteVertexArrays(1,&VAO);
    for(auto & b: buffers)
        b.release();
}

void agl::Model::addBuffer(agl::Buffer b)
{
    buffers.push_back(b);
}

agl::Buffer agl::Model::addBuffer(GLuint type, const void *data, GLuint size)
{
    agl::Buffer temp;
    temp.create(type);
    temp.loadData(data,size);

    buffers.push_back(temp);
    return temp;
}

void agl::Model::bindBuffers()
{
    glBindVertexArray(VAO);
    for(auto & b:buffers)
        b.bind();

    glBindVertexArray(0);
    for(auto & b:buffers)
        b.unbind();
}

void agl::Model::bind()
{
    glBindVertexArray(VAO);
}
