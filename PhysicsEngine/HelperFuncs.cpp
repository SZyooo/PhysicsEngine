#include "HelperFuncs.h"
#include<Tool.h>
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

void YoungEngine::drawBasis(const glm::vec3& pos, const glm::mat4& view, const glm::mat4& project)
{
    static GLuint program = create_program("basis_vs.glsl", "basis_fs.glsl", 0, 0, "basis_gs.glsl");
    glUseProgram(program);
    glUniformMatrix4fv(glGetUniformLocation(program, "view"),1,GL_FALSE,glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_FALSE, glm::value_ptr(project));
    glUniform3fv(glGetUniformLocation(program, "position"),1,glm::value_ptr(pos));
    glLineWidth(3);
    glDisable(GL_DEPTH_TEST);
    glDrawArrays(GL_POINTS, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(1);
}

