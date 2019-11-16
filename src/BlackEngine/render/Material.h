//
// Created by popof on 28.10.2018.
//

#ifndef BLACKENGINE_MATERIAL_H
#define BLACKENGINE_MATERIAL_H

#include "../common/CommonHeaders.h"
#include "../common/Color.h"

#include <memory>

namespace black {
class Texture;
class ShaderProgram;

/**
 * Some shader information about concrete material.
 */
struct BLACK_EXPORTED Material {
  Material(const Material &material);
  Material();

  Material(std::shared_ptr<Texture> texture, const Color &color, float spectacularFactor);

  std::shared_ptr<Texture> texture;
  Color color = Color::BLACK;
  float spectacularFactor = 1.0f;
};

}

#endif //BLACKENGINE_MATERIAL_H
