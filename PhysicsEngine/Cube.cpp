#include "Cube.h"



YoungEngine::Geometry::Cube::Cube(const glm::mat4& m, float x, float y, float z)
    :Shape(m)
{
    std::vector<Vertex>& vertices = getVerticesData();
    Vec3D v(x/2, y/2, z/2);

    float unit = 0.125;
    vertices.push_back({ v.componentProduct({ -1,-1,-1}),{0,0,-1},unit * 3,unit * 8 });//0
    vertices.push_back({ v.componentProduct({1,1,-1}),{0,0,-1},unit * 5,unit * 6 });//2
    vertices.push_back({ v.componentProduct({1,-1,-1}),{0,0,-1},unit * 5,unit * 8 });//1

    vertices.push_back({ v.componentProduct({ -1,-1,-1}),{0,0,-1},unit * 3,unit * 8 });//0
    vertices.push_back({ v.componentProduct({-1,1,-1}),{0,0,-1},unit * 3,unit * 6 });//3
    vertices.push_back({ v.componentProduct({1,1,-1}),{0,0,-1},unit * 5,unit * 6 });//2

    vertices.push_back({ v.componentProduct({-1,1,-1}),{0,1,0},unit * 3,unit * 6 });//3
    vertices.push_back({ v.componentProduct({1,1,1}),{0,1,0},unit * 5,unit * 4 });//6
    vertices.push_back({ v.componentProduct({1,1,-1}),{0,1,0},unit * 5,unit * 6 });//2

    vertices.push_back({ v.componentProduct({-1,1,-1}),{0,1,0},unit * 3,unit * 6 });//3
    vertices.push_back({ v.componentProduct({-1,1,1}),{0,1,0},unit * 3,unit * 4 });//7
    vertices.push_back({ v.componentProduct({1,1,1}),{0,1,0},unit * 5,unit * 4 });//6

    vertices.push_back({ v.componentProduct({-1,1,1}),{0,0,1},unit * 3,unit * 5 });//7
    vertices.push_back({ v.componentProduct({1,-1,1}),{0,0,1},unit * 5,unit * 2 });//5
    vertices.push_back({ v.componentProduct({1,1,1}),{0,0,1},unit * 5,unit * 4 });//6

    vertices.push_back({ v.componentProduct({-1,1,1}),{0,0,1},unit * 3,unit * 4 });//7
    vertices.push_back({ v.componentProduct({-1,-1,1}),{0,0,1},unit * 3,unit * 2 });//4
    vertices.push_back({ v.componentProduct({1,-1,1}),{0,0,1},unit * 5,unit * 2 });//5

    vertices.push_back({ v.componentProduct({-1,-1,1}),{0,-1,0},unit * 3,unit * 2 });//4
    vertices.push_back({ v.componentProduct({1,-1,-1}),{0,-1,0},unit * 5,unit * 0 });//1'
    vertices.push_back({ v.componentProduct({1,-1,1}),{0,-1,0},unit * 5,unit * 2 });//5

    vertices.push_back({ v.componentProduct({-1,-1,1}),{0,-1,0},unit * 3,unit * 2 });//4
    vertices.push_back({ v.componentProduct({ -1,-1,-1}),{0,-1,0},unit * 3,unit * 0 });//0'
    vertices.push_back({ v.componentProduct({1,-1,-1}),{0,-1,0},unit * 5,unit * 0 });//1'

    vertices.push_back({ v.componentProduct({ -1,-1,-1}),{-1,0,0},unit * 1,unit * 6 });//0''
    vertices.push_back({ v.componentProduct({-1,1,1}),{-1,0,0},unit * 3,unit * 4 });//7
    vertices.push_back({ v.componentProduct({-1,1,-1}),{-1,0,0},unit * 3,unit * 6 });//3

    vertices.push_back({ v.componentProduct({ -1,-1,-1}),{-1,0,0},unit * 1,unit * 6 });//0''
    vertices.push_back({ v.componentProduct({-1,-1,1}),{-1,0,0},unit * 1,unit * 4 });//4'
    vertices.push_back({ v.componentProduct({-1,1,1}),{-1,0,0},unit * 3,unit * 4 });//7

    vertices.push_back({ v.componentProduct({1,1,-1}),{1,0,0},unit * 5,unit * 6 });//2
    vertices.push_back({ v.componentProduct({1,-1,1}),{1,0,0},unit * 7,unit * 4 });//5'
    vertices.push_back({ v.componentProduct({1,-1,-1}),{1,0,0},unit * 7,unit * 6 });//1''

    vertices.push_back({ v.componentProduct({1,1,-1}),{1,0,0},unit * 5,unit * 6 });//2
    vertices.push_back({ v.componentProduct({1,1,1}),{1,0,0},unit * 5,unit * 4 });//6
    vertices.push_back({ v.componentProduct({1,-1,1}),{1,0,0},unit * 7,unit * 4 });//5'

    std::vector<unsigned int>& indices = getIndicesData();
    unsigned int indices_arr[36];
    for (int i = 0; i < 36; i++) {
        indices_arr[i] = i;
    }
    indices.insert(indices.begin(), indices_arr, indices_arr + 36);
}
