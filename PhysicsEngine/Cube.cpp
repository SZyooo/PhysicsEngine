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
    unsigned int indices_arr[] = {0,2,1,0,3,2,4,3,0,4,7,3,5,7,4,5,6,7,1,6,5,1,2,6,7,6,2,7,2,3,4,1,5,4,0,1};
    indices.insert(indices.begin(), indices_arr, indices_arr + 36);
}
