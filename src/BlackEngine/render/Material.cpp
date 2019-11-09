//
// Created by popof on 28.10.2018.
//

#include "Material.h"
#include "Texture.h"

#include <memory>

namespace black {


Material::Material(const Material &material) = default;

Material::Material() = default;

Material::Material(std::shared_ptr<Texture> texture, const Color &color, float spectacularFactor) : texture(std::move(
  texture)), color(color), spectacularFactor(spectacularFactor) {}
}