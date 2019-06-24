//
// Created by popof on 28.10.2018.
//

#include "Material.h"
#include "Texture.h"

#include <memory>

namespace black {

Material::Material(std::shared_ptr<Texture> texture) : texture(std::move(texture)) {}
Material::Material() = default;

}