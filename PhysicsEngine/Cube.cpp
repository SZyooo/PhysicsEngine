#include "Cube.h"



YoungEngine::Cube::Cube(const glm::mat4& m, float xspan, float yspan, float zspan)
    :Shape(m)
{
    std::vector<Vertex>& vertices = getVerticesData();
    vertices.push_back({ -xspan / 2,-yspan / 2,-zspan / 2 });
    vertices.push_back({ xspan / 2,-yspan / 2,-zspan / 2 });
    vertices.push_back({ xspan / 2,yspan / 2,-zspan / 2 });
    vertices.push_back({ -xspan / 2,yspan / 2,-zspan / 2 });
    vertices.push_back({-xspan / 2, -yspan / 2, zspan / 2 });
    vertices.push_back({ xspan / 2, -yspan / 2, zspan / 2 });
    vertices.push_back({ xspan / 2, yspan / 2, zspan / 2 });
    vertices.push_back({ -xspan / 2, yspan / 2, zspan / 2 });
    std::vector<unsigned int>& indices = getIndicesData();
    unsigned int indices_arr[] = {0,1,2,0,2,3,4,0,3,4,3,7,5,4,7,5,7,6,1,5,6,1,6,2,7,6,2,7,2,3,4,5,1,4,1,0};
    indices.insert(indices.begin(), indices_arr, indices_arr + 36);
}
