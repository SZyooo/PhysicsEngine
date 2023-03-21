#include "HelperFuncs.h"
#include<GL/glew.h>
#include"Vertex.h"
unsigned int YoungEngine::moveVertexToBuffer(const std::vector<YoungEngine::Vertex>& vertices)
{
    GLuint buffer;
    glCreateBuffers(1, &buffer);
    glNamedBufferStorage(buffer, vertices.size() * YoungEngine::Vertex::StructSize, &vertices[0], GL_MAP_WRITE_BIT);
    return buffer;
}

unsigned int YoungEngine::generateVAOForCubeShader(unsigned int bufferid)
{
    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glVertexArrayAttribFormat(vao, 0, 4, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayVertexBuffer(vao, 0, bufferid, 0, YoungEngine::Vertex::StructSize);
    glEnableVertexArrayAttrib(vao, 0);
    return vao;
}

glm::vec3 YoungEngine::convertVector3ToGLMVec3(const Vector3& v)
{
    return glm::vec3(v.x,v.y,v.z);
}

