//
// Created by popof on 28.10.2018.
//

#include "Material.h"

namespace black {

    Material::Material(const std::shared_ptr<Texture> &texture) : texture(texture) {}
    Material::Material() {}
}