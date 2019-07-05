//
// Created by popof on 28.10.2018.
//

#include "Material.h"
#include "Texture.h"

#include <memory>

namespace black {

Material::Material(std::shared_ptr<Texture> texture)
  : texture(std::move(texture)), color(0.0f, 0.0f, 0.0f, 1.0f) {}

Material::Material() : color(0.3f, 0.3f, 0.3f, 1.0f) {

}

Material::Material(Color color) : color(color) {

};

}