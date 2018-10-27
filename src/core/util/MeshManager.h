//
// Created by popof on 25.10.2018.
//

#ifndef BLACKENGINE_MESHMANAGER_H
#define BLACKENGINE_MESHMANAGER_H

#include <CommonHeaders.h>
#include <Engine.h>
#include <Mesh.h>

namespace black {

    /**
     * Mesh helper class. Util functions.
     */
    class BLACK_EXPORTED MeshManager {
    public:
        static std::shared_ptr<Mesh> createSquare(float sideSize);

        static std::shared_ptr<Mesh> createEquilateralTriangle(float sideSize);

        static std::shared_ptr<Mesh> createRectangle(float a, float b);

        static std::shared_ptr<Mesh> createFromFile(std::string fileName);

        static std::shared_ptr<Mesh> createCube();
    };

}
#endif //BLACKENGINE_MESHMANAGER_H
