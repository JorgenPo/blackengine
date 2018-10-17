#include <utility>

//
// Created by popof on 17.10.2018.
//

#include "Meshes.h"
#include <Engine.h>

namespace black {

    std::shared_ptr<Mesh> Meshes::create(std::vector<float> vertices) {
        return Engine::GetCurrentRenderSystem()->createMesh(std::move(vertices));
    }
}