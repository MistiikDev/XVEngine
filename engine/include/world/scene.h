#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <graphics/objects/mesh.h>

struct Scene {
    std::vector<Mesh*> meshes;
};

#endif