#ifndef MESH_H
#define MESH_H

#include <vector>
#include <graphics/objects/vertex.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Mesh {
    unsigned int ID;

    std::vector<Vertex> verticies;
    std::vector<uint32_t> indicies;

    glm::mat4 transform;
};

#endif