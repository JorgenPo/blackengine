//
// Created by popof on 28.10.2018.
//

#ifndef BLACKENGINE_MATERIAL_H
#define BLACKENGINE_MATERIAL_H

#include <CommonHeaders.h>
#include <render/Texture.h>

namespace black {
    /**
     * Some shader information about concrete material.
     */
    struct BLACK_EXPORTED Material {
        std::shared_ptr<Texture> texture;

        Material(const std::shared_ptr<Texture> &texture);

        Material();
    };

}

#endif //BLACKENGINE_MATERIAL_H
