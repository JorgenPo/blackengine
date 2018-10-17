//
// Created by popof on 17.10.2018.
//

#ifndef BLACKENGINE_MESHES_H
#define BLACKENGINE_MESHES_H

#include <CommonHeaders.h>
#include <Mesh.h>

namespace black {
    /**
     * Helper class to create and manipulate meshes
     */
    class BLACK_EXPORTED Meshes {

    public:
        static std::shared_ptr<Mesh> create(std::vector<float> vertices);
    };
}


#endif //BLACKENGINE_MESHES_H
