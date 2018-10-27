//
// Created by popof on 25.10.2018.
//

#include "MeshManager.h"

namespace black {
    std::shared_ptr<Mesh> MeshManager::createSquare(float sideSize) {
        const auto halfSide = sideSize / 2;

        return Engine::GetCurrentRenderSystem()->createMesh({
            halfSide, halfSide, 0.0f,
            -halfSide, halfSide, 0.0f,
            halfSide, -halfSide, 0.0f,
            -halfSide, halfSide, 0.0f,
            -halfSide, -halfSide, 0.0f,
            halfSide, -halfSide, 0.0f,});
    }

    std::shared_ptr<Mesh> MeshManager::createEquilateralTriangle(float sideSize) {
        const auto halfSide = sideSize / 2;

        return Engine::GetCurrentRenderSystem()->createMesh({
            0.0f, halfSide, 0.0f,
            -halfSide, -halfSide, 0.0f,
            halfSide, -halfSide, 0.0f, });
    }

    std::shared_ptr<Mesh> MeshManager::createRectangle(float a, float b) {
        const auto halfA = a / 2;
        const auto halfB = b / 2;

        return Engine::GetCurrentRenderSystem()->createMesh({
            halfA, halfB, 0.0f,
            -halfA, halfB, 0.0f,
            halfA, -halfB, 0.0f,
            -halfA, halfB, 0.0f,
            -halfA, -halfB, 0.0f,
            halfA, -halfB, 0.0f,
        });
    }

    std::shared_ptr<Mesh> MeshManager::createFromFile(std::string fileName) {
        return Engine::GetCurrentRenderSystem()->createMesh({});
    }

    std::shared_ptr<Mesh> MeshManager::createCube() {
        return Engine::GetCurrentRenderSystem()->createMesh({
            1.000000f, -1.000000f, -2.000000f,
            1.000000f, -1.000000f, 0.000000f,
            -1.000000f, -1.000000f, 0.000000f,

            -1.000000f, -1.000000f, -2.000000f,
            1.000000f, 1.000000f, -2.000000f,
            0.999999f, 1.000000f, 0.000001f,
            -1.000000f, 1.000000f, 0.000000f,
            -1.000000f, 1.000000f, -2.000000f,
        });
    }
}